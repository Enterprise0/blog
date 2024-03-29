# 嵌入式
----
## 基础
1. C语言：《the c programming language》，中文版《C程序设计语言》
    >重点理解：指针。

2. 51单片机（可以跳过，直接学32）：淘宝买一套开发板，大概六七十，可以先不买模块配件。淘宝卖家和b站都有教程，我看的b站的清翔。

3. stm32单片机（裸机开发，即不运行操作系统）：淘宝买一块最小系统板大概20，富哥可以买开发板（多加了一些配件），但是有些模块用不到，可以用到再买。淘宝和b站都有教程，个人推荐野火的教程，可能比较长但是有助于理解。比赛用hal库开发（stm32cubemx初始化配置很方便），可以直接学hal库。如果想学的深一点，可以先学标准库。
    >重点理解：寄存器，定时器，中断，iic、spi、usart、can等通信协议，有逻辑分析仪的话有助于理解，不用买太贵的。
    - 往届战队培训是c语言 -> arduino -> stm32，因为考虑到培训和校内赛时间，所以先学arduino，可以很快上手控制电机等模块。但是学不到单片机的重点（可以直接控制底层硬件），有精力可以自己先学32。
    - 渐渐的学会看原理图、数据手册和参考手册。

4. 自己动手做一辆平衡小车，不要买套件（太贵了），模块驱动可以cv网上代码，但是程序逻辑和PID参数要自己完成。如果独立完成，就可以入队直接调车了。
    >重点理解：PID算法和调试方法。

5. 多敲代码，很多东西多敲代码就记住了，学完C语言尽快上手单片机或其他工程项目（比如平衡小车，或者上网找些开源的小玩意）。早点摆脱考试的思维，有些知识一段时间不用就会忘记，但是要记得重点和做学习记录（推荐markdown格式），知道需要重新学习的时候可以在什么地方找到。尽早学会科学上网（翻墙），很多东西可以在google或百度上找到，优先google。习惯阅读英文文档，反正有翻译，记住专业名词就好。


## 进阶
1. RTOS实时操作系统：一般都是运行在嵌入式设备上的操作系统，RTOS适合复杂场景，可以运行多个任务。推荐野火的教程（FreeRTOS、uCOS-III、RT-Thread都可以），战队使用FreeRTOS，只要学其中一种就可以融会贯通。 

2. 相关算法：用的最多的是PID算法。其他算法比如滤波算法等需要用到再学，可能要学《信号与系统》、《数字信号处理》。

3. pcb：大学里用的最多的应该是AD（Altium Designer），但是电脑配置不好的话每次打开要等很久，画些小板子可以用kicad或者立创eda。b站都有教程。

4. 交叉编译：一般我们在x86平台（就是你的pc，intel或amd都是x86架构）上编译程序，然后把代码烧录到mcu上。但是mcu是arm架构或risc-v架构，一种架构的指令不能在另一种架构的机器上运行，所以需要交叉编译工具链。

5. make、cmake：用于编译生成可执行文件，说明文件间的依赖关系。大型工程可能需要自己写makefile，比较麻烦，可以用cmake生成。

6. 嵌入式linux：资料比较多的开发板是imx6ull，性能一般但是用来学习够用了，现在stm32mp157也挺火。教程有韦东山、正点原子和野火，韦东山做了很多年了，正点原子和野火最近也开始做了。这个我就不推荐了，因为板子比较贵，我也买不起:)。但是玩32是吃不上饭的，这个可以。
    >在ubuntu下玩嵌入式可以了解一下openocd和gdb。


# 拓展
----
可以先了解，有需要再学。有些书的各个章节是独立的，需要的时候再看，不用读完整本书。机械工业出版社的计算机领域的书（俗称黑皮书）有很多都是圣经，计算机领域优先看国外的书和课程，有时间和精力可以看英文版，国内的书大多是抄国外的。有些配套实验设计的很好。

1. linux：linux有不同发行版本，一般用ubuntu。可以装双系统（最大程度发挥电脑配置，但是初次安装麻烦）或者虚拟机（配置不好会卡）。

