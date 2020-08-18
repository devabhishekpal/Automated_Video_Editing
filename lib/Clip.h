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

//Get absolute pts for clip i.e the pts of original Video File
int64_t get_abs_clip_pts(Clip* clip, int64_t relative_pts);

//Convert absolute pts from VideoContext into a pts relative to clip bounds
int64_t cov_clip_pts_relative(Clip* clip, int64_t abs_pts);

//Convert raw video packet timestamp into clip relative audio pts
int64_t clip_ts_audio(Clip* clip, int64_t pkt_ts);

//Get index of last frame in clip
int64_t get_clip_end_frame_index(Clip* clip);

//Determine if VideoContext is out of clip bounds
//This case means that the VideoContext was used by another clip and needs to be reset on the current clip with seek_clip_pts(clip, 0)
bool is_vc_outof_bounds(Clip* clip);

//Detects if we are done reading the current packet stream
bool done_read_curr_pkt_stream(Clip* clip, AVPacket* pkt);

//Reads a single AVPacket from clip
int clip_read_packet(Clip* clip, AVPacket* pkt);

//Reset all internal flags and packet couter to allow another read cycle
int reset_packet_counter(Clip* clip);

//Set internal variables used to read stream data
void init_internal_vars(Clip* clip);

//Compare two clips based on pts
int64_t compare_clips(Clip* first, Clip* second);

//Compare clips by:
//First using date and time
//Then by original start pts
int64_t compare_clips_sequential(Clip* first, Clip* second);

//Get timebase of clip video stream
AVRational get_clip_video_timebase(Clip* clip);

//Get timebase of clip audio stream
AVRational get_clip_audio_timebase(Clip* clip);

//Get video stream from clip
AVStream* get_clip_video_stream(Clip* clip);

//Get audio stream from clip
AVStream* get_clip_audio_stream(Clip* clip);

//Get codec params of clip video stream
AVCodecParameters* get_clip_video_param(Clip* clip);

//Get codec params of clip audio stream
AVCodecParameters* get_clip_audio_param(Clip* clip);

//Cut a clip
//oc ---> Original Clip to be cut
//sc ---> newly created clip with set bounds
int cut_clip_internal(Clip* oc, int64_t pts, Clip** sc);

//Free clip data and allocated space
void free_clip(Clip** clip);

//Get data about clip as a string
char* list_print_clip(void* toBePrinted);

//Free clip memory and all its data if it was allocated on heap
void list_delete_clip(void* toBeDeleted);

//Compare two clips within a linked list
int list_compare_clips(const void* first, const void* second);

//Compare two clips in a linked list by date and time then by original start pts
//Orders clips by time they were shot
int list_compare_clips_sequential(const void* first, const void* second);

#endif