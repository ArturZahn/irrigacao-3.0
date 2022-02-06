#include "cli.h"

void cliRunCommand(String cmd, byte cmdSource)
{
    if(cmdSource == CLI_SOURCE_WIFI) startLogBuffering();

    String args;
    splitCmdArgs(cmd, &cmd, &args);

    if(cmd == F("mostrarProgramacoes")) showProgramations();
    
    else if(cmd == F("alterarProgramacao")) alterProgramation(args);

    // else if(cmd == F("mostrarHora")) CMDprintln("showTime();"); //showTime();
    
    // else if(cmd == F("ajustarHora")) CMDprintln("ajustTime(args);"); //ajustTime(args);
    
    else if(cmd == F("pausarProgramacoes")) { pauseProgramations(); CMDprint("Programações pausadas"); }
    
    else if(cmd == F("retomarProgramacoes")) { resumeProgramations(); CMDprint("Programações retomadas"); }
    
    // else if(cmd == F("mostrarSetorManual")) CMDprintln("showManualSetor();"); //showManualSetor();
    
    // else if(cmd == F("alterarSetorManual")) CMDprintln("alterManualSetor(args);"); //alterManualSetor(args);
    
    else if(cmd == F("dispararProgramacao")) startEvent(args.toInt());

    else if(cmd == F("reiniciar")) restartSystem();

    else if(cmd == F("wifi")) exeWifiCommand(args);

    // else if(cmd == F("mostrarErros")) CMDprintln("showErrors();"); //showErrors();
    
    // else if(cmd == F("limparErros")) CMDprintln("clearErrors();"); //clearErrors();
    
    else
    {
        CMDprint(F("Erro, comando '"));
        CMDprint(cmd);
        CMDprintln(F("' não existe"));
    }
}