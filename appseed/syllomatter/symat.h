#pragma once


class CLASS_DECL_CA2_SYLLOMATTER symat :
   public bergedge_object_impl1
{
public:
   void create(const WCHAR * psz);
   void checkout(const WCHAR * pszRepos, const WCHAR * pszPath);
};