// cmg.h
// Tecgraf/PUC-Rio
// earp@tecgraf.puc-rio.br
// Jul 2006

#ifndef CMG_H
#define CMG_H

#define CMG_DEFAULT_DICTFILE "data/dcta201010.dat" // current program dictionary file.
                                                   // to be concatenated with INSTALLDIR/app/geresim.

/**
 * Initializes the CMG reservoir model file format opener.
 * Returns true if successful, false if dictionary is invalid or could not be found.
 */
bool gposcmg_init (const char *dictfile);

void gposcmg_release ();

#endif
