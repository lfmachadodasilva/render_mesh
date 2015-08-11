
#ifndef _TOP_POS_READER_H
#define _TOP_POS_READER_H

#include "defines.h"
#include "../hash.h"

class  TopModel;

class TOPSRD_API TopPosReader
{
private:
  TopModel* m_model;
  int m_nnodes;
  int m_nnodes_alloc;
  TopNode* m_nodes;
  
  int ReadNodes(FILE* fp);
  int ReadElemTETR4(FILE* fp);
  int ReadElemT3(FILE* fp);
  int ReadElemQ4(FILE* fp);
  int ReadElemQUAD(FILE* fp);

public: 
  TopPosReader(TopModel* m);
  ~TopPosReader();

  /**
    Reads elements from node and element files into a model.
  */
  int Read(const char* filename); 
};

class TOPSRD_API TopPosWriter
{
public:
  typedef enum {
    NF_ELE_T3=0,
    NF_ELE_T6,
    NF_ELE_Q4,  
    NF_ELE_Q8,
    NF_ELE_Q9,
    NF_ELE_DKT,
    NF_ELE_DKQ,
    NF_ELE_QUAD,
    NF_ELE_INTERFACE,
    NF_ELE_INFINITE,
    NF_ELE_INF3DS,
    NF_ELE_INT3DS,
    NF_ELE_TETR4,
    NF_ELE_TETR10,
    NF_ELE_WEDGE6,
    NF_ELE_WEDGE15,
    NF_ELE_BRICK8,
    NF_ELE_BRICK20,
    NF_ELE_BRICKS,
    NF_ELE_TYPE_MAX, // Maximum element type id.
  } NfElemType;

  enum {
    NF_ELE_NUM_NODES_MAX = 32
  };

  TopPosWriter();

  ~TopPosWriter();

  void SetMaterialId(TopElement elem, int id);

  void SetNfType(int tops_type, int nf_type);

  int Write(TopModel* model, const char* filename);
private:
  //static const int NF_ELE_NUM_NODES_MAX;
  static const int NF_ELE_NUM_NODES[NF_ELE_TYPE_MAX];
  static const char* NF_ELE_NAME[NF_ELE_TYPE_MAX];
  int m_nf_types[TopModel::ELEMENT_MAX];
  int m_tops_to_nf_map[TopModel::ELEMENT_MAX][NF_ELE_TYPE_MAX][NF_ELE_NUM_NODES_MAX];
  TopHash<unsigned int, int> m_elem_materials;

  void InitNfTypes();
  void InitTopsToNfIncMap();
};

#endif
