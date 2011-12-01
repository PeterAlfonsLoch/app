#pragma once

/*extern DWORD g_MsDownloadSize;
extern char * g_MsDownloadBuffer;


bool ms_download(const char * pszUrl, const char * pszFile, bool bUrlEncode = true, int * piStatus = NULL);
bool ms_download_progress(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode = true, int * piStatus = NULL);
void dlr(DWORD dwDownload);
*/


CLASS_DECL_c void ms_download_callback(void * param, int i, DWORD_PTR dwLen);
CLASS_DECL_c void ms_get_callback(void * param, int i, DWORD_PTR dwLen);

CLASS_DECL_c void dlr(DWORD dwDownload);