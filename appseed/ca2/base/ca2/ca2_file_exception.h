#pragma once


#include "base/ca2/ca2_opened_files.h"



namespace ca2
{


   class CLASS_DECL_ca2 file_exception :
      virtual public ::io_exception
   {
   public:


      enum
      {
         none,
         type_generic,
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




      int32_t      m_cause;
      LONG     m_lOsError;
      string   m_strFileName;
      string   m_strAdd;



      // Constructor
      file_exception(const file_exception & e) :
         exception(e),
         ::base_exception(e.get_app()),
         ::simple_exception(e.get_app()),
         ::io_exception(e.get_app()),
         ::call_stack(e.get_app())
      {
      }

      file_exception(sp(::ca2::application) papp, int32_t cause = file_exception::none, LONG lOsError = -1, const char * lpszArchiveName = NULL);

      virtual void Construct(int32_t cause = file_exception::none, LONG lOsError = -1, const char * lpszArchiveName = NULL);

      virtual ~file_exception();

      virtual int32_t get_cause();
      virtual LONG get_os_error();
      virtual string get_file_path();

#ifdef WINDOWSEX


      static void CALLBACK CallBackFunc( OF_INFO_t OpenedFileInfo, uint_ptr pUserContext );
      void OnFileFound(OF_INFO_t OpenedFileInfo );

#endif

      virtual void dump(dump_context &) const;

      virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


   };


} // namespace ca2



