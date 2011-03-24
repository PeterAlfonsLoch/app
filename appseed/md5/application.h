#pragma once

namespace md5
{

   class CLASS_DECL_CA2_MD5 application :
      virtual public cube::application
   {
   public:
      application(void);
      virtual ~application(void);

      ::userbase::single_document_template *    m_ptemplateAlarm;
      ::userbase::multiple_document_template *    m_ptemplateAlatel;

      bool initialize_instance();
      int exit_instance();

      bool bergedge_start();

      void _001OnFileNew();

	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         FileManagerItemArray & itema);

      ::document * _001OpenDocumentFile(var varFile);

   };

   inline CLASS_DECL_CA2_MD5 application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace md5