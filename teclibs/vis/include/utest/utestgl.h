#ifndef UTESTGL_H
#define UTESTGL_H

#ifndef UTESTGL_DLL
# ifndef TEC_DLL
#  define UTESTGLAPI
# else
#  define UTESTGLAPI __declspec(dllimport)
# endif
#else
# define UTESTGLAPI __declspec(dllexport)
#endif

struct UTestGL;

/**
 * Initializes an OpenGL test.
 * 'printlabel', if different than NULL, specifies a label tag 
 * to be printed before useful messages. Example:
 * PRINTLABEL: initializing random number generator (seed=0)
 *
 * 'testname' specifies a name for the test being run.
 * 'readseedfile' specifies if the previous used seed must be used. if false,
 * a new seed is created and saved to the file 'testname.seed'.
 *
 * 'w' and 'h' specify the OpenGL context dimensions.
 *
 * 'depth_buffer', if true, specifies a depth buffer for the context.
 * 'alpha_buffer', if true, specifies an alpha buffer for the context.
 * 'stencil_buffer', if true, specifies a stencil buffer for the context.
 *
 * Returns a UTestGL structure if successful, NULL otherwise.
 */
UTESTGLAPI UTestGL* utestgl_initialize (const char *printlabel,
                                        const char *testname,
                                        bool readseedfile,
                                        int w,
                                        int h,
                                        bool depth_buffer,
                                        bool alpha_buffer,
                                        bool stencil_buffer);

/**
 * Executes a test with name 'testname'.
 *
 * The current framebuffer contents are read and compared with a previously
 * accepted result from call of this checkpoint.
 *
 * The checkpoint is identified by the tag 'checkpointname'.
 *
 * 'interactive' specifies if messages can be displaying requesting the user
 * to accept or deny different images.
 *
 * If on interactive mode, 'show_diff_image' requests the visualization
 * of a difference image.
 *
 * If on interactive mode, 'show_read_image' requests the visualization
 * of the read image.
 *
 * If on interactive mode, 'show_original_image' requests the visualization
 * of the 'correct' image.
 *
 * This functions prints an error message and exits with the '1' error code
 * if the check point image is rejected.
 */
UTESTGLAPI void utestgl_checkpoint (UTestGL* utestgl,
                                    const char* testname,
                                    const char* checkpointname,
                                    bool interactive,
                                    bool show_diff_image,
                                    bool show_read_image,
                                    bool show_original_image);

/**
 * Finalizes an OpenGL test.
 */
UTESTGLAPI void utestgl_destroy (UTestGL* utestgl);

#endif

