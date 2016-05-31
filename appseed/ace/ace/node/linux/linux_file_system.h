#pragma once


namespace linux
{



   class CLASS_DECL_ACE file_system :
      virtual public ::file::system
   {
   public:



      file_system(::ace::application *  papp);
      virtual ~file_system();



      bool update_module_path();
      
      
      virtual ::file::buffer_sp get_file(var varFile,UINT nOpenFlags,cres * pfesp,::ace::application * papp);
      
      
   };


} // namespace ca2


