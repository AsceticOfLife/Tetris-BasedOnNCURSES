# GCC是什么

> **GCC不仅仅是一个C语言编译器**

## GNU计划

GNU全称 "GNU is  Not UNIX"，为抵制UNIX操作系统不开源而制定的计划，本意是创造一个开源、自由的操作系统。这个计划后续产生了一些软件，最著名的是Linux，也包括GCC。

## GCC

早期 GCC 的全拼为 GNU C Compiler，即 GUN 计划诞生的 C 语言编译器，显然最初 GCC 的定位确实只用于编译 C 语言。但经过这些年不断的迭代，GCC 的功能得到了很大的扩展，它不仅可以用来编译 C 语言程序，还可以处理 C++、Go、Objective -C 等多种编译语言编写的程序。与此同时，由于之前的 GNU C Compiler 已经无法完美诠释 GCC 的含义，所以其英文全称被重新定义为 GNU Compiler Collection，即 GNU 编译器套件。

几乎所有的 Linux 发行版也都默认安装有 GCC 编译器。

GCC 编译器没有我们熟悉的界面窗口，要想使用它，必须编写对应的 gcc 命令。

## GCC的组成部分以及使用到的软件

表 1 列出了 GCC 的各个部分，但它们也并不总是出现 的。有些部分是和语言相关的，所以如果没有安装某种特定语言，系统:中就不会出现相关的文件。

| 部分        | 描述                                                         |
| ----------- | ------------------------------------------------------------ |
| **c++**     | **gcc 的一个版木，默认语言设置为 C++，而且在连接的时候自动包含标准 C++ 库。这和 g++ 一样** |
| ccl         | 实际的C编译程序                                              |
| cclplus     | 实际的 C++ 编泽程序                                          |
| collect2    | 在不使用 GNU 连接程序的系统上，有必要运行 collect2 来产生特定的全局初始化代码（例如 C++ 的构造函数和析构函数） |
| configure   | GCC 源代码树根目录中的一个脚木。用于设置配置值和创建GCC 编译程序必需的 make 程序的描述文件 |
| crt0.o      | 这个初始化和结束代码是为每个系统定制的，而且也被编译进该文件，该文件然后会被连接到每个可执行文件中来执行必要的启动和终止程序 |
| cygwin1.dll | Windows 的共享库提供的 API，模拟 UNIX 系统调用               |
| f77         | 该驱动程序可用于编译 Fortran                                 |
| f771        | 实际的 Fortran 编译程序                                      |
| **g++**     | **gcc 的一个版木，默认语言设置为 C++，而且在连接的时候自动包含标准 C++ 库。这和 c++ 一样** |
| **gcc**     | **该驱动程序等同于执行编译程序和连接程序以产生需要的输出**   |
| gcj         | 该驱动程序用于编译 Java                                      |
| gnat1       | 实际的 Ada 编译程序                                          |
| gnatbind    | 一种工具，用于执行 Ada 语言绑定                              |
| gnatlink    | 一种工具，用于执行 Ada 语言连接                              |
| jc1         | 实际的 Java 编译程序                                         |
| libgcc      | 该库包含的例程被作为编泽程序的一部分，是因为它们可被连接到实际的可执行程序中。 它们是特殊的例程，连接到可执行程序，来执行基木的任务，例如浮点运算。这些库中的例程通常都是平台相关的 |
| libgcj      | 运行时库包含所有的核心 Java 类                               |
| libobjc     | 对所有 Objective-C 程序都必须的运行时库                      |
| libstdc++   | 运行时库，包括定义为标准语言一部分的所有的 C++ 类和函数      |

表 2 列出的软件和 GCC 协同工作，目的是实现编译过程。有些是很基本的（例如 as 和 Id），而其他一些则是非常有用但不是严格需要的。尽管这些工具中的很多都是各种 UNIX 系统的本地工具，但还是能够通过 GNU 包 binutils 得到大多数工具。

