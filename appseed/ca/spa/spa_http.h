#pragma once

/*extern uint32_t g_MsDownloadSize;
extern char * g_MsDownloadBuffer;


bool ms_download(const char * pszUrl, const char * pszFile, bool bUrlEncode = true, int32_t * piStatus = NULL);
bool ms_download_progress(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode = true, int32_t * piStatus = NULL);
void dlr(uint32_t dwDownload);
*/


CLASS_DECL_ca void ms_download_callback(void * param, int32_t i, uint_ptr dwLen);
CLASS_DECL_ca void ms_get_callback(void * param, int32_t i, uint_ptr dwLen);

CLASS_DECL_ca void dlr(uint32_t dwDownload);