<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [简介](#简介)
- [01-basic](#01-basic)
  - [含头文件和源文件的cmake](#含头文件和源文件的cmake)
  - [library](#library)
  - [install](#install)
  - [参考](#参考)

<!-- /code_chunk_output -->


# 简介
----
记录一些cmake的语法，老是忘记。

# 01-basic
----

## 含头文件和源文件的cmake
```
cmake_minimum_required(VERSION 3.5)

# Set the project name
# 有利于在多个文件里寻找cmake变量
project (hello_headers)

# 设置变量，源文件列表
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

# Add an executable with the above sources
# 第一个参数是生成的可执行文件名称，第二个参数是源文件列表
add_executable(hello_headers ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
# 最好把头文件放在一个子文件夹下，方便
target_include_directories(hello_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
```

- [cmake常用变量和常用环境变量](https://www.cnblogs.com/linuxAndMcu/p/10670591.html)
- private：该目录被添加到该target（可执行文件）的包含目录中
- interface：该目录被添加到任何链接此库的包含目录中
- public：private和interface的集合

## library
- 创建库
	```
	# STATIC从源文件列表中生成libhello_library.a
	# SHARED从源文件列表中生成libhello_library.so
	add_library(hello_library STATIC
	    src/Hello.cpp
	)
	```

- 链接库
	```
	add_executable(hello_binary
    	src/main.cpp
	)
	
	target_link_libraries( hello_binary
	    PRIVATE
	        hello_library
	)
	```

## install
----
命令行输入以下指令改变`make install`的下载目的目录的相对路径前缀
```bash
$cmake -DCMAKE_INSTALL_PREFIX=
```
cmake语法
```
install (TARGETS
    DESTINATION bin
    LIBRARY DESTINATION lib)
```
- TARGETS用于下载可执行二进制文件、静态库、动态库等，还可以下载FILES、DIRECTORY、SCRIPT、CODE等。
- TARGETS等后面时要下载的文件源路径。

在install时执行cmake代码，打印提示语句：
```
install(CODE "MESSAGE(\"Sample install message.\")")
```

可以在`make install`指令指定下载路径
```bash
$make install DESTDIR=<path>
```
- 下载路径在`${DESTDIR}/${CMAKE_INSTALL_PREFIX}`

## 参考
- [cmake examples](https://github.com/ttroy50/cmake-examples)
- [modern cmake](https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html)