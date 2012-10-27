#include "framework.h"

verisimple_string::verisimple_string()
{
   m_psz = NULL;
}

verisimple_string::verisimple_string(const wchar_t * pwsz)
{

   m_psz = NULL;

   operator = (pwsz);

}


verisimple_string::verisimple_string(const char * psz)
{
   if(psz == NULL)
      m_psz = NULL;
   else
   {
      m_psz = (char *) strdup_dup(psz);
   }
}

verisimple_string::verisimple_string(char ch)
{
   m_psz = NULL;
   operator = (ch);
}

verisimple_string::verisimple_string(const char * psz, int_ptr count)
{
   if(psz == NULL)
      m_psz = NULL;
   else
   {
      if(count < 0)
         count += strlen_dup(psz) + 1;
      if(count > strlen_dup(psz))
         count = strlen_dup(psz);
      m_psz = strndup_dup(psz, count);
   }
}

verisimple_string::verisimple_string(const verisimple_string & str)
{
   m_psz = NULL;
   operator = (str);
}

verisimple_string::~verisimple_string()
{
   if(m_psz != NULL)
   {
//      g_pfixedallocaWstring->ca2_free(m_psz, (wcslen(m_psz) + 1) * 2);
      _ca_free(m_psz, 0);
   }
}

char * verisimple_string::alloc(::count iCount)
{
   clear();
   ::count iAlloc = (iCount + 1) * sizeof(char);
   //m_psz = (char *) g_pfixedallocaWstring->alloc(iAlloc);
   m_psz = (char *) _ca_alloc(iAlloc);
   m_psz[iCount] = L'\0';
   return m_psz;
}

count verisimple_string::get_length() const
{
   if(m_psz == NULL)
      return 0;
   return strlen_dup(m_psz);
}

count verisimple_string::size() const
{
   return get_length();
}

count verisimple_string::length() const
{
   return get_length();
}

verisimple_string & verisimple_string::operator = (const verisimple_string & str)
{
   if(this != &str)
   {
      operator = (str.m_psz);
   }
   return *this;
}

verisimple_string & verisimple_string::operator = (const char * psz)
{
   if(m_psz != psz)
   {
      if(m_psz != NULL)
      {
         clear();
      }
      if(psz == NULL)
         m_psz = NULL;
      else
      {
         m_psz = strdup_dup(psz);
      }
   }
   return *this;
}


verisimple_string & verisimple_string::operator = (char ch)
{
   if(m_psz != NULL)
   {
      //g_pfixedallocaWstring->ca2_free(m_psz, (wcslen(m_psz) + 1) * 2);
      _ca_free(m_psz, 0);
      m_psz = NULL;
   }
   if(ch == '\0')
   {
      m_psz = (char *) _ca_alloc(1);
      m_psz[0] = '\0';
   }
   else
   {
      //m_psz = (char *) g_pfixedallocaWstring->alloc((wcslen(psz) + 1) * 2);
      m_psz = (char *) _ca_alloc(2);
      m_psz[0] = ch;
      m_psz[1] = '\0';
   }
   return *this;
}

void verisimple_string::attach(const char * psz)
{
   if(m_psz != psz)
   {
      if(m_psz != NULL)
      {
         //g_pfixedallocaWstring->ca2_free(m_psz, (wcslen(m_psz) + 1) * 2);
         _ca_free(m_psz, 0);
         m_psz = NULL;
      }
      m_psz = (char *) psz;
   }
}

verisimple_string & verisimple_string::operator = (const wchar_t * pwsz)
{

   attach(utf16_to_8(pwsz));

   return *this;

}


void verisimple_string::trim_left()
{
   while(length() > 0 &&
      (m_psz[0] == '\n' || m_psz[0] == '\t'
      || m_psz[0] == '\r' || m_psz[0] == ' '))
   {
      *this = substr(1);
   }
}

void verisimple_string::trim_right()
{
   while(length() > 0 &&
      (m_psz[length() - 1] == '\n' || m_psz[length() - 1] == '\t'
      || m_psz[length() - 1] == '\r' || m_psz[length() - 1] == ' '))
   {
      *this = substr(0, length() - 1);
   }
}


