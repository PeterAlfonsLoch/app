#pragma once


namespace user
{


   class split_bar;


   class CLASS_DECL_CORE split_layout :
      virtual public ::user::place_holder_container
   {
   public:


      friend class split_bar;


      enum e_orientation
      {

         orientation_none        = 0,
         orientation_horizontal  = 1,
         orientation_vertical    = 2,

      };


      enum
      {
         stateInitial = 1,
         stateDragging = 2
      };


      class CLASS_DECL_CORE Pane :
         virtual public element
      {
      public:


         id                      m_id;
         rect                    m_rect;
         size                    m_sizeFixed;
         bool                    m_bFixedSize;
         sp(::user::place_holder)    m_pholder;


         Pane(sp(base_application) papp);


      };


      spa(split_bar)                               m_splitbara;
      spa(Pane)                                    m_panea;
      e_orientation                                m_eorientationSplit;
      int32_t                                      m_iIndex;
      int32_t                                      m_iState;
      bool                                         m_bInitialized;
      ::critical_section                           m_mutex;
      static const int32_t                         m_iMarging;
      int32_t                                      m_cxBorder;
      int32_t                                      m_cyBorder;


      split_layout(sp(base_application) papp);
      virtual ~split_layout();


      virtual int32_t get_normal_dimension();
      virtual int32_t get_ortogonal_dimension();

      void RelayEventSplitBar(int32_t iSplitBar, UINT message, WPARAM wParam, LPARAM lParam);
      e_orientation GetSplitOrientation();
      int32_t GetMaxPos(int32_t iPane);
      int32_t GetMinPos(int32_t iPane);
      bool InsertPaneAt(int32_t iIndex, sp(::user::interaction)pwindow, bool bFixedSize, id idPane = id());
      bool SetPane(int32_t iIndex, sp(::user::interaction)pwindow, bool bFixedSize, id idPane = id());
      bool RemovePaneAt(int32_t iIndex);
      void SetPaneFixedSize(int32_t iIndex, SIZE * pSize);
      void SetVisible(bool bNewValue);
      void CalcSplitBarRect(int32_t iIndex, LPRECT lpRect);
      void CalcPaneRect(int32_t nMinPos, int32_t nMaxPos, LPRECT lpRect);
      void CalcPaneRect(int32_t iIndex, LPRECT lpRect);

      virtual sp(::user::interaction) get_pane_window(int32_t iPane);
      virtual sp(::user::place_holder) get_pane_holder(int32_t iPane);
      virtual id get_pane_id(int32_t iPane);
      virtual int32_t get_pane_by_id(::id id);


      int32_t get_pane_count();

      int32_t get_split_count();
      int32_t get_position(int32_t iIndex);
      void set_position(int32_t iIndex, int32_t nPos);
      void set_position_rate(int32_t iIndex, double dRate, double dMinimumRate = 0.1, double dMaximumRate = 0.9);
      void layout();
      int32_t GetMaxPos();
      int32_t GetMinPos();
      int32_t GetPos(int32_t xPos, int32_t yPos);
      void RelayChildEvent(int32_t iIndex, const MESSAGE *  lpMsg);

      void SetSplitOrientation(e_orientation eorientation);

      bool SetPaneCount(int32_t iPaneCount);

   };


} // namespace user



