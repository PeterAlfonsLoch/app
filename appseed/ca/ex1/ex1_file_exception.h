#pragma once


namespace ex1
{


   class CLASS_DECL_ca file_exception :
      virtual public exception
   {
   public:
      enum
      {
         none,
         generic,
         fileNotFound,
         badPath,
         tooManyOpenFiles,
         accessDenied,
         invalidFile,
         removeCurrentDir,
         directoryFull,
         badSeek,
         hardIO,
         sharingViolation,
         lockViolation,
         diskFull,
         endOfFile
      };




   int      m_cause;
   LONG     m_lOsError;
   string   m_strFileName;



   // Constructor
      file_exception(const file_exception & e) :
         exception(e)
      {
      }

      file_exception(::ca::application * papp, int cause = file_exception::none, LONG lOsError = -1,
         const char * lpszArchiveName = NULL);

      virtual void Construct(int cause = file_exception::none, LONG lOsError = -1, const char * lpszArchiveName = NULL);

      virtual ~file_exception();

      virtual int get_cause();
      virtual LONG get_os_error();
      virtual string get_file_path();


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
   #endif
      virtual BOOL GetErrorMessage(string & str, PUINT pnHelpContext = NULL) const;


   };


   typedef ca::smart_pointer < file_exception > file_exception_sp;


} // namespace ex1


