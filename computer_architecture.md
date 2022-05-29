<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [## 指令集架构ISA](#-指令集架构isa)
- [## 流水线（pipelining）](#-流水线pipelining)
- [魔术代码（magic code）：](#魔术代码magic-code)

<!-- /code_chunk_output -->


## 指令集架构ISA
----

- 哈佛结构计算机：数据和指令不存放在同一存储器中。
    冯·诺依曼结构计算机：数据和指令存放在同一存储器中。

- load-store型处理器：所有计算都在寄存器中进行，内存中的数据要先移到寄存器中。

- CISC（complex instruction set computer)复杂指令集计算机：Intel的IA32（Intel Architecture 32-bit）架构，Intel和AMD的X86-64架构。
    RISC（reduced instruction set computer)精简指令集计算机：MIPS、ARM、RISC-V架构。（前两者是定长指令）。

- ARM有16个通用寄存器。ARM所有指令和字（32位）数据必须按4字节对齐存放，PC每次+4，反汇编时每4个字节反汇编一次。
![ARM通用寄存器](pic/ARM%E9%80%9A%E7%94%A8%E5%AF%84%E5%AD%98%E5%99%A8.png)

- Thumb指令集：使用ARM处理器的32位指令集并压缩为16位。

- 大端：最高字节放在最高位字节地址处（0x0）
    小端：最高字节放在最低位字节地址处（0x3）
![大端小端](pic/%E5%A4%A7%E7%AB%AF%E5%B0%8F%E7%AB%AF.png)


## 流水线（pipelining）
----

执行一条指令分为：取值、译码、读操作数、执行、保存操作数等阶段。分成几个阶段就是几级流水线。
流水线性能极限是每周期一条指令，会被分支等操作影响，分支跳转导致已经进入流水线的指令清空。$\Rightarrow$ 分支预测、延迟分支、气泡......


## 魔术代码（magic code）：

## 动态分配和静态分配内存