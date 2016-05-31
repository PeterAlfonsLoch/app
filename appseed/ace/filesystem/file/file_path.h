#pragma once


namespace path
{

   
   CLASS_DECL_AURA ::file::path app();
   CLASS_DECL_AURA ::file::path a_spa();
   CLASS_DECL_AURA ::file::path a_spaadmin();
   CLASS_DECL_AURA ::file::path vcredist();
   CLASS_DECL_AURA ::file::path app_install(string strPlatform = "");
   CLASS_DECL_AURA ::file::path app_plugin_container();
   CLASS_DECL_AURA ::file::path module(HMODULE pmoduleosdata = NULL);
   CLASS_DECL_AURA ::file::path install_log();
   

   
} // namespace path