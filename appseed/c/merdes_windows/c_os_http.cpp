#include "framework.h"
#include <msxml6.h>
#include <collection.h>
#include <wrl.h>

namespace http
{

   inline void CheckHResult(HRESULT hResult)
   {
      if (hResult == E_ABORT)
      {
         concurrency::cancel_current_task();
      }
      else if (FAILED(hResult))
      {
         throw Platform::Exception::CreateException(hResult);
      }
   }

   namespace details
   {

      // Implementation of IXMLHTTPRequest2Callback used when partial buffers are needed from the response.
      // When only the complete response is needed, use HttpRequestStringCallback instead.
      class HttpRequestBuffersCallback :
         public Microsoft::WRL::RuntimeClass<
         Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
         IXMLHTTPRequest2Callback,
         Microsoft::WRL::FtmBase>
      {
      private:


         // Signals that the download operation was canceled.
         cancellation_token cancellationToken;

         // Used to unregister the cancellation token callback.
         cancellation_token_registration registrationToken;

         // The IXMLHTTPRequest2 that processes the HTTP request.
         ComPtr<IXMLHTTPRequest2> request;

         // Task completion event that is set when the 
         // download operation completes.
         task_completion_event<tuple<HRESULT, std::wstring>> completionEvent;

         int statusCode;
         wstring reasonPhrase;

      public:
         HttpRequestBuffersCallback(IXMLHTTPRequest2* httpRequest, 
            concurrency::cancellation_token ct = concurrency::cancellation_token::none()) :
            request(httpRequest), cancellationToken(ct), responseReceived(false), dataHResult(S_OK), statusCode(200)
         {
            // Register a callback function that aborts the HTTP operation when 
            // the cancellation token is canceled.
            if (cancellationToken != concurrency::cancellation_token::none())
            {
               registrationToken = cancellationToken.register_callback([this]() 
               {
                  if (request != nullptr) 
                  {
                     request->Abort();
                  }
               });
            }

            dataEvent = concurrency::task_completion_event<void>();
         }

         // Called when the HTTP request is being redirected to a new URL.
         IFACEMETHODIMP OnRedirect(IXMLHTTPRequest2*, PCWSTR) 
         {
            return S_OK;
         }

         // Called when HTTP headers have been received and processed.
         IFACEMETHODIMP OnHeadersAvailable(IXMLHTTPRequest2*, DWORD statusCode, PCWSTR reasonPhrase)
         {
            HRESULT hr = S_OK;

            // We must not propagate exceptions back to IXHR2.
            try
            {
               this->statusCode = statusCode;
               this->reasonPhrase = reasonPhrase;

               concurrency::critical_section::scoped_lock lock(dataEventLock);
               dataEvent.set();
            }
            catch (std::bad_alloc&)
            {
               hr = E_OUTOFMEMORY;
            }
            return hr;
         }

         // Called when a portion of the entity body has been received.
         IFACEMETHODIMP OnDataAvailable(IXMLHTTPRequest2*, ISequentialStream* stream)
         {
            HRESULT hr = S_OK;

            // We must not propagate exceptions back to IXHR2.
            try
            {
               // Store a reference on the stream so it can be accessed by the task.
               dataStream = stream;

               // The work must be done as fast as possible, and must not block this thread,
               // for example, waiting on another event object.  Here we simply set an event
               // that can be processed by another thread.
               concurrency::critical_section::scoped_lock lock(dataEventLock);
               dataEvent.set();
            }
            catch (std::bad_alloc&)
            {
               hr = E_OUTOFMEMORY;
            }
            return hr;
         }

         // Called when the entire entity response has been received.
         IFACEMETHODIMP OnResponseReceived(IXMLHTTPRequest2* xhr, ISequentialStream* responseStream)
         {
            responseReceived = true;
            return OnDataAvailable(xhr, responseStream);
         }

         // Called when an error occurs during the HTTP request.
         IFACEMETHODIMP OnError(IXMLHTTPRequest2*, HRESULT hrError) 
         {
            HRESULT hr = S_OK;

            // We must not propagate exceptions back to IXHR2.
            try
            {
               concurrency::critical_section::scoped_lock lock(dataEventLock);
               dataHResult = hrError;
               dataEvent.set();
            }
            catch (std::bad_alloc&)
            {
               hr = E_OUTOFMEMORY;
            }

            return hr;
         }

         // Create a task that completes when data is available, in an exception-safe way.
         concurrency::task<void> CreateDataTask();

         HRESULT GetError() const
         {
            return dataHResult;
         }

         int GetStatusCode() const
         {
            return statusCode;
         }

         std::wstring const& GetReasonPhrase() const
         {
            return reasonPhrase;
         }

         bool IsResponseReceived() const
         {
            return responseReceived;
         }

         // Copy bytes from the sequential stream into the buffer provided until
         // we reach the end of one or the other.
         unsigned int ReadData(
            _Out_writes_(outputBufferSize) byte* outputBuffer,
            unsigned int outputBufferSize);

      private:
         ~HttpRequestBuffersCallback()
         {
            // Unregister the callback.
            if (cancellationToken != concurrency::cancellation_token::none())
            {
               cancellationToken.deregister_callback(registrationToken);
            }
         }

         // Signals that the download operation was canceled.
         concurrency::cancellation_token cancellationToken;

         // Used to unregister the cancellation token callback.
         concurrency::cancellation_token_registration registrationToken;

         // The IXMLHTTPRequest2 that processes the HTTP request.
         Microsoft::WRL::ComPtr<IXMLHTTPRequest2> request;

         // Task completion event that is set when data is available or error is triggered.
         concurrency::task_completion_event<void> dataEvent;
         concurrency::critical_section dataEventLock;

         // We cannot store the error obtained from IXHR2 in the dataEvent since any value there is first-writer-wins,
         // whereas we want a subsequent error to override an initial success.
         HRESULT dataHResult;

         // Referenced pointer to the data stream.
         Microsoft::WRL::ComPtr<ISequentialStream> dataStream;

         // HTTP status code and reason returned by the server.
         int statusCode;
         std::wstring reasonPhrase;

         // Whether the response has been completely received.
         bool responseReceived;
      };

   };

