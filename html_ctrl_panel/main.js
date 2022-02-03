var espURL;

function startApp(_espURL)
{
    espURL = _espURL;
    var content = $(
        `<div class="pageContainer">
            <div class="page pageMain" style="display: none;">
                <div class="container-fluid header">
                    <h1>Painel de controle</h1>
                </div>
                <div class="px-2 pb-1">
                    <div class="container-md card my-2">
                        <h2>Programações automáticas:</h2>
                        <p>
                            Status:
                            <input id="pg_main" class="chb" type="checkbox">
                            <label for="pg_main">
                                <span class="chb"><span>&#8203;</span></span>
                                <span id="pg_main_input_text">Oi</span>
                            </label>
                        </p>

                        <div id="programations" class="container-fluid lineBetweenRows spacingBetweenRows"></div>
                        <input type="button" id="trigProgBtn" onclick="triggerProgramationBtn()" class="mt-2" value="Disparar programação">
                    </div>
                    <div class="container-md card my-2">
                        <h2>Ativar setor manualmente:</h2>
                        <p class="text-light-gray">É necessário pausar as programações automáticas</p>

                        <div id="manualSection" class="container-fluid lineBetweenRows spacingBetweenRows "></div>
                        <input type="button" id="setManualDefault" onclick="setManualDefaultBtn()" class="mt-2" value="Definir setor padrão">
                    </div>
                </div>
            </div>

            <!-- programations page -->

            <div class="page pageProgramation" style="display: none;">
                <div class="container-fluid header">
                    <span class="returnToMain returnArrow">&#9666;</span><h1>Programação <span id="progNum">x</span></h1>
                    <!--◀-->
                </div>
                <div class="px-2 pb-1">
                    <div class="container-md card my-2">
                        <h2>Ativação automática:</h2>
                        <p>
                            Status:
                            <input id="paax_prog" class="chb" type="checkbox">
                            <label for="paax_prog">
                                <span class="chb"><span>&#8203;</span></span>
                            </label>
                        </p>
                    </div>
                    <div class="container-md card my-2">
                        <h2>Ordem e tempo de ativação:</h2>
                        <div id="orderDuratContainer" class="container-fluid">
                            <div class="row">
                            </div>
                        </div>
                    </div>
                    <div class="container-md card my-2">
                        <h2>Horários de ativação:</h2>
                        <div id="timesContainer" class="container-fluid">
                            <div class="row">
                            </div>
                        </div>
                    </div>
                    <div class="container-md containerButtons">
                        <input type="button" value="Cancelar" onclick="loadMainPage()">
                        <input type="button" id="save_prog" value="Salvar" onclick="saveProgramationAlt()">
                    </div>
                </div>
            </div>
        </div>`
    );
    
    content.ready(contentReady);
    
    $("body").append(content);
}

function contentReady()
{
    $("#pg_main").change(handle_pg_main_change);
    $(".returnToMain").click(loadMainPage);

    loadMainPage();
}

function getData(functionToRunAfterFinishing)
{
    getInfo(()=>{
        getProgramations(()=>{
            if(typeof functionToRunAfterFinishing == "function") functionToRunAfterFinishing();
        });
    });
}

var info = {
    numOfStages: null,
    numOfTriggers: null,
    numOfProgramations: null,
    numOfSections: null,
    programationEmpty: null,
    sectionEmpty: null,
    maxDuration: null,
    areProgramationsPaused: null,
    manuallyActivatedSector: null,
    automaticProgramationRunning: null,
    defaultManualSection: null,
}
function getInfo(functionToRunAfterFinishing)
{
    runCommand({
        cmd: "mostrarInformacoes",
        success: (data)=>{
            var gotError = false;

            splitInLinesRemoveSpaces(data).forEach(line=>{
                if(gotError) return;
                
                var doubp = line.indexOf(":");
                var val = parseInt(line.substr(doubp+1));
                switch(line.substr(0, doubp))
                {
                    case "numOfStages":
                        info.numOfStages = val;
                        break;
                    case "numOfTriggers":
                        info.numOfTriggers = val;
                        break;
                    case "numOfProgramations":
                        info.numOfProgramations = val;
                        break;
                    case "numOfSections":
                        info.numOfSections = val;
                        break;
                    case "programationEmpty":
                        info.programationEmpty = val;
                        break;
                    case "sectionEmpty":
                        info.sectionEmpty = val;
                        break;
                    case "maxDuration":
                        info.maxDuration = val;
                        break;
                    case "areProgramationsPaused":
                        info.areProgramationsPaused = Boolean(val);
                        break;
                    case "manuallyActivatedSector":
                        info.manuallyActivatedSector = val;
                        break;
                    case "automaticProgramationRunning":
                        info.automaticProgramationRunning = val;
                        break;
                    case "defaultManualSection":
                        info.defaultManualSection = val;
                        break;
                    default:
                        gotError = true;
                        return;
                }
            });

            Object.getOwnPropertyNames(info).forEach(propName=>{
                if(info[propName] === null && !gotError) gotError = true;
            });

            if(gotError)
            {
                error(1);
                return;
            }
            else if(typeof functionToRunAfterFinishing == "function") functionToRunAfterFinishing();
        }
    });
}

