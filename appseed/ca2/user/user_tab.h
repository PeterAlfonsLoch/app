#pragma once

class ::user::interaction;

namespace user
{

   class tab_callback;

   class CLASS_DECL_ca tab :
      virtual public control,
      virtual public place_holder_container
   {
   public:




      class CLASS_DECL_ca pane
      {
      public:


         id                m_id;
         string            m_strTitleEx;
         ::visual::dib_sp  m_dib;
         place_holder *    m_pholder;
         bool              m_bVisible;
         bool              m_bPermanent;


         pane();


         bool get_title(::ax::application * papp, string & str);


      };


      class CLASS_DECL_ca pane_array :
         public array_ptr_alloc < pane, pane & >
      {
      public:


         virtual pane * get_by_id(id id);
         count get_visible_count();


      };


      class CLASS_DECL_ca data :
         virtual public ::ax::data
      {
      public:

         int                              m_iHeightAddUp;
         ::ax::pen_sp                     m_pen;
         ::ax::font_sp                    m_font;
         ::ax::font_sp                    m_fontUnderline;
         ::ax::font_sp                    m_fontBold;
         bool                             m_bCreated;
         int                              m_iTabHeight;
         int                              m_iTabWidth;
         pane_array                       m_panea;
         rect                             m_rectTab;
         rect                             m_rectTabClient;
         visual::graphics_extension       m_dcextension;
         int_array                        m_iaSel;
         rect                             m_rectBorder;
         rect                             m_rectMargin;
         rect                             m_rectTextMargin;
         int                              m_iHover;
         image_list                       m_imagelist;
         tab_callback *                   m_pcallback;
         int                              m_iDragTab;
         bool                             m_bDrag;
         bool                             m_bVertical;
         ::ex1::match::any                m_matchanyRestore;
         bool                             m_bEnableCloseAll;


         data(::ax::application * papp);
         virtual ~data();

         virtual pane * get_pane_by_id(id id);

         count get_visible_tab_count();

      };

      ::visual::graphics_extension     m_dcextension;
      bool                             m_bRestoringTabs;
      bool                             m_bShowTabs;
      e_element                        m_eelement;


      tab(::ax::application * papp);
            virtual ~tab();



      data * get_data();


      virtual void on_show_view();

      virtual void  _001SetVertical(bool bSet = true);
      virtual void _001SelectTab(int iTab);
      virtual void _001CloseTab(int iTab);
      virtual pane * get_pane(int iTab, bool bVisible = true);
      virtual ::user::interaction * get_tab_window(int iTab, bool bVisible = true);
      virtual ::user::place_holder * get_tab_holder(int iTab, bool bVisible = true);

      void _000OnMouse(::gen::message::mouse * pmouse);

      virtual ::user::interaction * get_view_uie();

      virtual void _001SetTabCallback(tab_callback * pcallback);
      virtual bool _001IsAddTab(int iTab);
      virtual void _001OnDropTab(int iTab, e_position eposition);
      virtual void set_cur_tab_by_id(id id);

      virtual id get_cur_tab_id();
      virtual id get_current_id();

      virtual void _001AddSel(int iSel);
      virtual int _001GetSel();
      virtual void _001SetSel(int iSel);

      virtual int _001GetPaneCount();

      virtual void _001OnTabClick(int iTab);
      virtual void _001OnTabClose(int iTab);
      virtual ::ax::window * GetNotifyWnd();
      virtual int hit_test(point pt, e_element & eelement);
      virtual e_position DragHitTest(point pt);
      virtual void GetDragRect(LPRECT lprect, e_position eposition);
      virtual INT_PTR GetTabCount();
      virtual bool get_element_rect(int iTab, LPRECT lprect, e_element eelement);

      virtual void layout();

      virtual void GetTabClientRect(LPRECT lprect);
      virtual void GetTabClientRect(__rect64 * lprect);

      virtual bool add_tab(const char * lpcsz, id idTab = id(), bool bVisible = true, bool bPermanent = false);
      virtual bool set_tab(const char * lpcsz, id idTab = id(), bool bVisible = true);
      virtual bool add_image_tab(const char * lpcsz, const char * pszImage, id idTab = id(), bool bVisible = true, bool bPermanent = false);
      virtual bool set_image_tab(const char * lpcsz, const char * pszImage, id idTab = id(), bool bVisible = true);
      virtual bool remove_tab_by_id(id idTab = id());
      virtual void remove_tab(int iTab, bool bVisible = true);
      virtual bool show_tab_by_id(id idTab = id(), bool bShow = true);
      virtual bool show_tab(int iTab, bool bShow = true);


      virtual bool set_title(int iTab, const char * psz);
      virtual bool SetTitleById(id id, const char * psz);

      virtual int get_tab_by_id(id id);
      virtual id get_id_by_tab(int iTab, bool bVisible = true);
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

      virtual void install_message_handling(::gen::message::dispatch * pinterface);
      virtual void _001ConnectParent(::gen::message::dispatch * pinterface);


      virtual bool has_restore_tab();
      virtual void get_restore_tab(var_array & vara);
      virtual void open_tabs(const var_array & vara);



      void _001OnDraw(::ax::graphics * pdc);
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