   // Utility class for performing asynchronous HTTP requests.
   // This class only supports one outstanding request at a time.
   class request
   {
   public:
      HttpRequest();

      int GetStatusCode() const
      {
         return statusCode;
      }

      std::wstring const& GetReasonPhrase() const
      {
         return reasonPhrase;
      }

      // Whether the response has been completely received, if using ReadAsync().
      bool IsResponseComplete() const
      {
         return responseComplete;
      }

      // Start an HTTP GET on the specified URI.  The returned task completes once the entire response
      // has been received, and the task produces the HTTP response text.  The status code and reason
      // can be read with GetStatusCode() and GetReasonPhrase().
      concurrency::task<std::wstring> GetAsync(
         Windows::Foundation::Uri^ uri, 
         concurrency::cancellation_token cancellationToken = concurrency::cancellation_token::none());

      // Start an HTTP POST on the specified URI, using a string body.  The returned task produces the 
      // HTTP response text.  The status code and reason can be read with GetStatusCode() and GetReasonPhrase().
      concurrency::task<std::wstring> PostAsync(
         Windows::Foundation::Uri^ uri,
         PCWSTR contentType,
         IStream* postStream,
         uint64 postStreamSizeToSend,
         concurrency::cancellation_token cancellationToken = concurrency::cancellation_token::none());

      // Start an HTTP POST on the specified URI, using a stream body.  The returned task produces the
      // HTTP response text.  The status code and reason can be read with GetStatusCode() and GetReasonPhrase().
      concurrency::task<std::wstring> PostAsync(
         Windows::Foundation::Uri^ uri,
         const std::wstring& str,
         concurrency::cancellation_token cancellationToken = concurrency::cancellation_token::none());

      // Send a request but don't return the response.  Instead, let the caller read it with ReadAsync().
      concurrency::task<void> SendAsync(
         const std::wstring& httpMethod,
         Windows::Foundation::Uri^ uri,
         concurrency::cancellation_token cancellationToken = concurrency::cancellation_token::none());

      // Read a chunk of data from the HTTP response, up to a specified length or until we reach the end
      // of the response, and store the value in the provided buffer.  This is useful for large content,
      // enabling the streaming of the result.
      concurrency::task<void> ReadAsync(
         Windows::Storage::Streams::IBuffer^ readBuffer,
         unsigned int offsetInBuffer,
         unsigned int requestedBytesToRead);

      static void CreateMemoryStream(IStream **stream);

   private:
      // Start a download of the specified URI using the specified method.  The returned task produces the
      // HTTP response text.  The status code and reason can be read with GetStatusCode() and GetReasonPhrase().
      concurrency::task<std::wstring> DownloadAsync(
         PCWSTR httpMethod,
         PCWSTR uri, 
         concurrency::cancellation_token cancellationToken,
         PCWSTR contentType,
         IStream* postStream,
         uint64 postStreamBytesToSend);

      // Referenced pointer to the callback, if using SendAsync/ReadAsync.
      Microsoft::WRL::ComPtr<details::HttpRequestBuffersCallback> buffersCallback;

      int statusCode;
      std::wstring reasonPhrase;

      // Whether the response has been completely received, if using ReadAsync().
      bool responseComplete;
   };

};


DWORD g_MsDownloadSize = 1024 * 16;
char * g_MsDownloadBuffer = NULL;
vsstring * g_pstrHost = NULL;


void reset_http()
{

   g_hSession           = NULL;

   g_hConnect           = NULL;

   g_hPreviousRequest   = NULL;

   g_MsDownloadSize     = 1024 * 16;

   g_MsDownloadBuffer   = NULL;

   g_pstrHost           = NULL;

}


void prepare_http()
{

   if(g_MsDownloadBuffer == NULL)
   {

      g_MsDownloadBuffer = new char[g_MsDownloadSize];

   }

   if(g_pstrHost == NULL)
   {

      g_pstrHost = new vsstring();

   }

}