var programations = [];
function getProgramations(functionToRunAfterFinishing)
{
    runCommand({
        cmd: "mostrarProgramacoes",
        success: (data)=>{
            var lines = splitInLinesRemoveSpaces(data);

            var gotError = false;

            lines.forEach((line, i) => {
                if(gotError) return;

                arrow = line.indexOf("→");
                dash = line.indexOf("-");

                var prog = {
                    enabled: null,
                    orders:[],
                    durations:[],
                    triggers: []
                }

                if(arrow == -1 || dash == -1)
                {
                    error(2);
                    gotError = true;
                    return;
                }

                if(i != parseInt(line.substr(0, arrow)))
                {
                    error(2);
                    gotError = true;
                    return;
                }



                var ordersDurations = line.substr(arrow+1, dash-arrow-1);
                switch(ordersDurations.substr(0, 1))
                {
                    case "L":
                    case "l":
                        prog.enabled = true;
                        break;
                    case "D":
                    case "d":
                        prog.enabled = false;
                        break;
                    default:
                        error(2);
                        gotError = true;
                        return;
                }

                if(ordersDurations.substr(-1) != "}") {error(2); gotError=true;return;}
                ordersDurations = ordersDurations.substr(1, ordersDurations.length-2).replaceAll("{", "");

                ordersDurations.split("}").forEach((orderDuration, i)=>{
                    var virg = orderDuration.indexOf(",");
                    prog.orders[i] = parseInt(orderDuration.substr(0, virg));
                    prog.durations[i] = parseInt(orderDuration.substr(virg+1));
                });

                var triggers = line.substr(dash+1).replaceAll("{", "");
                if(triggers.substr(-1) != "}") {error(2); gotError=true;return;}
                triggers = triggers.substr(0, triggers.length-1);

                triggers.split("}").forEach((trigger, i)=>{
                    prog.triggers[i] = trigger.substr();
                });

                for(j = prog.triggers.length; j < info.numOfTriggers; j++) prog.triggers[j] = "";

                programations[i] = prog;
            });

            if(!gotError && typeof functionToRunAfterFinishing == "function") functionToRunAfterFinishing();
        }
    });
}

function splitInLinesRemoveSpaces(str)
{
    return str.replaceAll(" ", "").split("\n");
}

function error(str, str2)
{
    if(typeof str == "number")
    {
        switch(str)
        {
            case 1:
                str = `Falha ao tentar decodificar "mostrarInformacoes"`;
                break;
            case 2:
                str = `Falha ao tentar decodificar "mostrarProgramacoes"`;
                break;
            case 3:
                str = `Falha ao conectar com ESP`;
                break;
            case 4:
                str = `Comando executado retornou erro\n`;
                break;
        }
    }

    if(typeof str2 != "undefined") str = `${str}${str2}`

    popup({
        title: "Erro",
        msg: str
    });
    console.log(str);
}



