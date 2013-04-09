#pragma once

struct simple_http_status
{
public:

   uint32_t             m_dwStatusCode;
   const char *      m_pszStatus;

};


CLASS_DECL_c void reset_http();
CLASS_DECL_c void prepare_http();


CLASS_DECL_c bool ms_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode = false, int32_t * piStatus = ::null(), void (*callback)(void *, int32_t, uint_ptr) = ::null(), void * callback_param = ::null());
CLASS_DECL_c vsstring ms_get_dup(const char * pszUrl, bool bCache = false, void (*callback)(void *, int32_t, uint_ptr) = ::null(), void * callback_param = ::null(), bool bProgressCallback = false);
CLASS_DECL_c vsstring defer_ls_get(const char * pszUrl, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_c vsstring ms_post_dup(const char * pszUrl, const char * pszPost);