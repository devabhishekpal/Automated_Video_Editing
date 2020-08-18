#ifndef _VIDEOCONTEXT_API_
#define _VIDEOCONTEXT_API_

#include <stdio.h>
#include <libavformat/avformat.h>
#include <libavutil/pixdesc.h>
#include <stdbool.h>
#include <sys/stat.h>

enum PacketStreamType {DEC_STREAM_none = -1, DEC_STREAM_VIDEO, DEC_STREAM_AUDIO};

typedef struct VideoContext{
    //Open file info
    AVFormatContext* fmt_cntx;
    
    //Codecs for decoding
    AVCodec *video_codec, *audio_codec;

    //CodecContexts used for demuxing
    AVCodecContext *video_codec_cntx, *audio_codec_cntx;

    //Index of stream in fmt_cntx -> stream[index]
    int video_stream_index, audio_stream_index;

    //clip_read_frame() uses this functuon
    enum PacketStreamType last_decoder_packet_stream;
    
    //Store video context open or closed state
    bool open;

    //Stores file statuses like creation time and others
    struct stat file_stats;

    char *url; //filename

    AVRational video_time_base, audio_time_base;

    double fps;

    //pts of seek position absolute to original vid
    // it is >=original_start_pts and <original_end_pts
    int64_t seek_pts; 

    //Current pts. Stores start_frame_pts by default and changes while reading packets
    int64_t curr_pts;

    //Number of clips for video Context
    int clip_count;

}VideoContext;

#define VIDEO_CONTEXT_STREAM_TYPES_LEN 2

AVStream *get_video_stream(VideoContext *vid_cntx);
AVStream *get_audio_stream(VideoContext *vid_cntx);
AVRational get_video_time_base(VideoContext *vid_cntx);
AVRational get_audio_time_base(VideoContext *vid_cntx);

//Gives the allocated context containing format streams and codecs.
int open_video_context(VideoContext *vid_cntx, char *filename);

//Opens the format of context
int open_format_context(VideoContext *vid_cntx, char *filename);

//Finds the streams and its respective codecs
int open_codec_context(VideoContext *vid_cntx, enum AVMediaType type);

//Initialize video context
void init_video_context(VideoContext *vid_cntx);

//Frees the codecs and ffmpeg struct data inside VideoContext
void close_video_context(VideoContext *vid_cntx);

//Free all VideoContext data
void free_video_context(VideoContext **vc);

//Check if the AVRational is valid
bool isValid_rational(AVRational r);

//Print the data in a AVCodecContext
char *print_codec_context(AVCodecContext *c);

#endif