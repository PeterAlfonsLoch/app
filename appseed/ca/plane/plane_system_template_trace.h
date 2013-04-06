#pragma once


namespace ca
{


   class CLASS_DECL_ca trace_add_file_and_line 
#if defined(LINUX) || defined(MACOS)
      : public string_format_printer
#endif
   {
   public:


      sp(::ca::application)     m_papp;
      const char * const      m_pszFileName;
      const int32_t               m_nLineNo;
      string                  m_str;

#if defined(LINUX) || defined(MACOS)

      class CLASS_DECL_ca category_level
      {
      public:


         uint32_t    m_dwCategory;
         UINT     m_nLevel;


      };

#endif

      trace_add_file_and_line(sp(::ca::application) papp, const char *pszFileName, int32_t nLineNo)
         : m_papp(papp), m_pszFileName(pszFileName), m_nLineNo(nLineNo)
      {
      }

      inline sp(::ca::application) get_app() const
      {
         return m_papp;
      }

      inline sp(::ca::application) get_app()
      {
         return m_papp;
      }

#ifdef WINDOWS

      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char *pszFmt, ...) const
      {
         va_list ptr; va_start(ptr, pszFmt);
         System.log().trace_v(m_pszFileName, m_nLineNo, dwCategory, nLevel, pszFmt, ptr);
         va_end(ptr);
      }

      inline void __cdecl operator()(const char *pszFmt, ...) const
      {
         va_list ptr; va_start(ptr, pszFmt);
         System.log().trace_v(m_pszFileName, m_nLineNo, trace::category_General, 0, pszFmt, ptr);
         va_end(ptr);
      }

#else



      void trace_category_level(void * pvoid, const char * psz)
      {

         category_level * pcategorylevel = (category_level *) pvoid;

         System.log().trace(m_pszFileName, m_nLineNo, pcategorylevel->m_dwCategory, pcategorylevel->m_nLevel, psz);

      }

      void trace(void *, const char * psz)
      {

         System.log().trace(m_pszFileName, m_nLineNo, trace::category_General, 0, psz);

      }

      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char *pszFmt) const
      {

         category_level categorylevel;

         categorylevel.m_dwCategory = dwCategory;
         categorylevel.m_nLevel = nLevel;

         string_format format(this, &trace_add_file_and_line::trace_category_level, &categorylevel);

         format.printf(pszFmt);


      }

      template<typename T, typename... Args>
      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char * pszFmt, const T & value, Args... args) const
      {

         category_level categorylevel;

         categorylevel.m_dwCategory = dwCategory;
         categorylevel.m_nLevel = nLevel;

         string_format format(this, &trace_add_file_and_line::trace_category_level, &categorylevel);

         format.printf(pszFmt, value, args...);

      }

      inline void __cdecl operator()(const char *pszFmt) const
      {

         string_format format(this, &trace_add_file_and_line::trace, ::null());

         format.printf(pszFmt);

      }

      template<typename T, typename... Args>
      inline void __cdecl operator()(const char * pszFmt, const T & value, Args... args) const
      {

         string_format format(this, &trace_add_file_and_line::trace, ::null());

         format.printf(pszFmt, value, args...);

      }


#endif

   private:
      /* unimplemented */
      trace_add_file_and_line &__cdecl operator=(const trace_add_file_and_line &right);

   };


} // namespace ca
