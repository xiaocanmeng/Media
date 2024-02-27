### 测试gstreamer安装成功

**Building the tutorials** section for your platform: [Linux](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html#InstallingonLinux-Build), [Mac OS X](https://gstreamer.freedesktop.org/documentation/installing/on-mac-osx.html#InstallingonMacOSX-Build) or [Windows](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html#InstallingonWindows-Build), or use this specific command on Linux:

gcc basic-tutorial-1.c -o basic-tutorial-1 `pkg-config --cflags --libs gstreamer-1.0`

gst-launch-1.0 playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm video-sink=autovideosink

### 查看调试输出：

GStreamer 将在控制台输出详细的调试信息。这些信息可能包含有关加载插件、媒体流处理和错误的详细信息。

### 调试级别：

`GST_DEBUG` 环境变量的值可以设置为不同的级别，例如：

* `0`: 无调试信息。
* `1`: 错误。
* `2`: 警告。
* `3`: 消息。
* `4`: 调试。
* `5`: 微调试。

export GST_DEBUG=3

### gtk3报错问题

0:00:00.012819894 12325 0x55d855bd5840 WARN     GST_ELEMENT_FACTORY gstelementfactory.c:458:gst_element_factory_make: no such element factory "gtkglsink"!
Could not create gtkglsink, falling back to gtksink.
0:00:00.012854044 12325 0x55d855bd5840 WARN     GST_ELEMENT_FACTORY gstelementfactory.c:458:gst_element_factory_make: no such element factory "gtksink"!
**请安装gstreamer1.0-gtk3
sudo apt install gstreamer1.0-gtk3**

### 在终端执行编译命令并将输出保存到文件（例如 build_log.txt）

**make > build_log.txt 2>&1**

如果没有 `2>&1`，则只有标准输出会被重定向到文件，而标准错误将会继续显示在终端上。这就意味着你在 `build_log.txt` 文件中只能看到编译过程中的标准输出，而标准错误信息仍然会在终端上显示。

使用 `2>&1` 的目的是将标准错误与标准输出合并到同一个文件中，这样你可以在一个文件中查看所有输出信息，包括标准错误。


### g++ 

编译并链接一个源文件，生成可执行文件

g++ my_program.cpp -o my_program

###### 仅编译源文件，生成目标文件

g++ -c my_program.cpp -o my_program.o

编译多个源文件，链接生成可执行文件

g++ file1.cpp file2.cpp -o my_program

指定C++标准版本

g++ -std=c++11 my_program.cpp -o my_program
