/*
** ftc.h
*/

#ifndef  FTC_H_
#define  FTC_H_


#ifdef FTC_APP_EXPORT
   #define FTC_APP_API __declspec(dllexport)
 #else
   #define FTC_APP_API __declspec(dllimport)
 #endif

#include <lua.hpp>
#include "ftc_exception.h"


/** 
 * @brief Classe que representa a API de acesso a um arquivo remoto. 
 */
class FTC_APP_API ftc {
  public:
    /** 
     * @brief Construtor 
     * 
     * @param id Identificador do arquivo.
     * @param writable Indica se o arquivo deve ser aberto para leitura.
     * @param host Endereço do servidor.
     * @param port Porta TCP do servidor.
     * @param accessKey Chave de acesso ao arquivo.
     */
    ftc( const char* id, bool writable, const char* host, \
                        unsigned long port, const char* accessKey ) ;
    /** 
     * @brief Destrutor 
     */
    ~ftc() ;

    /** 
     * @brief Abre o arquivo remoto. 
     * 
     * @param readonly Indica se o arquivo deve ser aberto apenas para leitura.
     */
    void open( bool readonly ) ;

    /** 
     * @brief Indica se o arquivo está aberto.
     * 
     * @return Verdadeiro se o arquivo estiver aberto
     */
    bool isOpen() ;

    /** 
     * @brief Fecha o arquivo. 
     */
    void close() ;

    /** 
     * @brief Posiciona o cursor de leitura no arquivo.
     * 
     * @param position Numero de bytes a partir do inicio do arquivo.
     */
    void setPosition( unsigned long long position ) ;

    /** 
     * @brief Define o tamanho do arquivo.
     * Pode ser usado para alocar um espaço ou truncar o arquivo. 
     * 
     * @param size Novo tamanho do arquivo em bytes. 
     */
	void setSize( unsigned long long size );

    /** 
     * @brief Define o tamanho do buffer de leitura utilizado na leitura do
     * arquivo.
     * 
     * @param size Tamanho do buffer de leitura em bytes.
     */
	void setReadBufferSize( unsigned long long size );

    /** 
     * @brief Retorna a atual posição do cursor de leitura no arquivo.
     * 
     * @return Posição a partir no inicio do arquivo em bytes. 
     */
    unsigned long long getPosition() ;

    /** 
     * @brief Retorna o tamanho atual do arquivo. 
     * 
     * @return O numero de bytes que o arquivo possui.
     */
    unsigned long long getSize() ;

    /** 
     * @brief Retorna o tamanho atual do buffer de leitura. 
     * 
     * @return Tamanho do buffer em bytes.
     */
    unsigned long long getReadBufferSize() ;

    /** 
     * @brief Le uma quantidade de bytes a partir de uma dada posição.
     * 
     * @param data Ponteiro para o espaço onde os bytes lidos serão escritos.
     * @param nbytes Quantidades de bytes a serem lidos. 
     * @param position Posição inicial da leitura.
     * 
     * @return Retorna o numero de bytes lidos.
     */
    unsigned long long read( char* data, unsigned long long nbytes, unsigned long long position ) ;

    /** 
     * @brief Escreve uma quantidade de bytes no arquivo. 
     * 
     * @param data Ponteiro de onde os dados serão lidos.
     * @param nbytes Quantidade de bytes a serem escritos. 
     * @param position Posição inicial da escrita.
     * 
     * @return Retorna a quantidade de bytes escritos. 
     */
    unsigned long long write( const char* data, unsigned long long nbytes, unsigned long long position ) ;

    /** 
     * @brief Transfere os dados do arquivo remoto diretamente para um arquivo
     * local. 
     * 
     * @param position Posição do cursor no arquivo remoto.
     * @param nbytes Quantidade de bytes a serem transferidos.
     * @param fd Descritor do arquivo local.
     * @param Buffer para ser utilizado na transferência.
     * 
     * @return Retorna o número de bytes escritos.
     */
	unsigned long long transferTo( unsigned long long position, unsigned long long nbytes, FILE* fd, char * data  );
    
    /** 
     * @brief Retorna o estado de Lua sendo utilizado
     * 
     * @return Lua_State
     */
    lua_State* getLuaVM() ;

  private:  
    // Estado de lua sendo utilizado.
    lua_State* LuaVM ;

    // Metodo que prepara o ambiente.
    void setEnv() ;
} ;

#endif
