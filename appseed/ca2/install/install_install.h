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


      virtual void add_spa_start(const char * pszId);
      virtual void remove_spa_start(const char * pszId);
      virtual void add_app_install(const char * pszId);
      virtual bool is(const char * pszId);
      virtual int  ca2_cube_install(const char * pszId);


   };

} // namespace ca2