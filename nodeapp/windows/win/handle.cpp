#include "StdAfx.h"


namespace win
{

   void PASCAL window::DeleteTempMap()
   {
      hwnd_map* pMap = AfxGetModuleThreadState()->m_pCurrentWinThread->m_pmapHWND;
      pMap->delete_temp();
   }


   void PASCAL graphics::DeleteTempMap()
   {
      hdc_map* pMap = AfxGetModuleThreadState()->m_pCurrentWinThread->m_pmapHDC;
      pMap->delete_temp();
   }

   void PASCAL graphics_object::DeleteTempMap()
   {
      hgdiobj_map* pMap = AfxGetModuleThreadState()->m_pCurrentWinThread->m_pmapHGDIOBJ;
      pMap->delete_temp();
   }

} // namespace win
