/*
%M taskresh.h  - reshape/editor de nos
%a Marcelo Medeiros Carneiro e Juli Huang
%d 20.09.94
%h Modificado em 20.06.96 para atender as necessidades do novo interact
*/
 
#ifndef __TASKRESHAPE__
#define __TASKRESHAPE__

#include "interactapi.h"
#include "itask.h"
#include "inodlist.h"

/*
%C Tarefa de Reshape de porimitivas 
*/
class INTERACT_API itrTaskReshape : public virtual itrTask
{
 protected:
  itrNodeList* nodes;       // lista dos nos do objeto
  int      pick_node;       // numero do no onde o mouse esta'
  double   x0, y0, x1, y1;  // posicao inicial (ButtonPress) e corrente do mouse (Motion)
  double   ins_x, ins_y;    // posicao do no' a ser inserido/criado
  int      new_node;        // 1, se existe um novo no' pronto para ser criado
  char     mode;            // 'f'ence ou 't'ranslate
  char    *old_cursor;      // cursor original do iup
  double   curr_x, curr_y;  // ponto onde foi realizado o Pick ou Insert
                            // Guarda o valor retornado por GetPickPos,
                            // GetNewNodePos 


 public:
  
  static int MarkSize;      // Tamanho das marcas colocadas nos no's 

  itrTaskReshape (); 
  virtual ~itrTaskReshape () {};

  virtual void Init ();
  virtual void Done ();

  virtual void Repaint ();
  virtual void Button1Pressed  ();
  virtual void Button1Motion   ();
  virtual void Button1Released ();
  virtual void MouseMove       ();
  virtual void Keyboard        (int key);

  virtual void FeedBack        ();
  virtual void FeedBackNodes   ();
  virtual void FeedBackLines   ();
  virtual void FeedBackFence   ();
  virtual void FeedBackNewNode ();

  virtual void* Pick          () = 0;
  virtual void* QuickPick     (){return 0;}
  virtual int   PickNode      ();
  virtual void  GetPickPos    (double *x, double* y);
  virtual void  GetPickPos    (int* x, int* y);
  virtual void  ReshapeObject () = 0;
  virtual int   GetNumNodes   ();
  virtual void* GetId         ();
  virtual int   GetNodeData   (int i, double* x, double* y, int* state=0);
  virtual int   GetNodeData   (int i, int* x,    int* y,    int* state=0);
 
  virtual void  DeleteNodes   ();
  virtual int   NotifyNewNode (int i);

  void          GetNewNodePos (double *x, double *y);
  void          GetNewNodePos (int* x, int* y);
  void          SetNewNodePos (double x, double y);
  void          SetNewNodePos (int x, int y);
  itrNodeList*  GetNodeList   ();
  itrNodeList*  ChangeNodeList(itrNodeList* nodelist);
  virtual int   VerifyNewNode ();
  virtual int   VerifyDelNode (int i);

  virtual void  BeginRegister (void *id, int type);
  virtual void  RegisterNode  (double x, double y, int st=ITR_NORMAL);
  virtual void  RegisterNode  (int x, int y, int st=ITR_NORMAL);
  virtual void  EndRegister   ();
};

/*
%F Retorna um ponteiro para a lista de no's.
*/
inline itrNodeList* itrTaskReshape::GetNodeList()
{
   return nodes;
} 

/*
%F Retorna a posicao do da posicao onde a tarefa pretende inserir um novo
   ponto
%o (x,y) - posicao do ponto em coordenadas raster
%x Esta funcao so e' valida dentro de VerifyNewNode() ou qualquer funcao chamada
   por esta ultima.
*/
inline void itrTaskReshape::GetNewNodePos(int* x, int* y)
{
   GetPickPos(x,y);
}

/*
%F Retorna a posicao do da posicao onde a tarefa pretende inserir um novo
   ponto
%o (x,y) - posicao do ponto em coordenadas do mundo
%x Esta funcao so e' valida dentro de VerifyNewNode() ou qualquer funcao chamada
   por esta ultima.
*/
inline void itrTaskReshape::GetNewNodePos(double* x, double* y)
{
   GetPickPos(x,y);
}



#endif