void verisimple_string::trim()
{
   trim_left();
   trim_right();
}


verisimple_string verisimple_string::substr(index offset, count count) const
{
   if(count < 0)
      count += length() + 1;
   if(count < 0)
      return "";
   return verisimple_string(&m_psz[max(0, min(offset, length()))], count);
}

verisimple_string & verisimple_string::operator += (const char * psz)
{
   verisimple_string strSum = *this + psz;
   *this = strSum;
   return *this;
}

verisimple_string & verisimple_string::operator += (const verisimple_string & str)
{
   verisimple_string strSum = *this + str;
   *this = strSum;
   return *this;
}


verisimple_string operator + (const verisimple_string & str1, const verisimple_string & str2)
{

   count iLen1 = str1.length();

   count iLen2 = str2.length();

   verisimple_string strRet;

   char * pszRet = (char *) _ca_alloc(iLen1 + iLen2 + 1);

   strcpy_dup(pszRet, str1);

   strcat_dup(pszRet, str2);

   strRet.attach(pszRet);

   return strRet;

}


verisimple_string operator + (const verisimple_string & str, const char * psz)
{
   return str + verisimple_string(psz);
}


verisimple_string operator + (const char * psz, const verisimple_string & str)
{
   return verisimple_string(psz) + str;
}

verisimple_string operator + (const verisimple_string & str, char ch)
{
   return str + verisimple_string(ch);
}

verisimple_string operator + (char ch, const verisimple_string & str)
{
   return verisimple_string(ch) + str;
}


bool verisimple_string::ends_ci(const verisimple_string & strSuffix) const
{
   return ends_ci((const char *) strSuffix);
}

bool verisimple_string::ends_ci(const char * pszSuffix) const
{
   vsstring strSuffix(pszSuffix == NULL ? "" : pszSuffix);
   if(length() < strSuffix.length())
      return false;
   if(substr(length() - strSuffix.length(), strSuffix.length()).CompareNoCase(strSuffix) != 0)
      return false;
   return true;
}

bool verisimple_string::begins_ci(const verisimple_string & strPrefix) const
{
   return begins_ci((const char *) strPrefix);
}


bool verisimple_string::begins_ci(const char * pszPrefix) const
{
   vsstring strPrefix(pszPrefix == NULL ? "" : pszPrefix);
   if(length() < strPrefix.length())
      return false;
   if(substr(0, strPrefix.length()).CompareNoCase(strPrefix) != 0)
      return false;
   return true;
}

bool verisimple_string::ends(const verisimple_string & strSuffix) const
{
   return ends((const char *) strSuffix);
}

bool verisimple_string::ends(const char * pszSuffix) const
{
   vsstring strSuffix(pszSuffix == NULL ? "" : pszSuffix);
   if(length() < strSuffix.length())
      return false;
   if(substr(length() - strSuffix.length(), strSuffix.length()) != strSuffix)
      return false;
   return true;
}


bool verisimple_string::begins(const verisimple_string & strPrefix) const
{
   return begins((const char *) strPrefix);
}


bool verisimple_string::begins(const char * pszPrefix) const
{
   vsstring strPrefix(pszPrefix == NULL ? "" : pszPrefix);
   if(length() < strPrefix.length())
      return false;
   if(substr(0, strPrefix.length()) != strPrefix)
      return false;
   return true;
}

bool verisimple_string::begins_eat(const char * pszPrefix)
{
   if(!begins(pszPrefix))
      return false;
   *this = substr(strlen_dup(pszPrefix));
   return true;
}

bool verisimple_string::begins_eat(const verisimple_string & strPrefix)
{
   return begins_eat((const char *) strPrefix);
}

bool verisimple_string::begins_eat_ci(const char * pszPrefix)
{
   if(!begins_ci(pszPrefix))
      return false;
   *this = substr(strlen_dup(pszPrefix));
   return true;
}

bool verisimple_string::begins_eat_ci(const verisimple_string & strPrefix)
{
   return begins_eat_ci((const char *) strPrefix);
}


bool verisimple_string::operator == (const char * psz) const
{
   return CompareCase(psz) == 0;
}

bool verisimple_string::operator == (const verisimple_string & str) const
{
   return CompareCase(str) == 0;
}

