#pragma once


namespace user
{

   class CLASS_DECL_BASE control :
      virtual public impact
   {
   public:


      enum EMessageParam
      {
         MessageParamGetBaseControlExPtr = 1
      };


      enum e_type
      {
         type_none,
         type_static,
         type_check_box,
         type_edit,
         type_simple_list,
         type_button,
         type_combo_box,
         type_edit_plain_text,
      };
      enum efunction
      {
         // Text got from control m_uiId member
         function_static,
         // Text got from control m_uiText member
         function_static2,
         function_data_selection,
         function_save_on_change,
         function_vms_data_edit,
         function_action,
         function_edit_multi_line,
      };
      enum edatatype
      {
         DataTypeString,
         DataTypeNatural,
      };
      enum eddx
      {
         ddx_none,
         ddx_flags,
         ddx_dbflags,
      };

   // sort_array < INT_PR, int_ptr >
      class CLASS_DECL_BASE ddx_dbflags
      {
      public:


         ddx_dbflags(::database::key key, int_ptr value);


         ::database::key                  m_key;
         int_ptr                          m_value;


      };

      class CLASS_DECL_BASE descriptor :
         virtual public element
      {
      public:

         union
         {
            void *                     m_pvoid;
            class ddx_dbflags *        m_pdbflags;
         } m_ddx;


         union
         {
            void                       * m_pvoid;
            Ex1FormInterfaceComboBox   * m_pcombobox;
         } m_data;

         form_interface *        m_pform;
         sp(control)             m_pcontrol;
         id                      m_id;
         id                      m_uiText;
         sp(type)     m_typeinfo;
         index                   m_iSubItem;
         id                      m_idPrivateDataSection;
         bool                    m_bTransparent;
         e_type                  m_etype;
         bool                    m_bCreated;
         bool                    m_bSubclassed;
         eddx                    m_eddx;
         ::database::id          m_dataid;
         flags < efunction >     m_flagsfunction;
         edatatype               m_edatatype;
         rect                    m_rect;


         descriptor();
         descriptor(const descriptor & descriptor);
         virtual ~descriptor();


         void clear();
         bool operator == (const descriptor & descriptor) const;
         descriptor & operator = (const descriptor & descriptor);
         e_type get_type();
         void set_type(e_type e_type);
         void add_function(efunction efunction);
         void remove_function(efunction efunction);
         bool has_function(efunction efunction);
         edatatype get_data_type();
         void set_data_type(edatatype edatatype);
         void set_ddx_dbflags(::database::id idSection, ::database::id idKey, ::database::id idIndex, int_ptr value);


      };

      class CLASS_DECL_BASE descriptor_set :
         public smart_pointer_array < descriptor >
      {
      public:


         descriptor_set();
         virtual ~descriptor_set();


         sp(control) get_control_by_id(id id);
         descriptor * get(sp(::user::interaction) puie);
         descriptor * get_by_sub_item(int32_t iSubItem);


      };

#ifdef WINDOWSEX
      static const uint32_t      g_uiMessage;
#endif
      index                      m_iHover;
      e_element                  m_eelementHover;
      descriptor *               m_pdescriptor;
      sp(::user::interaction)    m_pwndCustomWindowProc;
      bool                       m_bCustomWindowProc;
      index                      m_iEditItem;
      form_interface *           m_pform;
      form_callback *            m_pformcallback;
      bool                       m_bControlExCommandEnabled;


      control();
      virtual ~control();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual bool create_control(class control::descriptor * pdescriptor);


      bool _003IsCustomMessage();
      ::user::interaction_base * _003GetCustomMessageWnd();



      virtual index get_hover();

      class descriptor & descriptor();

      virtual void _003CallCustomDraw(::draw2d::graphics * pdc, ::user::draw_context * pitem);
      virtual bool _003CallCustomWindowProc(sp(::user::interaction) pwnd, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      virtual void _003OnCustomDraw(::draw2d::graphics * pdc, ::user::draw_context * pitem);
      virtual void _003CustomWindowProc(signal_details * pobj);

      virtual form_interface * get_form();

      //virtual form_list * get_form_list();
      virtual bool _001IsPointInside(point64 pt);

      Ex1FormInterfaceComboBox * GetComboBox();
      control null() { return control(); }
      bool Validate(string & str);
      bool get_data(sp(::user::interaction) pwnd, var & var);
      void SetEditItem(index iItem);
      void SetEditSubItem(index iItem);
      index GetEditSubItem();
      index GetEditItem();

      virtual sp(::user::interaction) ControlExGetWnd();

      using ::user::interaction::GetClientRect;
      using ::user::interaction::GetWindowRect;
      virtual void GetClientRect(LPRECT lprect);
      virtual void GetWindowRect(LPRECT lprect);


      bool operator == (const class ::user::control::descriptor & descriptor) const;
      bool operator == (const class control & control) const;


      virtual bool IsControlCommandEnabled();
      virtual void EnableControlCommand(bool bEnable);


      virtual void BaseControlExOnMouseMove(UINT nFlags, point point);

      virtual index hit_test(point point, e_element & eelement);

      DECL_GEN_SIGNAL(_001OnMouseMove);
         DECL_GEN_SIGNAL(_001OnMouseLeave);

   };


   class control_cmd_ui : public ::base::cmd_ui
   {
   public:

      control_cmd_ui(class ::signal * psignal);


      map < id, id, id, id > m_mapControlCommand;
      virtual void Enable(bool bOn);
      virtual void SetCheck(int32_t nCheck);
      virtual void SetText(const char * lpszText);
      id GetControlCommand(id id);
   };

   class control_view_impl :
      virtual public ::object
   {
   public:

      control_view_impl();

      virtual LRESULT BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
      virtual void BaseControlExOnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler);
      virtual bool BaseControlExOnCommand(WPARAM wParam, LPARAM lParam) ;
      virtual sp(::user::interaction) get_window();

      control_cmd_ui  m_cmdui; // cmd_ui derived class used to update
                                    // base_controlex derived controls
      list<oswindow, oswindow> m_listwndptrBlackList;
   };



} // namespace user
