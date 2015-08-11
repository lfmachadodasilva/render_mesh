/*
%M taskresh.h - Lista de nos de uma tarefa de reshape
%a Marcelo Medeiros Carneiro, Juli Huang
%d 20.09.94
%h Modificado em 20.09.96 para atender as necessivades do novo interact
*/
 
#ifndef __NODELIST__
#define __NODELIST__

/*
%K Atributos permitidos para um ponto
*/
#define ITR_NORMAL     0  // unmarked e unlocked
#define ITR_MARKED     1  // no' selecionado
#define ITR_VLOCKED    2  // no  fixo no sentido vertical(so anda na horizontal)
#define ITR_HLOCKED    4  // no  fixo no sentido horizontal(so anda na vertical)
#define ITR_LOCKED     6  // no' fixo, nao pode ser movido
#define ITR_VBOUNDED   8  // no' limitado, em X as coordenadas do vizinho
#define ITR_HBOUNDED   16 // no' limitado, em Y as coordenadas do vizinho
#define ITR_BOUNDED    24 // no' limitado  a estar entre os vizinhos (X e Y).


/*
%K Atributos permitidos para a primitiva descrita pelos pontos
*/
#define ITR_CLOSED     1  // primitiva fechada
#define ITR_OPEN       0  // primitiva aberta

#include "interactapi.h"
#include "icanvas.h"
#include "itask.h"

/*
%C Interface padrao para uma lista de nos que deseje ser usada por uma 
   itrTaskReshape
%x Se um usuario precisar modificar o comportamento da nodelist, basta
   herdar uma classe de itrNodeList.  Por conta da estrutura interna
   de itrTaskReshape a lista de nos deve guarda-los e operar sobre eles
   sempre em double.
*/
class INTERACT_API itrNodeList
{
   itrTask* task;
public:
   itrNodeList(itrTask* owner);            // Construtor
   virtual ~itrNodeList();                 // Destrutor

 // Limpa a estrutura de dados
   virtual void Reset         ()=0;        

 // Comeca a registrar pontos 
 // id = identificador da primitiva selecionad
 // type = tipo da primitiva selecionada 
   virtual void BeginRegister (void* id, int type)=0; 
 // Registra um ponto 
 // (x,y) - coordenada do ponto
 // state - estado do ponto (marcado, bloqueado...)
   virtual int  Register      (double x, double y, int state)=0; 
 // Termina a fase de resgistro de pontos 
   virtual void EndRegister   ()=0;        

 // Inicia um drag dos nos selecionados 
   virtual void BeginDrag     ()=0;    
 // Atualiza a nodelist com a "distancia" atual do drag
 // (dx,dy) Diferenca entre a posicao corrente do mouse e o ponto inicial do drag    
   virtual void Drag          (double dx, double dy)=0;
 // Termina o drag da nodelist
   virtual void EndDrag       ()=0; 

 // Marca o i-esimo ponto da nodelist
   virtual void Mark          (int i)=0;
 // Desmarca o i-esimo ponto da nodelist
   virtual void Unmark        (int i)=0;
 // Desmarca todos os pontos da nodelist
   virtual void UnmarkAll     ()=0;
 // Bloqueia o i-esimo ponto da nodelist
   virtual void Lock          (int i)=0;
 // Desbloqueia o i-esimo ponto da nodelist
   virtual void Unlock        (int i)=0;

 // Testa se o i-esimo ponto esta bloqueado
   virtual int  IsLocked      (int i)=0;
 // Testa se o i-esimo ponto esta marcado
   virtual int  IsMarked      (int i)=0;

 // Retorna o identificador associado a primitiva representada pelo nodelist
   virtual void* GetId        ()=0;
 // Retorna o numero de pontos da primitiva
   virtual int  GetNum        ()=0;
 // Retorna o tipo de primitiva respresentada pelo nodelist (aberta/fechada)
   virtual int  GetType       ()=0;
 // Retorna informacoes sobre o i-esimo ponto 
   virtual void Get           (int i, double* px, double* py,int* state=0)=0;
 
 // Insere um ponto na i-esima posicao.  O atual i-esimo deve passar a (i+1)-esimo.
   virtual void Insert        (int i, double x, double y, int state)=0; 
 // Remove o i-esimo ponto.  O atual i-esimo passa a (i-1)-esimo.
   virtual void Delete        (int i)=0;
};

/*
%M Classe default de lista de nos
%x Essa versao de nodelist ja e' mais flexivel do que a interface minima exigida por
   itrTaskReshape
*/
class INTERACT_API itrDefaultNodeList:public itrNodeList
{
 protected:
  double *px, *py;        // array dos nos
  double *apx,*apy;       // array dos nos ancora
  int    *state;          // locked, marked etc.
  int    n;               // numero de nos no array
  void  *id;              // ponteiro para o objeto sendo reshaped
  int    maxnodes;        // tamanho alocado
  int    prim_type;       // ITR_CLOSED ou ITR_OPEN
 
 public:
  itrDefaultNodeList (itrTask* mytast);
  virtual ~itrDefaultNodeList ();

  virtual void Reset     ();

  virtual void BeginRegister(void *id,int type);
  virtual int  Register  (double x, double y, int st);
  virtual void EndRegister() {}

  virtual void BeginDrag ();
  virtual void Drag      (double dx, double dy);
  virtual void EndDrag   ();

  virtual void Mark      (int i);
  virtual void Unmark    (int i);
  virtual void UnmarkAll ();
  virtual void Lock      (int i);
  virtual void Lock      (int i, int type);
  virtual void Unlock    (int i);
  virtual void Bound     (int i, int type = ITR_BOUNDED);
  virtual void Unbound   (int i);

  virtual int  IsMarked  (int i);
  virtual int  IsLocked  (int i);
  virtual int  IsHLocked (int i);
  virtual int  IsVLocked (int i);
  virtual int  IsBounded (int i);
  virtual int  IsHBounded(int i);
  virtual int  IsVBounded(int i);

  virtual void *GetId    ();
  virtual int  GetNum    ();
  virtual int  GetType   ();
  virtual void Get       (int i, double *x, double *y, int* st=0);

  virtual void SetType   (int type);

  virtual void Insert    (int i, double x, double y, int st);
  virtual void Delete    (int i);

  virtual void Change    (int i, double x, double y, int st=ITR_NORMAL);
};

#endif
