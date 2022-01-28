#include <Arduino.h>
#include "watchTime.h"
#include "programations.h"
#include "serialControl.h"
#include "timeFuncs.h"
#include "rtc.h"

void setup()
{
    Serial.begin(115200);

    initSections();
    initRTC();
    initializeEEPROM();
    readEEPROMData();
    initializeProgramations();


    // for(byte prog = 0; prog < numOfProgramations; prog++)
    // {
        
    //     getProgramation(prog).setStatus(false);
    //     for(byte actTm = 0; actTm < numOfTriggers; actTm++)
    //     {
    //         getProgramation(prog).setTrigger(actTm, triggerEmpty);
    //         // getProgramation(prog).setTrigger(actTm, (prog+2)*100 + actTm*2);
    //     }
        
    //     for(byte subprogNum = 0; subprogNum < numOfStages; subprogNum++)
    //     {
    //         getProgramation(prog).setSectionOrder(subprogNum, sectionEmpty);
    //         getProgramation(prog).setDuration(subprogNum, 0);

    //         // getProgramation(prog).setSectionOrder(subprogNum, subprogNum+10);
    //         // getProgramation(prog).setDuration(subprogNum, (subprogNum*2)+10);
    //     }
    //     Serial.println("\n");
    // }

    // storeEEPROMData();
}

void loop()
{
    handleWatchTime();
    handleActiveEvent();
    handleSerialControl();
}
















// // #include <Arduino.h>
// // #include <freertos/FreeRTOS.h>
// // #include <freertos/task.h>
// // #include <esp_system.h>
// // #include <time.h>
// // #include <sys/time.h>
// // struct tm data;//Cria a estrutura que contem as informacoes da data.
// // void setup()
// // {
// //   timeval tv;//Cria a estrutura temporaria para funcao abaixo.
// //   tv.tv_sec = 1551355200;//Atribui minha data atual. Voce pode usar o NTP para isso ou o site citado no artigo!
// //   settimeofday(&tv, NULL);//Configura o RTC para manter a data atribuida atualizada.
// // }

// // void loop()
// // {
// //     vTaskDelay(pdMS_TO_TICKS(1000));//Espera 1 seg
// //     time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
// //     data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    
// //     char data_formatada[64];
// //     strftime(data_formatada, 64, "%d/%m/%Y %H:%M:%S", &data);//Cria uma String formatada da estrutura "data"
// //     printf("\nUnix Time: %d\n", int32_t(tt));//Mostra na Serial o Unix time
// //     printf("Data formatada: %s\n", data_formatada);//Mostra na Serial a data formatada
// //     /*
// //       Com o Unix time, podemos facilmente controlar acoes do MCU por data, visto que utilizaremos os segundos
// //       e sao faceis de usar em IFs
// //       Voce pode criar uma estrutura com a data desejada e depois converter para segundos (inverso do que foi feito acima)
// //       caso deseje trabalhar para atuar em certas datas e horarios
// //       No exemplo abaixo, o MCU ira printar o texto **APENAS** na data e horario (28/02/2019 12:00:05) ate (28/02/2019 12:00:07)
// //     */
// //     if (tt >= 1551355250 && tt < 1551355253)//Use sua data atual, em segundos, para testar o acionamento por datas e horarios
// //     {
// //       printf("Acionando carga durante 3 segundos...\n");
// //     }
// // }















// void loop () {
  
//     delay(1000);
  
    
    
//     Serial.print(" since midnight 1/1/1970 = ");
//     Serial.print(now.unixtime());
//     Serial.print("s = ");
//     Serial.print(now.unixtime() / 86400L);
//     Serial.println("d");
// }