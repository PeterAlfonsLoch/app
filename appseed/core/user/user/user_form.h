#pragma once


namespace user
{


   class CLASS_DECL_CORE form : 
      virtual public scroll_view
   {
   public:


      bool                       m_bOnEditUpdate;
      bool                       m_bOnLanguageChange;
      UINT                       m_uiId;
      control::descriptor_set    m_controldescriptorset;
      bool                       m_bInitialized;
      form_callback *            m_pcallback;


      form(sp(base_application) papp);
      virtual ~form();


      //array < CTransparentStatic *, CTransparentStatic * > m_staticpa;

      virtual string get_path();
      virtual bool open_document(var varFile);


      using control::create;
      using ::user::control::_001IsPointInside;
      virtual bool _001IsPointInside(sp(control) pcontrol, point64 pt);
      virtual void control_get_window_rect(sp(control) pcontrol, LPRECT lprect);
      virtual void control_get_client_rect(sp(control) pcontrol, LPRECT lprect);


      virtual bool _001Initialize();

      virtual void _017OnAppLanguage();
      virtual void _001OnButtonAction(sp(control) pcontrol);
      virtual void _001OnInitializeForm(sp(control) pcontrol);
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(sp(control) pcontrol);
      virtual void _001RemoveControls();
      bool _001Validate(sp(control) pcontrol, var & var);
      bool _001SaveEdit(sp(control) pcontrol);
      virtual bool on_simple_action(id id);
      DECL_GEN_VSIGNAL(_001OnNotify);
      DECL_GEN_VSIGNAL(_001OnMessageNotify);
      virtual void _001GetSelection(::database::id & key, ::database::selection & selection);
      void Update(bool bSave);
      bool _001SetData(id uiId, bool bData);
      bool _001GetData(id uiId, bool & bData);
      int_ptr _001AddControl(class control::descriptor & descriptor);
      void _001FillCombo(sp(control) pcontrol);

      virtual void WfiOnClose();
      
      DECL_GEN_VSIGNAL(_000OnPosCreate);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void install_message_handling(::message::dispatch *pinterface);
      virtual void _001InitializeFormPreData();
      virtual void _001OnUpdate(sp(::user::impact) pviewSender, LPARAM lhint, object* phint);
      virtual void _001Update(sp(control) pcontrol);
      virtual void _001UpdateCheckBox(sp(control) pcontrol);
      virtual void _001UpdateComboBox(sp(control) pcontrol);
      virtual void _001UpdateEdit(sp(control) pcontrol);
      virtual void _001UpdateSimpleList(sp(control) pcontrol);

      virtual void _001UpdateDbFlags(sp(control) pcontrol);
      virtual void _001UpdateDbFlagsCheckBox(sp(control) pcontrol);
      
      DECL_GEN_SIGNAL(_001OnAppLanguage);

      bool OnCommand(WPARAM wparam, LPARAM lparam);
      bool OnCommandButton(sp(control) pcontrol, UINT uiNotificationCode, LPARAM lparam);
      bool OnCommandCheckBox(sp(control) pcontrol, UINT uiNotificationCode, LPARAM lparam);
      bool OnCommandComboBox(sp(control) pcontrol, UINT uiNotificationCode, LPARAM lparam);
      bool OnCommandEdit(sp(control) pcontrol, UINT uiNotificationCode, LPARAM lparam);


      DECL_GEN_VSIGNAL(data_on_after_change);


      virtual bool create_control(class control::descriptor * pdescriptor);
      virtual bool normalize_control_descriptor_typeinfo(class ::user::control::descriptor * pdescriptor);

      bool operator == (const control & control) const;

      bool BaseOnControlEvent(::user::control_event * pevent);
      void _001SetControlFactory();


      virtual void OnBeforeNavigate2(var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);
//        form_view(sp(base_application) papp);
  //    virtual ~form_view();

      //virtual void install_message_handling(::message::dispatch * pinterface);

//      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace user


