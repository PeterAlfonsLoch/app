#include "framework.h"


wchar_t * wstring_data::get_nil()
{

   static wstring_data s_nil;

   return s_nil;

}


verisimple_wstring::verisimple_wstring(manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   m_pwsz         = wstring_data::get_nil();

}

verisimple_wstring::verisimple_wstring(const char * psz,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   m_pwsz         = wstring_data::get_nil();

   operator = (psz);

}


verisimple_wstring::verisimple_wstring(const byte * psz,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   m_pwsz         = wstring_data::get_nil();

   operator = ((const char *) psz);

}


verisimple_wstring::verisimple_wstring(const wchar_t * pwsz,strsize iCount,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   if(pwsz == NULL)
   {

      m_pwsz         = wstring_data::get_nil();

   }
   else
   {
      while(iCount < 0)
         iCount = wcslen(pwsz) + iCount + 1;
      m_pwsz = (wchar_t *) wstring_data::alloc(iCount + 1);
      get_data()->m_iLength = iCount;
      memcpy_dup(m_pwsz, pwsz, get_data()->m_iLength * sizeof(wchar_t));
      m_pwsz[get_data()->m_iLength] = L'\0';

   }
}


verisimple_wstring::verisimple_wstring(const wchar_t * pwsz,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   if(pwsz == NULL)
   {

      m_pwsz         = wstring_data::get_nil();

   }
   else
   {

      m_pwsz = NULL;

      assign(pwsz);

   }

}


void verisimple_wstring::assign(const wchar_t * pwsz)
{

   if(m_pwsz != NULL && m_pwsz != wstring_data::get_nil())
   {
      
      wstring_data::free(m_pwsz);

      m_pwsz = NULL;

   }

   ::count iLen         = wcslen_dup(pwsz);

   m_pwsz = (wchar_t *)wstring_data::alloc(iLen + 1);

   get_data()->m_iLength = iLen;

   memcpy_dup(m_pwsz,pwsz,get_data()->m_iLength * sizeof(wchar_t));

   m_pwsz[get_data()->m_iLength] = L'\0';

}


verisimple_wstring::verisimple_wstring(const verisimple_wstring & wstr,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   m_pwsz         = wstring_data::get_nil();

   operator = (wstr);

}

verisimple_wstring::~verisimple_wstring()
{

   wstring_data::free(m_pwsz);
   m_pwsz = NULL;

}

wchar_t * verisimple_wstring::alloc(::count iCount)
{

   if(m_pwsz != NULL && iCount < get_data()->m_iAllocation)
      return m_pwsz;

   wstring_data::free(m_pwsz);

   m_pwsz            = (wchar_t *) wstring_data::alloc(iCount);

   return m_pwsz;

}


verisimple_wstring & verisimple_wstring::operator = (const verisimple_wstring & wstr)
{

   if(this != &wstr)
   {

      if(m_pwsz != NULL && get_data()->m_iAllocation >= (wstr.length() + 1))
      {

         memcpy_dup(m_pwsz, wstr.m_pwsz, (wstr.length() + 1) * sizeof(wchar_t));

      }
      else
      {

         alloc(wstr.storage_size());
         memcpy_dup(m_pwsz, wstr.m_pwsz, storage_size() * sizeof(wchar_t));

      }

      set_length(wstr.get_length());


   }

   return *this;

}

verisimple_wstring & verisimple_wstring::operator = (const wchar_t * pwsz)
{

   if(m_pwsz != pwsz)
   {

      ::count iLen = wcslen_dup(pwsz);

      if(storage_size() >= (iLen + 1))
      {

         memcpy_dup(m_pwsz, pwsz, (iLen + 1) * sizeof(wchar_t));


      }
      else
      {

         alloc(iLen + 1);
         memcpy_dup(m_pwsz, pwsz, storage_size() * sizeof(wchar_t));
      }

      set_length(iLen);

   }

   return *this;

}

verisimple_wstring & verisimple_wstring::operator = (const char * psz)
{

   ::count iLen = utf16_len(psz);

   alloc(iLen + 1);

   utf8_to_utf16(*this, psz);

   set_length(iLen);

   return *this;

}



verisimple_wstring operator + (const verisimple_wstring & wstr1, const verisimple_wstring & wstr2)
{

   ::count iLen1 = wstr1.length();

   ::count iLen2 = wstr2.length();

   wstring wstrRet;

   wstrRet.alloc(iLen1 + iLen2 + 1);

   wcscpy_dup(wstrRet, wstr1);

   wcscat_dup(wstrRet, wstr2);

   wstrRet.set_length(iLen1 + iLen2);

   return wstrRet;

}


verisimple_wstring operator + (const verisimple_wstring & wstr, const wchar_t * wpsz)
{
   return wstr + verisimple_wstring(wpsz);
}

verisimple_wstring operator + (const wchar_t * wpsz, const verisimple_wstring & wstr)
{
   return verisimple_wstring(wpsz) + wstr;
}


wstring gen_utf8_to_16(const char * psz)
{

   wstring wstr;

   ::count iLen = utf16_len(psz);

   if(iLen < 0)
      return wstr;

   wstr.alloc(iLen + 1);

   utf8_to_utf16(wstr, psz);

   wstr.set_length(iLen);

   return wstr;

}



verisimple_wstring verisimple_wstring::substr(::index iStart, ::count count)
{
   if(m_pwsz == NULL)
   {

      return L"";

   }
   else
   {

      if(count < 0)
      {
         count = get_data()->m_iLength - iStart + count + 1;
      }

      if(iStart + count > get_data()->m_iLength)
      {
         count = get_data()->m_iLength - iStart;
      }

      if(count <= 0)
      {
         return L"";
      }

      return wstring(&m_pwsz[iStart], count);

   }

}




verisimple_wstring & verisimple_wstring::replace(::index iStart,::count c,const wchar_t * psz)
{
   if(c < 0)
   {
      return operator = (substr(0,iStart) + psz);
   }
   else
   {
      return operator = (substr(0,iStart) + psz + substr(iStart + c));
   }
   

}