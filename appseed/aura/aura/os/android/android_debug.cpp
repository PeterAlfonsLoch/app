

#include <android/log.h>


//static string * m_pstrOutputDebugStringA = NULL;
static mutex * m_pmutexOutputDebugStringA = NULL;

VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString)
{

   if (m_pmutexOutputDebugStringA == NULL)
   {
      m_pmutexOutputDebugStringA = new mutex(NULL);
   }

   synch_lock sl(m_pmutexOutputDebugStringA);

   //if (m_pstrOutputDebugStringA == NULL)
   //{

   //   m_pstrOutputDebugStringA = new string();

   //}

   //m_pstrOutputDebugStringA->operator +=(lpOutputString);

   //// very lazy implementation

   //stringa stra;

   //stra.add_lines(*m_pstrOutputDebugStringA);

   //if (stra.get_count() > 0)
   //{

   //   *m_pstrOutputDebugStringA = stra.pop();

   //   if (stra.get_count() > 0)
   //   {

   //      for (auto str : stra)
   //      {

            //__android_log_print(ANDROID_LOG_INFO, "OutputDebugString", str);

            __android_log_print(ANDROID_LOG_INFO,"OutputDebugString",lpOutputString);

   //      }

   //   }

   //}


}




VOID WINAPI OutputDebugStringW(LPCWSTR lpOutputString)
{


   OutputDebugStringA(string(lpOutputString));


}




DWORD
WINAPI
FormatMessage(
   DWORD dwFlags,
   LPCVOID lpSource,
   DWORD dwMessageId,
   DWORD dwLanguageId,
   LPSTR lpBuffer,
   DWORD nSize,
   va_list *Arguments
   )
{


   return 0;


}