bool ms_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode, int * piStatus, void (*callback)(void *, int, dword_ptr), void * callback_param )
{

   if(piStatus != NULL)
      *piStatus = 0;

   vsstring strUrl;

   char * szBuf = (char *) _ca_alloc(4096);

   prepare_http();
   std::wstring wstrFile(pszFile);

   if(file_exists_dup(pszFile) && !::DeleteFile(wstrFile))
   {
      //trace("download failed: could not delete file prior to download.");
      vsstring str;
      str = "ms_download_dup: error url=\"";
      str += pszUrl;
      str += "\"";
      str = "file path=\"";
      str += pszFile;
      str += "\"";
      trace(str);
      return false;
   }

   if(callback != NULL)
   {
      callback(callback_param, -1, 0);
   }

   int iCol = 3;


   strUrl = pszUrl;
   if(bUrlEncode)
   {
      strUrl = url_encode_dup(strUrl);
      strUrl.replace_ci("%5C", "\\");
      strUrl.replace_ci("\\", "/");
      strUrl.replace_ci("%3A", ":");
      strUrl.replace_ci("%2F", "/");
   }
   vsstring strHost;
   vsstring strReq;
   if(strUrl.substr(0, 7) == "http://")
   {
      size_t iPos = strUrl.find("/", 8);
      strHost = strUrl.substr(7, iPos - 7);
      strReq = strUrl.substr(iPos);
   }
   DWORD dwSize = 0;
   LPSTR pszOutBuffer;
   bool  bResults = FALSE;

   http::request request;

   ::concurrency::cancellation_token token;

   request.GetAsync(Windows::Foundation::Uri(pszUrl), token);


   HINTERNET hRequest = NULL;
   if (g_hConnect != NULL)
      hRequest = HttpOpenRequest( g_hConnect, "GET", strReq,
      NULL, "ca2 ccvotagus spa",
      NULL,
      INTERNET_FLAG_EXISTING_CONNECT
      | INTERNET_FLAG_KEEP_CONNECTION,
      1);

   if (hRequest)
      bResults = HttpSendRequest(hRequest, NULL, 0, NULL, 0) != FALSE;

   if(hRequest != g_hPreviousRequest)
   {
      InternetCloseHandle(g_hPreviousRequest);
   }


   DWORD dwStatusCode = 0;
   DWORD dwBufferLen = sizeof(dwStatusCode);
   DWORD dwIndex = 0;
   if(bResults)
      bResults = HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatusCode, &dwBufferLen, &dwIndex) != FALSE;
   if(piStatus != NULL)
      *piStatus = dwStatusCode;
   dwBufferLen = 1024;
   char * pszStatus = (char *) _ca_alloc(dwBufferLen);
   if(pszStatus != NULL)
   {
      memset_dup(pszStatus, 0, dwBufferLen);
      dwIndex = 0;
      HttpQueryInfo(
         hRequest,
         HTTP_QUERY_STATUS_TEXT,
         pszStatus,
         &dwBufferLen,
         &dwIndex);
   }

   if(bResults && dwStatusCode != HTTP_STATUS_OK)
   {
      if(piStatus == NULL)
      {
         /*dwBufferLen = 1024 + 256;
         char * pszMessage = (char *) _ca_alloc(dwBufferLen);
         if(pszMessage != NULL)
         {
         //sprintf_s(pszMessage, dwBufferLen, "download error : status %d - %s", dwStatusCode, pszStatus);
         //trace(pszMessage);
         free(pszMessage);
         }
         else
         {
         char sz[1024];
         sprintf_s(sz, sizeof(sz), "download error : status %d", dwStatusCode);
         trace(sz);
         }*/
      }
      bResults = FALSE;
   }
   if(pszStatus != NULL)
   {
      _ca_free(pszStatus, 0);
   }

   if (bResults)
   {

      DWORD dwWritten;
      DWORD dwError;
      DWORD dwDownloaded;
      vsstring strPath;
      strPath = pszFile;
      DWORD dwLen = 0;
      dir::mk(dir::name(strPath));
      HANDLE hfile = ::CreateFile(strPath,
         GENERIC_WRITE, 0, NULL,
         CREATE_ALWAYS, 0, NULL);
      if(hfile == INVALID_HANDLE_VALUE)
      {
         dwError = ::GetLastError();
         return false;
      }
      DWORD dwSize = g_MsDownloadSize;
      pszOutBuffer = g_MsDownloadBuffer;
      if (!pszOutBuffer)
      {
         ::CloseHandle(hfile);
         ::OutputDebugStringA("Out of memory\n");
         vsstring str;
         str = "ms_download_dup: out of memory error url=\"";
         str += pszUrl;
         str += "\"";
         trace(str);
         return false;
      }
      if(callback != NULL)
      {

         callback(callback_param, 0, 0);
      }
      while(true)
      {
         memset_dup(pszOutBuffer, 0, dwSize);
         dwDownloaded = 0;
         if (!InternetReadFile( hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
         {
            //sprintf(szBuf, "Error %u in WinHttpReadData.\n", GetLastError());
            //trace(szBuf);
            if(callback != NULL)
            {
               callback(callback_param, -2, 0);
            }
         }
         else
         {
            ::WriteFile(hfile, pszOutBuffer, dwDownloaded, &dwWritten, NULL);
            dwLen += dwWritten;
            if(callback != NULL)
            {
               callback(callback_param, 1, dwLen);
            }
         }
         if(dwDownloaded == 0)
            break;
      }
      ::CloseHandle(hfile);
   }
   if(bResults)
   {
      if(callback != NULL)
      {
         callback(callback_param, 2,  0);
      }
   }
   else
   {
      //sprintf(szBuf, "Error %d has occurred.\n",dw);
      //trace(szBuf);
      if(callback != NULL)
      {
         callback(callback_param, -2, 0);
      }
   }
   delete [] pwzHost;
   g_hPreviousRequest = hRequest;

   if(!bResults)
   {
      vsstring str;
      str = "ms_download_dup: error url=\"";
      str += pszUrl;
      str += "\"";
      str = "file path=\"";
      str += pszFile;
      str += "\"";
      trace(str);
   }

   return bResults != FALSE;
}



vsstring ms_get_dup(const char * pszUrl, bool bCache, void (*callback)(void *, int, dword_ptr), void * callback_param, bool bProgress)
{

   prepare_http();
   vsstring strRet;
   vsstring strUrl(pszUrl);
   vsstring strHost;
   vsstring strReq;
   int iPort = 80;
   if(strUrl.substr(0, 7) == "http://")
   {
      size_t iPos = strUrl.find("/", 8);
      strHost = strUrl.substr(7, iPos - 7);
      strReq = strUrl.substr(iPos);
   }
   else if(strUrl.substr(0, 8) == "https://")
   {
      size_t iPos = strUrl.find("/", 9);
      strHost = strUrl.substr(8, iPos - 8);
      strReq = strUrl.substr(iPos);
      iPort = 443;
   }
   int iFind = strReq.find("?");
   if(iFind >= 0)
   {
      vsstring strQ = strReq.substr(iFind);
      strQ.replace("/", "%2F");
      strReq = strReq.substr(0, iFind) + strQ;
   }
   DWORD dwSize = 0;
   DWORD dwDownloaded = 0;
   LPSTR pszOutBuffer;
   bool  bResults = FALSE;
   HINTERNET  hSession = NULL,
      hConnect = NULL,
      hRequest = NULL;

   WCHAR * pwzHost = utf8_to_16(strHost);

   /*WCHAR * pwzAutoUrl = NULL;
   if(WinHttpDetectAutoProxyConfigUrl(
   WINHTTP_AUTO_DETECT_TYPE_DHCP|
   WINHTTP_AUTO_DETECT_TYPE_DNS_A, pwzAutoUrl))
   {
   WinHttpGetProxyForUrl
   GlobalFree((HGLOBAL) pwzAutoUrl);
   }*/



   // Use WinHttpOpen to obtain a session handle.
   hSession =
      InternetOpen(
      "ccvotagus_ca2_fontopus",
      INTERNET_OPEN_TYPE_PRECONFIG,
      NULL,
      NULL,
      0);

   if(hSession)
      hConnect =
      InternetConnect(
      hSession,
      strHost,
      iPort,
      NULL,
      NULL,
      INTERNET_SERVICE_HTTP,
      iPort == 443 ? INTERNET_FLAG_SECURE : 0,
      1);

   DWORD dwFlags = 0;

   if(!bCache)
   {
      dwFlags |= INTERNET_FLAG_NO_CACHE_WRITE;
      dwFlags |= INTERNET_FLAG_PRAGMA_NOCACHE;
      dwFlags |= INTERNET_FLAG_RELOAD;
   }

   if(iPort == 443)
   {
      dwFlags |= INTERNET_FLAG_SECURE;
   }

   if(hConnect)
      hRequest =
      HttpOpenRequest(
      hConnect,
      "GET",
      strReq,
      NULL,
      "ca2 ccvotagus spa",
      NULL, // accept types
      dwFlags,
      1); // dwContext

   if(hRequest)
      bResults =
      HttpSendRequest(hRequest, NULL, 0, NULL, 0) != FALSE;

   if(!bResults)
   {
      if(callback != NULL)
      {
         callback(callback_param, -2, 0);
      }
   }

   DWORD dwStatusCode = 0;
   DWORD dwBufferLen = sizeof(dwStatusCode);
   DWORD dwIndex = 0;
   if(bResults)
      bResults = HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatusCode, &dwBufferLen, &dwIndex) != FALSE;
   dwBufferLen = 1024;
   char * pszStatus = (char *) _ca_alloc(dwBufferLen);
   if(pszStatus != NULL)
   {
      memset_dup(pszStatus, 0, dwBufferLen);
      dwIndex = 0;
      HttpQueryInfo(
         hRequest,
         HTTP_QUERY_STATUS_TEXT,
         pszStatus,
         &dwBufferLen,
         &dwIndex);
   }

   if(bResults && dwStatusCode != HTTP_STATUS_OK)
   {
      if(callback != NULL)
      {
         simple_http_status status;
         status.m_dwStatusCode = dwStatusCode;
         status.m_pszStatus = pszStatus;
         callback(callback_param, -3, (dword_ptr) (void *) &status);
         bResults = FALSE;
      }
   }
   if(pszStatus != NULL)
   {
      _ca_free(pszStatus, 0);
   }

   DWORD dwLen = 0;
   DWORD dwLast100k = 0;
   dwSize = 1024 * 64;
   // Allocate space for the buffer.
   pszOutBuffer = new char[dwSize+1];
   if (bResults)
   {
      if(callback != NULL)
      {
         callback(callback_param, 0, 0);
      }

      do
      {
         if (!pszOutBuffer)
         {
            ::OutputDebugStringA("Out of primitive::memory\n");
            dwSize=0;
         }
         else
         {
            // Read the Data.
            memset_dup(pszOutBuffer, 0, dwSize + 1);

            if (!InternetReadFile( hRequest, (LPVOID)pszOutBuffer,
               dwSize, &dwDownloaded))
            {
               //printf( "Error %u in WinHttpReadData.\n",
               //      GetLastError());
               if(callback != NULL)
               {
                  callback(callback_param, -2, 0);
               }
            }
            else
            {
               strRet += vsstring(pszOutBuffer, dwDownloaded);
               dwLen += dwDownloaded;
               if(bProgress && callback != NULL)
               {
                  callback(callback_param, 1, dwSize);
               }
            }
         }
         // Free the primitive::memory allocated to the buffer.
      }
      while (dwDownloaded>0);
      if(callback != NULL)
      {

         callback(callback_param, 2, 0);
      }

   }
   delete [] pszOutBuffer;

   if (hRequest) InternetCloseHandle(hRequest);
   if (hConnect) InternetCloseHandle(hConnect);
   if (hSession) InternetCloseHandle(hSession);
   delete [] pwzHost;

   if(!bResults)
   {
      vsstring str;
      str = "ms_download_dup: error url=\"";
      str += pszUrl;
      str += "\"";
      trace(str);
   }

   return strRet;

}