2. 推荐书籍和各领域圣经：
以下书籍可以在学习嵌入式时并行学习，或者对cs的兴趣大于嵌入式的可以直接看下面的书：
    - 《CSAPP》，中文版《深入理解计算机系统》。可以对计算机有一个大体的了解。boomlab即逆向工程实验比较出名，可以顺便学一下x86汇编和gdb调试。
    - 微机原理和计算机组成原理：黑皮书的《计算机组成原理》。一般微机原理讲的是8086计算机的组成和x86汇编，没什么书推荐，基本一样。
    - 操作系统：mit6.s081和进阶mit6.828（一定要做配套实验，很棒很经典，在qemu上仿真risc-v架构上运行的的os：xv6）、现代操作系统。
    - linux内核：《linux内核完全剖析》赵炯，分析linux0.12的内核源码，最早的比较完善的linux内核版本，现在的linux内核太大了。
    - 计算机网络：《计算机网络自顶向下》、《TCP/IP详解》（有3卷，我只看完1卷）。
    - 《程序员的自我修养：链接、装载与库》：大型工程项目用的软件都是各种IDE（集成开发环境），将编译、链接、装载等步骤抽象为一个个按钮，对于喜欢追根究底同时热爱计算机的初学者来说比较痛苦。这种时候可以google或百度，一步步学习更深的知识。这些知识不是什么屠龙术，但是可以产生更深远的影响，更多的是潜在的影响。

3. ros机器人操作系统：可以看古月居和官方教程，也可以看《ROS机器人开发实践》但是里面的版本感觉比较老，用C艹写的，官方教程python和C艹都有。

4. 飞控：自己搭一架四旋翼，微型四旋翼可以用32做主控，电机用空心杯电机，自己参考开源飞控写一个自己的飞控。我用的是最有名的开源飞控px4，但是不适合学习，玩无人机挺烧钱的，我炸了几次机就不敢乱飞了。

5. 视觉：主要分为传统视觉和机器视觉（用机器学习训练模型）。建议先学传统视觉，一般就这几个步骤：预处理、阈值分割、轮廓提取等，网上扒个opencv的代码（识别数字啥的）看一下就会了，想深入的话看一下冈萨雷斯的《数字图像处理》。机器学习的话自己去网上搜怎么学，如果说以上内容我都懂一点点的话，机器学习我可以说一窍不通，只是会调参。我不是很喜欢炼丹，而且本科生掌握的数学工具完全不够做机器学习。

6. 控制领域：《Feedback Control of dynamic Systems》中文版《动态系统的反馈控制》，也可以看哈工大的自动控制原理。还有现代控制理论，是基于状态空间的控制理论。进阶的话去知乎搜控制理论书籍。

7. robotics：《Introduction to Robotics》中文版机器人学导论。


# 关于RM和苍穹
----
记得我第一次了解到RM这比赛是高考完的暑假，当时我就想，上大学一定要打这个比赛。但是我进了工带后发现我们学校没有参加这比赛，然后去找金老师问我们学校可不可以打这个比赛，没想到金老师说他们正打算组一支队伍，我就加入了。当时工带有2支队伍，计院这边叫Zero One，工培中心的创客空间也有一支队伍叫苍穹，第一年因为疫情等原因2支队伍只参加了线上单项赛。在第一年里我就跟在学长学姐后面学习，连车都摸不着，而且基本上是自学。毕竟是第一年，学长学姐们都忙着调车，而且经费不足，那时候我都不知道C板是什么。

