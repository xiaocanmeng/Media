安装 Audacity，用于查看.wav文件

gst-launch-1.0 alsasrc device=MIC1_SWSRC_IN num-buffers=1000 ! queue ! audioconvert ! wavenc ! filesink location=test.wav
gst-launch-1.0 alsasrc num-buffers=1000 ! queue ! audioconvert ! wavenc ! filesink location=test.wav
arecord -D "plughw:0,62" -f S16_LE -r 16000 -d 5 -t wav file.wav