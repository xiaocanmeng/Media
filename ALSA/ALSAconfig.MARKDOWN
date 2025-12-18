# ALSA配置技巧笔记：aplay -L vs strace

## 问题现象

- 使用 `aplay -L` 能看到虚拟设备
- 使用 `strace -e open aplay` 看不到 `.asoundrc` 被读取

## 分析

- ALSA 惰性加载：只有调用了自定义设备名才会加载配置文件
- 没有 `.asoundrc` 或 `/etc/asound.conf` 的情况下也不会加载
- 有些配置被缓存了，导致 `strace` 看不到加载过程

## 验证方法

```bash
aplay -D myvirtual test.wav
strace -f -e open,openat aplay -D myvirtual test.wav 2>&1 | grep asound
