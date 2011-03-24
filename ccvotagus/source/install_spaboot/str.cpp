#include "install_spaboot.h"



void strcat_dup(char * dest, const char * cat)
{
   while(*dest != 0)
      dest++;
   while(*cat != 0)
      *dest++ = *cat++;
   *dest = '\0';
}

void strcpy_dup(char * dest, const char * cpy)
{
   while(*cpy != 0)
      *dest++ = *cpy++;
   *dest = '\0';
}

int  strlen_dup(const char * str)
{
   const char * pszEnd = str;
   while(*pszEnd != 0)
      pszEnd++;
   return pszEnd - str;
}

const char * strdup_dup(const char * src)
{
   int iLen = strlen_dup(src);
   char * dup = (char *) malloc(iLen + 1);
   strcpy_dup(dup, src);
   return dup;
}

int stricmp_dup(const char * sz1, const char * sz2)
{
   if(sz1 == NULL)
   {
      if(sz2 == NULL)
         return 0;
      else
         return 1;
   }
   else if(sz2 == NULL)
   {
      return -1;
   }
   int iCmp;
   while(*sz1 != '\0' && *sz2 != '\0')
   {
      iCmp = to_lower(*sz1) - to_lower(*sz2);
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
   }
   return *sz1 - *sz2;
}

int strcmp_dup(const char * sz1, const char * sz2)
{
   if(sz1 == NULL)
   {
      if(sz2 == NULL)
         return 0;
      else
         return 1;
   }
   else if(sz2 == NULL)
   {
      return -1;
   }
   int iCmp;
   while(*sz1 != '\0' && *sz2 != '\0')
   {
      iCmp = *sz1 - *sz2;
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
   }
   return *sz1 - *sz2;
}

char * strrch_dup(char * szStart, char ch)
{
   char * sz = szStart;
   while(*sz != '\0')
   {
      sz++;
   }
   while(sz != szStart)
   {
      sz--;
      if(*sz == ch)
         return sz;
   }
   return NULL;

}

char to_lower(int ch)
{
   if(ch >= 'A' && ch <= 'Z')
   {
      ch = ch - 'A' + 'a';
   }
   return ch;
}

const char * strstr_dup(const char * src, const char * find)
{
   while(*src != '\0')
   {
      const char * srcParse = src;
      const char * findParse = find;
      while(*srcParse != '\0' && *findParse != '\0')
      {
         if(*srcParse != *findParse)
            break;
         srcParse++;
         findParse++;
      }
      if(*findParse == '\0')
         return src;
      src++;
   }
   return NULL;
}

const char * stristr_dup(const char * src, const char * find)
{
   while(*src != '\0')
   {
      const char * srcParse = src;
      const char * findParse = find;
      while(*srcParse != '\0' && *findParse != '\0')
      {
         if(to_lower(*srcParse) != to_lower(*findParse))
            break;
         srcParse++;
         findParse++;
      }
      if(*findParse == '\0')
         return src;
      src++;
   }
   return NULL;
}


const char * read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType)
{
	
   HRSRC hrsrc = ::FindResource(hinst, MAKEINTRESOURCE(nID), lpcszType);
	
   if(hrsrc == NULL)
		return NULL;
   
   HGLOBAL hres = ::LoadResource(hinst, hrsrc);
	
   if(hres == NULL)
		return NULL;
   
   DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

   char * psz = NULL;

	if(hres != NULL)
   {
	
      UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);

      psz = (char *) malloc(dwResSize + 1);
      memcpy_dup(psz, lpnRes, dwResSize);
      psz[dwResSize] = '\0';
      ::FreeResource(hres);
	}
	
   return psz;

}
