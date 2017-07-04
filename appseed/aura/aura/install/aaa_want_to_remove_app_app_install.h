#pragma once


namespace app_app
{


   class app_install :
      virtual public ::object
   {
   public:







      app();
      virtual ~app();




      bool is_user_using(const char * pszDll);

      ATOM spaboot_message_register_class(HINSTANCE hInstance);

      int32_t cube_run(const char * id);

      void call_self_privileged_sync(const char * param);

      int32_t spaboot_registry_register(const char * lpszFile);

      void call_sync(const char * path, const char * param);

      void installer_call_sync(const char * path, const char * param);


   };


} // namespace app_app







