#pragma once


#include "file_opened.h"



namespace file
{


   class CLASS_DECL_AXIS exception :
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
      exception(const exception & e) :
         ::exception::base(e.get_app()),
         ::simple_exception(e.get_app()),
         ::io_exception(e.get_app()),
         ::call_stack(e.get_app())
      {

            printf(":file");
      }

      exception(sp(::base::application) papp, int32_t cause = exception::none, LONG lOsError = -1, const char * lpszArchiveName = NULL);

      virtual void Construct(int32_t cause = exception::none, LONG lOsError = -1, const char * lpszArchiveName = NULL);

      virtual ~exception();

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


} // namespace file



CLASS_DECL_AXIS void throw_file_exception(::base::application * papp, int32_t cause, LONG lOsError,   const char * lpszFileName = NULL);