vsstring url_encode_dup(const char * psz)
{
   vsstring str;
   char sz[256];
   while(*psz != '\0')
   {
      unsigned char uch = *psz;
      if(isdigit_dup(uch)
         || isalpha_dup(uch)
         || uch == '.'
         || uch == '-'
         || uch== '_')
      {
         str += uch;
      }
      else if(uch == ' ')
      {
         str += "+";
      }
      else
      {
         itoa_dup(sz, uch, 16);
         if(strlen_dup(sz) == 0)
         {
            str += "%00";
         }
         else if(strlen_dup(sz) == 1)
         {
            str += "%0";
            str += sz;
         }
         else if(strlen_dup(sz) == 2)
         {
            str += "%";
            str += sz;
         }
      }
      psz++;
   }
   return str;
}





/*
vsstring ms_post(const char * pszUrl, const char * pszPost)
{
vsstring strUrl(pszUrl);
vsstring strHost;
vsstring strReq;
int iPort;
if(strUrl.substr(0, 7) == "http://")
{
int iPos = strUrl.find("/", 8);
strHost = strUrl.substr(7, iPos - 7);
strReq = strUrl.substr(iPos);
iPort = 80;
}
else if(strUrl.substr(0, 8) == "https://")
{
int iPos = strUrl.find("/", 9);
strHost = strUrl.substr(8, iPos - 8);
strReq = strUrl.substr(iPos);
iPort = 443;
}
DWORD dwSize = 0;
DWORD dwDownloaded = 0;
LPSTR pszOutBuffer;
bool  bResults = FALSE;
HINTERNET  hSession = NULL,
hConnect = NULL,
hRequest = NULL;

WCHAR * pwzHost = utf8_to_16(strHost);

/*WCHAR * pwzAutoUrl = NULL;
if(WinHttpDetectAutoProxyConfigUrl(
WINHTTP_AUTO_DETECT_TYPE_DHCP|
WINHTTP_AUTO_DETECT_TYPE_DNS_A, pwzAutoUrl))
{
WinHttpGetProxyForUrl
GlobalFree((HGLOBAL) pwzAutoUrl);
}*/



