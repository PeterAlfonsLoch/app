#include "StdAfx.h"
   
   void url_domain::create(const char * pszServerName)
   {
      m_strOriginalName = pszServerName;
      if(m_strOriginalName.is_empty())
         return;
      m_stra.add_tokens(pszServerName, ".", TRUE);
      m_bHasWww = m_stra[0] == "www";
      if(m_bHasWww)
      {
         m_stra.remove_at(0);
      }
      m_iCount = m_stra.get_size();
      if(m_iCount <= 1)
      {
         m_strRadix  = pszServerName;
         m_strRadix  = m_strDomain;
         m_strName   = m_strDomain;
         return;
      }
      if(m_iCount == 2)
      {
         m_strSuffix = m_stra[1];
         m_strRadix  = m_stra[0];
         m_strDomain = m_strRadix + "." + m_strSuffix;
         m_strName   = m_strDomain;
         m_strTopLevel = m_stra[1];
         return;
      }
      if(m_stra[m_iCount - 1] == "br" && m_stra[m_iCount - 2] == "nom")
      {
         m_strSuffix    = m_stra[m_iCount - 2] + "." + m_stra[m_iCount - 1];
         m_strRadix     = m_stra[m_iCount - 4] + "." + m_stra[m_iCount - 3];
         m_strPrefix    = m_stra.implode(".", 0, m_iCount - 4);
      }
      else if(m_stra[m_iCount - 1] == "am" 
         && (m_stra[m_iCount - 2] == "north" ||
         m_stra[m_iCount - 2] == "south"))
      {
         m_strSuffix    = m_stra[m_iCount - 2] + "." + m_stra[m_iCount - 1];
         m_strTopLevel  = m_strSuffix;
         m_strRadix     = m_stra[m_iCount - 3];
         m_strPrefix    = m_stra.implode(".", 0, m_iCount - 3);
         m_strDomain = m_strRadix + "." + m_strSuffix;
         if(m_strPrefix.get_length() > 0)
            m_strName   = m_strPrefix + "." + m_strDomain;
         else
            m_strName   = m_strDomain;
         return;
      }
      else    if(server_is_top_domain(m_stra[m_iCount - 1], m_stra[m_iCount - 2]))
      {
         m_strSuffix = m_stra[m_iCount - 2] + "." +m_stra[m_iCount - 1];
         m_strRadix  = m_stra[m_iCount - 3];
         m_strPrefix = m_stra.implode(".", 0, m_iCount - 3);
      }
      else
      {
         m_strSuffix = m_stra[m_iCount - 1];
         m_strRadix  = m_stra[m_iCount - 2];
         m_strPrefix = m_stra.implode(".", 0, m_iCount - 2);
      }
      m_strDomain = m_strRadix + "." + m_strSuffix;
      if(m_strPrefix.get_length() > 0)
         m_strName   = m_strPrefix + "." + m_strDomain;
      else
         m_strName   = m_strDomain;
      m_strTopLevel = m_stra[m_iCount - 1];
   }
   
   bool CLASS_DECL_ca server_is_top_domain(string strTop1, string strTop2)
   {
      if(strTop1 == "ar")
      {
         if(strTop2 == "com")
         {
            return true;
         }
      }
      else if(strTop1 == "at")
      {
         if(strTop2 == "co"
         || strTop2 == "or")
         {
            return true;
         }
      }
      else if(strTop1 == "br")
      {
         if(strTop2 == "blog"
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
         }
      }
      else if(strTop1 == "cc")
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
      }
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


