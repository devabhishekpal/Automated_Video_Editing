# Automated_Video_Editing
A video editing program that uses FFMpeg to decode modify and re-encode videos into new files.

Written in C, used libAV libraries.

https://ffmpeg.org/doxygen/trunk/group__lavc__core.html used for help with functions and structures of FFMpeg.


The whole program has two directories.
lib and src.

##lib
Contains the header files and required libraries
Header files were used to avoid writing so many function declarations in main sources


#lib directory headers descriptions.


##OutputContext
Functions to write and process output like copying streams, parameters, writing sequences, setting muxers etc.


##OutputContextStructures
Contains data structures associated with the video files like Video Codec ID, frame height and width, Audio bitrates, FPS .etc.


##Sequence
Contains functions for editing sequences i.e deleting clips, cutting sequences, etc.

##LinkedListAPI
Contains linkedList data structures and functions to implement various sequence operations and other linked List operations/functions like  pointers for nodes of clips and other video data, deletion of nodes, addition of nodes etc corresponding to sequence operations.

##Util
Cotains utility functions like printing data, clearing strings etc.