// Use WinHttpOpen to obtain a session handle.
/*  hSession = WinHttpOpen( L"ccvotagus_ca2_fontopus",
WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
WINHTTP_NO_PROXY_NAME,
WINHTTP_NO_PROXY_BYPASS, 0);

WCHAR * pwzReq = utf8_to_16(strReq);
WCHAR * pwzUrl = utf8_to_16(strUrl);
config_session_proxy(hSession, pwzUrl);





// Specify an HTTP server.
if (hSession)
hConnect = WinHttpConnect( hSession, pwzHost,
iPort, 0);


// Create an HTTP request handle.
if (hConnect)
hRequest = WinHttpOpenRequest( hConnect, L"POST",
pwzReq,
NULL, WINHTTP_NO_REFERER,
WINHTTP_DEFAULT_ACCEPT_TYPES,
iPort == 443 ? WINHTTP_FLAG_SECURE : 0);
//                                       WINHTTP_FLAG_SECURE);

// add a request header.
WCHAR * hd1 = utf8_to_16(("Host: " + strHost));
if( hRequest )
bResults = WinHttpAddRequestHeaders( hRequest,
hd1,
-1,
WINHTTP_ADDREQ_FLAG_ADD );
if( hRequest )
bResults = WinHttpAddRequestHeaders( hRequest,
L"Content-Type: application/x-www-form-urlencoded",
-1,
WINHTTP_ADDREQ_FLAG_ADD );

// Send a request.
if (hRequest)
bResults = WinHttpSendRequest( hRequest,
WINHTTP_NO_ADDITIONAL_HEADERS,
0, WINHTTP_NO_REQUEST_DATA, 0,
strlen(pszPost), 0);

DWORD dwUploaded;
if (bResults)
if (! (bResults = WinHttpWriteData( hRequest, (LPVOID)pszPost,
strlen(pszPost), &dwUploaded)))
printf( "Error %u in WinHttpReadData.\n",
GetLastError());

// End the request.
if (bResults)
bResults = WinHttpReceiveResponse( hRequest, NULL);

vsstring strResult;

// Keep checking for data until there is nothing left.
if (bResults)
{
do
{

// Check for available data.
dwSize = 0;
if (!WinHttpQueryDataAvailable( hRequest, &dwSize))
printf( "Error %u in WinHttpQueryDataAvailable.\n",
GetLastError());

// Allocate space for the buffer.
pszOutBuffer = new char[dwSize+1];
if (!pszOutBuffer)
{
printf("Out of primitive::memory\n");
dwSize=0;
}
else
{
// Read the Data.
ZeroMemory(pszOutBuffer, dwSize+1);

if (!WinHttpReadData( hRequest, (LPVOID)pszOutBuffer,
dwSize, &dwDownloaded))
printf( "Error %u in WinHttpReadData.\n",
GetLastError());
else
{
g_dwDownloadLen += dwSize;
strResult += pszOutBuffer;
}

// Free the primitive::memory allocated to the buffer.
delete [] pszOutBuffer;
}

} while (dwSize>0);
}

DWORD dw = GetLastError();
// Report any errors.
if (!bResults)
printf("Error %d has occurred.\n",dw);

delete [] hd1;
delete [] pwzUrl;
delete [] pwzReq;
delete [] pwzHost;

// Close any open handles.
if (hRequest) WinHttpCloseHandle(hRequest);
if (hConnect) WinHttpCloseHandle(hConnect);
if (hSession) WinHttpCloseHandle(hSession);
return strResult;
}
*/
/*
void config_session_proxy(HINTERNET hSession, WCHAR * pwzUrl)
{
WINHTTP_AUTOPROXY_OPTIONS apop;

char szPac[4096];
memset_dup(szPac, 0, sizeof(szPac));
DWORD lcbPac;
HKEY hkey;
memset_dup(&apop, 0, sizeof(apop));
bool bGot = false;
lcbPac = sizeof(szPac);
if(RegOpenKey(HKEY_CURRENT_USER,
"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections",
&hkey) == ERROR_SUCCESS)
{
LONG l;
DWORD dw;
if((l = RegQueryValueEx(hkey, "DefaultConnectionSettings", NULL, NULL, (LPBYTE) &szPac, &lcbPac)) == ERROR_SUCCESS
&& (szPac[8] & 8))
{
apop.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
apop.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
apop.fAutoLogonIfChallenged = TRUE;
apop.lpszAutoConfigUrl = NULL;
bGot = true;
}
else
{
FormatMessage(0, 0, l, 0, szPac, sizeof(szPac), NULL);
}
}
lcbPac = sizeof(szPac);
if(!bGot)
{
if(RegOpenKey(HKEY_CURRENT_USER,
"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
&hkey) == ERROR_SUCCESS)
{
LONG l;
if((l = RegQueryValueEx(hkey, "AutoConfigURL", NULL, NULL, (LPBYTE) szPac, &lcbPac)) == ERROR_SUCCESS)
{

apop.dwAutoDetectFlags = 0;
apop.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
apop.lpszAutoConfigUrl = utf8_to_16(szPac);
apop.fAutoLogonIfChallenged = TRUE;
bGot = true;
}
else
{
FormatMessage(0, 0, l, 0, szPac, sizeof(szPac), NULL);
}
}
}
if(!bGot)
{
return;
}

WINHTTP_PROXY_INFO pinfo;


if(WinHttpGetProxyForUrl(
hSession,
pwzUrl,
&apop,
&pinfo))
{
WinHttpSetOption(
hSession,
WINHTTP_OPTION_PROXY,
&pinfo,
sizeof(pinfo));

}


}
*/




