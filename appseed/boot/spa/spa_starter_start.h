#pragma once

CLASS_DECL_ca void update_ca2_build();
CLASS_DECL_ca const char * ca2_get_build();
CLASS_DECL_ca void update_ca2_installed(bool bUnloadIfNotInstalled = true);
CLASS_DECL_ca bool is_ca2_installed();
CLASS_DECL_ca void update_ca2_updated();
CLASS_DECL_ca bool is_ca2_updated();
CLASS_DECL_ca void set_ca2_updated(const char * pszBuild);
CLASS_DECL_ca void update_updated();
CLASS_DECL_ca bool is_updated();
CLASS_DECL_ca void set_updated(const char * pszBuild);


CLASS_DECL_ca void set_installing_ca2(bool bSet = true);
CLASS_DECL_ca bool is_installing_ca2();




class CLASS_DECL_ca spa_starter_start
{
public:
      
      
   ::hotplugin::plugin  *              m_pplugin;
   string                            m_strCommandLine;


   UINT start();

};

uint32_t _ca2_starter_start(void * pvoid);




