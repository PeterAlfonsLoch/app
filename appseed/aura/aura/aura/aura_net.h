#pragma once


CLASS_DECL_AURA string url_encode_dup(const char * psz);


CLASS_DECL_AURA string url_decode_dup(const char * psz);
CLASS_DECL_AURA string url_decode_dup(const char * lpszUrl,strsize iLen);


CLASS_DECL_AURA bool url_query_get_param_dup(string & strParam,const char * pszKey,const char * pszUrl);



#if defined(APPLEOS)

CLASS_DECL_AURA void openURL(const string &url_str);

#endif






class open_url :
   virtual public ::object
{
public:
   
   
   string m_strLink;
   string m_strTarget;
   
   
   open_url(sp(::aura::application) papp, const string & strLink,const string & pszTarget);
   
   bool open();

   static uint32_t c_cdecl thread_proc(void * p);

   static bool start(sp(::aura::application) papp, const string & strLink,const string & strTarget);

};


