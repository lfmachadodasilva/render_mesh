//* filemanager.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Aug 2010

#ifndef TRN_FILEMANAGER_H
#define TRN_FILEMANAGER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "defines.h"
#include "typedefs.h"

#include <ds/hash.h>

class TrnFile;
class TrnHelperLzo;

//---------------------//
// TrnFileAccess Class //
//---------------------//

class TERRAINAPI TrnFileManager
{
public:

  // Constructor and Destructor

  TrnFileManager ();
  ~TrnFileManager ();

  // LzoHelper

  TrnHelperLzo* GetLzoHelper () const
  {
    return m_lzoHelper;
  }

  // Terrain Name and File Paths

  bool SetTerrainName (const char* name);
  const char* GetTerrainName () const
  {
    return m_terrainName;
  }

  bool SetTerrainPath (const char* path);
  const char* GetTerrainPath () const
  {
    return m_terrainPath;
  }

  bool SetResourcePath (const char* path);
  const char* GetResourcePath () const
  {
    return m_resourcePath;
  }

  // File Server

  bool SetServerHost (const char* host);
  const char* GetServerHost () const
  {
    return m_serverHost;
  }

  void SetServerPort (long port);
  long GetServerPort () const
  {
    return m_serverPort;
  }

  void SetUseFtc (bool state);
  long GetUseFtc () const
  {
    return m_useFtc;
  }

  // Open

  TrnFile* Open (const char* fileName, TrnFileAccess access = TRN_FILE_READ);
  bool Close (const char* fileName);
  bool Close (TrnFile* file);
  void CloseAllFiles ();

  // File Versioning

  int GetFileMajorVersion ();
  int GetFileMinorVersion ();

  // Filename Generators

  char* GetVtfFilename ();
  char* GetHgtDataFilename (TrnTileHeight* tile);
  char* GetHgtInfoFilename (TrnTileHeight* tile);
  char* GetTexDataFilename (TrnTileTexture* tile);
  char* GetTexInfoFilename (TrnTileTexture* tile);

  char* GetTerrainFilename (const char* basename);
  char* GetResourceFilename (const char* basename);

private:

  DsHash<TrnFile*, DsStringKey> m_mapFileToName;
  DsHash<DsStringKey, TrnFile*> m_mapNameToFile;

  TrnHelperLzo* m_lzoHelper;

  char* m_terrainName;
  char* m_terrainPath;
  char* m_resourcePath;

  char* m_serverHost;
  long  m_serverPort;

  bool m_useFtc;

};

#endif // TRN_FILEMANAGER_H
