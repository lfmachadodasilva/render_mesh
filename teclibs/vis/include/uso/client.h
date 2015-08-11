// Client class
// fabraham@tecgraf.puc-rio.br
// Aug 2003 

#ifndef USO_CLIENT_H
#define USO_CLIENT_H

#include "defines.h"

/**
 * This class represents a synchronous client.
 * Methods are provided to:
 * - initialize the client
 * - connect to a server
 * - send and receive data
 * - close the connection
 */
class USO_API USOClient
{
protected:
  int m_sockfd;
public:
  /**
   * Errors thrown.
   */
  typedef enum
  {
    /**
     * No error.
     */
    ERR_NONE = 0,
    /**
     * Connection in progress (for nonblocking sockets).
     */
    ERR_INPROGRESS,
    /**
     * Error connecting (connection refused).
     */
    ERR_CONNECT,
    /**
     * Error resolving host.
     */
    ERR_RESOLVE,
    /**
     * Already connected.
     */
    ERR_ALREADY_CONNECTED,
  } Error;
public:
  /**
   * Returns a string describing the connection error.
   */
  static const char* ErrorMessage (Error e);
public:
  /**
   * Obtains the server socket.
   */
  int GetSocket ()
  {
    return m_sockfd;
  }
  /**
   * Initializes the client, creating and binding its socket.
   * 'blocking' specifies if the socket must be blocking or non-blocking.
   */
  bool Init(bool blocking=true);
  /**
   * Sets socket as blocking or non-blocking.
   */
  void SetBlocking (bool blocking);
  /**
   * Shuts down the client, closing its socket.
   */
  bool Close(void);
  /**
   * Connects to a server at ip 'ip' and port 'port'.
   * Returns the following error codes:
   * ERR_AGAIN: try again (for nonblocking sockets)
   * ERR_CONNECT: connection refused
   * ERR_NONE: connection successful
   */
  Error Connect(const char* ip,int port);
  /**
   * Sends 'size' bytes from buffer 'data' to server. Returns number of bytes sent if successful, -1 if not
   */
  int  Send(const void * data, int size);
  /**
   * Waits for 'size' bytes from the server. Returns number of bytes received if successful, -1 if not. Received data is saved on buffer 'buffer'.
   */
  int  Receive(void * buffer, int maxlen);
  /**
   * Same as 'Send', but sends all the bytes and returns false on error.
   */
  bool SendAll(const void* data,int size);
  /**
   * Same as 'Receive', but waits for all the bytes to arrive and returns false on error.
   */
  bool ReceiveAll(void* buffer,int size);
  /**
   * Waits for the passed clients to change status.
	 * 'nread', 'nwrite' and 'nexcpt' are the number of clients passed.
	 * The result is returned on the arrays 'readchange', 'writechange' and 'excptchange'.
	 * 'timeout' specifies an upper bound on the ammount of time until the function returns with no status change.
	 * If 'timeout' is 0.0, then the function will wait forever until a status change.
   */
  static int Select(int nread , USOClient* readclients  , bool* readchange, 
                    int nwrite, USOClient* writeclients , bool* writechange, 
                    int nexcpt, USOClient* exceptclients, bool* excptchange, double timeout);
  /**
   * Same as above, but excludes the clients with accept[i]=false
   */
  static int Select(int nread , USOClient* readclients  , bool* readchange,   bool* readaccept, 
                    int nwrite, USOClient* writeclients , bool* writechange,  bool* writeaccept,
                    int nexcpt, USOClient* exceptclients, bool* excptchange,  bool* exceptaccept, double timeout);
};

#endif
