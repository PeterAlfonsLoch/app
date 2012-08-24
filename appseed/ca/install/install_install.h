#pragma once


namespace ca2
{


   class CLASS_DECL_ca install :
      public ::radix::object
   {
   public:

      
      HANDLE m_hmutexBoot;


      install();
      virtual ~install();


      virtual void add_spa_start(const char * pszType, const char * pszId);
      virtual void remove_spa_start(const char * pszType, const char * pszId);
      virtual void add_app_install(const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
      virtual bool is(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
      virtual int  start(const char * pszCommandLine);
      virtual int  synch(const char * pszCommandLine);


   };


} // namespace ca2