// function runCommand(obj)
function runCommand(obj, delay, giveError)
{
    console.log(`running "${obj.cmd}"`);

    if(typeof giveError == "undefined") giveError = false;
    if(typeof delay == "undefined") delay = 0;

    if(typeof obj.before == "function") obj.before();

    var args = "";
    var cmd = "";
    var spcIdx = obj.cmd.indexOf(" ");
    if(spcIdx == -1) cmd = obj.cmd;
    else
    {
        args = obj.cmd.substr(spcIdx+1);
        cmd = obj.cmd.substr(0, spcIdx);
    }

    setTimeout(()=>{
        $.ajax({
            // url: `${espURL}/${cmd}.txt`,
            url: `${espURL}/${cmd}.txt`+(giveError?"-":""),
            success: (data)=>{
                data = data.replaceAll("\r\n", "\n");
                var fsn = data.indexOf("\n");
                if(fsn == -1) fsn = data.length;
                var firstLine = data.substr(0, fsn);
                if(firstLine != "OK")
                {
                    if(!giveError) error(4, `"${obj.cmd}":\n${data}`);
                    if(typeof obj.error == "function") obj.error();
                }
                else if(typeof obj.success == "function") obj.success(data.substr(fsn+1));
            },
            error: ()=>{
                // error(3);
                if(!giveError) error(3);
                if(typeof obj.error == "function") obj.error();
            },
            complete: ()=>{
                if(typeof obj.complete == "function") obj.complete();
            }
        });
    }, delay);
}




function loadPage(pageClass)
{
    $(`.page:not(.${pageClass})`).hide();
    $(`.page.${pageClass}`).show();
}

function loadMainPage()
{
    getData(()=>{
        $("#programations").html("");
        programations.forEach((programation, i)=>{
            $("#programations").append(`
                <div class="row" id="p${i}_main" onclick="loadProgramationPage(${i})">
                    <div class="col-1">${i}</div>
                    <div class="col pstt ${info.areProgramationsPaused?"text-light-gray":(programation.enabled?"text-success":"text-danger")}">${programation.enabled?"Ligado":"Desligado"}</div>
                    <div class="col-auto">setores: </div>
                    <div class="col">${orderStr(programation.orders)}</div>
                </div>
            `);
        });

        inputStates["pg_main"] = {
            state: !info.areProgramationsPaused,
            transition: false,
        }
        updtInput("pg_main");

        $("#manualSection").html("")
        for(i = 0; i < info.numOfSections; i++)
        {
            $("#manualSection").append(`
                <div class="row">
                    <div class="col-auto">${i}</div>
                    <div id="sma${i}_main_default" class="col smax_main_default">${info.defaultManualSection==i?"Padrão":""}</div>
                    <div id="sma${i}_main_input_text" class="col-auto"></div>
                    <div class="col-auto">
                        <input id="sma${i}_main" class="chb smax_main" type="checkbox" onchange="handle_smax_main_change(${i})">
                        <label for="sma${i}_main">
                            <span class="chb"><span>&#8203;</span></span>
                        </label>
                    </div>
                </div>
            `);

            inputStates[`sma${i}_main`] = {
                state: info.manuallyActivatedSector==i,
                transition: false,
            };

            updtInput(`sma${i}_main`);
        }

        $("#trigProgBtn").val(info.automaticProgramationRunning == info.programationEmpty?"Disparar programação":"Em andamento: "+info.automaticProgramationRunning);

        loadPage("pageMain");
    });
}

function orderStr(orders)
{
    var str = "";
    orders.forEach((order, i)=>{
        if(order != info.sectionEmpty)
        {
            if(i != 0) str += " ";
            str += order;
        }
    });
    return str;
}

var progNum;
function loadProgramationPage(_progNum)
{
    progNum = _progNum;
    getData(()=>{
        var prog = programations[progNum];
        $("#progNum").text(progNum);
        $("#paax_prog")[0].checked = prog.enabled;
        
        $("#orderDuratContainer > *").html("");
        for(i = 0; i < info.numOfStages; i++)
        {
            $("#orderDuratContainer > *").append(
                `<div class="col-auto my-1 orderDurat${i}">
                    ${i+1}º:
                    <input type="number" class="order" value="${prog.orders[i]==info.sectionEmpty?"":prog.orders[i]}" placeholder="Vazio">
                    <input type="number" class="duration" value="${prog.durations[i]}" placeholder="0">
                </div>`
            );
        }
                
        $("#timesContainer > *").html("");
        for(i = 0; i < info.numOfTriggers; i++)
        {
            $("#timesContainer > *").append(
                `<div class="time${i} col-auto my-1">
                    <span class="p-2" onclick="clearTime(${i})">✕</span><input type="time" value="${formatTime(prog.triggers[i])}">
                </div>`
            );
        }
        loadPage("pageProgramation");
    });
}

function clearTime(timeNum)
{
    console.log(timeNum)
    $(`#timesContainer > * .time${timeNum} input`).val("");
}

function formatTime(str)
{
    [h, m] = str.split(":");
    h = parseInt(h);
    m = parseInt(m);
    if(isNaN(h) || isNaN(m)) return "";
    return `${(h<10?"0":"")}${h}:${(m<10?"0":"")}${m}`;
}