//-----------------------------------------------------------------------
// 
//  Copyright (C) Microsoft Corporation.  All rights reserved.
// 
// 
// THIS CODE AND INFORMATION ARE PROVIDED AS-IS WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//-----------------------------------------------------------------------
#include "pch.h"
#include "HttpRequest.h"
#include <robuffer.h>
#include <shcore.h>

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace std;
using namespace Web;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;

// Implementation of IXMLHTTPRequest2Callback used when only the complete response is needed.
// When processing chunks of response data as they are received, use HttpRequestBuffersCallback instead.
class HttpRequestStringCallback 
   : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IXMLHTTPRequest2Callback, FtmBase>
{
public:
   HttpRequestStringCallback(IXMLHTTPRequest2* httpRequest, 
      cancellation_token ct = concurrency::cancellation_token::none()) :
      request(httpRequest), cancellationToken(ct)
   {
      // Register a callback function that aborts the HTTP operation when 
      // the cancellation token is canceled.
      if (cancellationToken != cancellation_token::none())
      {
         registrationToken = cancellationToken.register_callback([this]() 
         {
            if (request != nullptr) 
            {
               request->Abort();
            }
         });
      }
   }

   // Called when the HTTP request is being redirected to a new URL.
   IFACEMETHODIMP OnRedirect(IXMLHTTPRequest2*, PCWSTR) 
   {
      return S_OK;
   }

   // Called when HTTP headers have been received and processed.
   IFACEMETHODIMP OnHeadersAvailable(IXMLHTTPRequest2*, DWORD statusCode, PCWSTR reasonPhrase)
   {
      HRESULT hr = S_OK;

      // We must not propagate exceptions back to IXHR2.
      try
      {
         this->statusCode = statusCode;
         this->reasonPhrase = reasonPhrase;
      }
      catch (std::bad_alloc&)
      {
         hr = E_OUTOFMEMORY;
      }

      return hr;
   }

   // Called when a portion of the entity body has been received.
   IFACEMETHODIMP OnDataAvailable(IXMLHTTPRequest2*, ISequentialStream*)
   {
      return S_OK;
   }

   // Called when the entire entity response has been received.
   IFACEMETHODIMP OnResponseReceived(IXMLHTTPRequest2*, ISequentialStream* responseStream)
   {
      std::wstring wstr;
      HRESULT hr = ReadUtf8StringFromSequentialStream(responseStream, wstr);

      // We must not propagate exceptions back to IXHR2.
      try
      {
         completionEvent.set(make_tuple<HRESULT, std::wstring>(move(hr), move(wstr)));
      }
      catch (std::bad_alloc&)
      {
         hr = E_OUTOFMEMORY;
      }

      return hr;
   }

   // Simulate the functionality of DataReader.ReadString().
   // This is needed because DataReader requires IRandomAccessStream and this
   // code has an ISequentialStream that does not have a conversion to IRandomAccessStream like IStream does.
   HRESULT ReadUtf8StringFromSequentialStream(ISequentialStream* readStream, std::wstring& str)
   {
      // Convert the response to Unicode std::wstring.
      HRESULT hr;

      // Holds the response as a Unicode string.
      wstringstream ss;

      while (true)
      {
         ULONG cb;
         char buffer[4096];

         // Read the response as a UTF-8 string.  Since UTF-8 characters are 1-4 bytes long,
         // we need to make sure we only read an integral number of characters.  So we'll
         // start with 4093 bytes.
         hr = readStream->Read(buffer, sizeof(buffer) - 3, &cb);
         if (FAILED(hr) || (cb == 0))
         {
            break; // Error or no more data to process, exit loop.
         }

         if (cb == sizeof(buffer) - 3)
         {
            ULONG subsequentBytesRead;
            unsigned int i, cl;

            // Find the first byte of the last UTF-8 character in the buffer.
            for (i = cb - 1; (i >= 0) && ((buffer[i] & 0xC0) == 0x80); i--);

            // Calculate the number of subsequent bytes in the UTF-8 character.
            if (((unsigned char)buffer[i]) < 0x80)
            {
               cl = 1;
            }
            else if (((unsigned char)buffer[i]) < 0xE0)
            {
               cl = 2;
            }
            else if (((unsigned char)buffer[i]) < 0xF0)
            {
               cl = 3;
            }
            else
            {
               cl = 4;
            }

            // Read any remaining bytes.
            if (cb < i + cl)
            {
               hr = readStream->Read(buffer + cb, i + cl - cb, &subsequentBytesRead);
               if (FAILED(hr))
               {
                  break; // Error, exit loop.
               }
               cb += subsequentBytesRead;
            }
         }

         // First determine the size required to store the Unicode string.
         int const sizeRequired = MultiByteToWideChar(CP_UTF8, 0, buffer, cb, nullptr, 0);
         if (sizeRequired == 0)
         {
            // Invalid UTF-8.
            hr = HRESULT_FROM_WIN32(GetLastError());
            break;
         }
         unique_ptr<char16[]> wstr(new(std::nothrow) char16[sizeRequired + 1]);
         if (wstr.get() == nullptr)
         {
            hr = E_OUTOFMEMORY;
            break;
         }

         // Convert the string from UTF-8 to UTF-16LE.  This can never fail, since
         // the previous call above succeeded.
         MultiByteToWideChar(CP_UTF8, 0, buffer, cb, wstr.get(), sizeRequired);
         wstr[sizeRequired] = L'\0'; // Terminate the string.
         ss << wstr.get(); // Write the string to the stream.
      }

      str = SUCCEEDED(hr) ? ss.str() : std::wstring();
      return (SUCCEEDED(hr)) ? S_OK : hr; // Don't return S_FALSE.
   }

   // Called when an error occurs during the HTTP request.
   IFACEMETHODIMP OnError(IXMLHTTPRequest2*, HRESULT hrError) 
   {
      HRESULT hr = S_OK;

      // We must not propagate exceptions back to IXHR2.
      try
      {
         completionEvent.set(make_tuple<HRESULT, std::wstring>(move(hrError), std::wstring()));
      }
      catch (std::bad_alloc&)
      {
         hr = E_OUTOFMEMORY;
      }

      return hr;
   }

   // Retrieves the completion event for the HTTP operation.
   task_completion_event<tuple<HRESULT, std::wstring>> const& GetCompletionEvent() const
   {
      return completionEvent; 
   }

   int GetStatusCode() const
   {
      return statusCode;
   }

   std::wstring GetReasonPhrase() const
   {
      return reasonPhrase;
   }

private:
   ~HttpRequestStringCallback()
   {
      // Unregister the callback.
      if (cancellationToken != cancellation_token::none())
      {
         cancellationToken.deregister_callback(registrationToken);
      }
   }

};

