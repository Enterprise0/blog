<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [todo](#todo)
- [基本知识](#基本知识)
- [飞行模式](#飞行模式)
  - [position mode](#position-mode)
  - [altitude mode](#altitude-mode)
  - [manual/stabilized mode](#manualstabilized-mode)
- [LED状态指示灯](#led状态指示灯)
  - [UI LED（集成在gps上）](#ui-led集成在gps上)
  - [Status LED（飞控硬件上）](#status-led飞控硬件上)

<!-- /code_chunk_output -->


## todo
----
- 设置failsafe，遥控器失控时输出


## 基本知识
----
- 有一些飞行模式需要gps信号才能解除安全开关（一般与gps集成在一起），否则不能解锁。室内飞行需要先调整到不需要gps信号的模式。
- pixhawk默认解锁（arm）方式为左手下右，加锁（disarm）方式为左手下左（美国手）。如果设定了开关则取消默认方式。地面站可以发送`MAVLink`命令加锁和解锁。
- throttle油门，yaw偏航角，pitch俯仰角，roll横滚角。


## 飞行模式
----
多旋翼飞行器自主模式下移动摇杆会默认进入`position`模式。

### position mode

最安全容易的手动模式，`需要gps。`

油门控制上升/下降速度，yaw控制水平旋转角速度，roll和pitch分别控制相对于地面的左右、前后加速度。释放摇杆时会锁定在当前位置，不会被风等因素影响。

### altitude mode
最安全容易的`无gps`的手动模式。

油门控制上升/下降速度，yaw控制水平旋转角速度，roll和pitch控制对应角度。释放摇杆时会锁定在当前高度， 但前后和左右方向会被风和摇杆回中前的动量等因素影响。

### manual/stabilized mode
比较难飞，不推荐新手用这种模式。

油门控制上升/下降速度，yaw控制水平旋转角速度，roll和pitch控制对应角度。在有外力（风）干扰时，需要手动修正油门和ypr轴。

## LED状态指示灯
----
pixhawk硬件有一个超亮的`UI LED`,fmuv4及之后的硬件把`UI LED`集成到了gps上。在pixhawk硬件上有`Status LED`。

### UI LED（集成在gps上）

- 蓝色闪烁，未解锁，无gps。
- 蓝色常亮，已解锁，无gps。
- 绿色闪烁，未解锁，有gps。
- 绿色常亮，已解锁，有gps。
- 紫色常亮，fail safe。可能是失控、严重低电量或内部错误等，此时会返航或原地降落。
- 黄色常亮，电池电量低。
- 红色闪烁，error。飞控需要配置或校准。

### Status LED（飞控硬件上）
指示了power、bootloader状态和错误情况。


