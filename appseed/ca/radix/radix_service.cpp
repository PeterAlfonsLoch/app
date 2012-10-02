#include "framework.h"


namespace ca2
{


   service::service()
   {
   }

   service::~service()
   {
   }


   int service::start(const char * pszServiceName)
   {

#ifdef WINDOWS

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
         return ::GetLastError();

      SC_HANDLE hdlServ =
         ::OpenService(
            hdlSCM,                    // SCManager database
            pszServiceName,               // name of service
            SC_MANAGER_ALL_ACCESS);                     // no password

      DWORD Ret = 0;

      if (!hdlServ)
         Ret = ::GetLastError();

      ::StartService(hdlServ, 0, NULL);
      CloseServiceHandle(hdlServ);

      return Ret;

#else

      throw not_implemented_exception(get_app());

      return 0;

#endif

   }

   int service::stop(const char * psz)
   {

#ifdef WINDOWS

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if (hdlSCM == 0) return ::GetLastError();

      SC_HANDLE hdlServ = ::OpenService(
         hdlSCM,                    // SCManager database
         psz,               // name of service
         SC_MANAGER_ALL_ACCESS);                     // no password

      DWORD Ret = 0;
      if (!hdlServ)
         Ret = ::GetLastError();
      SERVICE_STATUS ss;
      memset(&ss, 0, sizeof(ss));
      ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss);

      CloseServiceHandle(hdlServ);

      return Ret;

#else

      throw not_implemented_exception(get_app());

      return 0;

#endif

   }


   int service::remove(const char * psz)
   {

#ifdef WINDOWS

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if (hdlSCM == 0) return ::GetLastError();

      SC_HANDLE hdlServ = ::OpenService(
         hdlSCM,                    // SCManager database
         psz,               // name of service
         SC_MANAGER_ALL_ACCESS);                     // no password

      DWORD Ret = 0;
      if (!hdlServ)
         Ret = ::GetLastError();

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      return Ret;

#else

      throw not_implemented_exception(get_app());

      return 0;

#endif

   }


   int service::create(const char * psz, const char * pszDisplayName, const char * pszVotagus)
   {

#ifdef WINDOWS

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

      string strFile = System.dir().votagus();
      strFile = System.dir().path(strFile, pszVotagus);
      string strCalling = strFile + " service";

      if (hdlSCM == 0) return ::GetLastError();

      SC_HANDLE hdlServ = ::CreateService(
         hdlSCM,                    // SCManager database
         psz,               // name of service
         pszDisplayName,        // service name to display
         STANDARD_RIGHTS_REQUIRED,  // desired access
         SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type
         SERVICE_AUTO_START,      // start type
         SERVICE_ERROR_NORMAL,      // error control type
         strCalling,                   // service's binary Path name
         0,                      // no load ordering group
         0,                      // no tag identifier
         0,                      // no dependencies
         0,                      // LocalSystem account
         0);                     // no password

      DWORD Ret = 0;
      if (!hdlServ) Ret = ::GetLastError();
         CloseServiceHandle(hdlServ);

      return Ret;

#else

      throw not_implemented_exception(get_app());

      return 0;

#endif

   }


} // namespace ca2


