#include "install_spaboot.h"

DWORD g_MsDownloadSize = 0;
char * g_MsDownloadBuffer = 0;
char * g_pszCa2Build = NULL;

void initialize_http_dup()
{
   if(g_MsDownloadSize == 0)
   {
      g_MsDownloadSize = 1024 * 128;
      g_MsDownloadBuffer = (char *) malloc(g_MsDownloadSize);
      g_pszCa2Build = (char *) ms_get_dup("spaignition.api.veriterse.net", "/ca2_get_build?authnone");
   }
}

bool ms_download_dup(const char * host, const char * request,  const char * pszFile)
{

   initialize_http_dup();

   if(file_exists_dup(pszFile) && !::DeleteFile(pszFile))
   {
      return false;
   }

   DWORD dwSize = 0;
   DWORD dwDownloaded = 0;
   LPSTR pszOutBuffer;
   BOOL  bResults = FALSE;

   HINTERNET hSession = InternetOpen(
      "ccvotagus_ca2_fontopus_install_spa_boot",
      INTERNET_OPEN_TYPE_PRECONFIG,
      NULL, 
      NULL, 
      0);

   HINTERNET hConnect = NULL;
   if(hSession != NULL)
      hConnect = InternetConnect(
         hSession, 
         host,
         80, 
         NULL, 
         NULL, 
         INTERNET_SERVICE_HTTP, 
         0, 
         0);

   HINTERNET hRequest = NULL;
   if (hConnect != NULL)
      hRequest = HttpOpenRequest(
         hConnect, 
         "GET", 
         request,
         HTTP_VERSION, 
         NULL, 
         0, 
         INTERNET_FLAG_DONT_CACHE,
         0);

   if (hRequest)
      bResults = HttpSendRequestA(
         hRequest,
         NULL, 0,
         NULL, 0);


   DWORD dwStatusCode = 0;
   DWORD dwBufferLen = sizeof(dwStatusCode);
   DWORD dwIndex = 0;
   if(bResults)
      bResults = HttpQueryInfo(
      hRequest, 
      HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
      &dwStatusCode,
      &dwBufferLen,
      &dwIndex);
   if(bResults && dwStatusCode != HTTP_STATUS_OK)
   {
      bResults = FALSE;
   }

   if (bResults)
   {
      
      DWORD dwWritten;
      DWORD dwError;
      DWORD dwLen = 0;
      HANDLE hfile = ::CreateFile(pszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
      if(hfile == INVALID_HANDLE_VALUE)
      {
         dwError = ::GetLastError();
         return false;
      }
      DWORD dwSize;
      
      dwSize         = g_MsDownloadSize;
      pszOutBuffer   = (char *) g_MsDownloadBuffer;
      if (!pszOutBuffer)
      {
         return false;
      }
      while(true)
      {
         memset_dup(pszOutBuffer, 0, dwSize);
         DWORD dwRead = dwSize;
         if(!InternetReadFile( hRequest, (LPVOID)pszOutBuffer, dwRead, &dwDownloaded))
         {
            char szbuf[300];
            DWORD dwError = 0;
            DWORD dwLen = sizeof(szbuf);
            InternetGetLastResponseInfo(&dwError, szbuf, &dwLen);
            DWORD dw = GetLastError();
            bResults = FALSE;
            break;
         }
         else
         {
            ::WriteFile(hfile, pszOutBuffer, dwDownloaded, &dwWritten, NULL);
         }
         if(dwDownloaded == 0)
            break;
      }
      ::CloseHandle(hfile);
   }
   DWORD dw = GetLastError();
   ::InternetCloseHandle(hRequest);
   ::InternetCloseHandle(hConnect);
   ::InternetCloseHandle(hSession);
   return bResults != FALSE;
}



const char * ms_get_dup(const char * host, const char * request)
{
   
   initialize_http_dup();

   DWORD dwSize = 0;
   DWORD dwDownloaded = 0;
   LPSTR pszOutBuffer;
   BOOL  bResults = FALSE;

   HINTERNET hSession = InternetOpen(
      "ccvotagus_ca2_fontopus_install_spa_boot",
      INTERNET_OPEN_TYPE_PRECONFIG,
      NULL, 
      NULL, 
      0);

   HINTERNET hConnect = NULL;
   if(hSession != NULL)
      hConnect = InternetConnect(
         hSession, 
         host,
         80, 
         NULL, 
         NULL, 
         INTERNET_SERVICE_HTTP, 
         0, 
         0);

   HINTERNET hRequest = NULL;
   if (hConnect != NULL)
      hRequest = HttpOpenRequest(
         hConnect, 
         "GET", 
         request,
         HTTP_VERSION, 
         NULL, 
         0, 
         INTERNET_FLAG_DONT_CACHE,
         0);

   if (hRequest)
      bResults = HttpSendRequestA(
         hRequest,
         NULL, 0,
         NULL, 0);


   DWORD dwStatusCode = 0;
   DWORD dwBufferLen = sizeof(dwStatusCode);
   DWORD dwIndex = 0;
   if(bResults)
      bResults = HttpQueryInfo(
      hRequest, 
      HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
      &dwStatusCode,
      &dwBufferLen,
      &dwIndex);
   if(bResults && dwStatusCode != HTTP_STATUS_OK)
   {
      bResults = FALSE;
   }
   dwSize         = g_MsDownloadSize;
   pszOutBuffer   = (char *) g_MsDownloadBuffer;
      int iLen = 0;

   if (bResults)
   {
      
      if (!pszOutBuffer)
      {
         return false;
      }
      while(true)
      {
         DWORD dwRead = dwSize;
         if(!InternetReadFile( hRequest, (LPVOID)&pszOutBuffer[iLen], max(0, min(dwRead, dwSize - iLen)), &dwDownloaded))
         {
            char szbuf[300];
            DWORD dwError = 0;
            DWORD dwLen = sizeof(szbuf);
            InternetGetLastResponseInfo(&dwError, szbuf, &dwLen);
            DWORD dw = GetLastError();
            break;
         }
         else
         {
            iLen += dwDownloaded;
         }
         if(dwDownloaded == 0)
         {
            break;
         }
      }
   }
   pszOutBuffer[iLen] = '\0';
   DWORD dw = GetLastError();
   ::InternetCloseHandle(hRequest);
   ::InternetCloseHandle(hConnect);
   ::InternetCloseHandle(hSession);
   return strdup_dup(pszOutBuffer);
}


const char * ca2_get_build()
{
   return g_pszCa2Build;
}