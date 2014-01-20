#include "framework.h"
#undef new
#include <msxml6.h>
#include <wrl.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Details;

#define MAX_BUFFER_LENGTH 4096

class CXMLHttpRequest2Callback :
   public Microsoft::WRL::RuntimeClass<RuntimeClassFlags<ClassicCom>, IXMLHTTPRequest2Callback>
{
private:

   //
   // Event object handle.
   //

   HANDLE m_hComplete;
   ::primitive::memory m_mem;

   //
   // Return value from final callbacks, including OnResponseReceived or
   // OnError event handler. Once a final callback is called, no more callback
   // will be executed.
   //

   HRESULT m_hr;

   //
   // HTTP status code from OnHeadersAvailable event handler.
   //

   DWORD m_dwStatus;

   CXMLHttpRequest2Callback();

   ~CXMLHttpRequest2Callback();

   STDMETHODIMP
      RuntimeClassInitialize();

   friend HRESULT Microsoft::WRL::Details::MakeAndInitialize<CXMLHttpRequest2Callback,CXMLHttpRequest2Callback>(CXMLHttpRequest2Callback **);

public:

   STDMETHODIMP
      OnRedirect(
      __RPC__in_opt IXMLHTTPRequest2 *pXHR,
      __RPC__in_string const WCHAR *pwszRedirectUrl
      );

   STDMETHODIMP
      OnHeadersAvailable(
      __RPC__in_opt IXMLHTTPRequest2 *pXHR,
      DWORD dwStatus,
      __RPC__in_string const WCHAR *pwszStatus
      );

   STDMETHODIMP
      OnDataAvailable(
      __RPC__in_opt IXMLHTTPRequest2 *pXHR,
      __RPC__in_opt ISequentialStream *pResponseStream
      );

   STDMETHODIMP
      OnResponseReceived(
      __RPC__in_opt IXMLHTTPRequest2 *pXHR,
      __RPC__in_opt ISequentialStream *pResponseStream
      );

   STDMETHODIMP
      OnError(
      __RPC__in_opt IXMLHTTPRequest2 *pXHR,
      HRESULT hrError
      );

   STDMETHODIMP
      ReadFromStream(
      _In_opt_ ISequentialStream *pStream
      );

   STDMETHODIMP
      WaitForComplete(
      _Out_ PDWORD pdwStatus
      );

   string as_string()
   {
      string str;
      m_mem.to_string(str);
      return str;
   }

   bool to_file(const char * pszFile)
   {
      return file_put_contents_dup(pszFile, m_mem) != FALSE;
   }

};

CXMLHttpRequest2Callback::CXMLHttpRequest2Callback()
{
   m_hr = S_OK;
   m_dwStatus = 0;
   m_hComplete = NULL;
}

CXMLHttpRequest2Callback::~CXMLHttpRequest2Callback()
{
   if (m_hComplete)
   {
      CloseHandle(m_hComplete);
      m_hComplete = NULL;
   }
}

STDMETHODIMP
   CXMLHttpRequest2Callback::RuntimeClassInitialize()
   /*++

   Routine Description:

   Initalize the call back instance.

   Arguments:

   None.

   Return Value:

   HRESULT.

   --*/
{
   HRESULT hr = S_OK;
   HANDLE hEvent = NULL;

   //
   // Callers needing to receive completion or status events on a STA or UI
   // thread must use a mechanism that will not block the threads window message
   // pump. One example is by posting a window message to the STA or UI thread
   // window handle.
   //

   hEvent = CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

   if (hEvent == NULL)
   {
      hr = HRESULT_FROM_WIN32(GetLastError());
      goto Exit;
   }

   m_hComplete = hEvent;
   hEvent = NULL;

Exit:

   if (hEvent)
   {
      CloseHandle(hEvent);
      hEvent = NULL;
   }

   return hr;
}

STDMETHODIMP
   CXMLHttpRequest2Callback::OnRedirect(
   __RPC__in_opt IXMLHTTPRequest2 *pXHR,
   __RPC__in_string const WCHAR *pwszRedirectUrl
   )
   /*++

   Routine Description:

   This funciton is called when the HTTP request is being redirected to a new URL.

   This callback function must not throw any exceptions.

   Arguments:

   pXHR - The interface pointer of IXMLHTTPRequest2 object.

   pwszRedirectUrl - The new URL for the HTTP request.

   Return Value:

   HRESULT.

   --*/
{
   UNREFERENCED_PARAMETER(pXHR);
   UNREFERENCED_PARAMETER(pwszRedirectUrl);

   m_hr = S_OK;
   SetEvent(m_hComplete);
   return m_hr;
}

