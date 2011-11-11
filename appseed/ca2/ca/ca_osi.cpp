#include "StdAfx.h"

namespace ca
{

   bool osi::shutdown(bool bIfPowerOff)
   {
      UNREFERENCED_PARAMETER(bIfPowerOff);
      throw interface_only_exception("this is an interface");   
   }

   bool osi::reboot()
   {
      throw interface_only_exception("this is an interface");   
   }

   void osi::terminate_processes_by_title(const char * pszName)
   {
      UNREFERENCED_PARAMETER(pszName);
      throw interface_only_exception("this is an interface");   
   }

   bool osi::get_pid_by_path(const char * pszName, DWORD & dwPid)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception("this is an interface");   
   }

   bool osi::get_pid_by_title(const char * pszName, DWORD & dwPid)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception("this is an interface");   
   }

   string osi::get_process_path(DWORD dwPid)
   {
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception("this is an interface");   
   }

   void osi::get_all_processes(dword_array & dwa )
   {
      UNREFERENCED_PARAMETER(dwa);
      throw interface_only_exception("this is an interface");   
   }

   string osi::get_module_path(HMODULE hmodule)
   {
      UNREFERENCED_PARAMETER(hmodule);
      throw interface_only_exception("this is an interface");   
   }

} // namespace ca