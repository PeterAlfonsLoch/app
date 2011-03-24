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


         bool get_title(::ca::application * papp, string & str);


      };

      class CLASS_DECL_ca pane_array :
         public array_ptr_alloc < pane, pane & >
      {
      };


      class CLASS_DECL_ca data :
         virtual public ::ca::data
      {
      public:

         int                              m_iHeightAddUp;
         ::ca::pen_sp                     m_pen;
         ::ca::font_sp                    m_font;
         ::ca::font_sp                    m_fontUnderline;
         ::ca::font_sp                    m_fontBold;
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


         data(::ca::application * papp);
         virtual ~data();

      };

      ::visual::graphics_extension m_dcextension;


      tab(::ca::application * papp);


      data * get_data();


      virtual void on_show_view();

      void  _001SetVertical(bool bSet = true);
      virtual void _001SelectTab(int iTab);
      virtual ::user::interaction * get_tab_window(int iTab);
      virtual ::user::place_holder * get_tab_holder(int iTab);

      void _000OnMouse(::user::win::message::mouse * pmouse);

      virtual ::user::interaction * get_view_uie();

      virtual void _001SetTabCallback(tab_callback * pcallback);
      virtual bool _001IsAddTab(int iTab);
      virtual void _001OnDropTab(int iTab, e_position eposition);
      void RemoveTab(int iTab);
      void _001SetSel(int iSel);
      void set_cur_tab_by_id(id id);
      id get_cur_tab_id();
      virtual id get_current_id();
      void _001AddSel(int iSel);
      int _001GetSel();
      virtual void _001OnTabClick(int iTab);
      ::ca::window * GetNotifyWnd();
      int hit_test(point pt);
      e_position DragHitTest(point pt);
      void GetDragRect(LPRECT lprect, e_position eposition);
      INT_PTR GetTabCount();
      void GetTabRect(int iTab, LPRECT lprect);
      void layout();
      virtual void GetTabClientRect(LPRECT lprect);
      virtual void GetTabClientRect(__rect64 * lprect);
      bool add_tab(const char * lpcsz, id id = class id());
      bool remove_tab(id id = class id());
      bool add_image_tab(const char * lpcsz, const char * pszImage, id id = class id());
      virtual ~tab();
      bool set_title(int iTab, const char * psz);
      bool SetTitleById(id id, const char * psz);
      int get_tab_by_id(id id);
      id get_id_by_tab(int iTab);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual void _001ConnectParent(::user::win::message::dispatch * pinterface);
      

      void _001OnDraw(::ca::graphics * pdc);
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnAppLanguage)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnTimer)
   };

} // namespace user