#pragma once


namespace user
{


   class tab_callback;


   class CLASS_DECL_ca2 tab :
      virtual public control,
      virtual public place_holder_container
   {
   public:




      class CLASS_DECL_ca2 pane :
         virtual public ::ca::object
      {
      public:


         id                   m_id;
         istring              m_istrTitleEx;
         ::visual::dib_sp     m_dib;
         place_holder *       m_pholder;
         bool                 m_bVisible;
         bool                 m_bPermanent;


         pane();
         pane(::ca::application * papp);
         pane(const pane & pane);
         virtual ~pane();


         pane & operator = (const pane & pane);


         string get_title();

      };


      class CLASS_DECL_ca2 pane_array :
         public spa(pane)
      {
      public:


         pane_array(::ca::application * papp);
         virtual ~pane_array();


         virtual pane * get_by_id(id id);
         ::count get_visible_count();


      };


      class CLASS_DECL_ca2 data :
         virtual public ::ca::data
      {
      public:

         int32_t                              m_iHeightAddUp;
         ::ca::pen_sp                     m_pen;
         ::ca::font_sp                    m_font;
         ::ca::font_sp                    m_fontUnderline;
         ::ca::font_sp                    m_fontBold;
         bool                             m_bCreated;
         int32_t                              m_iTabHeight;
         int32_t                              m_iTabWidth;
         pane_array                       m_panea;
         rect                             m_rectTab;
         rect                             m_rectTabClient;
         visual::graphics_extension       m_dcextension;
         index_array                      m_iaSel;
         rect                             m_rectBorder;
         rect                             m_rectMargin;
         rect                             m_rectTextMargin;
         ::index                          m_iHover;
         image_list                       m_imagelist;
         tab_callback *                   m_pcallback;
         ::index                          m_iDragTab;
         bool                             m_bDrag;
         bool                             m_bVertical;
         ::ca::match::any                m_matchanyRestore;
         bool                             m_bEnableCloseAll;


         data(::ca::application * papp);
         virtual ~data();

         virtual pane * get_pane_by_id(id id);

         ::count get_visible_tab_count();

      };


      class CLASS_DECL_ca2 remove_tab_exception
      {
      public:

         string m_strHint;

         remove_tab_exception(const char * pszHint)
         {
            m_strHint = pszHint;
         }

      };


      sp(data)                         m_spdata;
      ::visual::graphics_extension     m_dcextension;
      bool                             m_bRestoringTabs;
      bool                             m_bShowTabs;
      bool                             m_bNoTabs;
      e_element                        m_eelement;
      sp(::ca::create_context)         m_spcreatecontext;


      tab(::ca::application * papp);
            virtual ~tab();



      data * get_data();


      virtual void on_show_view();

      virtual void  _001SetVertical(bool bSet = true);
      virtual void _001SelectTab(::index iTab);
      virtual void _001CloseTab(::index iTab);
      virtual pane * get_pane(::index iTab, bool bVisible = true);
      virtual ::user::interaction * get_tab_window(::index iTab, bool bVisible = true);
      virtual ::user::place_holder * get_tab_holder(::index iTab, bool bVisible = true);

      void _000OnMouse(::ca::message::mouse * pmouse);

      virtual ::user::interaction * get_view_uie();

      virtual void _001SetTabCallback(tab_callback * pcallback);
      virtual bool _001IsAddTab(::index iTab);
      virtual void _001OnDropTab(::index iTab, e_position eposition);
      virtual void set_cur_tab_by_id(id id, ::ca::create_context * pcreatecontext = NULL);

      virtual id get_cur_tab_id();
      virtual id get_current_id();

      virtual void _001AddSel(::index iSel);
      virtual ::index _001GetSel();
      virtual void _001SetSel(::index iSel);

      virtual ::count _001GetPaneCount();

      virtual void _001OnTabClick(::index iTab);
      virtual void _001OnTabClose(::index iTab);
      virtual ::ca::window * GetNotifyWnd();
      virtual index hit_test(point pt, e_element & eelement);
      virtual e_position DragHitTest(point pt);
      virtual void GetDragRect(LPRECT lprect, e_position eposition);
      virtual int_ptr GetTabCount();
      virtual bool get_element_rect(::index iTab, LPRECT lprect, e_element eelement);

      virtual void layout();
      virtual void layout_pane(index iPane);

      virtual void GetTabClientRect(LPRECT lprect);
      virtual void GetTabClientRect(__rect64 * lprect);

      virtual bool add_tab(const char * lpcsz, id idTab = id(), bool bVisible = true, bool bPermanent = false);
      virtual bool set_tab(const char * lpcsz, id idTab = id(), bool bVisible = true);
      virtual bool add_image_tab(const char * lpcsz, const char * pszImage, id idTab = id(), bool bVisible = true, bool bPermanent = false);
      virtual bool set_image_tab(const char * lpcsz, const char * pszImage, id idTab = id(), bool bVisible = true);
      virtual bool remove_tab_by_id(id idTab = id());
      virtual void remove_tab(::index iTab, bool bVisible = true);
      virtual bool show_tab_by_id(id idTab = id(), bool bShow = true);
      virtual bool show_tab(::index iTab, bool bShow = true);


      virtual bool set_title(::index iTab, const char * psz);
      virtual bool SetTitleById(id id, const char * psz);

      virtual ::index get_tab_by_id(id id);
      virtual id get_id_by_tab(::index iTab, bool bVisible = true);
      virtual pane * get_pane_by_id(id id);
      virtual pane * ensure_pane_by_id(id id);
      virtual void ensure_tab_by_id(id id);

      virtual void on_change_pane_count();

      virtual void get_text_id(stringa & stra);

      virtual void get_prefixed_ci_id(stringa & stra, const char * pszPrefix);
      virtual void get_suffixed_ci_id(stringa & stra, const char * pszSuffix);
      virtual void get_presuffixed_ci_id(stringa & stra, const char * pszPrefix, const char * pszSuffixed);

      virtual void get_begins_ci_eat_id(stringa & stra, const char * pszPrefix);
      virtual void get_ends_ci_eat_id(stringa & stra, const char * pszSuffix);
      virtual void get_begins_ends_ci_eat_id(stringa & stra, const char * pszPrefix, const char * pszSuffixed);

      virtual void install_message_handling(::ca::message::dispatch * pinterface);
      virtual void _001ConnectParent(::ca::message::dispatch * pinterface);


      virtual bool has_restore_tab();
      virtual void get_restore_tab(var_array & vara);
      virtual void open_tabs(const var_array & vara);



      void _001OnDraw(::ca::graphics * pdc);


      void _001OnDrawStandard(::ca::graphics * pdc);
      void _001OnDrawSchema01(::ca::graphics * pdc);



      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_011OnCreate)
      DECL_GEN_SIGNAL(_001OnAppLanguage)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnTimer)

   };


} // namespace user


