@echo off
echo Building...
PATH=%PATH%;C:\Program Files\arm_sdk\bin;C:\Program Files\arm_sdk\arm-none-eabi\bin;C:\Program Files\arm_sdk\lpc21isp_197
make
echo --------------------------------------------
echo *  Instructions
echo *  Press RESET and Mode/ISP buttons
echo *  release RESET 
echo *  then release Mode/ISP
echo --------------------------------------------

pause
echo Downloading...
lpc21isp main.hex com6 9600 12000000
echo Done
pause