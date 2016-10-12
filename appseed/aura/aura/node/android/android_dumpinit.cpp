//#include "framework.h"


/////////////////////////////////////////////////////////////////////////////
// ___DEBUG_STATE implementation

#ifndef ___NO_DEBUG_CRT
//static _CRT_DUMP_CLIENT pfnOldCrtDumpClient = NULL;

#ifdef DEBUG


void __cdecl __crt_dump_client(void * pvData, size_t nBytes)
{
   char sz[1024];
   try
   {

//      if(_CrtReportBlockType(pvData) != ___CLIENT_BLOCK)
  //       return;

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

      if(pobject == NULL)
      {
// xxx            C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "unknown object at $%p, %u bytes long\n", pvData, nBytes));
      }
      else if(::aura::system::g_p->m_pdumpcontext->GetDepth() > 0)
      {
         // long form
         pobject->dump(*::aura::system::g_p->m_pdumpcontext);
         *::aura::system::g_p->m_pdumpcontext << "\n";
      }
      if(false) // else
      {
         //::object & obj = *pobject;
         // short form
// xxx         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "a %hs object at $%p, %u bytes long\n", typeid(obj).name(), pvData, nBytes));
         *::aura::system::g_p->m_pdumpcontext << sz;
      }
   }
/* xxx   catch(std::__non_rtti_object & e)
   {
      *::aura::system::g_p->m_pdumpcontext << "_::ca2::CrtdumpClient __non_rtti_object ";
      ::aura::system::g_p->m_pdumpcontext << e.what();
   } */
   catch(...)
   {
      // short form for trashed objects
// xxx      sprintf_s(sz, _countof(sz), "faulted while dumping object at $%p, %u bytes long\n", pvData, nBytes);
      *::aura::system::g_p->m_pdumpcontext << sz;
   }
   //if (pfnOldCrtDumpClient != NULL)
   //   (*pfnOldCrtDumpClient)(pvData, nBytes);
}

int32_t __cdecl __crt_report_hook(int32_t nRptType, char *szMsg, int32_t* pResult)
{
   // no hook on asserts or when m_pFile is NULL
   if (nRptType == _CRT_ASSERT || ::aura::system::g_p->m_pdumpcontext->m_pfile == NULL)
      return FALSE;

   ASSERT( pResult != NULL );
   if( pResult == NULL )
      throw invalid_argument_exception(::get_thread_app());

   ASSERT( szMsg != NULL );
   if( szMsg == NULL )
      throw invalid_argument_exception(::get_thread_app());

   // non-NULL m_pFile, so go through ::aura::system::g_p->m_pdumpcontext for the message
   *pResult = FALSE;
   *::aura::system::g_p->m_pdumpcontext << szMsg;
   //Allow other report hooks to be called.
   return FALSE;
}

#endif
#endif // ___NO_DEBUG_CRT


#ifdef DEBUG

//___DEBUG_STATE::___DEBUG_STATE()
//{
//#ifndef ___NO_DEBUG_CRT
//   ASSERT(pfnOldCrtDumpClient == NULL);
//   pfnOldCrtDumpClient = _CrtSetDumpClient(__crt_dump_client);
//
//   ASSERT(_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL,__crt_report_hook) != -1);
//   _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
//#endif // ___NO_DEBUG_CRT
//}
//
//___DEBUG_STATE::~___DEBUG_STATE()
//{
//#ifndef ___NO_DEBUG_CRT
//   if(::is_debugger_attached() && false)
//   {
//      try
//      {
//         _CrtDumpMemoryLeaks();
//      }
///*  xxx     catch(std::__non_rtti_object & e)
//      {
//         ::OutputDebugString("~___DEBUG_STATE _CrtdumpMemoryLeaks std::__non_rtti_object\n");
//         ::OutputDebugString(e.what());
//         ::OutputDebugString("\n");
//      } */
//      catch(...)
//      {
//         ::OutputDebugString("~___DEBUG_STATE _CrtdumpMemoryLeaks exception\n");
//      }
//   }
//   int32_t nOldState = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
//   _CrtSetDbgFlag(nOldState & ~_CRTDBG_LEAK_CHECK_DF);
//
//   ASSERT(_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE,__crt_report_hook) != -1);
//   _CrtSetDumpClient(pfnOldCrtDumpClient);
//#endif // ___NO_DEBUG_CRT
//}
//
//PROCESS_LOcaL(___DEBUG_STATE, afxDebugState)
//
//bool CLASS_DECL_AURA __diagnostic_init()
//{
//   // just get the debug state to cause initialization
//   ___DEBUG_STATE* pState = afxDebugState.get_data();
//   ASSERT(pState != NULL);
//
//   return TRUE;
//}

#endif



//__DATADEF bool g_bTraceEnabled = TRUE;
//__DATADEF UINT g_uiTraceFlags = 0;
//static bool gen_DiagnosticInit = __diagnostic_init();
