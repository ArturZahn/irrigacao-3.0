@REM @REM ↓↓↓↓ coisa de por a hora no nome do arquivo ↓↓↓↓
@REM set CUR_YYYY=%DATE:~10,4%
@REM set CUR_MM=%DATE:~4,2%
@REM set CUR_DD=%DATE:~7,2%
@REM set CUR_HH=%time:~0,2%
@REM if %CUR_HH% lss 10 (set CUR_HH=0%time:~1,1%)

@REM set CUR_NN=%time:~3,2%
@REM set CUR_SS=%time:~6,2%
@REM set CUR_MS=%time:~9,2%

@REM set SUBFILENAME=%DATE:~6,4%-%DATE:~3,2%-%DATE:~0,2%_%CUR_HH%.%CUR_NN%.%CUR_SS%
@REM @REM ↑↑↑↑ coisa de por a hora no nome do arquivo ↑↑↑↑




mkdir C:\irrigacao\hmmmmm1.0

@REM "C:\irrigacao\wget.exe" -O C:/irrigacao/output/output_%SUBFILENAME%.txt http://127.0.0.1/irrigacao/saveMeasures.php
"C:\irrigacao\wget.exe" -O C:/irrigacao/output/output.txt http://127.0.0.1/irrigacao/saveMeasures.php

mkdir C:\irrigacao\hmmmmm2.0