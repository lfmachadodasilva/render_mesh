#ifndef UGL_VIDEO_H
#define UGL_VIDEO_H

#include "uglimavi.h"

UGLIMAVIAPI bool uglimavi_save_video (const char *video_filename, const char* tempdir, const char *image_base_filename, const char *extension, float fps, float quality, const char *codec, int lastimageindex);

#endif
