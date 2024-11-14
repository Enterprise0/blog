# Introduce
----

i.mx6ull uboot

# Reference
----

[Develop U-Boot](https://docs.u-boot.org/en/stable/develop/index.html)

# U-Boot Porting Guide(from u-boot README)
----

```c
int main(int argc, char *argv[])
{
	sighandler_t no_more_time;

	signal(SIGALRM, no_more_time);
	alarm(PROJECT_DEADLINE - toSec (3 * WEEK));

	if (available_money > available_manpower) {
		Pay consultant to port U-Boot;
		return 0;
	}

	Download latest U-Boot source;

	Subscribe to u-boot mailing list;

	if (clueless)
		email("Hi, I am new to U-Boot, how do I get started?");

	while (learning) {
		Read the README file in the top level directory;
		Read https://www.denx.de/wiki/bin/view/DULG/Manual;
		Read applicable doc/README.*;
		Read the source, Luke;
		/* find . -name "*.[chS]" | xargs grep -i <keyword> */
	}

	if (available_money > toLocalCurrency ($2500))
		Buy a BDI3000;
	else
		Add a lot of aggravation and time;

	if (a similar board exists) {	/* hopefully... */
		cp -a board/<similar> board/<myboard>
		cp include/configs/<similar>.h include/configs/<myboard>.h
	} else {
		Create your own board support subdirectory;
		Create your own board include/configs/<myboard>.h file;
	}
	Edit new board/<myboard> files
	Edit new include/configs/<myboard>.h

	while (!accepted) {
		while (!running) {
			do {
				Add / modify source code;
			} until (compiles);
			Debug;
			if (clueless)
				email("Hi, I am having problems...");
		}
		Send patch file to the U-Boot email list;
		if (reasonable critiques)
			Incorporate improvements from email list code review;
		else
			Defend code as written;
	}

	return 0;
}

void no_more_time (int sig)
{
      hire_a_guru();
}
```

# uboot启动方式
----

因为nandflash没有地址总线，所以不能直接在nandflash中运行，
选择这种上电方式后会将nandflash前4k拷贝到RAM中。

norflash有地址总线，选择这种启动方式后，会将norfalsh映射到`0x0000 0000`，
cpu会在norflash上执行。

[uboot在nandflash和norflash是如何运行的](https://www.cnblogs.com/aaronLinux/p/5540606.html)

[u-boot分析1：Nandflash、Norflash启动](https://blog.csdn.net/qq_31917863/article/details/79863756)

[野火 IMX6ULL uboot启动流程](https://doc.embedfire.com/lubancat/build_and_deploy/zh/latest/building_image/boot_image_analyse/boot_image_analyse.html)

目前uboot也可以使用设备树的方式配置该阶段需要使用的驱动参数。

# IMX6ULL BOOT
----

参考<mark><<i.MX 6UltraLite Applications Processor Reference Manual>>
Chapter 8 System Boot<mark>

- boot flow：

    ```mermaid
    graph LR  
    1(hardware reset logic) --> 2(on-chip boot ROM) --> 3(boot device)
    ```
    片上ROM不包含DCD数据，只存在于program image中。

- iROM/RAM memory map：

    <div align=center><img src=./pic/IMX6ULL%20Internal%20ROM%20and%20RAM%20memory%20map.png/></div>
    iROM不会初始化DDR，需要在DCD中初始化。

- Enabling MMU and caches

    The boot ROM includes a feature that enables the Memory Management Unit (MMU)
    and the caches to improve the boot speed.

    The L1 instruction cache is enabled at the start of the image download. The L1 data cache, L2 cache, and MMU are enabled during the image authentication. When the HAB authentication completes, the ROM disables the L1 data cache, L2 cache, and MMU.

    The L1 Instruction cache, L1 data cahce, L2 cache, and MMU is controlled by eFuse. By default, these features are enabled.

    Enabling the MMU when booting non-securely with SEC_CONFIG=Open and setting
    the CSF pointer in the Image Vector Table to NULL has no impact on the boot
    performance. With this configuration, it is recommended to blow the
    BT_MMU_DISABLE fuse.

- 部分boot device(internal boot)

    - NOR Flash Boot Operation
        ![NOR Flash Boot Operation](./pic/NOR%20Flash%20Boot%20Operation.png)

    - Expansion Device Boot Operation
        ![Expansion Device Boot Operation](./pic/Expansion%20Device%20Boot%20Operation.png)
        copy 4Kbyte to iRAM, check IVT header, DCD check(by ROM code),
        copy image data to RAM(depend on destination pointer and length of image from Boot Data Data Structure, max 32MB)

- Expansion device structures layout

    <div align=center><img src=./pic/Expansion%20device%20structures%20layout.png/></div>

- Program image

    - Image vector table—a list of pointers located at a fixed address that the ROM examines to determine where the other components of the program image are located.

    - Boot data—a table that indicates the program image location, program image size in bytes, and the plugin flag.

    - Device configuration data—IC configuration data.

    - User code and data.

- Image Vector Table and Boot Data

    <div align=center><img src=./pic/Image%20Vector%20Table%20and%20Boot%20Data.png/></div>
    
    <mark> The initial 4 KB of the program image must contain the IVT, DCD, and the Boot Data structures. <mark>

- Devicetree in U-Boot

    [Devicetree in U-Boot](https://docs.u-boot.org/en/stable/develop/devicetree/control.htmlhttps://docs.u-boot.org/en/stable/develop/devicetree/index.html)

- Driver Model

    [Driver Model](https://docs.u-boot.org/en/stable/develop/driver-model/index.html)

# 设备树
----

linux首先引入设备树，然后uboot引入。

aarch64一开始设备驱动和参数是写死的，但是不同的arm开发板有不同的硬件，会造成代码臃肿。
所以分离出来，通过设备树可以知道有哪些硬件，以及配置这些硬件的驱动需要的参数。

前提是需要在编译uboot和kernel前使能使用设备树的选项。

在x86上可以自动枚举PCIE总线上的设备。

[为什么linux在x86上不需要设备树，在aarch64上需要设备树？](https://www.zhihu.com/question/475730584/answer/2709878631)
