rem /**
rem  * \file build.bat
rem  * \brief compilar as fontes usando o CCS
rem  */
del *.err
del *project.hex

set CCS="H:\Private\Programas\PICC\CCSC.exe"

rem 	PIC16 +FM
rem 	PIC18 +FH
rem +PE	Keep status window up only if there are errors
set D1= +FM 
rem +PE

set LIB="H:\Private\Programas\PICC\Devices;H:\Private\Programas\PICC\Drivers"

%CCS% %D1% I=%LIB% +EXPORT Hardware.c
%CCS% %D1% I=%LIB% +EXPORT menu.c
%CCS% %D1% I=%LIB% +EXPORT HardwareEEPROM.c
%CCS% %D1% I=%LIB% +EXPORT HardwareControl.c
%CCS% %D1% I=%LIB% +EXPORT EEPROM.c
%CCS% %D1% I=%LIB% +EXPORT display.c
%CCS% %D1% I=%LIB% +EXPORT main.c


%CCS% %D1% LINK="project.hex=Hardware.o,menu.o,HardwareEEPROM.o,HardwareControl.o,EEPROM.o,display.o,main.o"

del c:\c.log

del *.lst
del *.STA
del *.TRE
del *.COF
del *.esym
del *.osym
del *.o
del *.cod
del *.sym
del *.pjt