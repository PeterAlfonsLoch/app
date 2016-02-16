//#include "framework.h"

const int verisimple_wstring::npos = -1;

unichar * wstring_data::get_nil()
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


verisimple_wstring::verisimple_wstring(const unichar * pwsz,strsize iCount,manager * pmanager)
{

   UNREFERENCED_PARAMETER(pmanager);

   if(pwsz == NULL)
   {

      m_pwsz         = wstring_data::get_nil();

   }
   else
   {
      while(iCount < 0)
         iCount = unilen(pwsz) + iCount + 1;
      m_pwsz = (unichar *) wstring_data::alloc(iCount);
      get_data()->m_iLength = iCount;
      memcpy_dup(m_pwsz, pwsz, get_data()->m_iLength * sizeof(unichar));
      m_pwsz[get_data()->m_iLength] = L'\0';

   }
}


verisimple_wstring::verisimple_wstring(const unichar * pwsz,manager * pmanager)
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


void verisimple_wstring::assign(const unichar * pwsz)
{

   if(m_pwsz != NULL && m_pwsz != wstring_data::get_nil())
   {

      wstring_data::free(m_pwsz);

      m_pwsz = NULL;

   }

   ::count iLen         = wcslen_dup(pwsz);

   if (iLen == 0)
   {

      m_pwsz = wstring_data::get_nil();

      return;

   }

   m_pwsz = (unichar *)wstring_data::alloc(iLen);

   get_data()->m_iLength = iLen;

   memcpy_dup(m_pwsz,pwsz,get_data()->m_iLength * sizeof(unichar));

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

unichar * verisimple_wstring::alloc(::count iCount)
{

   if(m_pwsz != NULL && iCount < get_data()->m_iAllocation)
      return m_pwsz;

   wstring_data::free(m_pwsz);

   m_pwsz            = (unichar *) wstring_data::alloc(iCount);

   return m_pwsz;

}


verisimple_wstring & verisimple_wstring::operator = (const verisimple_wstring & wstr)
{

   if(this != &wstr)
   {

      if(m_pwsz != NULL && get_data()->m_iAllocation >= (wstr.length() + 1))
      {

         memcpy_dup(m_pwsz, wstr.m_pwsz, (wstr.length() + 1) * sizeof(unichar));

      }
      else
      {

         alloc(wstr.storage_size());
         memcpy_dup(m_pwsz, wstr.m_pwsz, storage_size() * sizeof(unichar));

      }

      set_length(wstr.get_length());


   }

   return *this;

}

verisimple_wstring & verisimple_wstring::operator = (const unichar * pwsz)
{

   if(m_pwsz != pwsz)
   {

      ::count iLen = wcslen_dup(pwsz);

      if(storage_size() >= (iLen + 1))
      {

         memcpy_dup(m_pwsz, pwsz, (iLen + 1) * sizeof(unichar));


      }
      else
      {

         alloc(iLen + 1);
         memcpy_dup(m_pwsz, pwsz, storage_size() * sizeof(unichar));
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


void verisimple_wstring::assign(const char * psz)
{

   ::count iLen = utf16_len(psz);

   alloc(iLen);

   utf8_to_utf16(m_pwsz, psz);

   set_length(iLen);

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


verisimple_wstring operator + (const verisimple_wstring & wstr, const unichar * wpsz)
{
   return wstr + verisimple_wstring(wpsz);
}

verisimple_wstring operator + (const unichar * wpsz, const verisimple_wstring & wstr)
{
   return verisimple_wstring(wpsz) + wstr;
}


wstring gen_utf8_to_16(const char * psz)
{

   wstring wstr;

   ::count iLen = utf16_len(psz);

   if(iLen < 0)
      return wstr;

   wstr.alloc(iLen);

   utf8_to_utf16(wstr, psz);

   wstr.set_length(iLen);

   return wstr;

}



verisimple_wstring verisimple_wstring::substr(::index iStart, ::count count)
{
   if(m_pwsz == NULL)
   {
      unichar push[]={0};
      return push;

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
         unichar push[]={0};
         return push;
      }

      return wstring(&m_pwsz[iStart], count);

   }

}




verisimple_wstring & verisimple_wstring::replace(::index iStart,::count c,const unichar * psz)
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



// find the first occurrence of character 'ch', starting at strsize 'iStart'
strsize verisimple_wstring::find(unichar ch,strsize iStart,strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();
   if(iStart < 0 || iStart >= nLength)
   {
      return npos;
   }

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart > nLength)
      nCount = nLength - iStart;

   if(nCount < 0)
      return npos;

   const unichar * psz = m_pwsz + iStart;
   for(int32_t i = 0; i < nCount; i++)
   {
      if(psz[i] == ch)
      {
         return iStart + i;
      }
   }
   return npos;
}
// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize verisimple_wstring::find(const unichar * pszSub,strsize iStart,strsize nCount,const unichar ** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if(pszSub == NULL)
   {
      return(npos);
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if(iStart < 0 || iStart > nLength)
   {
      return(npos);
   }

   strsize nLength2 = unilen(pszSub);

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart + nLength2 > nLength)
      nCount = nLength - iStart - nLength2;

   if(nCount < 0)
      return npos;

   const unichar * psz = m_pwsz + iStart;
   for(int32_t i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      int32_t j;
      for(j = 0; j < nLength2; j++)
      {
         if(psz[j] != pszSub[j])
         {
            bFound = false;
            break;
         }
      }
      if(bFound && j == nLength2)
      {
         if(pszTail)
            *pszTail = &psz[j];
         return i + iStart;
      }
      psz++;
   }
   return npos;
}