var inputStates = {};

function setInputState(input, state)
{
    inputStates[input].state = state;
    updtInput(input);
}
function setInputTransition(input, trst)
{
    inputStates[input].transition = trst;
    updtInput(input);
}
function getInputState(input)
{
    return inputStates[input].state;
}
function getInputTransition(input)
{
    return inputStates[input].transition;
}
function updtInput(input)
{
    $("#"+input)[0].checked = inputStates[input].state;

    var txt = $(`#${input}_input_text`);

    if(inputStates[input].state) txt.addClass("text-success").removeClass("text-danger");
    else txt.addClass("text-danger").removeClass("text-success");

    if(inputStates[input].transition)
    {
        txt.css("opacity", "0.5");
        if(inputStates[input].state) txt.text("Ligando...");
        else txt.text("Desligando...");
    }
    else
    {
        txt.css("opacity", "1");
        if(inputStates[input].state) txt.text("Ligado");
        else txt.text(input == "pg_main"?"Desligado":"");
    }
}

function updateProgramationsStt()
{
    var stts = $("#programations > * .pstt");
    if(getInputState("pg_main"))
    {   
        stts.removeClass("text-light-gray");
        stts.each(function(i){
            $(this).addClass(programations[i].enabled?"text-success":"text-danger");
        });
    }
    else stts.removeClass("text-success").removeClass("text-danger").addClass("text-light-gray")
}

function handle_pg_main_change(e)
{
    if(getInputTransition("pg_main"))
    {
        $("#pg_main")[0].checked = !$("#pg_main")[0].checked;
        return;
    };

    var initialSmaxStates = [];
    runCommand({
        cmd: $("#pg_main")[0].checked?"retomarProgramacoes":"pausarProgramacoes",
        before: ()=>{
            for(i = 0; i < info.numOfSections; i++)
            {
                initialSmaxStates.push(getInputState(`sma${i}_main`));
                setInputState(`sma${i}_main`, false)
            }
            setInputState("pg_main", $("#pg_main")[0].checked);
            setInputTransition("pg_main", true);
            updateProgramationsStt();
        },
        success: data=>{
            info.areProgramationsPaused = $("#pg_main")[0].checked;
        },
        error: data=>{
            setInputState("pg_main", !getInputState("pg_main"));
            updateProgramationsStt();
            
            for(i = 0; i < info.numOfSections; i++)
            {
                setInputTransition(`sma${i}_main`, false);
                setInputState(`sma${i}_main`, initialSmaxStates[i])
            }
        },
        complete: data=>{
            setInputTransition("pg_main", false);
        }
    });
}

function handle_smax_main_change(sectionNum)
{
    //@#@ retornar se trigger programation tiver esperando
    var ipt = `sma${sectionNum}_main`;
    if(getInputTransition(ipt) || triggerProgramationTranst)
    {
        $("#"+ipt)[0].checked = !$("#"+ipt)[0].checked;
        return;
    };
    var initialSmaxStates = [];
    var initial_pg_main_state;
    runCommand({
        cmd: $("#"+ipt)[0].checked?"ligarSetor "+sectionNum:"desligarSetores",
        before: ()=>{
            
            for(i = 0; i < info.numOfSections; i++) initialSmaxStates.push(getInputState(`sma${i}_main`));

            setInputState(ipt, $("#"+ipt)[0].checked);

            for(i = 0; i < info.numOfSections; i++)
            {
                var needToClear = !getInputState(`sma${i}_main`) && i != sectionNum;
                
                if(sectionNum != i)
                {
                    setInputState(`sma${i}_main`, false);
                }
                setInputTransition(`sma${i}_main`, true);

                if(needToClear) $(`#sma${i}_main_input_text`).text("");
            }

            initial_pg_main_state = getInputState("pg_main");
            setInputState("pg_main", false);
            updateProgramationsStt();
        },
        success: ()=>{
            for(i = 0; i < info.numOfSections; i++) setInputTransition(`sma${i}_main`, false);
            info.manuallyActivatedSector = $("#"+ipt)[0].checked?sectionNum:info.sectionEmpty;
            
            $("#trigProgBtn").val("Disparar programação").css("opacity", "1");
            info.automaticProgramationRunning = info.programationEmpty;
            
        },
        error: ()=>{
            for(i = 0; i < info.numOfSections; i++)
            {
                setInputTransition(`sma${i}_main`, false);
                setInputState(`sma${i}_main`, initialSmaxStates[i])
            }
            
            setInputState("pg_main", initial_pg_main_state);
            updateProgramationsStt();
        }
    });
}

