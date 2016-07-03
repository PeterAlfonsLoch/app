#pragma once




namespace aura
{


   class CLASS_DECL_AURA trace_add_file_and_line
#if defined(VARIADIC_TEMPLATE_FORMAT2)
      : public string_format_printer
#endif
   {
   public:


      ::aura::application *      m_pauraapp;
      const char * const         m_pszFileName;
      const int32_t              m_nLineNo;
      string                     m_str;

//#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      class CLASS_DECL_AURA category_level
      {
      public:


         uint32_t    m_dwCategory;
         UINT     m_nLevel;


      };

//#endif

      trace_add_file_and_line(::aura::application * papp, const char *pszFileName, int32_t nLineNo)
         : m_pauraapp(papp),m_pszFileName(pszFileName),m_nLineNo(nLineNo)
      {
      }

      inline sp(::aura::application) get_app() const
      {
         return m_pauraapp;
      }

      inline sp(::aura::application) get_app()
      {
         return m_pauraapp;
      }

#if defined(VARIADIC_TEMPLATE_FORMAT2)

      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char *pszFmt) const
      {

         System.log().trace_str(m_pszFileName, m_nLineNo, dwCategory, nLevel, pszFmt);

      }

      template<typename T, typename... Args>
      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char * pszFmt, const T & value, Args... args) const
      {

         string_format format;

         format.format(pszFmt, value, args...);

         System.log().trace_str(m_pszFileName, m_nLineNo, dwCategory, nLevel, format.to_string());


      }

      inline void __cdecl operator()(const char *psz) const
      {

         System.log().trace_str(m_pszFileName, m_nLineNo, trace::category_General, 0, psz);


      }

      template<typename T, typename... Args>
      inline void __cdecl operator()(const char * pszFmt, const T & value, Args... args) const
      {

         string_format format;

         format.format(pszFmt, value, args...);

         System.log().trace_str(m_pszFileName, m_nLineNo, trace::category_General, 0, format.to_string());

      }


#elif !defined(VARIADIC_TEMPLATE_FORMAT)

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

#endif
   private:
      /* unimplemented */
      trace_add_file_and_line &__cdecl operator=(const trace_add_file_and_line &right);

   };


} // namespace aura













