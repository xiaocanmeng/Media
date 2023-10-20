extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#include <iostream>

int main() {
    const int width = 640;
    const int height = 480;
    const AVRational dst_fps = {30, 1};

    // 初始化 libavformat 并注册所有的 muxers, demuxers 和协议
    avformat_network_init();

    // 创建一个新的 AVFormatContext
    AVFormatContext* oc = avformat_alloc_context();
    oc->oformat = av_guess_format("mp4", NULL, NULL);
    if (!oc->oformat) {
        return 1;
    }

    // 创建一个新的视频流
    AVStream* stream = avformat_new_stream(oc, NULL);
    if (!stream) {
        return 1;
    }

    // 设置编码器参数
    AVCodec const * codec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);
    if (!codec) {
        return 1;
    }

    AVCodecContext* c = avcodec_alloc_context3(codec);
    c->codec_id = AV_CODEC_ID_MPEG4;
    c->bit_rate = 400000;
    c->width = width;
    c->height = height;
    c->time_base = av_inv_q(dst_fps);
    c->gop_size = 12;
    c->pix_fmt = AV_PIX_FMT_YUV420P;

    // 打开编码器
    if (avcodec_open2(c, codec, NULL) < 0) {
        return 1;
    }

    // 将编码器上下文复制到流中
    int error_code = avcodec_parameters_from_context(stream->codecpar, c);
    if (error_code < 0) {
        std::cout<<"avcodec_parameters_from_context error";
        return error_code;
    // 处理错误
    }
    // 打开输出文件
    if (!(oc->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&oc->pb, "output.mp4", AVIO_FLAG_WRITE) < 0) {
            return 1;
        }
    }

    // 写文件头
    avformat_write_header(oc, NULL);

    // 编码视频
    AVFrame* frame = av_frame_alloc();
    frame->format = c->pix_fmt;
    frame->width = c->width;
    frame->height = c->height;
    int ret = av_frame_get_buffer(frame, 32);
    if (ret < 0) {
        return 1;
    }

    AVPacket* pkt = av_packet_alloc();
    for (int i = 0; i < 100; i++) {
        ret = av_frame_make_writable(frame);
        if (ret < 0) {
            return 1;
        }

        // 填充 Y, Cb, Cr 数据
        for (int y = 0; y < c->height; y++) {
            for (int x = 0; x < c->width; x++) {
                frame->data[0][y * frame->linesize[0] + x] = x + y + i * 3;
            }
        }

        for (int y = 0; y < c->height / 2; y++) {
            for (int x = 0; x < c->width / 2; x++) {
                frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
                frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
            }
        }

        frame->pts = i;

        // 编码图像
        ret = avcodec_send_frame(c, frame);
        if (ret < 0) {
            return 1;
        }

        // 获取编码后的数据
        ret = avcodec_receive_packet(c, pkt);
        if (ret < 0) {
            return 1;
        }

        // 写入新的帧
        av_interleaved_write_frame(oc, pkt);
    }

    // 写文件尾
    av_write_trailer(oc);

    // 释放资源
    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);

    if (!(oc->oformat->flags & AVFMT_NOFILE)) {
        avio_closep(&oc->pb);
    }

    avformat_free_context(oc);

    return 0;
}
