/**
 * ftc_exception.h
 */

#ifndef FTC_EXCEPTION_H_
#define FTC_EXCEPTION_H_

#include <string>
#include <exception>

/** 
 * @brief Descreve o erros do protocolo. 
 */
enum FtcErrorCode{
    OK = 0,
    FILE_NOT_OPEN=249,
    MAX_CLIENTS_REACHED=250,
    FILE_LOCKED,
    NO_PERMISSION,
    FILE_NOT_FOUND,
    INVALID_KEY,
    FAILURE
};

/** 
 * @brief Define a excecao base da biblioteca FTC. 
 */
class FTC_APP_API FtcException : public std::exception {
    public:  
        /** 
         * @brief Construtor
         * 
         * @param code
         * @param msg
         */
        explicit FtcException( FtcErrorCode errcode, std::string msg ) 
        {
            code = errcode;
            m_msg = msg;
        }

        /** 
         * @brief Destrutor 
         */
        virtual ~FtcException() throw() {}

        /** 
         * @brief Retorna a mensagem de erro associada a exceção.
         * 
         * @return Mensagem de erro.
         */
        virtual const char * what(){
            return m_msg.c_str(); 
        } 
        
        /** 
         * @brief Retorna o código de erro da exceção 
         * 
         * @return FtcErrorCode
         */
        virtual FtcErrorCode erroCode(){
            return code;
        }

    protected:
        FtcErrorCode code;
        std::string m_msg;
};

/** 
 * @brief Essa exceção é lançada quando o metodo close é chamado sem
 * que o arquivo remoto esteja aberto
 */
class FTC_APP_API FileNotOpenException : public FtcException{
    public:
        /** 
         * @brief Construtor 
         * 
         * @param msg
         */
        explicit FileNotOpenException( std::string msg )
            : FtcException(FILE_NOT_OPEN,msg){}
};

/** 
 * @brief Essa exceção é lançada quando o servidor atingiu o número máximo
 * de clientes. 
 */
class FTC_APP_API MaxClientsReachedException : public FtcException{
    public:
        /** 
         * @brief Construtor 
         * 
         * @param msg
         */
        explicit MaxClientsReachedException( std::string msg )
            : FtcException(MAX_CLIENTS_REACHED,msg){}
};

/** 
 * @brief Essa exceção é lançada quando o arquivo está reservado para 
 * acesso exclusivo.
 */
class FTC_APP_API FileLockedException: public FtcException{
    public:
        /** 
         * @brief Construtor
         * 
         * @param msg
         */
        explicit FileLockedException( std::string msg )
            : FtcException(FILE_LOCKED,msg){}
};

/** 
 * @brief Essa exceção é lançada quando uma operação falha por causa
 * de falta de permissões para realizar-la.
 */
class FTC_APP_API NoPermissionException: public FtcException{
    public:
        /** 
         * @brief Construtor
         * 
         * @param msg
         */
        explicit NoPermissionException( std::string msg )
            : FtcException(NO_PERMISSION,msg){}
};

/** 
 * @brief Essa exceção é lançada quando o arquivo não é encontrado no
 * servidor. 
 */
class FTC_APP_API FileNotFoundException : public FtcException{
    public:
        /** 
         * @brief Construtor
         * 
         * @param msg
         */
        explicit FileNotFoundException( std::string msg ) 
            : FtcException(FILE_NOT_FOUND,msg) {}
};

/** 
 * @brief Essa exceção é lançada quando a chave de acesso utilizada na
 * conexão é inválida.
 */
class FTC_APP_API InvalidKeyException: public FtcException{
    public:
        /** 
         * @brief Construtor  
         * 
         * @param msg
         */
        explicit InvalidKeyException( std::string msg )
            : FtcException(INVALID_KEY,msg){}
};

/** 
 * @brief Essa exceção é lançada quando uma falha desconhecida aconteceu. 
 */
class FTC_APP_API FailureException: public FtcException{
    public:
        /** 
         * @brief Construtor 
         * 
         * @param msg
         */
        explicit FailureException( std::string msg )
            : FtcException(FAILURE,msg){}
};

#endif

