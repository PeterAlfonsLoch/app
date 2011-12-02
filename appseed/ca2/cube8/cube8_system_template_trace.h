#pragma once


namespace _template
{

   class CTraceFileAndLineInfo
   {
   public:
      CTraceFileAndLineInfo(::ax::application * papp, const char *pszFileName, int nLineNo)
         : m_papp(papp), m_pszFileName(pszFileName), m_nLineNo(nLineNo)
      {}

      inline ::ax::application * get_app() const
      {
         return m_papp;
      }

      inline ::ax::application * get_app()
      {
         return m_papp;
      }

      inline void __cdecl operator()(DWORD_PTR dwCategory, UINT nLevel, const char *pszFmt, ...) const
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

   private:
      /* unimplemented */
      CTraceFileAndLineInfo &__cdecl operator=(const CTraceFileAndLineInfo &right);
      ::ax::application * m_papp;
      const char *const m_pszFileName;
      const int m_nLineNo;
   };


} // namespace _template