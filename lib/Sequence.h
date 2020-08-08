#ifndef _SEQUENCE_API_
#define _SEQUENCE_API_

#define SEQ_VIDEO_FRAME_DUR 1000

#include <stdint.h>

#include "Clip.h"
#include "LinkedListAPI.h"
#include "Util.h"

/**
    We are defining a Sequence structure.
    We know that a sequence is a list of several clips
    We are using a LinkedList to store the clips
    An iterator object is used to seek through clips
*/
typedef struct Sequence{
    
    //LinkedList containing clips
    List clips;

    //Iterator object to seek
    listIterator clips_iterator;

    AVRational video_timebase, audio_timebase;//Used to store timebases which is the unit of representation of timestamps

    double fps;
    int video_frame_dur;//Stores duration of single video frame

    int64_t current_frame_indx; //Current location of seek pointer in sequence

    int current_clip_indx; //Current clip index

} Sequence;

//Initialize new sequence and list of clips
//sample_rate stores sample rate of audio; Audio timebase = 1/sample_rate;
int init_sequence(Sequence* seq, double fps, int sample_rate);

//Initialize new sequence, list of clips.
//Uses a comapre function for InserttionSort
int init_sequence_compare(Sequence* seq, double fps, int sample_rate, int(*compareFunc)(const void* first, const void* second));

//Allocate clip in a sequence and use reference to the same vidContext for clips with same filename
//seq is for storing Sequence where clip will be added
//url is filename of clip
Clip* seq_allocate_clip(Sequence* seq, char* url);

//Get duration of sequence in terms of frames
int64_t get_sequence_dur(Sequence* seq);

//Insert clip in sequence in sorted order
void seq_add_clip(Sequence* seq, Clip* clip, int start_frame_index);

//Insert clip at end
void seq_append_clip(Sequence* seq, Clip* clip);

//Insert clip in sorted manner:
//Each clip is sorted in accordance to
//Date and time of file
//Original start presentation time stamp of clip
//Generates the sequence points for the clip
int seq_insert_clip_sorted(Sequence* seq, Clip* clip);

//Shift sequence presentation time stamp to next node
int shift_clips_aftr(Sequence* seq, Clip* clip);

//Delete a clip from a sequence and move all following clips forward (Ripple Delete)
int sequence_ripple_del_clip(Sequence* seq, Clip* clip);

//Convert sequence frame number to presentation time stamp
int64_t seq_frame_indx_pts(Sequence* seq, int frame_indx);

//Convert presentation timestamp to frame index in sequence
int seq_pts_to_frame_indx(Sequence* seq, int64_t pts);

//Cut a clip within a sequence so that it splits into two
int cut_clip(Sequence* seq, int frame_indx);

//Iterate overa ll clips in sequence to find the clip that contains current frame_index in sequence
int64_t find_clip_at_index(Sequence* seq, int frame_indx, Clip** found_clip);

//Determine is a sequence frame lies in a clip
//If [xxx] is a clip and |---| is videoContext: |---[xxx]------|
//0 would be returned on first x then 1 on second x and so on...
//Can be used to seek through clips
int64_t seq_frame_within_clip(Sequence* seq, Clip* clip, int frame_indx);

//Seek to exact frame in sequence
int sequence_seek(Sequence* seq, int frame_indx);

//Read our edited sequence
//AVPacket gives an output of packets
//close_clips when assigned true will ensure each clip is closed after its read cycle ends (and reopened if read again)
int sequence_read_packet(Sequence* seq, AVPacket* pkt, bool close_clips_flag);

//Sets start presentation time stamp of a clip in sequence
int move_clip(Sequence* seq, Clip* clip, int start_frame_indx);

//Sets presentation time stamp of a clip in sequence
//This is based of the start presentation time stamp unlike the start frame in above method
void move_clip_pts(Sequence* seq, Clip* clip, int64_t start_pts);

//Get current clip from sequence
//Seeks current position for next read
Clip* get_current_clip(Sequence* seq);

//Convert raw packet timestamp to sequence timestamp
int64_t audio_pkt_to_seq_ts(Sequence* seq, Clip* clip, int64_t orig_pkt_ts);

//Free the entire sequence along with the clips
void free_sequence(Sequence* seq);

//Get sequence string
char* print_sequence(Sequence* seq);

#endif