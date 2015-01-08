#pragma once



namespace windows
{


   namespace axis
   {


      class file_system:
         virtual public ::windows::file_system,
         virtual public ::file::axis::system
      {
      public:


         file_system(::aura::application * papp);
         virtual ~file_system();


         virtual bool FullPath(string & str,const char * lpszFileIn);
         virtual bool FullPath(wstring & wstrFullPath,const wstring & wstrPath);
         virtual UINT GetFileName(const char * lpszPathName,string & str);
         virtual void GetModuleShortFileName(HINSTANCE hInst,string & strShortName);
         virtual var length(const string & strPath,::aura::application * papp);


      };


   } // namespace axis


} // namespace windows

















