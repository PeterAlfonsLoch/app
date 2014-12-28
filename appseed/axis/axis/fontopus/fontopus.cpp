#include "framework.h"

//string url_get_server(const char * psz)
//{
//
//   string strRoot = url_get_root(psz);
//
//   strsize iPos = strRoot.find(":");
//
//   if (iPos < 0)
//      return strRoot;
//
//   return strRoot.Left(iPos);
//
//}
//
//
//string url_get_root(const char * psz)
//{
//   string str(psz);
//   index iPos = str.find(":");
//   if (iPos == -1)
//      return "";
//   iPos++;
//   while (iPos < str.get_length() && str[iPos] == '/')
//   {
//      iPos++;
//   }
//   index iStart = iPos;
//   index iEnd = str.find("/", iStart);
//   if (iEnd < 0)
//      return str.Mid(iStart);
//   else
//      return str.Mid(iStart, iEnd - iStart);
//}


namespace fontopus
{


   void set_cred_ok(::aura::application * papp,string strToken,bool bOk)
   {

      if(bOk)
      {

         Sys(papp).crypto().file_set(::dir::userappdata("cred/" + strToken + "_c.data"),"ok",strToken, papp);

      }
      else
      {
         Sys(papp).crypto().file_set(::dir::userappdata("cred/" + strToken + "_c.data"),"failed",strToken, papp);

      }

   }

   void set_cred(::aura::application * papp,string strToken,const char * pszUsername,const char * pszPassword)
   {

      string strUsername(pszUsername);
      string strPassword(pszPassword);
      string strUsernamePrevious;
      string strPasswordPrevious;

      get_cred(papp,strUsernamePrevious,strPasswordPrevious,strToken);

      if((strUsername.has_char() && strPassword.has_char())
         && (strUsernamePrevious != strUsername || strPasswordPrevious != strPassword))
      {
         dir::mk(::dir::userappdata("cred"));
         Sys(papp).crypto().file_set(::dir::userappdata("cred/" + strToken + "_a.data"),strUsername,"", papp);
         Sys(papp).crypto().file_set(::dir::userappdata("cred/" + strToken + "_b.data"),strPassword,strToken, papp);
      }

   }


   string CLASS_DECL_AXIS get_cred(::aura::application * papp,string & strUsername,string & strPassword,string strToken)
   {

      string str;
      Sys(papp).crypto().file_get(::dir::userappdata("cred/" + strToken + "_a.data"),strUsername,"", papp);
      Sys(papp).crypto().file_get(::dir::userappdata("cred/" + strToken + "_b.data"),strPassword,strToken, papp);
      Sys(papp).crypto().file_get(::dir::userappdata("cred/" + strToken + "_c.data"),str,strToken, papp);

      return str;

   }


   string CLASS_DECL_AXIS get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      return Sess(papp).get_cred(papp,strRequestUrlParam,rect,strUsername,strPassword,strToken,strTitle,bInteractive);
      
   }


} // namespace fontopus










