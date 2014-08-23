#include "framework.h"


namespace axis
{


   os::os(sp(::axis::application) papp) :
      element(papp)
   {
   }

   os::~os()
   {
   }


   bool os::shutdown(bool bIfPowerOff)
   {
      UNREFERENCED_PARAMETER(bIfPowerOff);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   bool os::reboot()
   {
      throw interface_only_exception(get_app(), "this is an interface");
   }

   void os::terminate_processes_by_title(const char * pszName)
   {
      UNREFERENCED_PARAMETER(pszName);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   bool os::get_pid_by_path(const char * pszName, uint32_t & dwPid)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   bool os::get_pid_by_title(const char * pszName, uint32_t & dwPid)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   string os::get_process_path(uint32_t dwPid)
   {
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   void os::get_all_processes(uint_array & dwa )
   {
      UNREFERENCED_PARAMETER(dwa);
      throw interface_only_exception(get_app(), "this is an interface");
   }

#ifdef WINDOWS

   string os::get_module_path(HMODULE hmodule)
   {
      UNREFERENCED_PARAMETER(hmodule);
      throw interface_only_exception(get_app(), "this is an interface");
   }

#endif


   bool os::connection_settings_get_auto_detect()
   {

      return true;

   }


   string os::connection_settings_get_auto_config_url()
   {

      return "";

   }

   bool os::local_machine_set_run(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::local_machine_set_run_once(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::current_user_set_run(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::current_user_set_run_once(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::defer_register_ca2_plugin_for_mozilla()
   {

      return false;

   }

   bool os::file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension)
   {

      UNREFERENCED_PARAMETER(straKey);
      UNREFERENCED_PARAMETER(pszExtension);

      return false;

   }

   bool os::file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension)
   {

      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(pszExtension);

      return false;

   }


   bool os::file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      UNREFERENCED_PARAMETER(pszIconPath);

      return false;

   }


   bool os::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      UNREFERENCED_PARAMETER(pszCommand);
      UNREFERENCED_PARAMETER(pszParam);

      return false;

   }


   bool os::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(strExtensionNamingClass);
      UNREFERENCED_PARAMETER(strCommand);
      UNREFERENCED_PARAMETER(strParam);

      return false;

   }

#ifdef WINDOWS

   bool os::open_in_ie(const char * lpcsz)
   {

      throw interface_only_exception(get_app());

      return false;

   }

#endif


   bool os::create_service(sp(::axis::application) papp)
   {


      throw not_implemented(get_app());


      return false;


   }


   bool os::remove_service(sp(::axis::application) papp)
   {


      throw not_implemented(get_app());


      return false;


   }


   bool os::start_service(sp(::axis::application) papp)
   {


      throw not_implemented(get_app());


      return false;


   }


   bool os::stop_service(sp(::axis::application) papp)
   {


      throw not_implemented(get_app());


      return false;


   }


   bool os::resolve_link(string & strTarget, const char * pszSource, sp(::user::interaction) puiMessageParentOptional)
   {


      throw interface_only_exception(get_app());


      return false;

   }


   bool os::is_remote_session()
   {

      return false;

   }


   void os::set_file_status(const char * lpszFileName, const ::file::file_status& status)
   {

      throw interface_only_exception(get_app());

   }

} // namespace core





