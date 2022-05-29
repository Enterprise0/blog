## 简介
----

- mit 6.s081

- 环境：RSIC-V四核处理器

## lab guidance
----

- print

- gdb调试：在一个终端开启gdb client`make qemu-gdb`，在另一个终端开启gdb server`gdb or riscv64-linux-gnu-gdb`。

- 查看`kernel.asm`，同时编译器编译内核后，会给每个user program生成对应的.asm。

- 内核崩溃时，报错信息里有pc寄存器的值，然后查看`kernel.asm`在哪个函数出错，或者运行`addr2line -e kernel/kernel pc-value`。

- `ctrl-a c`进入qemu的monitor，可以查看虚拟机的信息。`info mem`查看页表（使用`cpu`指令选择`info mem`查看哪个核，`make qemu CPUS=1`模拟单核）。