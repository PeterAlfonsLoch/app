#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class WorkSet;


         class CLASS_DECL_CORE DockManager
         {
         public:


            bool IsDocked();

            bool MoveWindow(int32_t x, int32_t y);
            bool OffsetWindowPos(int32_t cx, int32_t cy);
            void layout();
            void UpdateDocking();
            void OnMoving();
            void OnMove();
            void OnSize();


            EDock GetDockState();
            bool Dock(EDock edock, bool bLayout = true);

            EDock GetDockMask();
            void SetDockMask(EDock emask);

            EDock CalcDock(int32_t x, int32_t y);
            bool update(WorkSet * pwf);
            virtual bool relay_event(signal_details * pobj);
            DockManager();
            virtual ~DockManager();

         protected:
            WorkSet  *           m_pworkset;

            EDock                  m_edock; // current dock state
            EDock                  m_edockMask; // current dock mode


         };


         EDock operator |=(EDock & edocki, const EDock  edockj);


      } // namespace frame


   } // namespace uinteraction


} // namespace user









