#pragma once

namespace userbase
{

   class split_bar;

   class CLASS_DECL_ca split_layout :
      virtual public user::place_holder_container
   {
   public:
      enum e_orientation
      {
         orientation_horizontal = 1,
         orientation_vertical = 2
      };
      enum
      {
         stateInitial = 1,
         stateDragging = 2
      };
      class CLASS_DECL_ca Pane
      {
      public:
         Pane();
         id                      m_id;
         rect                    m_rect;
         size                    m_sizeFixed;
         bool                    m_bFixedSize;
         user::place_holder *    m_pholder;
      };
      array_app_alloc < split_bar, split_bar & > m_splitbara;
      array_ptr_alloc < Pane, Pane &> m_panea;
      e_orientation            m_eorientationSplit;
      int                     m_iIndex;
      int                     m_iState;
      bool                     m_bInitialized;
      ::critical_section      m_mutex;
      static const int        m_iMarging;
      int                     m_cxBorder;
      int                     m_cyBorder;

      split_layout(::ca::application * papp);
      virtual ~split_layout();

      virtual int get_normal_dimension();
      virtual int get_ortogonal_dimension();

      void RelayEventSplitBar(int iSplitBar, UINT message, WPARAM wParam, LPARAM lParam);
      e_orientation GetSplitOrientation();
      int GetMaxPos(int iPane);
      int GetMinPos(int iPane);
      bool InsertPaneAt(int iIndex, ::user::interaction *pWnd, bool bFixedSize, class id id = class id());
      bool SetPane(int iIndex, ::user::interaction *pWnd, bool bFixedSize, class id id = class id());
      bool RemovePaneAt(int iIndex);
      void SetPaneFixedSize(int iIndex, SIZE * pSize);
      void SetVisible(bool bNewValue);
      void CalcSplitBarRect(int iIndex, LPRECT lpRect);
      void CalcPaneRect(int nMinPos, int nMaxPos, LPRECT lpRect);
      void CalcPaneRect(int iIndex, LPRECT lpRect);

      virtual ::user::interaction  * get_pane_window(int iPane);
      virtual ::user::place_holder * get_pane_holder(int iPane);
      virtual id _001GetPaneId(int iPane);

      
      int get_pane_count();

      int get_split_count();
      int get_position(int iIndex);
      void set_position(int iIndex, int nPos);
      void set_position_rate(int iIndex, double dRate, double dMinimumRate = 0.1, double dMaximumRate = 0.9);
      void layout();
      int GetMaxPos();
      int GetMinPos();
      int GetPos(int xPos, int yPos);
      void RelayChildEvent(int iIndex, const MSG *  lpMsg);
      
      void SetSplitOrientation(e_orientation eorientation);
      
      bool SetPaneCount(int iPaneCount);

      friend class split_bar;
   };

} // namespace userbase