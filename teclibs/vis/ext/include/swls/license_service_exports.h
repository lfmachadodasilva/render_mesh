/* This include exports some methods for authenticating the application client at the 
* license server. It makes part of an API built-in as a DLL file. The DLL can be 
* used by C, Java and C++ application for both authenticate the client locally and remotely.
* 
* In the remote authentication, the API sends the client local IP 
* to the license server and receives a reply with one of the 
* following values: AUTHENTICATION_FAILURE or SUCCESSFUL_AUTHENTICATION.
* The client will be successfully authenticated if it belongs to any IP network
* set up in the license server properties file.
*
* However, when the client does not have network connectivity it will be 
* authenticated locally. During the software installation the method
* 'generate_client_id_token(...,file_path)' creates a client identification 
* token and stores it in the file passed as argument. This token will 
* be used by the 'authenticate_client()' method to implement the local authentication. 
* The token consists of a encrypted message with a cryptography algorithm 
* which uses as input Key the host mac address.
* Thus, the client will be locally authenticated, by the method 
* 'authenticate_client()', if this method is able to decrypt the message using the 
* host mac address, in other words,
* if it can decrypt the message it means that the software is running on the same 
* host on which it was installed.
*
*  
* The methods exported by the DLL through this include file are listed below
*/

#ifdef SWLS_EXPORTS
#define SWLS_API __declspec(dllexport)
#else
#define SWLS_API
#endif

#define authenticate_client			_push 
#define generate_client_id_token	_pop

/**
* A constant indicating that the client could not be authenticated.
*/
#define AUTHENTICATION_FAILURE				0
/**
* A constant indicating that the client has been successfully authenticated.
*/
#define SUCCESSFUL_AUTHENTICATION			1

/**
* A constant indicating that occured some error at communication with the server, e.g. 
*   the connection could not be established.
*/
#define COMMUNICATION_ERROR					2
/**
* A constant indicating that occurred any general error, e.g. invalid parameters.
*/
#define CONFIGURATION_ERROR					3

/**
 * A constant indicating that the client has been authenticated by the server
 */
#define SUCCESSFUL_REMOTE_AUTHENTICATION	4

/**
 * A constant indicating that the client has been locally authenticated
 */
#define SUCCESSFUL_LOCAL_AUTHENTICATION		5

/**
* A constant indicating that the local authentication failed.
*/
#define LOCAL_AUTHENTICATION_FAILURE		6

/**
* A constant indicating that the remote authentication failed.
*/
#define REMOTE_AUTHENTICATION_FAILURE		7

/**
* A constant indicating that the file could not be created.
*/
#define		FILE_NOT_CREATED				1001

#define		DIR_NOT_CREATED				        1002

/**
* A constant indicating that the required operation was succeeded.
*/
#define		SUCCESSFUL_OPERATION			1005

/**
* A constant indicating that it was not possible to get the host mac address.
*/
#define		INVALID_MAC_ADDRESS				1004

/**
* A constant indicating that the message could not be encrypted with the AES algorithm. 
*/
#define		ENCRYPTION_ERROR				1007

/**
* A constant indicating that the file was not found.
*/
#define		FILE_NOT_FOUND					1008

/**
* Server configuration address must be set.
*/
#define		SERVER_CONFIGURATION_ERROR		1009

/**
* Server configuration address must be set.
*/
#define INVALID_COMMAND						1010

/**
* Required operation failed.
*/
#define FAILURE								1011


/**
* This method must be called during the software installation. It generates 
* the client identification token which will be stored in the file passed
* as argument.  Before generating the token the client is 
* authenticated at the license server. If the authentication fails it will 
* return an error and the token will not be generated.
* 
*
* @param server_address License Server IP Address or domain name
* @param port Server port
* @param host_id_file_path Path to the file that will store the encoded host identification token. 
* @param ca_file_path Path to the file with the Certification Authority (CA) certificate. 
*
* @return int Returns a code stating if the token was created or not.
* The possible return codes are:
* <ul>
  *  <li>AUTHENTICATION_FAILURE - if the client could not be authenticated.
  *  <li>SUCCESSFUL_OPERATION - if the authentication succeeded and the 
  *  token was successfully created.
  *  <li>COMMUNICATION_ERROR - if occur any problem on the communication, e.g. 
  *   the connection could not be established.
  *  <li>CONFIGURATION_ERROR - if occur any general error, e.g. invalid parameters.
  *  <li>INVALID_MAC_ADDRESS - if it was not possible to get the host mac address.
  *  <li>FILE_NOT_CREATED - if the file could not be created. 
  *  <li>DIR_NOT_CREATED - if the directory could not be created. 
  *  <li>ENCRYPTION_ERROR - if the message could not be encrypted.
* </ul>
*
*/
SWLS_API int __stdcall _pop(char *server_address, int port, char *host_id_file_path, char *ca_file_path);

