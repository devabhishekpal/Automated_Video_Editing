#ifndef _CLIP_ENCODE_
#define _CLIP_ENCODE_

#include "ClipDecoder.h"
#include "OutputContext.h"

//Reads packet from clip, decode it into AVFrame and re-encode it for output
int clip_encode_frame(OutputContext* oc, Clip* clip, AVPacket* pkt);

//Receive an ancoded packet given an output stream and handle the return value
int clip_receive_enc_packet(OutputContext* oc, OutputStream* os, Clip* clip, AVPacket* pkt);

//Sedn a frame to encoder
int clip_send_frame_to_encoder(OutputContext* oc, Clip* clip, AVPacket* pkt);

//Handle the return value from avcodec_send_frame()
int handle_send_frame(OutputContext* oc, Clip* clip, enum AVMediaType type, int ret, AVPacket* pkt);

#endif