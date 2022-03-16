# OS Kernel
I started this project, because I wanted to learn how to write a kernel. Quickly, I found out how way in over my head 
I was when it comes to C, Make, and Linux. Therefore, I went to Google & started looking for resources. From the get-go
I knew there wouldn't be a simple "100 steps to your own Kernel", thus, I focused on searching for specific keywords.
Such as "kernel", "kernel development", "kernel programming", "kernel programming tutorial", "kernel programming guide",
"libc kernel", "memory management", "memory management tutorial", "memory management guide" & more. Eventually I came across
[Wikipedia](https://en.wikipedia.org/wiki/Kernel_(computing)), [OSDev](https://www.osdev.org/) & [Kernel.org](https://www.kernel.org/).

## Key Tutorials used
- [Getting Started](https://wiki.osdev.org/Getting_Started)
- [Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)
- [Bare Bones](https://wiki.osdev.org/Bare_Bones)
- [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton)
- [Going Further on x86](https://wiki.osdev.org/Going_Further_on_x86)
- [Kernel Model](https://wiki.osdev.org/Monolithic_Kernel)

## Changes made
Obviously I didn't just copy and paste code from the tutorials / resources above & call it my own Kernel. I did however,
put effort into learning exactly why things are done (such as the purpose of linker.ld & boot.asm). Furthermore,
I use [JetBrains](https://www.jetbrains.com/) tool suite to write my code, under their student licence. 
Specifically I useCLion for C++ while it mas MakeFile support. It is not as clean
as the Cmake support. Thus, I wrote CMakeLists.txt script in order to have my entire kernel be able to be compiled with CMake.
### CMakeLists.txt
One of the first bugs I encountered was that CMake complained that my Cross-Compiler was failing its tests, due to the default
"dynamic" parameter that is used, thus I found through much trail & error along with "Google-Fu", that we can actually
set CMake parameters such that it looks like all compiler tests will pass. The 5 lines of code below are these parameters:
```cmake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)
```
For the first 1 or 2 days of attempting to get this working, I was using ```add_library()``` for my kernel. However, I found
that I should instead be using ```add_executable()``` & ```target_link_libraries()``` in order to get the linker to work.

I added a debug message to list all sources that "GLOB RECURSE" found. This is to help me debug any issues I may encounter 
in the future. 

### TTY.C/TTY.H
While looking through [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton), structure, I found that they put a lot of the 
"terminal" printing characters code in this file & it caused me to look deeper into the meaning behind this acronym. "TTY" stands
"teletypewriter", which is refering to (funny enough) Unix terminal. The phrase coming from the "old days". 
This [StackOverflow answer](https://stackoverflow.com/a/4426291) was especially useful. In this definition.

I extended the ability of this TTY.c to support ```terminal_moveup()```, which essentially removes the first line of the terminal,
and moves all the lines up, giving the affect of scrolling. This is achieved by changing the VGA array. 

### CLion setup
As previously mentioned I use [CLion](https://www.jetbrains.com/clion/) for C++. Configuring CLion to properly work 
was a bit of a challenge. 
The following image contains the configuration setup:
#
![image](https://user-images.githubusercontent.com/40865296/158657358-17f22cc0-e988-46d4-a663-2eab8e130294.png)
Where "CMake Application" defines the configurations' auto-detected by CLion. 
Remote Debug, was the GDB configuration needed to debug my kernel through QEMU. 
& Start QEMU shell script started the QEMU emulator with necessary parameters & arguments.