function saveProgramationAlt()
{
    var prog = programations[progNum];
    console.log("salvar")
    
    prog.enabled = $("#paax_prog")[0].checked;

    $("#orderDuratContainer > * > *").each(function(i){
        var v = parseInt($(this).find(".order").val());
        if(isNaN(v)) v = info.sectionEmpty;
        prog.orders[i] = v>=info.numOfSections?info.sectionEmpty:v;
        v = parseInt($(this).find(".duration").val());
        if(isNaN(v)) v = 0;
        prog.durations[i] = v>info.maxDuration?info.maxDuration:v;
    });

    $("#timesContainer > * > * input").each(function(i){
        prog.triggers[i] = $(this).val();
    });
    prog.triggers.sort();
    prog.triggers = prog.triggers.filter(value=>{return value!=""});
    for(j = prog.triggers.length; j < info.numOfTriggers; j++) prog.triggers[j] = "";

    var cmd = `alterarProgramacao ${progNum} → `;
    prog.orders.forEach((order, i)=>{
        cmd += `{${order},${prog.durations[i]}}`;
    });
    cmd += `-{${prog.triggers.filter(value=>{return value!=""}).join(",")}}`;
    

    runCommand({
        cmd: cmd,
        before: ()=>{
            $("#save_prog").val("Salvando...");
        },
        success: ()=>{
            loadMainPage();
        },
        complete: ()=>{
            $("#save_prog").val("Salvar");
        },
    });
}
function btnTemplate(val)
{
    return $(`<div class="col"><input type="button" value="${typeof val != "undefined"?val:"Fechar"}"></div>`)
}
function popup(obj)
{
    if(typeof obj == "undefined") obj = {};
    if(typeof obj.buttonsPos == "undefined") obj.buttonsPos = "with";
    var popup;

    var buttonsCont1 = $(`<div class="row buttonsCont1"></div>`);
    var buttonsCont2 = $(`<div class="row buttonsCont2"></div>`)
    var buttonsAdd = [];
    var closeBtn = btnTemplate(obj.close);
    closeBtn.click(()=>{closePopup(popup, obj.onClose)});
    buttonsCont1.append(closeBtn);
    
    if(typeof obj.buttons == "object")
    {
        Object.getOwnPropertyNames(obj.buttons).forEach(btnName=>{
            var btn = btnTemplate(btnName);
            btn.click(()=>{
                obj.buttons[btnName]();
                closePopup(popup);
            });
            buttonsAdd.push(btn);
        });

        if(obj.buttonsPos == "with")
        {
            for(i = 0; i < buttonsAdd.length; i++)
            {
                buttonsCont1.append(buttonsAdd[i]);
            }
        }
        else if(obj.buttonsPos == "before")
        {
            for(i = 0; i < buttonsAdd.length; i++)
            {
                buttonsCont2.append(buttonsAdd[i]);
            }
        }
    }

    popup = $(
        `<div class="popup">
            <div class="popupVoid"></div>
            <div class="popupBody">
                ${typeof obj.title != "undefined"?`<h3>${obj.title.replace(/\n/g, "<br />")}</h3>`:""}
                ${typeof obj.msg != "undefined"?`<p>${obj.msg.replace(/\n/g, "<br />")}</p>`:""}
                <div class="popupBeforeBotoes container-fluid"></div>
                <div class="popupBotoes container-fluid"></div>
            </div>
        </div>`
    );

    popup.find(".popupVoid").click(()=>{closePopup(popup, obj.onClose)});
    popup.find(".popupBotoes").append(buttonsCont1);
    popup.find(".popupBeforeBotoes").append(buttonsCont2);
    
    scroll.lock();
    $("body").append(popup);
}

function closePopup(popup, onClose, runOnClose)
{
    popup.remove();
    scroll.unlock();
    if(typeof onClose != "undefined") onClose();
}

// function testPopup()
// {
//     popup({
//         title: "Mensagem",
//         msg: "Oi, tudo bem?",
//         close: "fechar",
//         onClose: ()=>{
//             alert("fechou")
//         },
//         buttons: {
//             "ç` $ ªáÀ": ()=>{
//                 alert("hmm");
//             }
//         }
//     });
// }