STDMETHODIMP
   CXMLHttpRequest2Callback::OnHeadersAvailable(
   __RPC__in_opt IXMLHTTPRequest2 *pXHR,
   DWORD dwStatus,
   __RPC__in_string const WCHAR *pwszStatus
   )
   /*++

   Routine Description:

   Sends a request using the Request Handle specified and implements
   proxy failover if supported.

   This callback function must not throw any exceptions.

   Arguments:

   pXHR - The interface pointer of IXMLHTTPRequest2 object.

   dwStatus - The value of HTTP status code.

   pwszStatus - The description text of HTTP status code.

   Return Value:

   HRESULT.

   --*/
{
   UNREFERENCED_PARAMETER(pwszStatus);

   HRESULT hr = S_OK;

   PWSTR pwszHeaders = NULL;
   PWSTR pwszSingleHeader = NULL;

   if (pXHR == NULL)
   {
      hr = E_INVALIDARG;
      goto Exit;
   }

   //
   // Demonstrate how to get all response headers.
   //

   hr = pXHR->GetAllResponseHeaders(&pwszHeaders);
   if (FAILED(hr))
   {
      goto Exit;
   }

   //
   // Demonstrate how to get a specific response header.
   //

   hr = pXHR->GetResponseHeader(L"server", &pwszSingleHeader);
   if (FAILED(hr) &&
      hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
   {
      goto Exit;
   }

   hr = S_OK;

Exit:

   if (pwszHeaders != NULL)
   {
      CoTaskMemFree(pwszHeaders);
      pwszHeaders = NULL;
   }

   if (pwszSingleHeader != NULL)
   {
      CoTaskMemFree(pwszSingleHeader);
      pwszSingleHeader = NULL;
   }

   m_dwStatus = dwStatus;
   return hr;
}

STDMETHODIMP
   CXMLHttpRequest2Callback::ReadFromStream(
   _In_opt_ ISequentialStream *pStream
   )
   /*++

   Routine Description:

   Demonstrate how to read from the HTTP response stream.

   Arguments:

   pStream - the data stream read form the http response.

   Return Value:

   HRESULT.

   --*/
{
   HRESULT hr = S_OK;
   BYTE buffer[MAX_BUFFER_LENGTH];
   DWORD cbRead = 0;

   if (pStream == NULL)
   {
      hr = E_INVALIDARG;
      goto Exit;
   }

   for(;;)
   {
      hr = pStream->Read(buffer, MAX_BUFFER_LENGTH - 1, &cbRead);

      if (FAILED(hr) ||
         cbRead == 0)
      {
         goto Exit;
      }

      m_mem.append(buffer, cbRead);
   }

Exit:

   return hr;
}

STDMETHODIMP
   CXMLHttpRequest2Callback::OnDataAvailable(
   __RPC__in_opt IXMLHTTPRequest2 *pXHR,
   __RPC__in_opt ISequentialStream *pResponseStream
   )
   /*++

   Routine Description:

   This function is called when a portion of the entity body has been received.
   The application can begin processing the data at this point,
   or wait until the whole response is complete.

   This callback function must not throw any exceptions.

   Arguments:

   pXHR - The interface pointer of IXMLHTTPRequest2 object.

   pResponseStream - a pointer to the input stream.

   Return Value:

   HRESULT.

   --*/
{
   UNREFERENCED_PARAMETER(pXHR);

   //
   // This sample function is processing data as it is received by reading from
   // the response stream. If real-time chunk-by-chunk processing (such as for
   // streaming applications) is not needed, then the entire response is available
   // from the OnResponseReceived callback.  Receiving will be suspended until
   // this callback function returns and this callback will be invoked multiple
   // times during a request.  This callback function must not block and
   // should not perform costly operations such as UI updates.
   //

   return ReadFromStream(pResponseStream);
}

STDMETHODIMP
   CXMLHttpRequest2Callback::OnResponseReceived(
   __RPC__in_opt IXMLHTTPRequest2 *pXHR,
   __RPC__in_opt ISequentialStream *pResponseStream
   )
   /*++

   Routine Description:

   Called when the entire entity body has been received.
   At this point the application can begin processing the data by calling Read
   on the response ISequentialStream or store a reference to the ISequentialStream
   for later processing.

   This callback function must not throw any exceptions.

   Arguments:

   pXHR - The interface pointer of IXMLHTTPRequest2 object.

   pResponseStream - a pointer to the input stream.

   Return Value:

   HRESULT.

   --*/
{
   UNREFERENCED_PARAMETER(pXHR);
   UNREFERENCED_PARAMETER(pResponseStream);

   m_hr = S_OK;
   SetEvent(m_hComplete);
   return m_hr;
}

STDMETHODIMP
   CXMLHttpRequest2Callback::OnError(
   __RPC__in_opt IXMLHTTPRequest2 *pXHR,
   HRESULT hrError
   )
   /*++

   Routine Description:

   Called when an error occurs during the HTTP request.  The error is indicated in hrError.

   This callback function must not throw any exceptions.

   Arguments:

   pXHR - The interface pointer of IXMLHTTPRequest2 object.

   hrError - The errocode for the httprequest.

   Return Value:

   HRESULT.

   --*/
{
   UNREFERENCED_PARAMETER(pXHR);

   m_hr = hrError;
   SetEvent(m_hComplete);
   return S_OK;
}

STDMETHODIMP
   CXMLHttpRequest2Callback::WaitForComplete(
   _Out_ PDWORD pdwStatus
   )
   /*++

   Routine Description:

   Waiting for completion of the request. Once it's done, get the execution
   result of final call backs, and http status code if it's available.

   N.B. Callers needing to receive completion or status events on a STA or UI
   thread must use a mechanism that will not block the threads window message
   pump. One example is by posting a window message to the STA or UI thread
   window handle.

   Arguments:

   pdwStatus - Supplies a pointer to access the status code.

   Return Value:

   HRESULT.

   --*/
{
   DWORD dwError = ERROR_SUCCESS;
   HRESULT hr = S_OK;

   if (pdwStatus == NULL)
   {
      hr = E_INVALIDARG;
      goto Exit;
   }

   dwError = WaitForSingleObjectEx(m_hComplete, (1984 + 1977) * 23, FALSE);

   if (dwError == WAIT_FAILED)
   {
      hr = HRESULT_FROM_WIN32(GetLastError());
      goto Exit;
   }
   else if (dwError != WAIT_OBJECT_0)
   {
      hr = E_ABORT;
      goto Exit;
   }
   else if (dwError == WAIT_OBJECT_0)
   {
   }
   else
   {
      hr = HRESULT_FROM_WIN32(GetLastError());
      goto Exit;
   }

   if (FAILED(m_hr))
   {
      hr = m_hr;
      goto Exit;
   }

   hr = S_OK;
   *pdwStatus = m_dwStatus;

Exit:

   return hr;
}


using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Web::Http;


string Get(LPCWSTR pcwszUrl)
{

   Uri ^ uri = ref new Uri(ref new Platform::String(pcwszUrl));

   HttpClient ^ httpClient = ref new HttpClient();

   Platform::String ^ str;

   try
   {

      str = ::wait(httpClient->GetStringAsync(uri));

   }
   catch (...)
   {

      return "";

   }

   return str;

}


bool Download(LPCWSTR pcwszUrl, const char * pszFile)
{

   Uri ^ uri = ref new Uri(ref new Platform::String(pcwszUrl));

   HttpClient ^ httpClient = ref new HttpClient();

   Windows::Storage::Streams::IBuffer ^ buf;

   try
   {

      buf = ::wait(httpClient->GetBufferAsync(uri));

   }
   catch (...)
   {

      return false;

   }

   ::primitive::memory memory;

   memory.set_os_buffer(buf);

   return file_put_contents_dup(pszFile, memory);

}


/*DWORD g_MsDownloadSize = 1024 * 16;
char * g_MsDownloadBuffer = NULL;
string * g_pstrHost = NULL;
*/

void reset_http()
{
   /*
   g_hSession           = NULL;

   g_hConnect           = NULL;

   g_hPreviousRequest   = NULL;

   g_MsDownloadSize     = 1024 * 16;

   g_MsDownloadBuffer   = NULL;

   g_pstrHost           = NULL;
   */

}


void prepare_http()
{
   /*
   if(g_MsDownloadBuffer == NULL)
   {

   g_MsDownloadBuffer = new char[g_MsDownloadSize];

   }

   if(g_pstrHost == NULL)
   {

   g_pstrHost = new string();

   }
   */
}


bool http_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode, int * piStatus, void (*callback)(void *, int, uint_ptr), void * callback_param )
{

   ComPtr<CXMLHttpRequest2Callback> spcallback;


   HRESULT hr = MakeAndInitialize<CXMLHttpRequest2Callback>(&spcallback);

   if (FAILED(hr))
   {

      return false;
   }

   return Download(wstring(pszUrl), pszFile);


}


string http_get_dup(const char * pszUrl, bool bCache, void (*callback)(void *, int, uint_ptr), void * callback_param, bool bProgress)
{

   return Get(wstring(pszUrl));

}


string url_encode_dup(const char * psz)
{
   string str;
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





