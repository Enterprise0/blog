## 简介
----
`Mastering Embedded Linux Programming（Third Edition）`

## Chapter 1:Starting Out
----

### Meeting the players
开源软件的制作者：
1. The open source community：非营利性组织、学术机构、商业公司等。比如Linux, U-Boot, BusyBox, Buildroot, the Yocto Project, and the many projects under the GNU umbrella.

2. CPU architects：Arm/Linaro (Arm Cortex-A), Intel (x86 and x86_64), SiFive (RISC-V), and IBM (PowerPC).

3. Soc venders(片上系统供应商Broadcom, Intel, Microchip, NXP, Qualcomm, TI, and many others)：从CPU architects拿到内核和工具链后，修改并支持芯片。设计参考板，为下一步设计开发板和产品做参考。

4. Board vendors and OEMs（原始设备制造商）：从Soc venders得到参考板，并构建到特定产品中（机顶盒、摄像头、通用开发板比如树莓派、BBB等）。

5. Commercial Linux vendors：Companies such as Siemens (Mentor), Timesys, and Wind River。提供经过严格的规则验证的linux商业发行版。

上述产业链中各环节开发商不会向上游推进它们的更改，并且通常只会对它们最新的芯片活跃的开发开源组件，对于老芯片的支持只有几年。
因此大多数嵌入式设计都基于老版本的软件，没有接受安全更新、性能提升或新特性。

### Moving through the project life cycle
- Elements of Embedded Linux (Chapters 1 to 8) will help you set up the development environment and create a working platform for the later phases. It is often referred to as the board bring-up phase.
可以通过Buildroot或the Yocto Project。
- System Architecture and Design Choices (Chapters 9 to 15) will help you to look at some of the design decisions you will have to make concerning the storage of programs and data, how to divide work between kernel device drivers and applications, and how to initialize the system.
- Writing Embedded Applications (Chapters 16 to 18) shows how to package and deploy Python applications, make effective use of the Linux process and thread model, and how to manage memory in a resource-constrained device.
- Debugging and Optimizing Performance (Chapters 19 to 21) describes how to trace, profile, and debug your code in both the applications and the kernel. The last chapter explains how to design for real-time behavior when required.

### The four elements of embedded Linux
- Toolchain: The compiler and other tools needed to create code for your
target device.
- Bootloader: The program that initializes the board and loads the Linux kernel.
- Kernel: This is the heart of the system, managing system resources and interfacing with hardware.
- Root filesystem: Contains the libraries and programs that are run once the kernel has completed its initialization.


## Chapter 2: Learning about Toolchains
----


### Introducing toolchains
GNU工具链包括以下三个部分：
- Binutils: A set of binary utilities including the assembler and the linker. It is available at http://gnu.org/software/binutils.
- GNU Compiler Collection (GCC): These are the compilers for C and other languages, which, depending on the version of GCC, include C++, Objective-C, Objective-C++, Java, Fortran, Ada, and Go. They all use a common backend that produces assembler code, which is fed to the GNU assembler. It is available at http://gcc.gnu.org/.
- C library: A standardized application program interface (API) based on the POSIX specification, which is the main interface to the operating system kernel for applications.

### CPU architectures
工具链根据目标CPU的功能构建，主要功能为：
- CPU architecture：ARM,MIPS,X86_64
- 大小端
- 是否支持硬件浮点运算单元
- Application Binary Interface (ABI)：分为OABI（old）和EABI（2000年后），EABI还有EABIHF（支持硬件浮点运算）。

GNU工具链中每种工具的名字前缀表明了不同的目标CPU：
- CPU架构
- Vendor：可能没有供应商
- Kernel：可能没有
- Operating system：A name for the user space component,可能为gnu或musl。可能附加abi信息，如gnueabi, gnueabihf, musleabi, musleabihf。
    >本地编译器通常会生成一个没有前缀的link，如gcc。
    ```bash
    gcc -dumpmachine
    x86_64-linux-gnu
    ```
