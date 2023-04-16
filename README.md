# Discord-DLL-Hijacking
This is a simple quick example of DLL hijacking enabling proxy execution for the Discord Binary. This can be beneficial for attackers requiring proxy execution to bypass EDR



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
Once you've compiled it, copy your DLL, the tmpXYZ.dll and your shellcode.bin into "C:\Users\<user>\AppData\Local\Discord\app-1.0.9012\". 

## Result 
![popped](https://user-images.githubusercontent.com/46195001/232325180-3ec3af99-d5f9-4c8c-935c-fd7d3c0ece51.png)

Running Discord.exe executes a shellode. Great! Interestingly Discord itself crashes out with no visual artifacts but our cmd.exe process remains. This is ideal if we drop discord ourselves as a persistence mechanism without user knowledge. 

## Weaponizing further. 

-> TODO macro download and install discord via cmd.exe with no prompts, replace with malicious DLL and easylife. 

 




