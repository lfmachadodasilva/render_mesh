#ifndef LUASTRATEGY_H
#define LUASTRATEGY_H

#include <sg/strategy.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

class SGLuaStrategy : public SGStrategy
{
	lua_State* m_L;
	int m_ref;
	int m_table;
	int* m_loadmethod;
	int* m_unloadmethod;
	int* m_whichloadmethod;
	int* m_whichunloadmethod;

	int LoadWithReturn (int type, void* o, const char* type_name); 
	int UnloadWithReturn (int type, void* o, const char* type_name);
	void LoadWithoutReturn (int type, void* o, const char* type_name);
	void UnloadWithoutReturn (int type, void* o, const char* type_name);
public:
	SGLuaStrategy (lua_State* L);
	virtual ~SGLuaStrategy ();

	void SetMethodTable (int lo);
	void PrintTables ();
	void Update ();

  virtual void Load (SGItem* i);
  virtual void Unload (SGItem* i);
  virtual void Load (SGAttribute* a);
  virtual void Unload (SGAttribute* a);
  virtual void Load (SGState* s);
  virtual void Unload (SGState* s);
  virtual void Load (SGBackground* b);
  virtual void Unload (SGBackground* b);
  virtual void Load (SGShape* s);
  virtual int Load (SGNode* n);
  virtual int Unload (SGNode* n);
  virtual int Load (SGLight* l);
  virtual int Unload (SGLight* l);
  virtual int Load (SGSpace* c);
  virtual int Unload (SGSpace* c);
  virtual int Load (SGEntity* e);
  virtual int Unload (SGEntity* e);
  virtual int Load (SGObject* o);
  virtual int Unload (SGObject* o);
  virtual int Load (SGGroup* g);
  virtual int Unload (SGGroup* g);
  virtual int Load (SGSwitch* s);
  virtual int Unload (SGSwitch* s);
  virtual int Load (SGScene* s);
  virtual int Unload (SGScene* s);
	virtual int Load (SGCollection* c);
	virtual int Unload (SGCollection* c);
  virtual int Load (SGColObject* c);
  virtual int Unload (SGColObject* c);
  virtual int Load (SGColLight* l);
  virtual int Unload (SGColLight* l);
  virtual int Load (SGColScene* s);
  virtual int Unload (SGColScene* s);
  virtual int Load (SGBin* b);
  virtual int Unload (SGBin* b);
};

#endif
