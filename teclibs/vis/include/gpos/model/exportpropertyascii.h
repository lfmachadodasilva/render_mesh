#ifndef RES_EXPORT_PROPERTY_ASCII_H
#define RES_EXPORT_PROPERTY_ASCII_H

#include <gpos/defines.h>

class ResProperty;
class ResModel;

RES_API bool res_export_property_ascii (ResModel* model, ResProperty* property, const char* filename);

#endif