bool verisimple_string::operator != (const char * psz) const
{
   return CompareCase(psz) != 0;
}

bool verisimple_string::operator != (const verisimple_string &str) const
{
   return CompareCase(str) != 0;
}

int verisimple_string::CompareCase(const char * psz) const
{
   return strcmp_dup(m_psz, psz);
}

int verisimple_string::CompareCase(const verisimple_string &str) const
{
   return strcmp_dup(m_psz, str);
}

int verisimple_string::CompareNoCase(const char * psz) const
{
   return stricmp_dup(m_psz, psz);
}

int verisimple_string::CompareNoCase(const verisimple_string &str) const
{
   return stricmp_dup(m_psz, str);
}


index verisimple_string::rfind(char ch) const
{
   const char * psz = m_psz + length() - 1;
   while(psz >= m_psz)
   {
      if(*psz == ch)
         return psz - m_psz;

      psz--;
   }

   return -1;
}

index verisimple_string::rfind(char ch, index iFind) const
{
   if(iFind >= length())
      iFind = length() - 1;
   const char * psz = m_psz + iFind;
   while(psz >= m_psz)
   {
      if(*psz == ch)
         return psz - m_psz;

      psz--;
   }

   return -1;
}


bool verisimple_string::is_empty() const
{
   return length() <= 0;
}

bool verisimple_string::has_char() const
{
   return length() > 0;
}


vsstring std_gen_international_unicode_to_utf8(const wchar_t * psz)
{
	CHAR * pszNew = utf16_to_8(psz);
	vsstring str(pszNew);
	delete pszNew;
	return str;
}

index verisimple_string::find(const verisimple_string & str, index iStart) const
{
   return find((const char *) str, iStart);
}

index verisimple_string::find(const char * str, index iStart) const
{
   if(iStart < 0)
      iStart = 0;
   if(iStart >= strlen_dup(m_psz))
      return -1;

   const char * pszFind = strstr_dup(&m_psz[iStart], str);
   if(pszFind == NULL)
      return -1;
   return pszFind - m_psz;
}

void verisimple_string::replace(const char * pszFind, const char * pszReplace)
{
   size_t sPosNew;
   size_t sPosOld = 0;
   size_t lenFind = strlen_dup(pszFind);
   size_t lenReplace = strlen_dup(pszReplace);

   while(true)
   {
      sPosNew = find(pszFind, sPosOld);
      if(sPosNew == size_t(-1))
         break;
      *this = substr(0, sPosNew) + pszReplace + substr(sPosNew + lenFind);
      sPosOld = sPosNew + lenReplace;
   }
}

index verisimple_string::find_ci(const verisimple_string & str, index iStart) const
{
   return find_ci((const char *) str, iStart);
}

index verisimple_string::find_ci(const char * str, index iStart) const
{
   if(iStart < 0)
      iStart = 0;
   if(iStart >= strlen_dup(m_psz))
      return -1;

   const char * pszFind = stristr_dup(&m_psz[iStart], str);
   if(pszFind == NULL)
      return -1;
   return pszFind - m_psz;
}

void verisimple_string::replace_ci(const char * pszFind, const char * pszReplace)
{
   size_t sPosNew;
   size_t sPosOld = 0;
   size_t lenFind = strlen_dup(pszFind);
   size_t lenReplace = strlen_dup(pszReplace);

   while(true)
   {
      sPosNew = find_ci(pszFind, sPosOld);
      if(sPosNew == 0xffffffff)
         break;
      *this = substr(0, sPosNew) + pszReplace + substr(sPosNew + lenFind);
      sPosOld = sPosNew + lenReplace;
   }
}

void verisimple_string::clear()
{
   if(m_psz != NULL)
   {
      _ca_free(m_psz, 0);
      m_psz = NULL;
   }
}



char & verisimple_string::operator [] (index iIndex)
{
    return (char &) (*((char *) &m_psz[iIndex]));
}

char verisimple_string::operator [] (index iIndex) const
{
    return m_psz[iIndex];
}


CLASS_DECL_c vsstring gen_utf16_to_8(const wchar_t * psz)
{
   return vsstring(utf16_to_8(psz));
}



