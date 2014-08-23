#include "framework.h"


namespace metrowin
{


//   void window::DeleteTempMap()
  // {
      
      /*hwnd_map* pMap = __get_module_state()->m_pmapHWND;

      if(::ca2::is_null(pMap))
         return;

      single_lock sl(&pMap->m_mutex, TRUE);

      raw_array < oswindow > hwndaRemove;
      raw_array < ::metrowin::window * > wndptraRemove;

      POSITION pos = pMap->m_temporaryMap.get_start_position();
      while (pos != NULL)
      {
         HANDLE h; // just used for asserts
         ::metrowin::window * pTemp;
         pMap->m_temporaryMap.get_next_assoc(pos, h, pTemp);


         if(!::IsWindow((oswindow) h))
         {
            hwndaRemove.add((oswindow) h);
            wndptraRemove.add(pTemp);
         }

      }

      for(int i = 0; i < wndptraRemove.get_count(); i++)
      {
         wndptraRemove[i]->m_handlea[0] = NULL;
         wndptraRemove[i]->m_handlea[1] = NULL;

         (*pMap->m_pfnDestructObject)(wndptraRemove[i]);   // destruct the object
      }

      for(int i = 0; i < hwndaRemove.get_count(); i++)
      {
         pMap->m_temporaryMap.remove_key(hwndaRemove[i]);
      }
      */
//   }


} // namespace metrowin


