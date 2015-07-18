#pragma once


CLASS_DECL_AURA bool vfxFullPath(wchar_t * lpszPathOut, const wchar_t * lpszFileIn);
CLASS_DECL_AURA bool vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);
CLASS_DECL_AURA UINT vfxGetFileName(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax);
CLASS_DECL_AURA void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
CLASS_DECL_AURA void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);


namespace windows
{


   class CLASS_DECL_AURA file_system:
      virtual public ::file::system
   {
   public:


      file_system(::aura::application * papp);
      virtual ~file_system();


      virtual bool get_status(const ::file::path & path,::file::file_status & status);
      virtual cres set_status(const ::file::path & path,const ::file::file_status & status);



      virtual bool FullPath(string & str, const char * lpszFileIn);
      virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      virtual UINT GetFileName(const char * lpszPathName, string & str);
      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);
      virtual var length(const string & strPath, ::aura::application * papp);

      virtual bool get_last_write_time(FILETIME * pfiletime,const string & strFilename);

      virtual bool update_module_path();

      virtual ::file::buffer_sp get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp);
      
   };


} // namespace windows




