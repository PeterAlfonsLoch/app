#include "StdAfx.h"

void symat::create(const WCHAR * psz)
{
   string str = International::UnicodeToUtf8(psz);
   ca2::app(get_app()).dir().mk(str);
   ca2::app(get_app()).dir().mk(ca2::app(get_app()).dir().path(str, "base"));
   ca2::app(get_app()).dir().mk(ca2::app(get_app()).dir().path(str, "file"));
   ca2::app(get_app()).dir().mk(ca2::app(get_app()).dir().path(str, "dir"));

}

void symat::checkout(const WCHAR * pszRepos, const WCHAR * pszPath)
{
   string strRepos = International::UnicodeToUtf8(pszRepos);
   string strPath = International::UnicodeToUtf8(pszPath);
   string strBase = ca2::app(get_app()).dir().name(strPath);
   string strTitle = ca2::app(get_app()).file().title(strPath);
   string strSyllo = ca2::app(get_app()).dir().path(strBase, "syllomatter");
   string strSylloBase = ca2::app(get_app()).dir().path(strSyllo, strTitle);
   string strProperty = ca2::app(get_app()).dir().path(strSylloBase, "property.txt");
   ca2::app(get_app()).dir().mk(strPath);
   ca2::app(get_app()).dir().mk(ca2::app(get_app()).dir().path(strSylloBase, "file"));
   ca2::app(get_app()).dir().mk(ca2::app(get_app()).dir().path(strSylloBase, "dir"));
   string strContent;
   strContent += "SystemVersion: 1\n";
   strContent += "RepositoryPath: " + strRepos + "\n";
   ca2::app(get_app()).file().put_contents(strProperty, strContent);
}