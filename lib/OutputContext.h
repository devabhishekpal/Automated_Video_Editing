#ifndef _OUTPUT_CONTEXT_API_
#define _OUTPUT_CONTEXT_API_

#include <stdio.h>
#include <libavformat/avformat.h>
#include <libavutil/timestamp.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>

#include "OutputContextStructures.h"
#include "SequenceEncoder.h"

//Initialize Output Streams
void init_output_stream(OutputStream* os);

//Initialize OutputContext Structures
void init_video_output(OutputContext* oc);

//Used to add stream and allocate codec for OutputStream
int add_stream(OutputContext* oc, OutputStream* os, enum AVCodecID codec_id);

//Set video codec and muxer params from VideoOutputParams
int set_video_codec_params(OutputContext* oc, VideoOutputParams* op);

//Set audio codec and muxer params from AudioOutputParams
int set_audio_codec_params(OutputContext* oc, AudioOutputParams* op);

//Set muxer paramers by copying
int set_muxer_params(OutputContext* oc, OutputStream* os, AVCodecContext* c); //AVCodecContext is used to associate with audio/video stream

//Open file for video output
//op is for storing video/audio codec/muxers
//Sequence is used to derive time_base for codec context
int open_video_output(OutputContext* oc, OutputParams* op, Sequence* seq);

//Open output file, write sequence frames and close file
int write_sequence(Sequence* seq, OutputParams* op);

//Write entire sequence to o/p file
int write_sequence_frame(OutputContext* oc, Sequence* seq);

//Set output params to given audio and video params
int set_output_params(OutputParams* op, char* filename, VideoOutputParams vp, AudioOutputParams ap);

//Copy the relevant codec context params from decoder to VideoOutputParams structure for encoding
//Also allow copying of clips decoder settings to encoder context
void set_video_output_params(VideoOutputParams* op, AVCodecContext* c);

//Copy the relevant codec context params from decoder to AudioOutputParams structure for encoding
void set_audio_output_params(AudioOutputParams* op, AVCodecContext* c);

//Free OutputParams internal data
void free_output_params(OutputParams* op);

//Close the codec context within output stream
void close_output_stream(OutputStream* os);

//Close video output file
//trailer_flag when set true, traler will attempt to be written
int close_video_output(OutputContext* out_cntx, bool trailer_flag);

#endif