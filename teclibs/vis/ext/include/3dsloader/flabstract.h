#ifndef _FLABSTRACT
#define _FLABSTRACT

#ifdef LOADER3DS_DLL
#define LOADER3DS_API __declspec(dllexport)
#else
#define LOADER3DS_API
#endif

class LOADER3DS_API flAbstractFactory
{
private:
  bool mShouldLoadLights;
  bool mShouldLoadCameras;
  char mFactoryName[100];
public: 
  flAbstractFactory(char *name);
  virtual ~flAbstractFactory(void);

  void SetShouldLoadLights (bool);
  void SetShouldLoadCameras(bool);

  //Hierarchy methods
  virtual void InsertNode(int id, void* entity) = 0;
  virtual void InsertNode(void *entity) = 0;

  virtual void InsertCamera(int id, void* entity) = 0;
  virtual void InsertCamera(void *entity) = 0;

  virtual void InsertLight(int id, void* entity) = 0;
  virtual void InsertLight(void *entity) = 0;

  //Reserve methods
  virtual bool ReserveAppearence(int count) = 0;
  virtual bool ReserveMesh(int count) = 0;
  virtual bool ReserveEntity(int count) = 0;

  //Get methods
  virtual void * GetMesh(int id) = 0;
  virtual void * GetCurTransform(void) = 0;
  virtual void * GetCurCamera(void) = 0;
  virtual void * GetCurLight(void) = 0;
  virtual void * GetAppearence(int id) = 0;
  virtual void * GetDefaultAppearence(void) = 0;
  virtual void * GetEntity(int id) = 0;

  //Create methods
  virtual void CreateEntity(int id, char *name, void* mesh, void* tr, void *app) = 0;

  virtual void CreatePerspCamera(char *name, bool enabled,
    float eyex,float eyey,float eyez,
    float centerx,float centery,float centerz,
    float upx,float upy, float upz,
    float fov, float fnear, float ffar) = 0;

  virtual void CreateNewMaterial(int id, char *name, bool two_sided,
    float Ra, float Ga, float Ba, float Aa,
    float Rd, float Gd, float Bd, float Ad,
    float shininess,
    float Rs, float Gs, float Bs, float As) = 0;

  virtual void CreateNewTexture(int id, char *name, bool two_sided, char *path,
    float Ra, float Ga, float Ba, float Aa,
    float Rd, float Gd, float Bd, float Ad,
    float shininess,
    float Rs, float Gs, float Bs, float As) = 0;

  virtual void CreatePointLight(char *name, int lightnum,bool enabled,
    float Ra,float Ga,float Ba, float Aa,
    float Rd,float Gd,float Bd, float Ad,
    float Rs,float Gs,float Bs, float As,
    float posx,float posy, float posz) = 0;

  virtual void CreateSpotLight(char *name, int lightnum,bool enabled,
    float Ra,float Ga,float Ba, float Aa,
    float Rd,float Gd,float Bd, float Ad,
    float Rs,float Gs,float Bs, float As,
    float posx,float posy, float posz,
    float dirx,float diry, float dirz,
    float exponent, float cutoff) = 0;

  virtual void CreateSubMesh(int id, char *name,
    void * mesh, int inf, short int *pfaces) = 0;

  virtual void CreateMesh(int id, char *name,
    int inv, float *pverts, float *pnorms, 
    int inf, int *pfaces, float *ptexverts) = 0;

  virtual void CreateTransform(float rx, float ry, float rz,
    float tx, float ty, float tz,
    float angle,
    float rotx, float roty, float rotz,
    float sx, float sy, float sz) = 0;

  bool LoadModel(char* model, char* map_dir);
};

#undef LOADER3DS_API

#endif

