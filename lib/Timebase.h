#ifndef _TIMEBASE_API_
#define _TIMEBASE_API_

//Set seek function to seek only I frames before our desired frame
#define FFMPEG_SEEK_FLAG AVSEEK_FLAG_BACKWARD

#include "VideoContext.h"
#include <string.h>

//Check if AVRational is valid
bool valid_rational(AVRational r);

//Convert video pts into frame index
int64_t conv_video_pts(VideoContext* vid_cntx, int64_t pts);

//Get the video frame at given index
int64_t get_video_frame_pts(VideoContext* vid_cntx, int frame_index);

//Video seeking functions...
int seek_video(VideoContext* vid_cntx, int frame_index);
int seek_video_pts(VideoContext* vid_cntx, int frame_index);

//Get audio frame at given index
int64_t get_audio_frame(VideoContext* vid_cntx, int frame_index);

int64_t cov_video_to_audio_pts(VideoContext* video_cntx, int frame_index);

//Print AVRational Structure
char* print_time_base(AVRational* tb);

#endif