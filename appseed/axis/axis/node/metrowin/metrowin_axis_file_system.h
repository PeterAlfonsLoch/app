#pragma once


namespace metrowin
{


   namespace axis
   {


      class file_system:
         virtual public ::metrowin::file_system,
         virtual public ::file::axis::system
      {
      public:


         file_system(::aura::application *  papp);
         virtual ~file_system();


         virtual bool FullPath(string & str,const char * lpszFileIn);
         virtual bool FullPath(wstring & wstrFullPath,const wstring & wstrPath);
         virtual UINT GetFileName(const char * lpszPathName,string & str);
         virtual void GetModuleShortFileName(HINSTANCE hInst,string & strShortName);

         virtual var length(const char * pszPath);


         virtual ::file::buffer_sp file_system::get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp);


      };


   } // namespace axis


} // namespace metrowin




















































