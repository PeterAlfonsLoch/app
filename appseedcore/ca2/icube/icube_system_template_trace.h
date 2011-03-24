#pragma once


namespace _template
{

   class CTraceFileAndLineInfo
   {
   public:
      CTraceFileAndLineInfo(::ca::application * papp, const char *pszFileName, int nLineNo)
         : m_papp(papp), m_pszFileName(pszFileName), m_nLineNo(nLineNo)
      {}

      inline void __cdecl operator()(DWORD_PTR dwCategory, UINT nLevel, const char *pszFmt, ...) const
      {
         va_list ptr; va_start(ptr, pszFmt);
         m_papp->m_psystem->log().trace_v(m_pszFileName, m_nLineNo, dwCategory, nLevel, pszFmt, ptr);
         va_end(ptr);
      }
   
      inline void __cdecl operator()(const char *pszFmt, ...) const
      {
         va_list ptr; va_start(ptr, pszFmt);
         m_papp->m_psystem->log().trace_v(m_pszFileName, m_nLineNo, trace::category_General, 0, pszFmt, ptr);
         va_end(ptr);
      }

   private:
      /* unimplemented */
      CTraceFileAndLineInfo &__cdecl operator=(const CTraceFileAndLineInfo &right);
      ::ca::application * m_papp;
      const char *const m_pszFileName;
      const int m_nLineNo;
   };


} // namespace _template