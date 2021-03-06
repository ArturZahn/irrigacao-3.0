#include "cli.h"

void cliRunCommand(String cmd)
{
    String args;
    splitCmdArgs(cmd, &cmd, &args);

    if(cmd == F("mostrarProgramacoes")) { showProgramations(); setCmdState(true); }
    else if(cmd == F("alterarProgramacao")) handleAlterProgramation(args);

    // else if(cmd == F("mostrarHora")) CMDprintln("showTime();"); //showTime();
    // else if(cmd == F("ajustarHora")) CMDprintln("ajustTime(args);"); //ajustTime(args);
    
    else if(cmd == F("pausarProgramacoes")) {
        setCmdState(true);
        pauseAutomaticProgramations();
        CMDprintln("Programações pausadas");
    }
    else if(cmd == F("retomarProgramacoes")) {
        setCmdState(true);
        resumeAutomaticProgramations();
        CMDprintln("Programações retomadas");
    }
    
    else if(cmd == F("mostrarSetorManualPadrao")) {
        CMDprintln(getDefaultManualSection());
        setCmdState(true);
    }
    else if(cmd == F("alterarSetorManualPadrao")) {
        if(!isNumber(args)) CMDprintln("Erro, digite o número válido");
        else if(setDefaultManualSection(args.toInt())) {
            setCmdState(true);
            CMDprintln("Setor manual alterado");
        }
        else CMDprintln("Erro, setor inválido");
    }
    
    else if(cmd == F("ativarSetorManual")) {
        if(!isNumber(args)) CMDprintln("Erro, digite o número válido");
        else if(activateManualSection(args.toInt())) {
            setCmdState(true);
            CMDprintln("Setor ativado");
        }
        else CMDprintln("Erro, setor inválido");
    }
    else if(cmd == F("desativarSetorManual")) {
        deactivateManualSection();
        setCmdState(true);
        CMDprintln("Setor desativado");
    }
    
    else if(cmd == F("dispararProgramacao")) {
        if(!isNumber(args)) CMDprintln("Erro, digite o número válido");
        else if(startEvent(args.toInt())) {
            setCmdState(true);
            CMDprintln("Programação iniciada");
        }
        else CMDprintln("Erro, programação inválida"); 
    }
    else if(cmd == F("pararProgramacao")) {
        stopEvent();
        CMDprintln("programacao parada");
        setCmdState(true);
    }

    else if(cmd == F("reiniciar")) restartSystem();

    else if(cmd == F("wifi")) exeWifiCommand(args);

    else if(cmd == F("mostrarInformacoes")) handleShowInformation();

    // else if(cmd == F("mostrarErros")) CMDprintln("showErrors();"); //showErrors();
    // else if(cmd == F("limparErros")) CMDprintln("clearErrors();"); //clearErrors();
    
    else
    {
        CMDprint(F("Erro, comando '"));
        CMDprint(cmd);
        CMDprintln(F("' não existe"));
    }
}

void handleShowInformation()
{
    CMDprint("numOfStages: ");
    CMDprintln(numOfStages);
    CMDprint("numOfTriggers: ");
    CMDprintln(numOfTriggers);
    CMDprint("numOfProgramations: ");
    CMDprintln(numOfProgramations);
    CMDprint("numOfSections: ");
    CMDprintln(numOfSections);
    CMDprint("programationEmpty: ");
    CMDprintln(programationEmpty);
    CMDprint("sectionEmpty: ");
    CMDprintln(sectionEmpty);
    CMDprint("maxDuration: ");
    CMDprintln(maxDuration);
    CMDprint("areProgramationsPaused: ");
    CMDprintln(d.areProgramationsPaused);
    CMDprint("manuallyActivatedSector: ");
    CMDprintln(getActiveManualSection());
    CMDprint("automaticProgramationRunning: ");
    CMDprintln(getActiveProgramation());
    CMDprint("defaultManualSection: ");
    CMDprintln(getDefaultManualSection());

    setCmdState(true);
}