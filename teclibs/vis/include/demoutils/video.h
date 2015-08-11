// Demo utils, video and camera path utilities
// fabraham@tecgraf.puc-rio.br
// Aug 2010
#ifndef DU_VIDEO_H
#define DU_VIDEO_H

class VglCanvas;
class VglManipViewSurface;
class VglModeHandler;

/**
 * Initializes the path recording/playing system.
 * Record handler is added on mode handler 'mode_handler' using key F10.
 * Play handler is added on mode handler 'mode_handler' using key F11.
 * 'camera_path_file' is the camera path file.
 * 'videofps' specifies the video frame rate. should only be used when
 * recording the video.
 */
void DUPathInit (VglManipViewSurface* surface,
                 VglModeHandler* mode_handler,
                 const char* camera_path_file,
                 double videofps = -1.0);
/**
 * Initializes the video recording system.
 * Will begin recording when the play handler starts and will end when
 * it stops.
 *
 * 'temp_dir' specifies the temporary directory for video images.
 * 'base_file_name' specifies the base for the images file names.
 */
void DUVideoInit (VglCanvas* canvas,
                  const char* temp_dir,
                  const char* base_file_name);

#endif