// Copy bytes from the sequential stream into the buffer provided until
// we reach the end of one or the other.
unsigned int Web::Details::HttpRequestBuffersCallback::ReadData(
   _Out_writes_(outputBufferSize) byte* outputBuffer,
   unsigned int outputBufferSize)
{
   // Lock the data event while doing the read, to ensure that any bytes we don't read will
   // result in the correct event getting triggered.
   concurrency::critical_section::scoped_lock lock(dataEventLock);

   ULONG bytesRead;
   CheckHResult(dataStream.Get()->Read(outputBuffer, outputBufferSize, &bytesRead));
   if (bytesRead < outputBufferSize)
   {
      // We need to reset the data event, which we can only do by creating a new one.
      dataEvent = task_completion_event<void>();
   }

   return bytesRead;
}

// Create a task that completes when data is available, in an exception-safe way.
task<void> Web::Details::HttpRequestBuffersCallback::CreateDataTask()
{
   concurrency::critical_section::scoped_lock lock(dataEventLock);
   return create_task(dataEvent, cancellationToken);
}

HttpRequest::HttpRequest() : responseComplete(true), statusCode(200)
{
}

// Start a download of the specified URI using the specified method.  The returned task produces the
// HTTP response text.  The status code and reason can be read with GetStatusCode() and GetReasonPhrase().
task<std::wstring> HttpRequest::DownloadAsync(PCWSTR httpMethod, PCWSTR uri, cancellation_token cancellationToken,
                                              PCWSTR contentType, IStream* postStream, uint64 postStreamSizeToSend)
{
   // Create an IXMLHTTPRequest2 object.
   ComPtr<IXMLHTTPRequest2> xhr;
   CheckHResult(CoCreateInstance(CLSID_XmlHttpRequest, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&xhr)));

   // Create callback.
   auto stringCallback = Make<HttpRequestStringCallback>(xhr.Get(), cancellationToken);
   CheckHResult(stringCallback ? S_OK : E_OUTOFMEMORY);

   auto completionTask = create_task(stringCallback->GetCompletionEvent());

   // Create a request.
   CheckHResult(xhr->Open(httpMethod, uri, stringCallback.Get(), nullptr, nullptr, nullptr, nullptr));

   if (postStream != nullptr && contentType != nullptr)
   {
      CheckHResult(xhr->SetRequestHeader(L"Content-Type", contentType));
   }

   // Send the request.
   CheckHResult(xhr->Send(postStream, postStreamSizeToSend));

   // Return a task that completes when the HTTP operation completes. 
   // We pass the callback to the continuation because the lifetime of the 
   // callback must exceed the operation to ensure that cancellation 
   // works correctly.
   return completionTask.then([this, stringCallback](tuple<HRESULT, std::wstring> resultTuple)
   {
      // If the GET operation failed, throw an Exception.
      CheckHResult(std::get<0>(resultTuple));

      statusCode = stringCallback->GetStatusCode();
      reasonPhrase = stringCallback->GetReasonPhrase();

      return std::get<1>(resultTuple);
   });
}

// Start an HTTP GET on the specified URI.  The returned task completes once the entire response
// has been received, and the task produces the HTTP response text.  The status code and reason
// can be read with GetStatusCode() and GetReasonPhrase().
task<std::wstring> HttpRequest::GetAsync(Uri^ uri, cancellation_token cancellationToken)
{
   return DownloadAsync(L"GET",
      uri->AbsoluteUri->Data(),
      cancellationToken,
      nullptr,
      nullptr,
      0);
}

