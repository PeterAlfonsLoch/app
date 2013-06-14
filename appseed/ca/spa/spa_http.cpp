#include "framework.h"


namespace spa
{


   void installer::ms_download_callback( int32_t i, uint_ptr dwLen)
   {
      bool bProgress = true;
      if(i == -1)
      {
         m_dwDownloadLen = 0;

         if(bProgress)
         {
            //trace("...");
         }

      }
      else if(i == 0)
      {
         m_dwDownloadCallbackLast100k = 0;
         m_iDownloadCallbackColumn = 0;
      }
      else if(i == 1)
      {
         m_dwDownloadLen = dwLen;
         /*if(bProgress)
         {
            for(int32_t i = 0; i < ((dwLen - m_dwDownloadCallbackLast100k) / (100 * 1024)); i++)
            {
               if(m_iDownloadCallbackColumn >= 84)
               {
                  trace(".");
                  m_iDownloadCallbackColumn = 1;
               }
               else
               {
                  m_iDownloadCallbackColumn++;
                  trace_add(".");
               }
            }
         }
         m_dwDownloadCallbackLast100k += ((dwLen - m_dwDownloadCallbackLast100k) / (100 * 1024) )*(100 / 1024);*/
         if(m_iProgressTotalGzLen > 0)
         {
            dlr(m_iGzLen + dwLen);
            set_progress((double) (m_iGzLen + dwLen) / (double) m_iProgressTotalGzLen);
         }
      }
      else if(i == 2)
      {
         while(bProgress && m_iDownloadCallbackColumn < 84)
         {
            //trace_add(".");
            m_iDownloadCallbackColumn++;
         }

      }
   }

   void installer::ms_get_callback( int32_t i, uint_ptr dwLen)
   {
//      bool bProgress = true;
      if(i == -3)
      {
  //       uint32_t dwBufferLen = 1024 + 256;
         simple_http_status * pstatus = (simple_http_status *) reinterpret_cast < void * > (dwLen);
         trace("ms_get_dup failed : status : " + itoa_dup(pstatus->m_dwStatusCode) + " - " + pstatus->m_pszStatus);
      }
      else if(i == -2)
      {
         trace("ms_get_dup failed");
#ifdef WINDOWS
         uint32_t dw = ::GetLastError();
	      wchar_t lastErrorTxt[1024];
         memset_dup(lastErrorTxt, 0, sizeof(lastErrorTxt));
	      FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, 0, lastErrorTxt, 1024, NULL);
         trace(vsstring(lastErrorTxt));
         trace("ms_get_dup failed : GetLastErrorCode : " + itoa_dup(dw));
#endif
      }
      else
      {
         ms_download_callback(i, dwLen);
      }
   }


} // namespace spa


void ms_download_callback(void * param, int32_t i, uint_ptr dwLen)
{
   spa::installer * pinstaller = ((spa::installer *) param);
   pinstaller->ms_download_callback(i, dwLen);
}




void ms_get_callback(void * param, int32_t i, uint_ptr dwLen)
{
   spa::installer * pinstaller = ((spa::installer *) param);
   pinstaller->ms_get_callback(i, dwLen);
}
