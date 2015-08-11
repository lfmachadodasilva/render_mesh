// open.h
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// Jul 2006

#ifndef RES_IO_OPEN_H
#define RES_IO_OPEN_H

#include <stdio.h>
#include <string.h>

#include <gpos/model/loadernew.h>
#include <gpos/defines.h>
#include <ds/hash.h>

typedef DsHash<DsStringKey,void*> ResOpenOptions;
class ResModel;
class ResModelNew;


#define GPOS_FILE_EXTENSION_INVALID "Extensao de arquivo invalida"

/**
 * ResOpener abstract class. Defines an interface for reservoir loaders.
 */
class RES_API ResOpener
{
public:
  virtual ~ResOpener ()
  {
  }
  /**
   * Returns true if the opener's class is named 't'.
   */
  bool IsOfType (const char *t) const
  {
    const char *it = ClassName();
    return it == t || strcmp(it,t)==0;
  }
  /**
   * Returns the opener's classname.
   */
  virtual const char* ClassName () const = 0;
};

/**
 * ResModelOpener abstract class.
 *
 * Reservoir model readers must derive from this class and register an instance
 * of it using gpos_register_model_opener(instance).
 *
 * The "Open" method must be implemented.
 * It must check if the model files match the expected file formats and, if so,
 * must return the pointer to the loaded ResModel.
 */
class RES_API ResModelOpener : public ResOpener
{
public:
  virtual ~ResModelOpener ()
  {
  }
  void SetOpenProfileFunc (SetOpenProfileCB cb, void* data)
  {
    m_opfunc = cb;
    m_opdata = data;
  }
  SetOpenProfileCB GetOpenProfileFunc () const
  {
    return m_opfunc;
  }
  void* GetOpenProfileFuncData () const
  {
    return m_opdata;
  }
  void SetUpdateSectionProgressFunc (UpdateSectionProgressCB cb, void* data)
  {
    m_uspfunc = cb;
    m_uspdata = data;
  }
  UpdateSectionProgressCB GetUpdateSectionProgressFunc () const
  {
    return m_uspfunc;
  }
  void* GetUpdateSectionProgressFuncData () const
  {
    return m_uspdata;
  }
  /**
   * CheckFormats method.
   * Informs if the specified filenames are destined to this reservoir opener.
   * Returns true if so, false otherwise.
   *
   * 'numfiles' inform that, in order to load this model, 'numfiles' filenames
   * were supplied in the 'filenames' pointer, in which the first file is
   * 'filenames[0]', the second is 'filenames[1]', and so on.
   * 
   * The function 'gpos_checkfileextension' can be used to check if the
   * supplied filenames were destined to this reservoir opener.
   */
  virtual bool CheckFormats (int numfiles, const char **filenames) = 0;
  /**
   * Open method.
   * Tries to open a model file and if successful, returns pointers to the models stored in the file.
   *
   * 'modelname' is the name of the model.
   * 'numfiles' inform that, in order to load this model, 'numfiles' filenames
   * were supplied in the 'filenames' pointer, in which the first file is
   * 'filenames[0]', the second is 'filenames[1]', and so on.
   *
   * 'options', if not NULL, present model format specific loading options.
   *
   * The number of loaded models is returned in the 'o_model_count' pointer,
   * and the model pointers in the 'o_models' array.
   * Array allocated for o_models must deleted by the caller with delete[].
   *
   * Opening a reservoir model usually consists of reading from files and
   * building the reservoir data structures.
   * In order to inform the progress of this operation, two methods are
   * provided in the ResModelOpener class:
   * - SetOpenProfile(profilename): specifies an operation profile, which is
   *   usually used to specify the type of the model being opened. This type
   *   will probably define which sub-operations must be completed in order to
   *   fully load the model. These sub-operations are called 'sections'.
   * - UpdateProgressSection(section,progress): updates the progress of the
   *   current profile's section named 'section'. 'progress' is a number
   *   between 0 and 1, where 0 means "section 'section' is 0% completed" and 1
   *   means "section 'section' is 100% completed".
   * 
   * Using these informations, the user interface can inform the user about the
   * progress of the loading operation.
   * 
   * The function 'gpos_setopenerror' can be used to specify that an error
   * occurred while opening the files.
   *
   * The function 'gpos_addopenwarning' can be used to signal that, although
   * the files loaded successfully, something unexpected happened.
   */
  virtual bool Open (const char *modelname,
                     int numfiles,
                     const char **filenames,
                     ResOpenOptions* options,
                     int* o_model_count,
                     ResModel*** o_models) = 0;
  /**
   * GetFilenames method.
   * Returns the filenames that compose this model.
   *
   * 'numfiles' inform that, in order to load this model, 'numfiles' filenames
   * were supplied in the 'filenames' pointer, in which the first file is
   * 'filenames[0]', the second is 'filenames[1]', and so on.
   *
   * Places the result in '*numfiles' and '*filenames'.
   * Memory for '*filenames' and '*(filenames)[i]' should be allocated with malloc/calloc/realloc.
   *
   * Returns true if this opener can open this model and the files were found, false otherwise.
   */
  virtual bool GetFilenames (int in_numfiles,
                             const char **in_filenames,
                             int *numfiles,
                             char ***filenames) = 0;
  /*
   * Specifies an operation profile, which is usually used to specify the type
   * of the model being opened. This type will probably define which
   * sub-operations must be completed in order to fully load the model.
   * These sub-operations are called 'sections'.
   */
  void SetOpenProfile (const char *name)
  {
    if (m_opfunc)
      m_opfunc(name, m_opdata);
  }
  /*
   * Updates the progress of the current profile's section named 'section'.
   * 'progress' is a number between 0 and 1, where 0 means "section 'section'
   * is 0% completed" and 1 means "section 'section' is 100% completed".
   */
  void UpdateSectionProgress (const char *section,float p)
  {
    if (m_uspfunc)
      m_uspfunc(section, p, m_uspdata);
  }
  void SetCallbacks (ResPosLoaderNew* loader);
protected:
  ResModelOpener () : 
    m_opfunc(NULL),
    m_opdata(NULL),
    m_uspfunc(NULL),
    m_uspdata(NULL)
  {
  }
private:
  SetOpenProfileCB m_opfunc;
  void* m_opdata;
  UpdateSectionProgressCB m_uspfunc;
  void* m_uspdata;
};

