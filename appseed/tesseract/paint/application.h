#pragma once

namespace paint
{

   class CLASS_DECL_CA2_TESSERACT application :
      public ::netnodecfg::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;


      application(void);
      virtual ~application(void);

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual ::ca::application * get_app() const;
      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace paint   

