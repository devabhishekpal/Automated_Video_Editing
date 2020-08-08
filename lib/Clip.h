#ifndef _CLIP_API_
#define _CLIP_API_

#include "VideoContext.h"
#include "Timebase.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Clip data structure stores a reference to a video file and its data within an editing sequence.
 * VideoContext represents original file on disk, allocated using open_video()
 */
typedef struct Clip{
   VideoContext* vid_cntx;

   //pts for original packets to find start and end frames
   int64_t orig_start_pts, orig_end_pts;

   //Position of clip in the sequence to be edited. pts is first and last packet in clip
   int64_t start_pts, end_pts;

   //Used for internal function, clip_read_packet
   bool done_reading_video, done_reading_audio;

   //Used by clip_read_frame to count
   int64_t frame_index;

} Clip;

//Alloc a new clip pointing to same VideoContext as Clip param
Clip* copy_clip_vc(Clip* src);

//Alloc new Clip without a VideoContext
Clip* alloc_clip_internal();

//Alloc clip on heap, initialize default values and open the clip.
//Clip is opened when first created to allow setting of default values like clip->orig_end_pts, clip->orig_start_pts by reading file contents
//url is used to refer to filename
Clip* alloc_clip(char* url);

//Initialize clip without VideoContext
int init_clip_internal(Clip* clip);

//Initialize clip with new VideoContext
int init_clip(Clip* clip, char* url);

//Open clip(VideoContext) to read data from original file
//Close clip
int open_clip(Clip* clip);
int open_clip_bounds(Clip* clip, int64_t start_index, int64_t end_index);
void close_clip(Clip* clip);

//Initialize clip object with start and end points
//start_index --> original video file start frame number
//end_index --> original video file end frame number
int set_clip_bounds(Clip* clip, int64_t start_index, int64_t end_index);

//Initialize clip object with start and end point
//This uses pts instead of frames to set bounds
int set_clip_bounds_pts(Clip* clip, int64_t orig_start_pts, int64_t orig_end_pts);

int set_clip_start_frame(Clip* clip, int64_t frame_index);

int set_clip_start(Clip* clip, int64_t pts); //Use pts

int set_clip_end_frame(Clip* clip, int64_t frame_index);

int set_clip_end(Clip* clip, int64_t pts); //Use pts instead of frame index

//Seek to clip frame relative to clip
int seek_clip(Clip* clip, int64_t seekframe_index);

//Seek to clip frame relative to clip using pts
int seek_clip_pts(Clip* clip, int64_t pts);

//Get absolute pts from VideoContext into a pts relative to the Clip bounds


#endif