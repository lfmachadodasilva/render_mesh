#ifndef _TOP_CTOPSRD_H
#define _TOP_CTOPSRD_H

#ifdef __cplusplus
extern "C" {
#else
#endif
  
int topModelReader_Read(TopModel* model, const char* filename);
int topModelReader_Write(TopModel* model, const char* filename);

#ifdef __cplusplus
}
#endif
  
#endif
