@echo off
tasklist|find /i "nginx.exe" > nul
if %errorlevel%==0 (
    taskkill /f /t /im nginx.exe > nul
    echo "nginx stoped!"
)else echo "nginx not running!"
