#include "framework.h"


/////////////////////////////////////////////////////////////////////////////
// ___DEBUG_STATE implementation

#ifndef ___NO_DEBUG_CRT
static _CRT_DUMP_CLIENT pfnOldCrtDumpClient = NULL;

#ifdef DEBUG


void __cdecl __crt_dump_client(void * pvData, size_t nBytes)
{
/*   char sz[1024];
   try
   {

      if(_CrtReportBlockType(pvData) != ___CLIENT_BLOCK)
         return;

//      ::object * pca = (::object * ) pvData;

      ::object * pobject = NULL;

      /*for(int32_t i = 0; i < 256; i++)
      {
         try
         {
            pobject = dynamic_cast < ::object * > ((::object *)&((int_ptr *)pca)[i]);
         }
         catch(std::__non_rtti_object & e)
         {
            pobject = NULL;
         }
         catch(...)
         {
            pobject = NULL;
         }
         if(pobject != NULL)
            break;
      }*/

/*      if(pobject == NULL)
      {
// xxx            C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "unknown object at $%p, %u bytes long\n", pvData, nBytes));
      }
      else if(g_dumpcontext.GetDepth() > 0)
      {
         // long form
         pobject->dump(g_dumpcontext);
         g_dumpcontext << "\n";
      }
      if(false) // else
      {
         ::object & obj = *pobject;
         // short form
// xxx         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "a %hs object at $%p, %u bytes long\n", typeid(obj).name(), pvData, nBytes));
         g_dumpcontext << sz;
      }
   }*/
/* xxx   catch(std::__non_rtti_object & e)
   {
      g_dumpcontext << "_::ca2::CrtdumpClient __non_rtti_object ";
      g_dumpcontext << e.what();
   } */
/*   catch(...)
   {
      // short form for trashed objects
// xxx      sprintf_s(sz, _countof(sz), "faulted while dumping object at $%p, %u bytes long\n", pvData, nBytes);
      g_dumpcontext << sz;
   }
   if (pfnOldCrtDumpClient != NULL)
      (*pfnOldCrtDumpClient)(pvData, nBytes);*/
}

int32_t __cdecl __crt_report_hook(int32_t nRptType, char *szMsg, int32_t* pResult)
{
   // no hook on asserts or when m_pFile is NULL
   if (nRptType == _CRT_ASSERT || g_dumpcontext.m_pfile == NULL)
      return FALSE;

   ASSERT( pResult != NULL );
   if( pResult == NULL )
      throw invalid_argument_exception(::get_thread_app());

   ASSERT( szMsg != NULL );
   if( szMsg == NULL )
      throw invalid_argument_exception(::get_thread_app());

   // non-NULL m_pFile, so go through g_dumpcontext for the message
   *pResult = FALSE;
   g_dumpcontext << szMsg;
   //Allow other report hooks to be called.
   return FALSE;
}

#endif
#endif // ___NO_DEBUG_CRT