/**
 * ResResultOpener abstract class.
 *
 * Reservoir simulation result readers must derive from this class and register an instance
 * of it using gpos_register_res_pos_opener(instance).
 */
class RES_API ResResultOpener : public ResOpener
{
public:
  virtual ~ResResultOpener ()
  {
  }
  virtual ResPosGeometryLoader* BuildGeometryLoader (ResOpenOptions* options) = 0;
  virtual ResPosMapResultLoader* BuildMapResultLoader (ResOpenOptions* options) = 0;
  virtual ResPosWellResultLoader* BuildWellResultLoader (ResOpenOptions* options) = 0;
  /**
   * CheckFormats method.
   * Informs if the specified filename is destined to this reservoir opener.
   * Returns true if so, false otherwise.
   *
   * The function 'gpos_checkfileextension' can be used to check if the
   * supplied filenames were destined to this reservoir opener.
   */
  virtual bool CheckFormats (const char *filename) = 0;
  /**
   * GetFilenames method.
   * Returns the filenames that are used to load this model's results.
   *
   * 'in_filename' is the filename supplied to LoadGeometry/LoadMapResult/LoadWellResult.
   *
   * Places the result in '*numfiles' and '*filenames'.
   * Memory for '*filenames' and '*(filenames)[i]' should be allocated with malloc/calloc/realloc.
   *
   * Returns true if this opener can open this model and the files were found, false otherwise.
   */
  //virtual bool GetFilenames (const char *in_filename,
  //                           int *numfiles,
  //                           char ***filenames) = 0;
private:
};

/**
 * Opens a reservoir file and returns pointers to the models associated with it.
 * 'modelname' is the base name of the model.
 * 'numfiles' inform that, in order to load this model, 'numfiles' filenames
 * were supplied in the 'filenames' pointer, in which the first file is
 * 'filenames[0]', the second is 'filenames[1]', and so on.
 * 'setopenprofilecb' can be specified
 *
 * 'options', if not NULL, specify some loading options. Supported options:
 *
 * - "BuildGeometry" [type bool]: specifies if the model geometry must be loaded.
 *
 * Models are returned in *o_model_count (number of models) and *o_models.
 * Array allocated for o_models must deleted by the caller with delete[].
 * Returns true in case of success, false otherwise.
 */
RES_API bool ResModelOpen (const char* modelname,
                           int numfiles,
                           const char **filenames,
                           ResOpenOptions* options,
                           int* o_model_count,
                           ResModelNew*** o_models,
                           SetOpenProfileCB setopenprofilecb = NULL,
                           void* setopenprofilecbdata = NULL,
                           UpdateSectionProgressCB updateprogresscb = NULL,
                           void* updateprogresscbdata = NULL);

