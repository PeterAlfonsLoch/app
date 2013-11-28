#pragma once


namespace core
{


   class CLASS_DECL_CORE install :
      public object
   {
   public:


      mutex m_mutex;

      ::string_to_string  m_strmapLatestBuildNumber;


      install(sp(base_application) papp);
      virtual ~install();


      virtual void add_spa_start(const char * pszType, const char * pszId);
      virtual void remove_spa_start(const char * pszType, const char * pszId);
      virtual void add_app_install(const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
      virtual bool is(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
      virtual int32_t  start(const char * pszCommandLine);
      virtual int32_t  synch(const char * pszCommandLine);

      virtual string get_latest_build_number(const char * pszVersion);

      virtual string fetch_latest_build_number(const char * pszVersion);

   };


} // namespace core



