#ifndef _SEQUENCE_DECODE_
#define _SEQUENCE_DECODE_

#include "Sequence.h"
#include "ClipDecoder.h"

//Read decoded frame from editing sequence
//close_clips_flag when true, closes clips after reading
int sequence_read_frame(Sequence* seq, AVFrame* frame, enum AVMediaType* frame_type, bool close_clips_flag);

//Clear fields on AVFrame from decoding
void clear_frame_decoding_garbage(AVFrame* f);

#endif