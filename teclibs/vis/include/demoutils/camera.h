// Demo utils, camera utilities
// fabraham@tecgraf.puc-rio.br
// Aug 2010
#ifndef DU_CAMERA_H
#define DU_CAMERA_H

class VglCamera;
class VglViewSurface;

/**
 * Initializes the application camera with the current camera index (usually 0).
 * Visualization surface must be passed (canvas, subcanvas).
 */
void DUCameraLoadInit (VglCamera* camera, VglViewSurface* surface);
/**
 * Saves the current camera to the current index (see DUCameraSetIndex).
 */
void DUCameraWrite (VglCamera* camera);
/**
 * Reads the saved camera of the current index (see DUCameraSetIndex).
 */
void DUCameraRead (VglCamera* camera, VglViewSurface* surface);
/**
 * Specifies the current camera index.
 */
void DUCameraSetIndex (int index);

#endif

