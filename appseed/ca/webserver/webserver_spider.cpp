#include "StdAfx.h"

namespace webserver
{


match_host::match_host(const char * hostname, const char * useragent)
{
   m_strHostname = hostname;
   m_strUserAgent = useragent;
   if(m_strHostname.has_char())
   {
      m_ppcreHostname = cregexp_util::CompileExpression(m_strHostname, true);
   }
   else
   {
      m_ppcreHostname = NULL;
   }
   if(m_strUserAgent.has_char())
   {
      m_ppcreUserAgent = cregexp_util::CompileExpression(m_strUserAgent, true);
   }
   else
   {
      m_ppcreUserAgent = NULL;
   }
}

match_host::~match_host()
{
   if(m_ppcreHostname != NULL)
   {
      delete m_ppcreHostname;
      m_ppcreHostname = NULL;
   }
   if(m_ppcreUserAgent != NULL)
   {
      delete m_ppcreUserAgent;
      m_ppcreUserAgent = NULL;
   }

}

bool match_host::matches(const char * hostname, const char * useragent)
{
   bool bTest = false;
   if(m_ppcreHostname != NULL)
   {
      bTest = true;
      if(!cregexp_util::match(hostname, m_ppcreHostname))
      {
         return false;
      }
   }
   if(m_ppcreUserAgent != NULL)
   {
      bTest = true;
      if(!cregexp_util::match(useragent, m_ppcreUserAgent))
      {
         return FALSE;
      }
   }
   return bTest;
}


} // namespace webserver