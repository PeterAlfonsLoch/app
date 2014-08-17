#include "framework.h"

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
