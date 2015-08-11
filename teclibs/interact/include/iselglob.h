#ifndef __ISELGLOBAL__
#define __ISELGLOBAL__


#define ITR_PNONE       0       // nenhuma permissao (apenas selecionar)
#define ITR_PTRANSLATE  1       // permissao para mover
#define ITR_PRESIZE     2       // permissao para mudar tamanho
#define ITR_PROTATE     4       // permissao para rodar 
#define ITR_PSHEAR      8       // permissao para cisalhar
#define ITR_PHDISTORT   16      // permissao para alterar o aspect ratio horizontal da primitiva
#define ITR_PVDISTORT   32      // permissao para alterar o aspect ratio vertical da primitiva
#define ITR_PDISTORT    (ITR_PVDISTORT|ITR_PHDISTORT) 

#define ITR_PTRANSFORM  (ITR_PTRANSLATE|ITR_PRESIZE| \
                         ITR_PROTATE|ITR_PSHEAR|ITR_PDISTORT)

#endif