scroll = {
    lock: ()=>{
        $('body').css({'overflow':'hidden'});
        $(document).bind('scroll',function () { 
            window.scrollTo(0,0); 
        });
    },
    unlock: ()=>{
        $(document).unbind('scroll'); 
        $('body').css({'overflow':'visible'});
    }
}

function triggerProgramationBtn()
{
    //@#@ retornar se manual estiver esperando
    if(triggerProgramationTranst || getInputTransition("sma0_main")) return;

    if(info.automaticProgramationRunning != info.programationEmpty)
    {
        popup({
            title: "Atenção!",
            msg: `Deseja interromper programação ${info.automaticProgramationRunning}?`,
            close: "Cancelar",
            buttons: {
                "Sim": ()=>{
                    stopProgramation();
                }
            }
        });
        return;
    }

    var btns = {};
    for (i = 0; i < info.numOfProgramations; i++) {
        btns[i] = ((b)=>{
            return ()=>{ 
                triggerProgramation(b);
            };
        })(i);
    }

    popup({
        title: "Disparar programação",
        msg: "Selecione o número da programação que deseja dispar.",
        close: "Calcelar",
        buttons: btns,
        buttonsPos: "before"
    })

}

var triggerProgramationTranst = false;
function triggerProgramation(progNum)
{
    if(triggerProgramationTranst) return;
    var dispProgInitialText = $("#trigProgBtn").val();
    
    runCommand({
        cmd: `dispararProgramacao ${progNum}`,
        before: ()=>{
            triggerProgramationTranst = true;
            $("#trigProgBtn").val("Em andamento: "+progNum).css("opacity", "0.5");
        },
        success: ()=>{
            info.automaticProgramationRunning = progNum;
            
            info.manuallyActivatedSector = info.sectionEmpty;
            for(i = 0; i < info.numOfSections; i++) setInputState(`sma${i}_main`, false);
            
        },
        error: ()=>{
            $("#trigProgBtn").val(dispProgInitialText);
        },
        complete: ()=>{
            triggerProgramationTranst = false;
            $("#trigProgBtn").css("opacity", "1");
        },
    });
}

function stopProgramation()
{
    if(triggerProgramationTranst) return;
    var dispProgInitialText = $("#trigProgBtn").val();
    
    runCommand({
        cmd: `pararProgramacao`,
        before: ()=>{
            triggerProgramationTranst = true;
            $("#trigProgBtn").val("Disparar programação").css("opacity", "0.5");
        },
        success: ()=>{
            info.automaticProgramationRunning = info.programationEmpty;
        },
        error: ()=>{
            $("#trigProgBtn").val(dispProgInitialText);
        },
        complete: ()=>{
            triggerProgramationTranst = false;
            $("#trigProgBtn").css("opacity", "1");
        },
    });
}

var setManualDefaultTrast = false;
function setManualDefaultBtn()
{
    if(setManualDefaultTrast) return;

    
    var btns = {};
    for (i = 0; i < info.numOfSections; i++) {
        btns[i] = ((b)=>{
            return ()=>{ 
                setManualDefault(b);
            };
        })(i);
    }
    
    popup({
        title: "Definir setor manual padrão",
        msg: "Selecione o setor que será ativado ao apertar botão físico.",
        close: "cancelar",
        buttons: btns,
        buttonsPos: "before"
    });
}

function setManualDefault(sectionNum)
{
    if(info.defaultManualSection == sectionNum) return;

    runCommand({
        cmd: `alterarSetorManual ${sectionNum}`,
        before: ()=>{
            setManualDefaultTrast = true;
            $("#setManualDefault").val("Definindo...").css("opacity", "0.5");
            updateManualDefaultInUI(sectionNum, true);
        },
        success: ()=>{
            info.defaultManualSection = sectionNum;
        },
        complete: ()=>{
            setManualDefaultTrast = false;
            $("#setManualDefault").val("Definir setor padrão").css("opacity", "1");
            updateManualDefaultInUI(info.defaultManualSection);
        },
    });
}

function updateManualDefaultInUI(sectionNum, temporary)
{
    if(typeof temporary == "undefined") temporary = false;

    $(`#manualSection > * .smax_main_default`).text("");
    if(sectionNum != info.sectionEmpty) 
    {   
        $(`#manualSection > * #sma${sectionNum}_main_default`).text("Padrão").css("opacity", temporary?"0.5":"1");
    }
}