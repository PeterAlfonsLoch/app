#pragma once
#include "ca/OpenedFiles.h"


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
   string   m_strAdd;



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

      static void CALLBACK CallBackFunc( OF_INFO_t OpenedFileInfo, UINT_PTR pUserContext );
      void OnFileFound(OF_INFO_t OpenedFileInfo );



      virtual void dump(dump_context&) const;
      
      virtual bool GetErrorMessage(string & str, PUINT pnHelpContext = NULL) const;

      virtual bool get_friendly_error_message(string & str, PUINT pnHelpContext = NULL) const;


   };


   typedef ca::smart_pointer < file_exception > file_exception_sp;


} // namespace ex1


