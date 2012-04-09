#include "StdAfx.h"

url_domain_base::url_domain_base()
{
   
   m_pszRadix     = NULL;
   m_iLenRadix    = 0;
   m_pszSuffix    = NULL;
   m_iLenSuffix   = 0;
   m_pszDomain    = NULL;
   m_iLenDomain   = 0;
   m_pszPrefix    = NULL;
   m_iLenPrefix   = 0;
   m_pszTopLevel  = NULL;
   m_iLenTopLevel = 0;
   m_pszName      = NULL;
   m_iLenName     = 0;

   m_iCount       = 0;
   m_bHasWww      = false;

}

   void url_domain_base::create(const char * pszServerName)
   {
      m_strOriginalName = pszServerName;
      if(m_strOriginalName.is_empty())
         return;
      const char * psz = m_strOriginalName;
      m_iCount = 1;
      while(*psz != '\0')
      {
         if(*psz == '.')
            m_iCount++;
         psz++;
      }
      psz = m_strOriginalName;
      m_bHasWww = gen::str::begins(pszServerName, "www.");
      if(m_bHasWww)
      {
         psz += 4;
         m_iCount--;
      }
      const char * pszEnd = ((LPCTSTR) m_strOriginalName) + m_strOriginalName.get_length();
      m_pszTopLevel = pszEnd;
      while(m_pszTopLevel > psz && *m_pszTopLevel != '.')
      {
         m_pszTopLevel--;
         m_iLenTopLevel++;
      }
      if(*m_pszTopLevel == '.')
      {
         m_pszTopLevel++;
         m_iLenTopLevel--;
      }
      else
      {
         m_pszTopLevel     = NULL;
         m_iLenTopLevel    = 0;
         m_pszRadix        = psz;
         m_iLenRadix       = m_strOriginalName.get_length();
         m_pszDomain       = psz;
         m_iLenDomain      = m_strOriginalName.get_length();
         m_pszName         = psz;
         m_iLenName        = m_strOriginalName.get_length();
         return;
      }
      if(m_iCount == 2)
      {
         m_pszSuffix       = m_pszTopLevel;
         m_iLenSuffix      = m_iLenTopLevel;
         m_pszRadix        = psz;
         m_iLenRadix       = (m_pszTopLevel - 1) - psz;
         m_pszDomain       = m_pszRadix;
         m_iLenDomain      = m_iLenRadix + 1 + m_iLenTopLevel;
         m_pszName         = m_pszDomain;
         m_iLenName        = m_iLenDomain;
         return;
      }
      const char * pszPreTopLevel = m_pszTopLevel - 2;
      int iLenPreTopLevel = 0;
      while(pszPreTopLevel > psz && *pszPreTopLevel != '.')
      {
         pszPreTopLevel--;
         iLenPreTopLevel++;
      }
      if(*pszPreTopLevel == '.')
      {
         pszPreTopLevel++;
      }
      else
      {
         throw "not_expected";
      }
      const char * pszPreTopLevel2 = NULL;
      int iLenPreTopLevel2 = 0;
      const char * pszPreTopLevel3 = NULL;
      int iLenPreTopLevel3 = 0;
      if(m_iCount >= 4)
      {
         pszPreTopLevel2 = pszPreTopLevel - 2;
         while(pszPreTopLevel2 > psz && *pszPreTopLevel2 != '.')
         {
            pszPreTopLevel2--;
            iLenPreTopLevel2++;
         }
         if(*pszPreTopLevel2 == '.')
         {
            pszPreTopLevel2++;
         }
         else
         {
            throw "not_expected";
         }
         if(m_iCount >= 5)
         {
            pszPreTopLevel3 = pszPreTopLevel2 - 2;
            while(pszPreTopLevel3 > psz && *pszPreTopLevel3 != '.')
            {
               pszPreTopLevel3--;
               iLenPreTopLevel2++;
            }
            if(*pszPreTopLevel3 == '.')
            {
               pszPreTopLevel3++;
            }
            else
            {
               throw "not_expected";
            }
         }
      }
      if(m_iLenTopLevel == 2 
      && m_pszTopLevel[0] == 'b'
      && m_pszTopLevel[1] == 'r'
      && iLenPreTopLevel == 3
      && pszPreTopLevel[0] == 'n'
      && pszPreTopLevel[1] == 'o'
      && pszPreTopLevel[2] == 'm'
      )
      {
         m_pszSuffix       = pszPreTopLevel;
         m_iLenSuffix      = pszEnd - pszPreTopLevel;
         if(m_iCount <= 4)
         {
            m_pszRadix     = psz;
            m_iLenRadix    = (pszPreTopLevel - 1) - psz;
         }
         else
         {
            m_pszRadix     = pszPreTopLevel3;
            m_iLenRadix    = (pszPreTopLevel - 1) - pszPreTopLevel3;
            m_pszPrefix    = psz;
            m_iLenPrefix   = (pszPreTopLevel3 - 1) - psz;
         }
      }
      else if(m_iLenTopLevel == 2 
      && m_pszTopLevel[0] == 'am'
      && m_pszTopLevel[1] == 'r'
      && iLenPreTopLevel == 5
      && ((pszPreTopLevel[0] == 'n'
      &&   pszPreTopLevel[2] == 'r') ||
          (pszPreTopLevel[0] == 's'
      &&   pszPreTopLevel[1] == 'u'))
      && pszPreTopLevel[1] == 'o'
      && pszPreTopLevel[3] == 't'
      && pszPreTopLevel[4] == 'h'
         )
      {
         m_pszSuffix       = pszPreTopLevel;
         m_iLenSuffix      = pszEnd - pszPreTopLevel;
         m_pszTopLevel     = pszPreTopLevel;
         m_iLenTopLevel    = pszEnd - pszPreTopLevel;
         if(m_iCount <= 3)
         {
            m_pszRadix     = psz;
            m_iLenRadix    = (pszPreTopLevel - 1) - psz;
            m_pszName      = m_pszRadix;
            m_iLenName     = pszEnd - m_pszDomain;
         }
         else
         {
            m_pszRadix     = pszPreTopLevel2;
            m_iLenRadix    = (pszPreTopLevel - 1) - pszPreTopLevel2;
            m_pszPrefix    = psz;
            m_iLenPrefix   = (pszPreTopLevel2 - 1) - psz;
            m_pszName      = m_pszPrefix;
            m_iLenName     = pszEnd - m_pszPrefix;
         }
         m_pszDomain       = m_pszRadix;
         m_iLenDomain      = pszEnd - m_pszDomain;
         return;
      }
      else if(server_is_top_domain(m_pszTopLevel, m_iLenTopLevel, pszPreTopLevel, iLenPreTopLevel))
      {
         m_pszSuffix       = pszPreTopLevel;
         m_iLenSuffix      = pszEnd - pszPreTopLevel;
         if(m_iCount <= 3)
         {
            m_pszRadix     = psz;
            m_iLenRadix    = (pszPreTopLevel - 1) - psz;
         }
         else
         {
            m_pszRadix     = pszPreTopLevel2;
            m_iLenRadix    = (pszPreTopLevel - 1) - pszPreTopLevel2;
            m_pszPrefix    = psz;
            m_iLenPrefix   = (pszPreTopLevel2 - 1) - psz;
         }
      }
      else
      {
         m_pszSuffix       = m_pszTopLevel;
         m_iLenSuffix      = m_iLenTopLevel;
         m_pszRadix        = pszPreTopLevel;
         m_iLenRadix       = (m_pszTopLevel - 1) - pszPreTopLevel;
         m_pszPrefix       = psz;
         m_iLenPrefix      = (pszPreTopLevel - 1) - psz;
      }
      m_pszDomain       = m_pszRadix;
      m_iLenDomain      = pszEnd - m_pszDomain;
      if(m_pszPrefix != NULL)
      {
         m_pszName      = m_pszPrefix;
         m_iLenName     = pszEnd - m_pszPrefix;
      }
      else
      {
         m_pszName      = m_pszDomain;
         m_iLenName     = m_iLenDomain;
      }
   }


   string url_domain_base::get_name(const char * pszServerName)
   {
   
      url_domain_base domainbase;

      domainbase.create(pszServerName);

      if(domainbase.m_pszName != NULL)
         return string(domainbase.m_pszName, domainbase.m_iLenName);
      else
         return "";

   }

   void url_domain::create(const char * pszServerName)
   {

      url_domain_base::create(pszServerName);

      if(m_pszRadix != NULL)
      {
         m_strRadix.assign(m_pszRadix, m_iLenRadix);
      }

      if(m_pszSuffix != NULL)
      {
         m_strSuffix.assign(m_pszSuffix, m_iLenSuffix);
      }

      if(m_pszDomain != NULL)
      {
         m_strDomain.assign(m_pszDomain, m_iLenDomain);
      }

      if(m_pszPrefix != NULL)
      {
         m_strPrefix.assign(m_pszPrefix, m_iLenPrefix);
      }

      if(m_pszTopLevel != NULL)
      {
         m_strTopLevel.assign(m_pszTopLevel, m_iLenTopLevel);
      }

      if(m_pszName != NULL)
      {
         m_strName.assign(m_pszName, m_iLenName);
      }
   }


   bool CLASS_DECL_ca server_is_top_domain(const char * pszTop1, int blen, const char * pszTop2, int alen)
   {
      char a1;
      char a2;
      char a3;
      char b1;
      char b2;
      char b3;
      if(blen >= 1)
      {
         b1 = pszTop1[0];
         if(blen >= 2)
         {
            b2 = pszTop1[1];
            if(blen >= 3)
            {
               b3 = pszTop1[2];
            }
            else
            {
               b3 = '\0';
            }
         }
         else
         {
            b2 = '\0';
            b3 = '\0';
         }
      }
      else
      {
         b1 = '\0';
         b2 = '\0';
         b3 = '\0';
      }
      if(alen >= 1)
      {
         a1 = pszTop2[0];
         if(alen >= 2)
         {
            a2 = pszTop2[1];
            if(alen >= 3)
            {
               a3 = pszTop2[2];
            }
            else
            {
               a3 = '\0';
            }
         }
         else
         {
            a2 = '\0';
            a3 = '\0';
         }
      }
      else
      {
         a1 = '\0';
         a2 = '\0';
         a3 = '\0';
      }
      if(alen == 3 && a1 == 'c' && a2 == 'o' && a3 == 'm')
         return true;
      if(b1 == 'a')
      {
         if(b2 == 'r')
         {
         }
         else if(b2 == 't')
         {
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'b')
      {
         if(b2 == 'r')
         {
            if(alen == 2)
            {
               if(a1 == 't' && a2 == 'v')
               {
                  return true;
                }
            }
         }
         /*if(strTop2 == "blog"
         || strTop2 == "com"
         || strTop2 == "emp"
         || strTop2 == "eng"
         || strTop2 == "etc"
         || strTop2 == "flog"
         || strTop2 == "ind"
         || strTop2 == "mus"
         || strTop2 == "net"
         || strTop2 == "nom"
         || strTop2 == "pro"
         || strTop2 == "radio"
         || strTop2 == "tv"
         || strTop2 == "vlog"
         || strTop2 == "wiki")
         {
            return true;
         }*/
      }
/*      else if(strTop1 == "cc")
      {
         if(strTop2 == "cc"
         || strTop2 == "co")
         {
            return true;
         }
      }
      else if(strTop1 == "cn")
      {
         if(strTop2 == "net"
         || strTop2 == "org")
         {
            return true;
         }
      }
      else if(strTop1 == "co")
      {
         if(strTop2 == "com"
         || strTop2 == "net"
         || strTop2 == "org"
         || strTop2 == "nom")
         {
            return true;
         }
      }
      else if(strTop1 == "com")
      {
         if(strTop2 == "asia"
         || strTop2 == "de"
         || strTop2 == "eu"
         || strTop2 == "uk"
         || strTop2.get_length() == 2)
         {
            return true;
         }
      }
      else if(strTop1 == "de")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "ee")
      {
         if(strTop2 == "co"
         || strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "es")
      {
         if(strTop2 == "com"
         || strTop2 == "nom"
         || strTop2 == "org")
         {
            return true;
         }
      }
      else if(strTop1 == "gt")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "ht")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "hu")
      {
         if(strTop2 == "co")
         {
            return true;
         }
      }
      else if(strTop1 == "il")
      {
         if(strTop2 == "co"
         || strTop2 == "org")
         {
            return true;
         }
      }
      else if(strTop1 == "in")
      {
         if(strTop2 == "co"
         || strTop2 == "firm"
         || strTop2 == "gen"
         || strTop2 == "ind"
         || strTop2 == "net"
         || strTop2 == "org")
         {
            return true;
         }
      }
      else if(strTop1 == "jp")
      {
         if(strTop2 == "co"
         || strTop2 == "ne"
         || strTop2 == "or")
         {
            return true;
         }
      }
      else if(strTop1 == "lv")
      {
         if(strTop2 == "com"
         || strTop2 == "net"
         || strTop2 == "org")
         {
            return true;
         }
      }
      else if(strTop1 == "mx")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "nl")
      {
         if(strTop2 == "co")
         {
            return true;
         }
      }
      else if(strTop1 == "nz")
      {
         if(strTop2 == "co")
         {
            return true;
         }
      }
      else if(strTop1 == "pt")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "ru")
      {
         if(strTop2 == "msk"
         || strTop2 == "spb"
         || strTop2 == "nov"
         || strTop2 == "net"
         || strTop2 == "org"
         || strTop2 == "pp")
         {
            return true;
         }
      }
      else if(strTop1 == "su")
      {
         if(strTop2 == "msk"
         || strTop2 == "spb"
         || strTop2 == "nov"
         || strTop2 == "net"
         || strTop2 == "org"
         || strTop2 == "pp")
         {
            return true;
         }
      }
      else if(strTop1 == "tr")
      {
         if(strTop2 == "tv"
         || strTop2 == "web"
         || strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "tw")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "ua")
      {
         if(strTop2 == "co"
         || strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "uk")
      {
         if(strTop2 == "me"
         || strTop2 == "org"
         || strTop2 == "co")
         {
            return true;
         }

      }
      else if(strTop1 == "pl")
      {
         if(strTop2 == "biz"
         || strTop2 == "com"
         || strTop2 == "info"
         || strTop2 == "net"
         || strTop2 == "org")
         {
            return true;
         }
      }*/
      return false;
   }

/*      bool url_domain_in(string str, string url)
   {
      int iPos = url.reverse_find('.');
      if(iPos < 0)
         return false;
      int iLen = str.get_length();
      if(url.get_length() < iLen + 1)
         return false;
      if(url[iLen] != '.')
         return false;
      if(iPos == 0)
         return true;
      if(url[iPos - 1] == '.')
         return true;
      else
         return false;
   }

   void url_domain_prefix(string suffix, string url, string & prefix)
   {
      int iLen = url.get_length();
      int iSufLen = suffix.get_length();
      if(iLen < iSufLen)
         return false;
      int iPos = iLen - iSufLen;
      if(strsubstr($str, $pos) != $suffix)
         return false;
      if($pos == 0)
         return true;
      if($pos == 1)
         return false;
      if($url[$pos - 1] != '.')
         return false;
      $prefix = substr($url, 0, $pos - 1);
      return true;
   }*/


