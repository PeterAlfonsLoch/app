#pragma once


namespace ex1
{


   class CLASS_DECL_ca file_system :
      virtual public ::radix::object
   {
   public:
      
      
      file_system();
      virtual ~file_system();

      virtual bool ComparePath(const char * lpcsz1, const char * lpcsz2);
      virtual bool FullPath(string & str, const char * lpszFileIn);
      virtual bool FullPath(wstring & strFullPath, const wstring & wstrPath);
      virtual UINT GetFileTitle(const char * lpszPathName, string & str);
      virtual UINT GetFileName(const char * lpszPathName, string & str);
      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);

      void normalize(string & str);
      int cmp(const char * psz1, const char* psz2);


   };


   typedef ca::smart_pointer < file_system > file_system_sp;


} // namespace ex1



