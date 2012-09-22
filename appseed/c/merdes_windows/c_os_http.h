#pragma once

struct simple_http_status
{
public:

   DWORD             m_dwStatusCode;
   const char *      m_pszStatus;

};


CLASS_DECL_c void reset_http();
CLASS_DECL_c void prepare_http();


CLASS_DECL_c bool ms_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode = false, int * piStatus = NULL, void (*callback)(void *, int, dword_ptr) = NULL, void * callback_param = NULL);
CLASS_DECL_c vsstring ms_get_dup(const char * pszUrl, bool bCache = false, void (*callback)(void *, int, dword_ptr) = NULL, void * callback_param = NULL, bool bProgressCallback = false);
CLASS_DECL_c vsstring defer_ls_get(const char * pszUrl, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_c vsstring ms_post_dup(const char * pszUrl, const char * pszPost);