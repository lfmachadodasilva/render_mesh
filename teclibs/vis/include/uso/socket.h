// Socket utils
// fabraham@tecgraf.puc-rio.br
// Feb 2005

#ifndef USO_SOCKET_H
#define USO_SOCKET_H

#include <float.h>

/**
 * 'nread', 'nwrite' and 'nexcept' are size of the sockets array passed.
 * This functions waits for the passed sockets that have *accept[i] = true to change status.
 * The result is returned on the arrays 'readchange', 'writechange' and 'exceptchange'.
 * 'timeout' specifies an upper bound on the ammount of time until the function returns with no status change.
 * The default value for timeout is 'DBL_MAX', which means: wait infinitely.
 * Returns the number of sockets that changed status, -1 in case of errors.
 */
int uso_select (int nread  , int *readsockets  , bool* readchange  , bool *readaccept, 
                int nwrite , int *writesockets , bool* writechange , bool *writeaccept,  
                int nexcept, int *exceptsockets, bool* exceptchange, bool *exceptaccept, double timeout=DBL_MAX);

#endif
