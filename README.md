# Automated_Video_Editing
A video editing program that uses FFMpeg to decode modify and re-encode videos into new files.

Written in C, used libAV libraries.

https://ffmpeg.org/doxygen/trunk/group__lavc__core.html used for help with functions and structures of FFMpeg.


### Note: pts in the files means Presentation Time Stamp not pointers.


The whole program has two directories.
lib and src.

## lib
Contains the header files and required libraries
Header files were used to avoid writing so many function declarations in main sources


# lib directory headers descriptions.


## LinkedListAPI
Contains linkedList data structures and functions to implement various sequence operations and other linked List operations/functions like  pointers for nodes of clips and other video data, deletion of nodes, addition of nodes etc corresponding to sequence operations.



## OutputContext
Functions to write and process output like copying streams, parameters, writing sequences, setting muxers etc.

## OutputContextStructures
Contains data structures associated with the video files like Video Codec ID, frame height and width, Audio bitrates, FPS .etc.



## Clip
Stores reference to video file and its data in an editing sequence. Contains data structures for storing this data and perform related functions like opening, closing, setting bounds, setting start frame etc.

## ClipEncoder
Uses the ClipDecoder header to get raw AVFrames from clip and then encode it

## ClipDecoder
Contains functions that use the clip_read_packet from Clip.h to get packet from original video file, decode it and then return AVFrame to be used by ClipEncoder



## Sequence
Contains functions for editing sequences i.e deleting clips, cutting sequences, etc.

## SequenceEncoder
Uses the SequenceDecoder header to encode all frames from a list of clips in a sequence

## SequenceDecoder
Uses the ClipDecoder header to implement functions that read all decoded frames from a list of clips in a sequence



## Timebase
Contains timebase conversion functions and seek functions for VideoContext

## Util
Cotains utility functions like printing data, clearing strings etc.