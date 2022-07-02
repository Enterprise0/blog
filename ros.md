# ros基础
----

## 下载开源功能包
```bash
sudo apt install ros-noetic-PACKAGE
```
PACKAGE为功能包名称。

## 创建功能包
```bash
cd ~/catkin_ws/src # 功能包要放在工作空间work space的src文件夹下
catkin_create_pkg <package_name> [depend1] [depend2] ...
cd ~/catkin_ws/; catkin_make
```
depend为其他依赖的功能包。

