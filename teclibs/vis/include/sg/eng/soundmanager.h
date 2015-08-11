// Sound class
// djavanes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// May 2003

#ifndef SG_SOUND_MANAGER_H
#define SG_SOUND_MANAGER_H

#include <sg/modules/sgsound.h>
#include <sg/engine.h>
#include <ds/list.h>
#include <alg/vector.h>

class SGScene;
class SGCamera;
class SGEntity;
class SndManager;
class SndSound;
class SndPointSound;
class SndBackSound;

class SGSOUNDAPI SGSoundManager : public SGEngine
{
  typedef struct {
    SndPointSound* sound;
    SGEntity*      entity;
		bool					 noentity;
    char*          name;
    bool           play;
    AlgVector      lastpos;
  } PointSound;
  typedef struct {
    SndBackSound* sound;
    char*         name;
    bool          play;
  } BackSound;
  typedef struct {
    SndPointSound* first;
    SndPointSound* last;
		SndPointSound** array;
    char*         name;
    int cont;
    int size;
  } ArraySound;
  
  typedef DsPList<PointSound>  PointSoundList;
  typedef DsPList<BackSound>   BackSoundList;
  typedef DsPList<ArraySound>  ArraySoundList;
  PointSoundList m_psounds;
  BackSoundList  m_bsounds;
  ArraySoundList m_asounds;
  SGScene*       m_scene;
  float          m_last_t;
  AlgVector      m_camera_lastpos;
  char*          m_path;

  SndSound*			 FindSound     (char* filename);
  SndBackSound*  FindBackSound (char* filename);
  SndPointSound* FindPointSound(char* filename);
public:
  static const char* CLASSNAME () { return "SoundManager"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGSoundManager (SGScene* scene);
  virtual ~SGSoundManager ();
	static void SetCamera(SGCamera* camera);
  void SetSoundsPath (const char* path);
  void ResetPath ();

  void CreateArraySound(char* array, char* snd, int size);
  void AddPointSound(char* name, SGEntity* entity);
  void AddBackSound (char* name);
  void RemoveSound (char* name);
  bool AddTrack(char* name, char* filename);
  void Play(char* name);
  void PlayArraySound(char* array);
  void PlayArraySound(char* array, float x, float y, float z);
  void SetTrack(char* name, int number);
  void SetChangeTime(char* name, int min_time, int max_time);
  void SetChangeTimeOff(char* name);
  void Stop(char* name);
  void Pause(char* name);
  void SetVolume(char* name,float volume);
  void SetLoop(char* name,bool loop);
  void SetRandom(char* name,bool random);
  void SetAutoplay(char* name,bool autoplay);
	void SetFadeTime(char* name,int time);
  void SetGain(char* name,float gain);
  void SetPitch(char* name,float pitch);
  void SetMaxDistance(char* name,float maxdistance);
  void SetMinDistance(char* name,float mindistance);
  void SetRollOff(char* name,float rolloff);

  void SetGlobalVolume(float volume);
  void SetPointsVolume(float volume);
  void SetBacksVolume(float volume);
  void SetDoppler(float velocity, float factor=1.0f);

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
