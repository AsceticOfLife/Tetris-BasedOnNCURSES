# 项目介绍

项目目的：尝试学习开源C++项目，即github上开源的tinytetris项目

项目内容：基于ncursesw库（2023年windows版本，mingw-20230423）完成一个俄罗斯方块游戏

整体设计框架来自于tinytetris项目，但是作者taylorconor虽然写的是c++文件，却只使用了C++四大组成部分中的C部分。因此为了锻炼C++语言中的C和Object-Oriented C++部分的语法掌握和能力，笔者重新设计了这个小游戏，主要是使用Object-Oriented C++部分的知识，以及对于游戏中的逻辑做了部分修改。

# 依赖库

这个项目需要可视化，因此使用了ncurses库，并且由于过去的ncurses库基本都是linux平台的，所以使用起来不是很方便。

所幸的是在2023年，ncurses发布了windows版本下的库，笔者采用的是mingw编译器版本。

使用上与linux版本几乎没有任何区别。

# 文件夹结构安排

作者将ncurses库均放在项目文件夹下（而非编译器所在目录），一方面是为了保护编译器文件夹的原始状态，另一方面也是提醒笔者这些文件是专用于本项目。这样导致的一个问题是采用g++编译命令会稍微有些复杂。笔者后续会更新makefile或者CMakeLists。

ncursesw：此文件夹下是ncurses库（window版本）的所有头文件。

lib：此文件夹下是库的静态链接。（为什么要有静态链接和动态链接库在md文件中有说明）

Mytetris：此文件夹是程序类实现。

所有的dll文件和config文件：为ncurses动态链接库。

code.cpp：主程序文件

其它就是一些杂项，比如目标文件、md文件等。

# 编译和运行

## 直接运行exe文件

需要在当前目录下运行exe文件，因为动态链接库都在当前文件夹下，并且笔者编译时也是在当前文件夹下编译的。因此在其它文件夹下运行会找不到动态链接库而失败。

## 编译命令

```c++
g++ -c ./Mytetris/chunk.cpp
g++ -c ./Mytetris/mytetris.cpp
g++ code.cpp chunk.o mytetris.o -L ./lib -l ncursesw -o code.exe
```

# 等待更新

1.需要更新makefile文件或者CMakeLists.txt文件使得编译命令更简单。（但是由于库文件的版本限制还是不能跨平台）

2.对于类设计的细化和修改，贯彻面向对象思想。











