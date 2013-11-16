#include "framework.h"

string_to_string                         m_mapFontopusServer;

string url_get_server(const char * psz)
{

   string strRoot = url_get_root(psz);

   strsize iPos = strRoot.find(":");

   if (iPos < 0)
      return strRoot;

   return strRoot.Left(iPos);

}


string url_get_root(const char * psz)
{
   string str(psz);
   index iPos = str.find(":");
   if (iPos == -1)
      return "";
   iPos++;
   while (iPos < str.get_length() && str[iPos] == '/')
   {
      iPos++;
   }
   index iStart = iPos;
   index iEnd = str.find("/", iStart);
   if (iEnd < 0)
      return str.Mid(iStart);
   else
      return str.Mid(iStart, iEnd - iStart);
}

namespace fontopus
{


   string get_server(const char * pszUrl, int32_t iRetry)
   {

      string strFontopusServer;

      if (m_mapFontopusServer.Lookup(pszUrl, strFontopusServer) && strFontopusServer.has_char())
      {
         return strFontopusServer;
      }

   retry:

      if (iRetry < 0)
         return ""; // should not retry or lookup is valid and strFontopusServer is really empty

      string strGetFontopus("http://" + url_get_server(pszUrl) + "/get_fontopus");
      try
      {
         strFontopusServer = http_get_dup(strGetFontopus);
      }
      catch (...)
      {
      }

      m_mapFontopusServer.set_at(pszUrl, strFontopusServer);

      iRetry--;

      if (strFontopusServer.is_empty())
         goto retry;

      return strFontopusServer;

   }


} // namespace fontopus