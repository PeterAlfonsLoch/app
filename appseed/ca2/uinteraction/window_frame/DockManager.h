#pragma once

#include "Constants.h"

namespace window_frame
{

   class WorkSet;

   class CLASS_DECL_ca2 DockManager  
   {
   public:
      bool IsDocked();
      
      bool MoveWindow(int x, int y);
      bool OffsetWindowPos(int cx, int cy);
      void layout();
      void UpdateDocking();
      void OnMoving();
      void OnMove();
      void OnSize();


      EDock GetDockState();
      bool Dock(EDock edock, bool bLayout = true);

      EDock GetDockMask();
      void SetDockMask(EDock emask);

      EDock CalcDock(int x, int y);
      bool update(WorkSet * pwf);
      virtual bool relay_event(gen::signal_object * pobj);
      DockManager();
      virtual ~DockManager();

   protected:
      WorkSet  *           m_pworkset;

      EDock                  m_edock; // current dock state
      EDock                  m_edockMask; // current dock mode


   };

   EDock operator |=(EDock & edocki, const EDock  edockj);

} // namespace window_frame
