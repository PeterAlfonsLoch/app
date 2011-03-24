#pragma once

UINT APIENTRY _ca2_starter_start(void * pParam);


void defer_install_spa();
int install_spa();
void update_spa_installed();
bool is_spa_installed();
void update_spa_updated();
bool is_spa_updated();
int spaboot_start(const char * pszVersion, const char * pszId);


void update_ca2_installed();
bool is_ca2_installed();
void update_ca2_updated();
bool is_ca2_updated();
bool is_installing_ca2();
void set_installing_ca2(bool bSet = true);

std::string get_ca2_folder_dup();
void get_ca2_folder_dup(char * lpszModuleFolder);


extern HINSTANCE g_hinstance;
extern UINT g_nCa2StarterStartThreadID;

const char * ca2_browser_plugin_get_module_name();

namespace npca2
{


   class plugin;


   class starter_start
   {
   public:
      
      
      plugin *                      m_pplugin;
      std::string                   m_strId;


      UINT start();


   };


} // namespace npca2