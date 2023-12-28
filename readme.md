**Building the tutorials** section for your platform: [Linux](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html#InstallingonLinux-Build), [Mac OS X](https://gstreamer.freedesktop.org/documentation/installing/on-mac-osx.html#InstallingonMacOSX-Build) or [Windows](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html#InstallingonWindows-Build), or use this specific command on Linux:

gcc basic-tutorial-1.c -o basic-tutorial-1 `pkg-config --cflags --libs gstreamer-1.0`
