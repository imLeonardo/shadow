@echo off
tasklist|find /i "nginx.exe" > nul
if %errorlevel%==0 (
tasklist /fi "imagename eq nginx.exe"
echo "nginx is running!"
exit /b
) else echo "nginx is stoped!"