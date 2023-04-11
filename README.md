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

Doing a basic filter results in ALOT of misconfigurations for search based DLL issues. What interested me was the 'ffmpeg.dll' I noticed elsehwhere in the procmon dump. This appears to be a common DLL used by a variety of applications. 

![image](https://user-images.githubusercontent.com/46195001/231240214-d6421d61-a458-4104-8591-03f38f26d2d4.png)
