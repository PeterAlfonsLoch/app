#pragma once

namespace platform
{

   class CLASS_DECL_CORE application :
      virtual public ::nature::application
   {
   public:


      sp(::user::single_document_template) m_ptemplate_html;


      application();
      virtual ~application();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);
         

      //virtual baseapplication * get_app() const;
      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };

} // namespace platform