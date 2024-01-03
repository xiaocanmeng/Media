video-sink=autovideosink

**Building the tutorials** section for your platform: [Linux](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html#InstallingonLinux-Build), [Mac OS X](https://gstreamer.freedesktop.org/documentation/installing/on-mac-osx.html#InstallingonMacOSX-Build) or [Windows](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html#InstallingonWindows-Build), or use this specific command on Linux:

gcc basic-tutorial-1.c -o basic-tutorial-1 `pkg-config --cflags --libs gstreamer-1.0`

gst-launch-1.0 playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm video-sink=autovideosink

gst-launch-1.0 playbin uri=file:///home/dev/work/Media/data/190101000052DCF0.mp4

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

如果报错
0:00:00.012819894 12325 0x55d855bd5840 WARN     GST_ELEMENT_FACTORY gstelementfactory.c:458:gst_element_factory_make: no such element factory "gtkglsink"!
Could not create gtkglsink, falling back to gtksink.
0:00:00.012854044 12325 0x55d855bd5840 WARN     GST_ELEMENT_FACTORY gstelementfactory.c:458:gst_element_factory_make: no such element factory "gtksink"!
请安装gstreamer1.0-gtk3
sudo apt install gstreamer1.0-gtk3