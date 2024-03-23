@echo off
chcp 65001

set flag=0

set installPath=C:\\"Program Files"\\nginx

set projectPath=D:\\Workspace\\project\\shadow\\web

set confFile=%projectPath%\\conf\\nginx.conf

echo install path: %installPath%
echo project prefix path: %projectPath%
echo config file: %confFile%
echo nginx starting

tasklist|find /i "nginx.exe" > nul
if %errorlevel%==0 (
    echo "nginx already running"
) else set flag=1

if %flag%==1 (
    @REM "start %installPath%\\nginx.exe -p %projectPath% -c %confFile%"
    %installPath%\\nginx.exe -p %projectPath% -c %confFile%
    ping localhost -n 2 > nul
)

tasklist /fi "imagename eq nginx.exe"

tasklist|find /i "nginx.exe" > nul

if %errorlevel%==0 (
    echo "nginx starting succeced"
)