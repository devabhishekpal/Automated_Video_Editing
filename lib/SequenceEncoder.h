#ifndef _SEQUENCE_ENCODE_
#define _SEQUENCE_ENCODE_

#include "SequenceDecoder.h"
#include "OutputContextStructures.h"

//Read encoded packets from sequence
int sequence_encode_frame(OutputContext* oc, Sequence* seq, AVPacket* pkt);

//Receive an encoded packet given an output stream, and handle return value
int seq_receive_enc_packet(OutputContext* oc, OutputStream* os, Sequence* seq, AVPacket* pkt);

//Send a frame to encoder
int seq_send_frame_to_encoder(OutputContext* oc, Sequence* seq, AVPacket* pkt);

//Handle the return from avcodec_send_frame().
//Used inside seq_send_frame_to_encoder()
//ret ---> return from avcodec_send_frame()
int seq_handle_send_frame(OutputContext* oc, Sequence* seq, enum AVMediaType type, int ret, AVPacket* pkt);

#endif