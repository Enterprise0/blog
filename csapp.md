<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [简介](#简介)
- [第二章](#第二章)
- [第三章 程序的机器级表示](#第三章-程序的机器级表示)

<!-- /code_chunk_output -->

## 简介
----
- 本书以x86-64架构为例。
- x86-64中，栈存放在内存中的某个区域，向低地址方向生长。


## 第二章
----

- 并发：上下文切换
  并行：


## 第三章 程序的机器级表示
----

- 寄存器：
    1. %rbx、%rbp和%r12~r15：被调用者寄存器（A call B并跳转到B后，若B需要使用这些寄存器，需要先保存到栈帧中）。
    2. 其他除%rsp外所有的寄存器为调用者保存寄存器。

- 栈是一种数据结构，可以存在与内存中的任何位置，由SF:SP指定一个栈。
>栈向高/低地址方向生长是由操作系统决定的。

- 过程（函数）调用：
    1. 参数存入寄存器和栈帧（>6个的参数存入栈中），后面的参数先传。
    >x86-64中，可以通过寄存器传递最多6个整形参数（整数和指针），通过栈传递数据需要字节对齐。
    1. `call B`，A返回地址（即A中函数调用后面一条指令的地址）入栈，并把PC设为过程B的第一条指令的地址。
    2. 在过程B中首先保存寄存器（若需要的话），然后为变量分配空间（先寄存器，后栈帧）。
>寄存器组是唯一被所有过程共享的资源。 

`过程调用和进程调用不是一回事。`

## objdump
----

```bash
-d 从可执行文件或者目标文件反汇编
-t 从可执行文件或者目标文件得到符号表，里面有函数名称和全局变量等
```