| 工具      | 描述                                                         |
| --------- | ------------------------------------------------------------ |
| addr2line | 给出一个可执行文件的内部地址，addr2line 使用文件中的调试信息将地址翻泽成源代码文 件名和行号。该程序是 binutils 包的一部分 |
| **ar**    | **这是一个程序，可通过从文档中增加、删除和析取文件来维护库文件。通常使用该工具是为了创建和管理连接程序使用的目标库文档。该程序是 binutils 包的一部分** |
| as        | GNU 汇编器。实际上它是一族汇编器，因为它可以被编泽或能够在各种不同平台上工作。 该程序是 binutils 包的一部分 |
| autoconf  | 产生的 shell 脚木自动配置源代码包去编泽某个特定版木的 UNIX   |
| c++filt   | 程序接受被 C++ 编泽程序转换过的名字（不是被重载的），而且将该名字翻泽成初始形式。 该程序是 binutils 包的一部分 |
| f2c       | 是 Fortran 到C的翻译程序。不是 GCC 的一部分                  |
| gcov      | gprof 使用的配置工具，用来确定程序运行的时候哪一部分耗时最大 |
| **gdb**   | **GNU 调试器，可用于检查程序运行时的值和行为**               |
| GNATS     | GNU 的调试跟踪系统（GNU Bug Tracking System）。一个跟踪 GCC 和其他 GNU 软件问题的在线系统 |
| gprof     | 该程序会监督编泽程序的执行过程，并报告程序中各个函数的运行时间，可以根据所提供 的配置文件来优化程序。该程序是 binutils 包的一部分 |
| ld        | GNU 连接程序。该程序将目标文件的集合组合成可执行程序。该程序是 binutils 包的一部 |
| libtool   | 一个基本库，支持 make 程序的描述文件使用的简化共享库用法的脚木 |
| **make**  | **一个工具程序，它会读 makefile 脚本来确定程序中的哪个部分需要编泽和连接，然后发布 必要的命令。它读出的脚本（叫做 makefile 或 Makefile）定义了文件关系和依赖关系** |
| nlmconv   | 将可重定位的目标文件转换成 NetWare 可加载模块（NetWare Loadable Module, NLM）。该 程序是 binutils 的一部分 |
| nm        | 列出目标文件中定义的符号。该程序是 binutils 包的一部分       |
| objcopy   | 将目标文件从一种二进制格式复制和翻译到另外一种。该程序是 binutils 包的一部分 |
| objdump   | 显示一个或多个目标文件中保存的多种不同信息。该程序是 binutils 包的一部分 |
| ranlib    | 创建和添加到 ar 文档的索引。该索引被 Id 使用来定位库中的模块。该程序是 binutils 包的一部分 |
| ratfor    | Ratfor 预处理程序可由 GCC 激活，但不是标准 GCC 发布版的一部分 |
| readelf   | 从 ELF 格式的目标文件显示信息。该程序是 binutils 包的一部分  |
| size      | 列出目标文件中每个部分的名字和尺寸。该程序是 binutils 包的一部分 |
| strings   | 浏览所有类型的文件，析取出用于显示的字符串。该程序是 binutils 包的一部分 |
| strip     | 从目标文件或文档库中去掉符号表，以及其他调试所需的信息。该程序是 binutils 包的一部 |
| vcg       | Ratfor 浏览器从文木文件中读取信息，并以图表形式显示它们。而 vcg 工具并不是 GCC 发布中的一部分，但 -dv 选项可被用来产生 vcg 可以理解的优化数据的格式 |
| windres   | Window 资源文件编泽程序。该程序是 binutils 包的一部分        |

## gcc和g++

# MinGW是什么

MinGW 是 Minimalist GNU for Windows 的缩写，**是 GCC 在 Windows 平台上的移植版本**。MinGW 提供了一组工具和库，使得开发人员可以**使用 GCC 和 GNU 工具集在 Windows 上进行本地编译**。MinGW 还包含一个轻量级的运行时库（CRT），它提供了 Windows API 的最小实现，以便在 Windows 上编译和链接本地代码。

# MingGW和GCC的区别

1.**MinGW 和 GCC 的主要区别在于它们的设计目标和用途。**GCC 是一个跨平台的编译器集合，可用于多种操作系统和处理器架构，包括 Windows。而 MinGW 是 GCC 在 Windows 平台上的移植版本，主要用于在 Windows 上本地编译 C 和 C++代码。

另外，MinGW 还提供了一个可选的 MSYS 组件，它允许在 Windows 上使用 Unix Shell 环境和 GNU 工具，类似于 Cygwin。这使得开发人员可以在 Windows 上开发类 Unix 应用程序，并使用 GNU 工具链构建和管理代码。

2.**体积大小。**GCC 包含了多种编译器，库和工具，因此它的体积比较大。而 MinGW 只包含了 GCC 和一些必需的库和工具，因此它的体积比较小。

3.**可用的库和工具。**GCC 可以与各种库和工具集成，可以使用 GNU 工具集和其他第三方库。而 MinGW 只能使用一些特定的库和工具，例如 WinAPI 和 MSVCRT 等。

4.**兼容性。**由于 MinGW 是 GCC 的一个移植版本，因此它可以使用 GCC 支持的大多数编程语言和特性。但是，由于 Windows 和 Linux 的一些差异，可能需要对代码进行一些调整才能在 MinGW 上正常工作。

5.**增量编译。**GCC 可以使用增量编译，它只会编译更改的部分，从而提高了编译速度。但是，MinGW 不支持增量编译，每次编译都需要重新编译整个程序。

总之，GCC 和 MinGW 都是非常流行的 C 和 C++编译器，可以用于不同的操作系统和处理器架构。选择使用哪一个取决于您的具体需求和使用场景。

# cygwin/gcc和MinGW

**cygwin/gcc完全可以和在linux下的gcc化做等号**，这个可以从boost库的划分中可以看出来端倪，cygwin下的gcc和linux下的gcc完全使用的是相同的Toolsets。

所以完全可以和linux一起同步更新gcc版本，而不用担心问题，并且在cygwin/gcc做的东西（不用win32的）可以无缝的用在linux下，没有任何问题。是在windows下开发linux程序的一个很好的选择。

但是 **在cygwin/gcc下编译出来的程序，在windows执行必须依赖cygwin1.dll，并且速度有些慢，** 如果不想依赖这个东西的化，必须在gcc的编译选项中加入-mno-cygwin。加入这个选项其实gcc编译器就会**自动的选择在安装cygwin/gcc时安上的mingw**,这个mingw就是gcc的一个交叉编译。

对于mingw作为gcc在windows上的一个实现，不像cygwin的gcc在一个模拟linux上运行，同时相当一部分linux的工具不能够使用。

根据以上的分析，**如果在windows开发linux程序，cygwin是很好的选择**。如果你开发的程序不介意有一个cygwin1.dll的话，也是可以选择cygwin的。如果你是想开发windows下的程序，还要必须用gcc的化，mingw是很好的一个选择。

# Cygwin

**Cygwin是一个可原生运行于Windows系统上的POSIX兼容环境。**

https://zhuanlan.zhihu.com/p/56692626



# WSL：“Windows Subsystem for Linux”

https://zhuanlan.zhihu.com/p/34885179















