

#if MEMDLEAK


BEGIN_EXTERN_C

#define MEMDLEAK_DEFAULT 0

int g_iGlobalMemdleakEnabled;

thread_int_ptr < int_ptr > t_iMemdleak;

CLASS_DECL_AURA int  memdleak_enabled()
{

   return global_memdleak_enabled() && (t_iMemdleak == (int_ptr) 1 || t_iMemdleak == (int_ptr)0);

}

CLASS_DECL_AURA void memdleak_enable(int enable)
{

   if (!enable)
   {
      
      t_iMemdleak = 1;

   }
   else
   { 

      t_iMemdleak = -1;

   }
   

}

CLASS_DECL_AURA int  global_memdleak_enabled()
{

   if (g_iGlobalMemdleakEnabled == 0)
   {

      uint32_t dwFileAttributes = GetFileAttributesW(L"C:\\archive\\ca2\\config\\system\\memdleak.txt");

      if (dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      {

         g_iGlobalMemdleakEnabled = 1;

      }
      else
      {

         if (MEMDLEAK_DEFAULT)
         {

            g_iGlobalMemdleakEnabled = 1;

         }
         else
         {

            g_iGlobalMemdleakEnabled = -1;

         }

      }

   }
   
   return g_iGlobalMemdleakEnabled == 1;

}


END_EXTERN_C


#endif



