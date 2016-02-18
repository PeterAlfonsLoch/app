#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE impact :
      virtual public ::signalizable
   {
   public:
      

      ::filemanager::manager *      m_pmanager;
      bool                          m_bEditConnectInit;


      impact();
      virtual ~impact();


      virtual void install_filemanager_impact_handling();
      virtual void install_filemanager_impact_handling(command_target * ptarget, ::message::dispatch * pdispatch);


      ::fs::item & get_filemanager_item();

      virtual ::filemanager::manager *                get_filemanager_manager();
      virtual ::filemanager::manager_template *       get_filemanager_template();
      virtual ::filemanager::data *                   get_filemanager_data();
      virtual ::user::impact *                        get_this_view();

      void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      virtual void browse_sync(::action::context actioncontext);
      virtual void knowledge(const string & strPath, ::action::context actioncontext);

      virtual void _001Refresh();

      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);

      DECL_GEN_SIGNAL(_001OnOperationDocMessage);

   };


} // namespace filemanager