/**
 * Opens a reservoir model and returns a pointer to it.
 * 'modelname' is the name of the model.
 * 'numfiles' inform that, in order to load this model, 'numfiles' filenames
 * were supplied in the 'filenames' pointer, in which the first file is
 * 'filenames[0]', the second is 'filenames[1]', and so on.
 * 'setopenprofilecb' can be specified
 *
 * 'options', if not NULL, specify some loading options. Supported options:
 *
 * - "BuildGeometry" [type bool]: specifies if the model geometry must be loaded.
 */
RES_API ResModelNew* ResModelOpen (
    const char* modelname,
    int numfiles,
    const char **filenames,
    ResOpenOptions* options,
    SetOpenProfileCB setopenprofilecb = NULL,
    void* setopenprofilecbdata = NULL,
    UpdateSectionProgressCB updateprogresscb = NULL,
    void* updateprogresscbdata = NULL);

RES_API ResModel* ResPosModelCreate (int loader_index, const char* modelname);

RES_API bool ResPosModelLoadGeometry (ResModel* m,
                                      const char *filename,
                                      int model_index,
                                      SetOpenProfileCB setopenprofilecb = NULL,
                                      void* setopenprofilecbdata = NULL,
                                      UpdateSectionProgressCB updateprogresscb = NULL,
                                      void* updateprogresscbdata = NULL,
                                      ResOpenOptions* options = NULL);

RES_API bool ResPosModelLoadMapResults (ResModel* m,
                                        const char *filename,
                                        int model_index,
                                        SetOpenProfileCB setopenprofilecb = NULL,
                                        void* setopenprofilecbdata = NULL,
                                        UpdateSectionProgressCB updateprogresscb = NULL,
                                        void* updateprogresscbdata = NULL,
                                        ResOpenOptions* options = NULL);

RES_API bool ResPosModelLoadWellResults (ResModel* m,
                                         const char *filename,
                                         int model_index,
                                         SetOpenProfileCB setopenprofilecb = NULL,
                                         void* setopenprofilecbdata = NULL,
                                         UpdateSectionProgressCB updateprogresscb = NULL,
                                         void* updateprogresscbdata = NULL,
                                         ResOpenOptions* options = NULL);

/**
 * Obtains, given 'in_numfiles' and 'in_filenames' (ResModelOpen parameters),
 * which files are required to load this model.
 * Place the result in '*numfiles' and '*filenames'.
 * Memory for '*filenames' and '*(filenames)[i]' must be freed with 'free'.
 *
 * Returns true if the files were found, false otherwise.
 *
 * //TODO: falar q os arquivos tem q estar no mesmo diretorio e nao se referenciarem
 */
RES_API bool ResGetModelFilenames (int in_numfiles,
                                   const char **in_filenames,
                                   int *numfiles,
                                   char ***filenames);
/**
 * Registers a reservoir model file opener.
 * Only one opener of each opener class is allowed.
 */
RES_API void gpos_register_model_opener (ResModelOpener *opener);
/**
 * Registers a reservoir result opener.
 * Only one opener of each opener class is allowed.
 */
RES_API void gpos_register_result_opener (ResResultOpener *opener);
RES_API const char* gpos_getlastopenerror ();
RES_API const char* gpos_getlastopenerrordetails ();
RES_API const char* gpos_getlastopenwarnings ();
RES_API const char* gpos_getlastwellopenwarnings ();
RES_API const char* gpos_getlastmapopenwarnings ();
RES_API const char* gpos_getlastgridopenwarnings ();
RES_API void gpos_setopenerror (const char *error, const char *details=NULL);
RES_API void gpos_addopenwarning (const char *warning);
RES_API void gpos_clearopenwarnings ();
RES_API void gpos_addwellopenwarning (const char *warning);
RES_API void gpos_addmapopenwarning (const char *warning);
RES_API void gpos_addgridopenwarning (const char *warning);
RES_API bool gpos_checkfileextension (const char *filename, const char *ext);
RES_API bool ResHasOption (ResOpenOptions* options, const char* optionname);
RES_API void ResSetOption (ResOpenOptions* options, const char* optionname, void* v);
RES_API void* ResGetOption (ResOpenOptions* options, const char* optionname);
RES_API void ResSetBooleanOption (ResOpenOptions* options, const char* optionname, bool* v);
RES_API bool ResGetBooleanOption (ResOpenOptions* options, const char* optionname, bool defaultvalue);
RES_API void ResSetFloatOption (ResOpenOptions* options, const char* optionname, float* v);
RES_API float ResGetFloatOption (ResOpenOptions* options, const char* optionname, float defaultvalue);
RES_API void ResSetIntOption (ResOpenOptions* options, const char* optionname, int* v);
RES_API int ResGetIntOption (ResOpenOptions* options, const char* optionname, int defaultvalue);
RES_API void ResChangeIntOption (ResOpenOptions* options, const char* optionname, int newvalue);

#endif

