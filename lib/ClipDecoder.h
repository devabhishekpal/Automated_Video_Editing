#ifndef _CLIP_DECODE_
#define _CLIP_DECODE_

#include "Clip.h"

//Read clip packet and decode it
//frame ---> output of decoded packet between clip bounds
int clip_read_frame(Clip* clip, AVFrame* frame, enum AVMediaType* frame_type);

//Used to detect is frame is before seek
//Returns true is frame is before seek position else returns false
//frame ---> decoded frame
bool frame_before_seek(Clip* clip, AVFrame* frame, enum AVMediaType type);

//Handle receive frame return, deciding to send another packet
int handle_receive_frame(Clip* clip, AVFrame* frame, int ret, enum AVMediaType* type);

//Sends a single clip packet and get the decoded frame
int clip_send_packet_get_frame(Clip* clip, AVFrame* frame, enum AVMediaType* type);

//Send clip packet to decoder
int clip_send_packet(Clip* clip);

#endif