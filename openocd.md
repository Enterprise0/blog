# 简介
----

OpenOCD（Open On-Chip Debugger）开源片上调试器，是一款开源软件，旨在提供针对嵌入式设备的调试、系统编程和边界扫描功能。

OpenOCD的功能是在仿真器的辅助下完成的，仿真器是能够提供调试目标的电信号的小型硬件单元。仿真器是必须的，因为调试主机（运行OpenOCD的主机）通常不具备这种电信号的直接解析功能。

常用arm仿真器有SWD（仅支持调试，不支持边界扫描）和JTAG（JTAG支持调试和边界扫描）。


# openocd server部署
----

用仿真器连接目标开发板，在命令行执行：
```bash
openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg
```
- interface：仿真器
- target：目标芯片
> 可以在`/usr/local/share/openocd/scripts/`下查看


# openocd命令
----

```bash
openocd -c "<cmd>;<cmd>;..."
```
