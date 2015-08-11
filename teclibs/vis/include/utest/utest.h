#ifndef UTEST_H
#define UTEST_H

#ifndef UTEST_DLL
# ifndef TEC_DLL
#  define UTESTAPI
# else
#  define UTESTAPI __declspec(dllimport)
# endif
#else
# define UTESTAPI __declspec(dllexport)
#endif

/**
 * Initializes the testing library.
 * 'printlabel' specifies a label tag to be printed before useful messages.
 * Example:
 * PRINTLABEL: initializing random number generator (seed=0)
 *
 * 'testname' specifies a name for the test being run.
 * 'readseedfile' specifies if the previous used seed must be used. if false,
 * a new seed is created and saved to the file 'testname.seed'.
 *
 * Returns true if successful, false otherwise.
 */
UTESTAPI bool utest_initialize (const char *printlabel, const char *testname, bool readseedfile);

#endif

