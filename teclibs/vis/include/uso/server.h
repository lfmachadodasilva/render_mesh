// Server class
// fabraham@tecgraf.puc-rio.br
// Aug 2003 

#ifndef USO_SERVER_H
#define USO_SERVER_H

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif
#include "defines.h"
#include <float.h>
#include <stdio.h>

/**
 * This class represents a synchronous server.
 * Methods are provided to:
 * - initialize the server
 * - listen and accept new connections
 * - send and receive data
 * - close connections
 */
class USO_API USOServer
{
protected:
  int m_sockfd;
  int m_port;
public:
  /**
   * This class represents a client. Passed to listen/disconnect/send/receive functions.
   * It contains methods to get the client ip and connection port.
   */
  class USO_API Client
  {
  private:
    int m_sockfd;
    struct sockaddr_in m_addr;
  public:
    /**
     * Default constructor.
     */
    Client ();
    /**
     * Copy constructor.
     */
    Client (Client* client);
    /**
     * Obtains the client socket id
     */
    int GetSocket()
    {
      return m_sockfd;
    }
    /**
     * Obtains client ip.
     */
    char * GetIP();
    /**
     * Obtains client port.
     */
    int GetPort();
    /**
     * Is this client connected?
     */
    bool IsConnected() const
    {
      return m_sockfd != -1;
    }
    /**
     * Returns 'true' if this client has incoming data, 'false' if a
     * Receive() call would block.
     */
    bool HasIncomingData ();
    friend class USOServer;
  };
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
     * Error on send.
     */
    ERR_SEND,
    /**
     * Error on receive.
     */
    ERR_RECEIVE,
    /**
     * Error, try again (for nonblocking sockets).
     */
    ERR_AGAIN,
    /**
     * Nothing happened before the specified timeout.
     */
    ERR_TIMEOUT,
    /**
     * AcceptTimed() called on a nonblocking socket.
     */
    ERR_ISNONBLOCKING,
    /**
     * Error accepting connections.
     */
    ERR_ACCEPT,
  } Error;
  /**
   * Constructs a new server to listen on the desired port.
   */
  USOServer(int port); 
  /**
   * Destroys a server.
   */
  virtual ~USOServer();
  /**
   * Obtains the server listening port.
   */
  int GetPort ()
  {
    return m_port;
  }
  /**
   * Obtains the server socket.
   */
  int GetSocket ()
  {
    return m_sockfd;
  }
  /**
   * Initializes the server, creating and binding the server to the desired listening port.
   * 'blocking' specifies if the server socket must be blocking or non-blocking.
   */
  bool Init(bool blocking=true);
  /**
   * Sets socket as blocking or non-blocking.
   */
  void SetBlocking (bool blocking);
  /**
   * Is socket blocking or nonblocking?
   */
  bool IsBlocking () const;
  /**
   * Specifies that the server is ready to listen for new connections.
   * Returns true if succeeded.
   */
  bool Listen();
  /**
   * Tries to accept a new connection.
   * Blocks if the socket is blocking until a new connection arrives or an error occurs.
   * Returns immediately if the socked is non-blocking.
   * Returns the error (or status).
   * Possible errors:
   * - ERR_NONE (success)
   * - ERR_AGAIN (try again for nonblocking sockets)
   * - ERR_ACCEPT (error accepting new connections)
   * On success, the client information is stored in 'client'.
   */
  Error Accept(Client *client);
  /**
   * Tries to accept a new connection (for blocking sockets).
   * Blocks if the socket is blocking until either a new connection arrives,
   * an error occurs or a timeout is reached.
   *
   * Returns the error (or status).
   * Possible errors:
   * - ERR_NONE (success)
   * - ERR_ISNONBLOCKING (called on a nonblocking socket)
   * - ERR_TIMEOUT (timeout reached)
   * - ERR_ACCEPT (error accepting new connections)
   * On success, the client information is stored in 'client'.
   */
  Error AcceptTimed (Client *client, double timeout);
  /**
   * Disconnects the client.
   */
  bool Disconnect(Client* client);
  /**
   * Shuts down the server, freeing the listening port.
   */
  bool ShutDown();
  /**
   * Sends 'size' bytes from buffer 'data' to client 'client'. Returns number of bytes sent if successful, -1 if not
   */
  int Send(Client* client,void* data,int size);
  /**
   * Waits for 'size' bytes from client 'client'. Returns number of bytes received if successful, -1 if not. Received data is saved on buffer 'buffer'.
   */
  int Receive(Client* client,void* buffer,int size);
  /**
   * Same as 'Send', but tries to send all the bytes. Returns false on disconnection, true on success.
   */
  bool SendAll(Client* client,const void* data,int size);
  /**
   * Same as 'Receive', but waits for all the bytes to arrive. Returns false on disconnection, true on success.
   */
  bool ReceiveAll(Client* client,const void* buffer,int size);
  /**
   * Same as 'SendAll', but sends all the bytes and throws 'Error' on error.
   */
  void SendAllE(Client* client,void* data,int size) throw(USOServer::Error);
  /**
   * Same as 'ReceiveAll', but waits for all the bytes to arrive and throws 'Error' on error.
   */
  void ReceiveAllE(Client* client,void* buffer,int size) throw(USOServer::Error);
  /**
   * Returns 'true' if the server has incoming clients (an Accept() call would not block).
   */
  bool HasIncomingConnections ();
  /**
   * Waits for the passed clients to change status.
	 * 'nread', 'nwrite' and 'nexcpt' are the number of clients passed.
	 * The result is returned on the arrays 'readchange', 'writechange' and 'excptchange'.
	 * 'timeout' specifies an upper bound on the ammount of time until the function returns with no status change.
	 * If 'timeout' is 0.0, then the function will wait forever until a status change.
   * Returns 0 if no clients changed status, nonzero otherwise.
   */
	static int Select(int nread , Client* readclients  , bool* readchange, 
                    int nwrite, Client* writeclients , bool* writechange, 
                    int nexcpt, Client* exceptclients, bool* excptchange, double timeout);
  /**
   * Waits for the server socket to change status.
	 * The result is returned on the booleans 'readchange', 'writechange' and 'excptchange'.
	 * 'timeout' specifies an upper bound on the ammount of time until the function returns with no status change.
	 * If 'timeout' is 0.0, then the function will wait forever until a status change.
   * Returns 0 if there was no status change, nonzero otherwise.
   */
	int Select(bool* readchange, bool* writechange, bool* excptchange, double timeout);
};

#endif
