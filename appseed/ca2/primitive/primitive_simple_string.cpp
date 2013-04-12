#include "framework.h"

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)


//CLASS_DECL_ca2 fixed_alloc_array * g_pfixedallocaWstring = ::null();


/*CLASS_DECL_ca2 fixed_alloc_array * new_wstring_manager()
{
   if(g_pfixedallocaWstring != ::null())
      return g_pfixedallocaWstring;
   fixed_alloc_array * pa = new fixed_alloc_array();
   bool bEnable = __enable_memory_tracking(FALSE);
   int32_t iCharSize = 2;
   try
   {
      pa->add(new fixed_alloc(ROUND4(32 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   try
   {
      pa->add(new fixed_alloc(ROUND4(64 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   try
   {
      pa->add(new fixed_alloc(ROUND4(128 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   try
   {
      pa->add(new fixed_alloc(ROUND4(256 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   try
   {
      pa->add(new fixed_alloc(ROUND4(512 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   try
   {
      pa->add(new fixed_alloc(ROUND4(768 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   try
   {
      pa->add(new fixed_alloc(ROUND4(1024 * iCharSize), 1024));
   }
   catch(...)
   {
   }
   __enable_memory_tracking(bEnable);
   g_pfixedallocaWstring = pa;
   return pa;
}*/
/*
verisimple_wstring::verisimple_wstring()
{
   m_pwsz = ::null();
}

verisimple_wstring::verisimple_wstring(const wchar_t * pwsz)
{
   if(pwsz == ::null())
      m_pwsz = ::null();
   else
   {
//      m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc((wcslen(pwsz) + 1) * 2);
      m_pwsz = (wchar_t *) ca2_alloc((wcslen(pwsz) + 1) * 2);
      wcscpy(m_pwsz, pwsz);
   }
}

verisimple_wstring::verisimple_wstring(const verisimple_wstring & wstr)
{
   m_pwsz = ::null();
   operator = (wstr);
}

verisimple_wstring::~verisimple_wstring()
{
   if(m_pwsz != ::null())
   {
//      g_pfixedallocaWstring->free(m_pwsz, (wcslen(m_pwsz) + 1) * 2);
      ca2_free(m_pwsz, 0);
   }
}

wchar_t * verisimple_wstring::alloc(int32_t iCount)
{
   if(m_pwsz != ::null())
   {
      free(m_pwsz);
      m_pwsz = ::null();
   }
   int32_t iAlloc = (iCount + 1) * sizeof(wchar_t);
   //m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc(iAlloc);
   m_pwsz = (wchar_t *) ca2_alloc(iAlloc);
   m_pwsz[iCount] = L'\0';
   return m_pwsz;
}

::count verisimple_wstring::get_length()
{
   if(m_pwsz == ::null())
      return -1;
   return wcslen(m_pwsz);
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
      if(m_pwsz != ::null())
      {
         //g_pfixedallocaWstring->free(m_pwsz, (wcslen(m_pwsz) + 1) * 2);
         ca2_free(m_pwsz, 0);
         m_pwsz = ::null();
      }
      if(pwsz == ::null())
         m_pwsz = ::null();
      else
      {
         //m_pwsz = (wchar_t *) g_pfixedallocaWstring->alloc((wcslen(pwsz) + 1) * 2);
         m_pwsz = (wchar_t *) ca2_alloc((wcslen(pwsz) + 1) * 2);
         wcscpy(m_pwsz, pwsz);
      }
   }
   return *this;
}
*/


wstringtou::wstringtou(string & str, int32_t iAllocCount)
{
   m_pstringUtf8 = &str;
   m_pwsz = wstring_data::get_nil();
   alloc(iAllocCount);
}

wstringtou::~wstringtou()
{
   if(m_pstringUtf8 != ::null())
   {
      ::ca::international::unicode_to_utf8(*m_pstringUtf8, m_pwsz);
   }
   if(m_pwsz != ::null())
   {
      //g_pfixedallocaWstring->free(m_pwsz, (wcslen(m_pwsz) + 1) * 2);
      wstring_data::free(m_pwsz);
      m_pwsz = wstring_data::get_nil();
   }
}
