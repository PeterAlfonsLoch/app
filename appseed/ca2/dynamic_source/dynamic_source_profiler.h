#pragma once


namespace dynamic_source
{

   

   class CLASS_DECL_ca profiler :
      public ptr
   {
   public:
      class CLASS_DECL_ca item
      {
      public:
         __int64  m_iEnterTime;
         __int64  m_iTotalTime;
         int      m_iCount;
         item();
         void enter(profiler * pprofiler, const char * pszName);
         void leave(profiler * pprofiler, const char * pszName);
      };

      class CLASS_DECL_ca scope
      {
      public:
         profiler * m_pprofiler;
         string m_strName;
         bool  m_bEntered;
         bool  m_bLeft;
         scope(profiler * pprofiler, const char * pszName, bool bEnter);
         ~scope();
         void enter();
         void leave();
      };

      

      ::collection::map < string, string, item, item > m_map;

      void enter(const char * psz);
      void leave(const char * psz);

      void display();
   };


   

} // namespace dynamic_source