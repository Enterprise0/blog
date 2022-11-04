[toc]

# todo
----
1. 如果工程电机太多，一个电池无法供电，需要用裁判系统输出端口作为继电器信号，控制多个电池。

2. 上位机用一个线程保存珍贵的实战比赛第一视角视频，一个线程通信，一个线程读取摄像头，一个线程处理图片。



# issue
----
1. 平衡步兵视觉



# CAN
----
1. [C620调整终端电阻](https://bbs.robomaster.com/thread-12094-1-1.html)
can网络里面有两个终端电阻就够了，线长短不一样更改一下阻抗匹配，用示波器看一下can上面的信号质量调整一下终端电阻数量至波形稳定就好了

2. [示波器看CAN终端电阻的作用](https://zhuanlan.zhihu.com/p/26096996)

3. [RM没必要使用CANopen](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=7367)：CANopen也是在CAN2.0基础上，将11位的标识符重新定义了一下，然后定义了几个通信对象（PDO,SDO,NMT），然后还有对象字典可以存储设备的很多信息，主站可以读写设备的一些信息。如果有好多设备，分布式系统，对实时性要求不是很高，可以采用CANopen。RM的话，其实没有那么多设备，也不需要对象字典来存储那么多信息，另外生产CANopen的厂家都必须向CiA协会申请唯一的厂商代码，其他应该也要服从协会的一些规定，对于自己开发的话可能用不太到。其实自己开发的话，完全可以在CAN的11位标识符很和8字节的数据上做文章，设计自己的应用层协议。

4. [CANOpen系列教程](https://www.strongerhuang.com/CANOpen/CANOpen%E7%B3%BB%E5%88%97%E6%95%99%E7%A8%8B.html)

5. CANopen轻松入门周立功



# 论坛开源资料
----
[论坛开源汇总](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=6979&extra=page%3D1)

## RM2021高校课程沙龙-江苏05-嵌入式经验分享(东南大学)
[视频链接](https://docs.qq.com/sheet/DUFlaU0FHZk1QS0l1?tab=cx5q1v)

1. FreeRTOS各任务之间尽量互不干扰，便于单独调试。正常情况下不允许有任务阻塞其他进程。创建一个LED BLINK任务，优先级最低，便于观察程序跑飞。

2. 任务调度可以使用systemview进行分析。

3. 对于一些要求精确时间的任务（比如PID控制任务要有精确的周期），尽量设置较高的优先级。

4. 全队代码框架和命名规范一致，便于代码复用和各车组间合作。

5. 为避免多个任务同时调用can发送数据包，存在冲突而发送失败的情况，可以建立一个can发送队列。
![canqueen](./pic/canqueen.png)

6. 超级电容：不能用裁判系统的功率数据进行超级电容的闭环控制。可以用simulink调试电路pid，不建议调试电机pid（建模难度大）。

7. 稳定性：
    - 不放过调试过程中的任何小问题，比如焊线，焊线不稳一定要重焊。
    - 和机械组沟通好布线问题
    - 尽量采用简洁的方案，更少的传感器。

8. 培训经验：注释认真写。


## RM圆桌第九期-PID控制深透析
[PID控制深透析](https://bbs.robomaster.com/thread-8106-1-1.html)

1. 串级PID内环计算频率≥外环计算频率，在RM中=即可。

2. 只用PI控制即可，没必要增加高频相应。
>现实系统都有低通特性，没有特殊或严格要求没必要加微分项。

3. 云台俯仰时底盘陀螺仪测的数据不是云台的实际角速度数据，而是云台实际角速度数据的分量。所以数据需要相应的旋转，或在云台上放个陀螺仪测云台相对于地面的绝对角度，底盘旋转不会影响云台PID。

4. 陀螺仪尽量安装在车子中轴线，远离震动源。MEMS陀螺仪会收到加速度干扰。


## 强队电控开源代码
1. 华南虎
    - [2021英雄](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12215)
    - [2021舵轮步兵](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12207)

2. 深大
    - [2021英雄](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12319)
    - [2021双云台哨兵](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12293)
    - [2021双枪舵轮步兵](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12265)
    - [2021麦轮步兵电控](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12262)

3. 浙大
    - [2021哨兵全套](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=6932) 电控代码丢失

4. 杭电
    - [2021麦轮、舵轮、全向轮底盘解算](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=17629)

5. 西北工业大学
    - [2021步兵电控](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12255)

6. 东北大学
    - [2021双枪步兵电控](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=12290)


## 电控小知识之电控视觉联调
[电控小知识之电控视觉联调](https://www.bilibili.com/video/BV1T5411K7nP/?spm_id_from=333.999.0.0&vd_source=b037d71dfcc90a4fe87a5c511ca50806)
1. 机械在sw设计的时候，要和电控视觉讨论布线，主要是电控。

2. 子弹出膛瞬间动量变化导致云台pitch轴角度发生变化的问题，如果通过机械上保证子弹初速度矢量与pitch轴转轴重合的话，感觉会比追求抗扰性能更好的控制算法更有效些。

3. 调通信的时候可以单独拿一块板来调 

4. 调视觉识别最好电控和视觉都在，在用pc（不是车上的视觉主机）调的时候准备一条比较长的线（比如2m），防止疯车的时候扯断线。

5. 布完线后让老队员检查一遍。



# 电控
----
1. 工程代码框架、命名规范和布线。暑假先重新阅读官方例程和开源代码，官方例程有一点臃肿。阅读完代码后再统一代码框架和命名规范等。可以先修改本赛季工程代码用于调试，但是后面要按照规定的代码框架重写。要有一套能够传承下去的代码框架。
代码框架要求：简洁、命名规范统一。

2. 代码版本管理：
    - 每个版本一个文件夹，文件夹附加版本信息，比如年月日
    - git

3. 卡尔曼滤波器及其在云台控制中的应用
[卡尔曼滤波器及其在云台控制中的应用](https://zhuanlan.zhihu.com/p/38745950)

## 官方3508速度环PID分析(空载)
![speed1m/s](./pic/speed1.png)
超调量：< 2%

![speed2m/s](./pic/speed2.png)
超调量：< 1% 

![speed3m/s](./pic/speed3.png)
超调量：< 0.5%，但是上方的点过多
>3508反馈的转速是转子转速，C620下最大转速（空载）482*（3591/187）（减速比）rpm
- 不要一昧的增加P，当下方的点过多时存在静差，增加I。 
- 增加开环增益P只能减小稳态误差，或者减缓稳态误差趋于无穷大时的速率（稳态误差有三种情况：0、大于0、无穷大）。
- 加入I相当于增加串联积分环节，可以消除稳态误差，改变系统无静差度。 
- 适当选取Kp和Kd可以增大无阻尼振荡角频率$ w_n $和阻尼比$  $（以标准二阶系统为例），改善系统快速性和平稳性。但是PD控制器会向系统传递函数引入一个零点。

## 电机编码器计算角度
```c
static fp32 motor_ecd_to_angle_change(uint16_t ecd, uint16_t offset_ecd)
{
    int32_t relative_ecd = ecd - offset_ecd;
    //过零检测
    if (relative_ecd > HALF_ECD_RANGE)
    {
        relative_ecd -= ECD_RANGE; 
    }
    else if (relative_ecd < -HALF_ECD_RANGE)
    {
        relative_ecd += ECD_RANGE;
    }

    return relative_ecd * MOTOR_ECD_TO_RAD;
}
```
根据以上函数只能计算转子的角度（没有减速箱时机械转子角度就是输出轴角度，-180°~180°。6020没有减速箱，所以可以用这种方法计算编码器角度。如果电机有减速箱就不能得到输出轴的角度（3508减速比约为19:1）。
不管有没有减速箱该方法只解决了过零检测，当输出轴转过360°时不能累计角度。

## 双轴云台控制
[Robomaster电控入门（7）双轴云台控制](https://www.guyuehome.com/35019)
云台的参数调节除了和PID参数有关之外，还和控制周期，传感器反馈频率，器件热噪声大小等因素有关，有的时候其实不需要复杂的参数就能有很好的控制效果

## 过零检测
[串级PID及角度过零处理](https://blog.csdn.net/qq_38972634/article/details/117036117?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-117036117-blog-115335500.pc_relevant_3mothn_strategy_and_data_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-117036117-blog-115335500.pc_relevant_3mothn_strategy_and_data_recovery&utm_relevant_index=13)

## 姿态解算（融合）

## PID
- 位置式PID：
$ u(k) = K_p e(k) + K_i\sum_{i=0}^{k}e(i) + K_d[e(k)-e(k-1)]  $
需要输出限幅、积分限幅。当输出饱和时，不加积分限幅会出现积分饱和。常见的抗积分饱和方法：积分分离法(e(k)绝对值大于阈值时只用PD)、遇限削弱积分法（积分限幅）、变速积分法（加强版的积分分离法)

- 增量式PID：
$ \Delta u(k) = u(k)-u(u-1) \\= K_p[e(k)-e(k-1)] + K_ie(k) + K_d[e(k)-2e(k-1)+e(k-2)] $
只需要输出限幅。



# 视觉
----
1. 了解CV和RoboMaster视觉组
[github](https://github.com/NeoZng/vision_tutorial/tree/v1.0.0)
[csdn](https://blog.csdn.net/neozng/category_11397138.html)

2. RoboMaster机甲大师——视觉组——总结、未来期望与比赛经验分享
[RoboMaster机甲大师——视觉组——总结、未来期望与比赛经验分享](https://blog.csdn.net/whl970831/article/details/108851630?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166678998216782414980789%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166678998216782414980789&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-108851630-null-null.142^v62^pc_search_tree,201^v3^control_2,213^v1^t3_esquery_v1&utm_term=RoboMaster%E6%9C%BA%E7%94%B2%E5%A4%A7%E5%B8%88%E2%80%94%E2%80%94%E8%A7%86%E8%A7%89%E7%BB%84%E2%80%94%E2%80%94%E6%80%BB%E7%BB%93%E3%80%81%E6%9C%AA%E6%9D%A5%E6%9C%9F%E6%9C%9B%E4%B8%8E%E6%AF%94%E8%B5%9B%E7%BB%8F%E9%AA%8C%E5%88%86%E4%BA%AB&spm=1018.2226.3001.4187)

3. RoboMaster视觉教程——浙大
[RoboMaster视觉教程——浙大](https://blog.csdn.net/u010750137/category_8994384.html)

4. RM圆桌005 | 抢人头要靠自瞄
[RM圆桌005 | 抢人头要靠自瞄](https://www.robomaster.com/zh-CN/resource/pages/activities/1009)
   - 自瞄一般思路：设置合适的相机帧率和曝光时间，图像预处理（颜色分割、二值化），灯条提取（findContours），装甲板识别（条件约束），云台控制。
   - 摄像头参数：较高帧率和较低的曝光时间,可以避免过多噪声，防止运动过快导致图像模糊，这些参数需要在不同光照条件下进行测试调参。一般工业相机帧数100hz。
   - 算法实时性：一般选择更加实时的方案（opencv），用各种滤波算法提高实时性。将视觉算法的速度做到极致，来使延迟的影响最小化。结合GPU，有些图像的操作在GPU上的速度会大大提高，充分利用各种图像加速的API。分辨率640*480，帧率60以上，距离3m。摄像头帧率要看算法的速度，保证马上处理下一帧数据。采用ROI的方法减少图像的运算，提高算法速度，但是要考虑相对运动造成roi的偏移。
   - 测距：单目测距，误差大概10%。利用小孔成像的原理测距。
   - 算法鲁棒性：充分测试各种环境下的识别率。调整摄像头的参数，提高算法的鲁棒性，在比赛条件下通过录像后期调试，测试场地时最好能实现远程调试。
   - 预测：算法相对控制存在延迟，加入预测来补偿延迟。但是要先保证算法的实时性再考虑。

5. RM圆桌008 | 如何击打大风车
[RM圆桌008 | 如何击打大风车](https://www.robomaster.com/zh-CN/resource/pages/activities/1015)
   - 相机焦距8mm，安装在底盘有助于打符。
   - 重力补偿：参考RoboRTS的抛物线弹道修正模型。简化模型，定点打靶，建立一个pitch偏移表，通过偏移量查表来进行补偿。
   - 相机标定误差：多次标定，去掉偏差较大的标定结果，取中位标定结果。
   - 等子弹打出去再发送下一次的预测位置。

6. 官方ICRA步兵开源项目RoboRTS
[官方ICRA步兵开源项目RoboRTS](https://github.com/RoboMaster/RoboRTS)
   - 有一个抛物线弹道修正模型

7. 内附代码｜今年的大风车能量机关识别就是这么地so easy！
[内附代码｜今年的大风车能量机关识别就是这么地so easy！](https://mp.weixin.qq.com/s/3B-iR32GX7jfVyxvNQVRXw)



# 平衡步兵
----

## 轮式平衡步兵
1. 驱动轮电机：

2. 平衡底盘属性：
    | 等级 | 上限血量  | 底盘功率上限（W） |
    | ---- |   ----   | ---- |
    |  1  |    300    | 60 |
    |  2  |    400    | 80 |
    |  3  |    500    | 100 |
    枪口每秒冷却值提高50%。 
    最大供电总容量：265Wh


## 双足轮腿机器人
----
1. 关节电机：
   - [宇树A1]()
2. 驱动轮电机：
   - [凌控MF9025 16T]()

3. ascento两轮机器人

4. SK8O两轮机器人