到了第二年，2支队伍打算打超级对抗赛就合并为苍穹。当时我想得是球球了让我碰下电机吧，让我调啥都行，哪怕最后获奖的时候没写上我也无所谓。让我没想到的是学长们让我做工程的电控，那应该是我大学里最开心的时候，机械没出车的时候我就玩C板，玩电机，虚空写代码，在机械出车前我就写好工程大部分功能了，虽然是从官方C板代码魔改的。寒假后终于出车了，并且好像快到中期答辩了，所以我下课了基本就是直接去工培调车。我忍不住吐槽一下，雕刻机实在是太吵了，工培那小房间也坐不下几个人，所以大家基本上都在房间外面调，但是大厅里也不容易，切板子的时候跟沙尘暴似的。过了中期答辩后工程决定做第二版车，我只能调调老工程，优化程序，逛下论坛看看其他学校的开源。第二版工程出车有点晚，好像比赛前一两周才装配好，救援和障碍块的PID还没调好就匆忙上场了，视觉也没时间加上去。基本上比赛那几天大家都在调车修车，特别是工程，调试时间太少了，我不敢睡。打完第一场比赛，好像继电器有问题，影响到了气动，记不太清了，只记得那天晚上我几乎没有睡觉。工程组的其他人也不敢睡，但是他们帮不上忙，因为是电控的问题，我就一边调车一边催他们睡觉。我调到了早上六点吧，睡了半个多小时。结果到赛场后精神不太好，感觉差点就remake了，接线的时候短路了，直接烧了一块C板，时间不够再换一块C板了（所以不要靠通宵来解决问题，效率太低容易出错）。所以第二场比赛工程没上，工程组除了操作手就坐在场外看直播，这场面我相信很多年后还忘不掉，这也是我大三没有继续再打的原因之一:)。打完第二场就确定不能出线了，收拾完就回去睡觉了，第三场是娱乐局，大家打的挺尽兴的。打完比赛在北京到处乱逛，也没啥心情。

回来后开会大家也没说我什么，可能是觉得一个星期调车确实太难了。但是哪怕过了一年，我每次回想起来都会喷自己做的跟shit一样。做的不行就该喷，人家强队都一样喷，我们就这点成绩还这么娇贵吗，那什么时候才能出线深圳。大三的时候yyh听到我不想干了就想接手工程，当时我觉得这学弟还不错而且一心打rm，而且工程这赛季这么拉还想过来，我就把工程全交给他了，因为我希望每一个rm魔怔人都有机会去到赛场。我现在打算考完研回来接着干吧，有什么地方能帮忙的我就帮一下，我也不在乎获奖上有没有我的名字，大二的时候不在乎，现在就更不在乎了。那张奖状已经证明我来过rm，见证了这一段难忘且有意义的经历。这就够了。


# 总结
----
以上仅供参考，有些我也只是了解一点皮毛（比如pcb和机器学习我就只学了一点皮毛，我认为至少会画高速板，炼丹至少会推导公式才算懂一点吧），但都是我认真读过并且写的挺好的书，大部分都是各领域圣经。可以google、百度或知乎XX怎么学、XX经典书籍、XX圣经等，再综合考虑。可以先看电子书，如果觉得对自己有用再买实体书支持作者，推荐2个电子书网站：google搜library genesis或zlibrary。
写这个的目的是因为我当年就希望能看到这样的文章，如果能对新人有一点帮助那自然是好的，如果觉得没用那也能图个乐。最后写上我在RM和苍穹的经历是因为我觉得很多人还不了解rm到底是一个什么样的比赛，我希望苍穹就是一个纯粹的打比赛的队伍，在这里没有什么学院之分，没有小团体，没有利益纠纷，大家一起造车、调车、修车，一起甩锅争吵道歉，一起熬夜通宵。当然培训和宣传要做好，强队也不只是强在技术。如果真心想要成为rm魔怔人，可以去论坛参考一下强队的培训（不是让你们放弃苍穹培训）。我知道有些人参加这比赛的一部分原因是加分，这个大家都理解，但我不希望只是为了加分，应该把对RM的热爱放在第一位。当然如果你只是为了加分来参加这比赛，还有时间认真调车那当我没说。所以获奖机制要搞好，如果天天来调车，哪怕是大一也应该有奖，如果不干活或者干的活不多就不应该拿奖甚至t出队伍。最后我希望大家在大学里少一点功利性，尽快找到感兴趣的方向，最后发现对RM不感兴趣也没关系，然后享受学习的乐趣，大学可能是你最自由的学习时间。


# 附录
----
1. [RM论坛](https://bbs.robomaster.com/portal.php)
2. [RM开源资料汇总](https://bbs.robomaster.com/forum.php?mod=viewthread&tid=6979&extra=page%3D1)
3. [机器人工程师学习计划](https://zhuanlan.zhihu.com/p/22266788)