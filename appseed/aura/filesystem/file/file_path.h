#pragma once


namespace path
{

   
   CLASS_DECL_AURA ::file::path app(string strPlatform);
   CLASS_DECL_AURA ::file::path app_app(string strPlatform);
   CLASS_DECL_AURA ::file::path app_appadmin(string strPlatform);
   CLASS_DECL_AURA ::file::path vcredist(string strPlatform);
   CLASS_DECL_AURA ::file::path app_install(string strPlatform);
   CLASS_DECL_AURA ::file::path app_plugin_container(string strPlatform);
   CLASS_DECL_AURA ::file::path module(HMODULE pmoduleosdata = NULL);
   CLASS_DECL_AURA ::file::path install_log(string strPlatform);
   

   
} // namespace path