/**
* Authenticates the client through the server. 
* If it does not occur any error at the communication level the authentication result (Grant or Deny) will be returned. Otherwise,
* it tries to authenticate the client from a local file that contains the host identification token.
* The local file is  created by the 'generate_client_id_token()' method during the software 
* instalation.
*
* @param server_address License Server IP Address or domain name
* @param port Server port
* @param ca_file_path Path to the file with the Certification Authority (CA) certificate. 
* @param host_id_file_path Path to the file with the encoded host identification token. 
*
* @return int Returns either the authentication result processed locally or remotely. 
* 
* The possible return codes are:
* <ul>
  *  <li>LOCAL_AUTHENTICATION_FAILURE - if the client was not locally authenticated
  *  <li>REMOTE_AUTHENTICATION_FAILURE - if the client was not authenticated by the server
  *  <li>SUCCESSFUL_LOCAL_AUTHENTICATION - if the client has been locally authenticated
  *  <li>SUCCESSFUL_REMOTE_AUTHENTICATION - if the client has been remotely authenticated
  *  <li>CONFIGURATION_ERROR - if occur any general error, e.g. invalid parameters
  *  <li>FILE_NOT_FOUND - if the file was not found.
  *  <li>INVALID_MAC_ADDRESS - if it was not possible to get the host mac address
* </ul>
*
*/
SWLS_API int __stdcall _push(char *server_address, int port, char *host_id_file_path, char *ca_file_path);

/**
* This method logs the application access time in the log file managed by the License Server.
*
* @param application_name Aplication name for which the server must register a log entry.
* @param usage_time Usage time of the application.
* @param server_address License Server IP Address or domain name
* @param port Server port
* @param ca_file_path Path to the file with the Certification Authority (CA) certificate. 
*
* @return int Returns a code with the status of the operation. 
* 
* The possible return codes are:
* <ul>
  *  <li>SUCCESSFUL_OPERATION - The required operation has been successfully implemented.
  *  <li>FAILURE - The required operation FAILED.
  *  <li>CONFIGURATION_ERROR - if the if occur any general configuration error, e.g. invalid parameters, invalid server address, etc  
  *  <li>INVALID_COMMAND - If the server's reply contains a invalid command 
  *  <li>COMMUNICATION_ERROR - if occur any problem on the communication, e.g. 
  *   the connection could not be established.
* </ul>
*
*/
SWLS_API int __stdcall _log(char *application_name, double usage_time, char *server_address, int port, char *ca_file_path);

/**
* This method gets the application data stored in the log file managed by the License Server.
*
* @param application_name Aplication name for which the server should returns access information.
* @param usage_time Usage time of the application notified by the server.
* @param access_number Number of times that the application has been accessed.
* @param server_address License Server IP Address or domain name
* @param port Server port
* @param ca_file_path Path to the file with the Certification Authority (CA) certificate. 
*
* @return int Returns a code with the status of the operation. 
* 
* The possible return codes are:
* <ul>
  *  <li>SUCCESSFUL_OPERATION - The required operation has been successfully implemented.
  *  <li>FAILURE - The required operation FAILED.
  *  <li>CONFIGURATION_ERROR - if the if occur any general configuration error, e.g. invalid parameters, invalid server address, etc  
  *  <li>INVALID_COMMAND - If the server's reply contains a invalid command 
  *  <li>COMMUNICATION_ERROR - if occur any problem on the communication, e.g. 
  *   the connection could not be established.
* </ul>
*
*/
SWLS_API int __stdcall get(char *application_name, double *usage_time, int *access_number, char *server_address, int port, char *ca_file_path);

/**
* This method resets the application's access time and access number in the log file managed by the License Server.
*
* @param application_name Aplication name for which the server must resets the access information.
* @param server_address License Server IP Address or domain name
* @param port Server port
* @param ca_file_path Path to the file with the Certification Authority (CA) certificate. 
*
* @return int Returns a code with the status of the operation. 
* 
* The possible return codes are:
* <ul>
  *  <li>SUCCESSFUL_OPERATION - The required operation has been successfully implemented.
  *  <li>FAILURE - The required operation FAILED.
  *  <li>CONFIGURATION_ERROR - if the if occur any general configuration error, e.g. invalid parameters, invalid server address, etc  
  *  <li>INVALID_COMMAND - If the server's reply contains a invalid command 
  *  <li>COMMUNICATION_ERROR - if occur any problem on the communication, e.g. 
  *   the connection could not be established.
* </ul>
*
*/
SWLS_API int __stdcall reset(char *application_name, char *server_address, int port, char *ca_file_path);

