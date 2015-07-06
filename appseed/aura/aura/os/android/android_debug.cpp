

#include <android/log.h>


static string * m_pstrOutputDebugStringA = NULL;


VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString)
{

   if (m_pstrOutputDebugStringA == NULL)
   {

      m_pstrOutputDebugStringA = new string();

   }

   m_pstrOutputDebugStringA->operator +=(lpOutputString);

   // very lazy implementation

   stringa stra;

   stra.add_lines(*m_pstrOutputDebugStringA);

   if (stra.get_count() > 0)
   {

      *m_pstrOutputDebugStringA = stra.pop();

      if (stra.get_count() > 0)
      {

         for (auto str : stra)
         {

            __android_log_print(ANDROID_LOG_INFO, "OutputDebugString", str);

         }

      }

   }


}




VOID WINAPI OutputDebugStringW(LPCWSTR lpOutputString)
{


   OutputDebugStringA(string(lpOutputString));


}

