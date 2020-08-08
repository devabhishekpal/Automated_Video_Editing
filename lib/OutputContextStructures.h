#ifndef _OUTPUT_CONTEXT_STRUCTURES_
#define _OUTPUT_CONTEXT_STRUCTURES_

#include <stdio.h>
#include <stdbool.h>
#include <libavformat/avformat.h>
#include <libavutil/timestamp.h>
#include <libavcodec/avcodec.h>

#include <libavutil/opt.h>


//Video Output parameters set using this structure
typedef struct VideoOutputParams{
    enum AVCodecID codec_id; //identify syntax and semantics of bitstream
    enum AVPixelFormat pixel_fmt; //Gives the pixel format for video is Palette img data

    int frame_w, frame_h;
    int64_t bit_rate; //store bitrate
    int fps; //get timebase of (1/fps)

} VideoOutputParams;

typedef struct AudioOutputParams{
    enum AVCodecID codec_id;
    enum AVSampleFormat sample_fmt; //AudioSample formats

    int64_t bit_rate;
    int sample_rate;
    uint64_t channel_layout;
} AudioOutputParams;

typedef struct OutputParams{
    VideoOutputParams video;
    AudioOutputParams audio;
    char* filename;
} OutputParams;


typedef struct OutputStream{
    AVCodec* codec;
    AVCodecContext* codec_cntx;
    AVStream* stream;
    bool flush_processing, flush_done;    
} OutputStream;

typedef struct OutputContext{
    AVFormatContext* frmt_cntx;
    OutputStream video, audio;
    AVFrame* bufferFrame; //decoded (raw) audio or video data
    enum AVMediaType last_enc_frame_type;
} OutputContext;

#endif