#pragma once

CLASS_DECL_____ void update_ca2_build();
CLASS_DECL_____ const char * ca2_get_build();
CLASS_DECL_____ void update_ca2_installed(bool bUnloadIfNotInstalled = true);
CLASS_DECL_____ bool is_ca2_installed();
CLASS_DECL_____ void update_ca2_updated();
CLASS_DECL_____ bool is_ca2_updated();
CLASS_DECL_____ void set_ca2_updated(const char * pszBuild);
CLASS_DECL_____ void update_updated();
CLASS_DECL_____ bool is_updated();
CLASS_DECL_____ void set_updated(const char * pszBuild);


CLASS_DECL_____ void set_installing_ca2(bool bSet = true);
CLASS_DECL_____ bool is_installing_ca2();


class CLASS_DECL_____ spa_starter_start
{
public:
      
      
   ::hotplugin::plugin  *              m_pplugin;
   vsstring                            m_strId;


   UINT start();

};

DWORD WINAPI _ca2_starter_start(LPVOID pvoid);