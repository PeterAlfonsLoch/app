#pragma once

struct simple_http_status
{
public:

   DWORD             m_dwStatusCode;
   const char *      m_pszStatus;

};

CLASS_DECL_____ bool ms_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode = false, int * piStatus = NULL, void (*callback)(void *, int, DWORD_PTR) = NULL, void * callback_param = NULL);
CLASS_DECL_____ vsstring ms_get_dup(const char * pszUrl, bool bCache = false, void (*callback)(void *, int, DWORD_PTR) = NULL, void * callback_param = NULL);
//CLASS_DECL_____ vsstring ms_post_dup(const char * pszUrl, const char * pszPost);