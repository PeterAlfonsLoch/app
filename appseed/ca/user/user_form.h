#pragma once


namespace user
{


   class CLASS_DECL_ca form : 
      virtual public control
   {
   public:


      bool                       m_bOnEditUpdate;
      bool                       m_bOnLanguageChange;
      UINT                       m_uiId;
      control::descriptor_set    m_controldescriptorset;
      bool                       m_bInitialized;
      form_callback *            m_pcallback;


      form(::ca::application * papp);
      virtual ~form();


      //base_array < CTransparentStatic *, CTransparentStatic * > m_staticpa;

      virtual string get_path();
      virtual bool open_document(var varFile);


      using control::create;
      using ::user::control::_001IsPointInside;
      virtual bool _001IsPointInside(control * pcontrol, point64 pt);
      virtual void control_get_window_rect(control * pcontrol, LPRECT lprect);
      virtual void control_get_client_rect(control * pcontrol, LPRECT lprect);


      virtual bool _001Initialize();

      virtual void _017OnAppLanguage();
      virtual void _001OnButtonAction(control * pcontrol);
      virtual void _001OnInitializeForm(control * pcontrol);
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(control * pcontrol);
      virtual void _001RemoveControls();
      bool _001Validate(control * pcontrol, var & var);
      bool _001SaveEdit(control * pcontrol);
      virtual bool _001OnCommand(id id);
      DECL_GEN_VSIGNAL(_001OnNotify)
      DECL_GEN_VSIGNAL(_001OnMessageNotify)
      virtual void _001GetSelection(::database::id & key, ::database::selection & selection);
      void Update(bool bSave);
      bool _001SetData(id uiId, bool bData);
      bool _001GetData(id uiId, bool & bData);
      int_ptr _001AddControl(class control::descriptor & descriptor);
      void _001FillCombo(control * pcontrol);

      virtual void WfiOnClose();
      
      DECL_GEN_VSIGNAL(_000OnPosCreate)
      DECL_GEN_SIGNAL(_001OnCreate)

      virtual void install_message_handling(::gen::message::dispatch *pinterface);
      virtual void _001InitializeFormPreData();
      virtual void _001OnUpdate(::view * pviewSender, LPARAM lhint, ::gen::object* phint);
      virtual void _001Update(control * pcontrol);
      virtual void _001UpdateCheckBox(control * pcontrol);
      virtual void _001UpdateComboBox(control * pcontrol);
      virtual void _001UpdateEdit(control * pcontrol);
      virtual void _001UpdateSimpleList(control * pcontrol);

      virtual void _001UpdateDbFlags(control * pcontrol);
      virtual void _001UpdateDbFlagsCheckBox(control * pcontrol);
      
      DECL_GEN_SIGNAL(_001OnAppLanguage)

      bool OnCommand(WPARAM wparam, LPARAM lparam);
      bool OnCommandButton(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);
      bool OnCommandCheckBox(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);
      bool OnCommandComboBox(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);
      bool OnCommandEdit(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);


      DECL_GEN_VSIGNAL(data_on_after_change)


      virtual bool create_control(class control::descriptor * pdescriptor);
      virtual bool normalize_control_descriptor_typeinfo(class ::user::control::descriptor * pdescriptor);

      bool operator == (const control & control) const;

      bool BaseOnControlEvent(::user::control_event * pevent);
      void _001SetControlFactory();


      virtual void OnBeforeNavigate2(var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel);


   };


} // namespace user


