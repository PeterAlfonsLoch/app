#include "StdAfx.h"


verisimple_wstring::verisimple_wstring()
{
   m_pwsz = NULL;
}

verisimple_wstring::verisimple_wstring(const wchar_t * pwsz, int iCount)
{
   if(pwsz == NULL)
      m_pwsz = NULL;
   else
   {
//      m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc((wcslen(pwsz) + 1) * 2);
      m_pwsz = (wchar_t *) ca2_alloc((iCount + 1) * sizeof(wchar_t));
      memcpy_dup(m_pwsz, pwsz, (iCount + 1) * sizeof(wchar_t));
      m_pwsz[iCount] = L'\0';
   }
}


verisimple_wstring::verisimple_wstring(const wchar_t * pwsz)
{
   if(pwsz == NULL)
      m_pwsz = NULL;
   else
   {
//      m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc((wcslen(pwsz) + 1) * 2);
      m_pwsz = (wchar_t *) ca2_alloc((wcslen_dup(pwsz) + 1) * 2);
      wcscpy_dup(m_pwsz, pwsz);
   }
}

verisimple_wstring::verisimple_wstring(const verisimple_wstring & wstr)
{
   m_pwsz = NULL;
   operator = (wstr);
}

verisimple_wstring::~verisimple_wstring()
{
   if(m_pwsz != NULL)
   {
//      g_pfixedallocaWstring->free(m_pwsz, (wcslen(m_pwsz) + 1) * 2);
      ca2_free(m_pwsz);
   }
}

void verisimple_wstring::attach(const wchar_t * pwsz)
{
   if(m_pwsz != pwsz)
   {
      if(m_pwsz != NULL)
      {
         //g_pfixedallocaWstring->ca2_free(m_psz, (wcslen(m_psz) + 1) * 2);
         ca2_free(m_pwsz);
         m_pwsz = NULL;
      }
      m_pwsz = (wchar_t *) pwsz;
   }
}


wchar_t * verisimple_wstring::alloc(int iCount)
{
   if(m_pwsz != NULL)
   {
      ca2_free(m_pwsz);
      m_pwsz = NULL;
   }
   int iAlloc = (iCount + 1) * sizeof(wchar_t);
   //m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc(iAlloc);
   m_pwsz = (wchar_t *) ca2_alloc(iAlloc);
   m_pwsz[iCount] = L'\0';
   return m_pwsz;
}

count verisimple_wstring::get_length()
{
   if(m_pwsz == NULL)
      return -1;
   return wcslen_dup(m_pwsz);
}

verisimple_wstring & verisimple_wstring::operator = (const verisimple_wstring & wstr)
{
   if(this != &wstr)
   {
      operator = (wstr.m_pwsz);
   }
   return *this;
}
   
verisimple_wstring & verisimple_wstring::operator = (const wchar_t * pwsz)
{
   if(m_pwsz != pwsz)
   {
      if(m_pwsz != NULL)
      {
         //g_pfixedallocaWstring->free(m_pwsz, (wcslen(m_pwsz) + 1) * 2);
         ca2_free(m_pwsz);
         m_pwsz = NULL;
      }
      if(pwsz == NULL)
         m_pwsz = NULL;
      else
      {
         //m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc((wcslen(pwsz) + 1) * 2);
         m_pwsz = (wchar_t *) ca2_alloc((wcslen_dup(pwsz) + 1) * 2);
         wcscpy_dup(m_pwsz, pwsz);
      }
   }
   return *this;
}

int verisimple_wstring::CompareNoCase(const wchar_t * psz) const
{
   return wcsicmp_dup(m_pwsz, psz);
}
int verisimple_wstring::CompareNoCase(const verisimple_wstring &str) const
{
   return wcsicmp_dup(m_pwsz, str);
}

count verisimple_wstring::get_length() const
{
   if(m_pwsz == NULL)
      return 0;
   return wcslen_dup(m_pwsz);
}


count verisimple_wstring::size() const
{
   return get_length();
}

count verisimple_wstring::length() const
{
   return get_length();
}


verisimple_wstring operator + (const verisimple_wstring & wstr1, const verisimple_wstring & wstr2)
{
   int iLen1 = wstr1.length();
   int iLen2 = wstr2.length();
   verisimple_wstring wstrRet;
   wchar_t * pwszRet = (wchar_t *) ca2_alloc((iLen1 + iLen2 + 1) * sizeof(wchar_t));
   wcscpy_dup(pwszRet, wstr1);
   wcscat_dup(pwszRet, wstr2);
   wstrRet.attach(pwszRet);
   return wstrRet;
}


verisimple_wstring operator + (const verisimple_wstring & wstr, const wchar_t * wpsz)
{
   return wstr + verisimple_wstring(wpsz);
}


CLASS_DECL_c wstring gen_utf8_to_16(const char * psz)
{
   return wstring(utf8_to_16(psz));
}





