#pragma once

namespace verifile
{

   class CLASS_DECL_CA2_TESSERACT application :
      public ::vericalc::application
   {
   public:
      application();
      virtual ~application();


      virtual void construct();


      bool initialize_instance();
      int exit_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual bool on_install();

      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };

} // namespace verifile