void HttpRequest::CreateMemoryStream(IStream **stream)
{
   auto randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();
   CheckHResult(CreateStreamOverRandomAccessStream(randomAccessStream, IID_PPV_ARGS(stream)));
}

// Start an HTTP POST on the specified URI, using a string body.  The returned task produces the
// HTTP response text.  The status code and reason can be read with GetStatusCode() and GetReasonPhrase().
task<std::wstring> HttpRequest::PostAsync(Uri^ uri, const std::wstring& body, cancellation_token cancellationToken)
{
   int length = 0;
   ComPtr<IStream> postStream;
   CreateMemoryStream(&postStream);

   if (body.length() > 0)
   {
      // Get the required buffer size.
      int size = WideCharToMultiByte(CP_UTF8,                         // UTF-8
         0,                               // Conversion type
         body.c_str(),                    // Unicode string to convert
         static_cast<int>(body.length()), // Size
         nullptr,                         // Output buffer
         0,                               // Output buffer size
         nullptr,
         nullptr);
      CheckHResult((size != 0) ? S_OK : HRESULT_FROM_WIN32(GetLastError()));

      std::unique_ptr<char[]> tempData(new char[size]);
      length = WideCharToMultiByte(CP_UTF8,                         // UTF-8
         0,                               // Conversion type
         body.c_str(),                    // Unicode string to convert
         static_cast<int>(body.length()), // Size
         tempData.get(),                  // Output buffer
         size,                            // Output buffer size
         nullptr,
         nullptr);
      CheckHResult((length != 0) ? S_OK : HRESULT_FROM_WIN32(GetLastError()));
      CheckHResult(postStream->Write(tempData.get(), length, nullptr));
   }

   return DownloadAsync(L"POST",
      uri->AbsoluteUri->Data(),
      cancellationToken,
      L"text/plain;charset=utf-8",
      postStream.Get(),
      length);
}

// Start an HTTP POST on the specified URI, using a stream body.  The returned task produces the
// HTTP response text.  The status code and reason can be read with GetStatusCode() and GetReasonPhrase().
task<std::wstring> HttpRequest::PostAsync(Uri^ uri, PCWSTR contentType, IStream* postStream,
                                          uint64 postStreamSizeToSend, cancellation_token cancellationToken)
{
   return DownloadAsync(L"POST",
      uri->AbsoluteUri->Data(),
      cancellationToken,
      contentType,
      postStream,
      postStreamSizeToSend);
}

// Send a request but don't return the response.  Instead, let the caller read it with ReadAsync().
task<void> HttpRequest::SendAsync(const std::wstring& httpMethod, Uri^ uri, cancellation_token cancellationToken)
{
   // Create an IXMLHTTPRequest2 object.
   ComPtr<IXMLHTTPRequest2> xhr;
   CheckHResult(CoCreateInstance(CLSID_XmlHttpRequest, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&xhr)));

   // Create callback.
   buffersCallback = Make<Web::Details::HttpRequestBuffersCallback>(xhr.Get(), cancellationToken);
   CheckHResult(buffersCallback ? S_OK : E_OUTOFMEMORY);

   ComPtr<IXMLHTTPRequest2Callback> xhrCallback;
   CheckHResult(buffersCallback.As(&xhrCallback));

   // Open and send the request.
   CheckHResult(xhr->Open(httpMethod.c_str(),
      uri->AbsoluteUri->Data(),
      xhrCallback.Get(),
      nullptr,
      nullptr,
      nullptr,
      nullptr));

   responseComplete = false;

   CheckHResult(xhr->Send(nullptr, 0));

   // Return a task that completes when the HTTP operation completes.
   // Since buffersCallback holds a reference on the callback, the lifetime of the callback will exceed
   // the operation and ensure that cancellation works correctly.
   return buffersCallback->CreateDataTask().then([this]()
   {
      CheckHResult(buffersCallback->GetError());

      statusCode = buffersCallback->GetStatusCode();
      reasonPhrase = buffersCallback->GetReasonPhrase();
   });
}

// Read a chunk of data from the HTTP response, up to a specified length or until we reach the end
// of the response, and store the value in the provided buffer.  This is useful for large content,
// enabling the streaming of the result.
task<void> HttpRequest::ReadAsync(Windows::Storage::Streams::IBuffer^ readBuffer, unsigned int offsetInBuffer,
                                  unsigned int requestedBytesToRead)
{
   if (offsetInBuffer + requestedBytesToRead > readBuffer->Capacity)
   {
      throw ref new InvalidArgumentException();
   }

   // Return a task that completes when a read completes. 
   // We pass the callback to the continuation because the lifetime of the 
   // callback must exceed the operation to ensure that cancellation 
   // works correctly.
   return buffersCallback->CreateDataTask().then([this, readBuffer, offsetInBuffer, requestedBytesToRead]()
   {
      CheckHResult(buffersCallback->GetError());

      // Get a pointer to the location to copy data into.
      ComPtr<IBufferByteAccess> bufferByteAccess;
      CheckHResult(reinterpret_cast<IUnknown*>(readBuffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess)));
      byte* outputBuffer; // Returned internal pointer, do not free this value.
      CheckHResult(bufferByteAccess->Buffer(&outputBuffer));

      // Copy bytes from the sequential stream into the buffer provided until
      // we reach the end of one or the other.
      readBuffer->Length = buffersCallback->ReadData(outputBuffer + offsetInBuffer, requestedBytesToRead);
      if (buffersCallback->IsResponseReceived() && (readBuffer->Length < requestedBytesToRead))
      {
         responseComplete = true;
      }
   });
}
