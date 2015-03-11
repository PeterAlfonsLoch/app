#pragma once


namespace url
{


   CLASS_DECL_AURA bool is_url(const char * pszCandidate,const char ** ppszRequest = NULL);


} // namespace url




inline bool is_url_dup(const string & strCandidate)
{
   
   return ::url::is_url(strCandidate);

}































