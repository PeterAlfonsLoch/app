#pragma once


namespace linux
{



   class CLASS_DECL_AURA file_system :
      virtual public ::file::system
   {
   public:



      file_system(::aura::application *  papp);
      virtual ~file_system();



      bool update_module_path();


      virtual ::file::file_sp get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp);

      virtual bool is_link(string strPath) override;


   };


} // namespace ca2


