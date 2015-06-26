#pragma once


#include "file_opened.h"


namespace file
{


   class CLASS_DECL_AURA exception :
      virtual public ::io_exception
   {
   public:



      enum e_cause
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

      e_cause           m_cause;
      LONG              m_lOsError;
      ::file::path      m_strFileName;
      string            m_strAdd;



      // Constructor
      exception(const exception & e) :
         ::exception::base(e.get_app()),
         ::simple_exception(e.get_app()),
         ::io_exception(e.get_app()),
         ::call_stack(e.get_app())
      {

         debug_print(":file");

      }


      exception(::aura::application * papp,e_cause cause = exception::none,LONG lOsError = -1,const char * lpszArchiveName = NULL);

      virtual void Construct(e_cause cause = exception::none, LONG lOsError = -1, const char * lpszArchiveName = NULL);

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


   class CLASS_DECL_AURA exception_sp :
      public sp(exception)
   {
   public:


      exception_sp() {}
      exception_sp(e_context_switcher_no_exception) {}
      exception_sp(e_context_switcher_failed)
      {
         m_p = canew(exception(::get_thread_app()));
         if(m_p != NULL)
         {
            m_p->add_ref();
         }
      }
      exception_sp(::aura::application * papp,exception::e_cause cause = exception::none,LONG lOsError = -1,const char * lpszArchiveName = NULL)
      {
         m_p = canew(exception(papp,cause,lOsError,lpszArchiveName));
         if(m_p != NULL)
         {
            m_p->add_ref();
         }
      }
      exception_sp(exception * p) { m_p = p;if(m_p != NULL) m_p->add_ref(); }
      ~exception_sp() { release(); }


      operator bool() { return is_null(); }


      bool failed() { return !is_null(); }

   };



} // namespace file


inline ::exception::exception * fesp() { return (::file::exception *)NULL; }
inline ::exception::exception * fesp(e_context_switcher_no_exception) { return (::file::exception *)NULL; }
inline ::exception::exception * fesp(e_context_switcher_failed) { return canew(::file::exception(::get_thread_app())); }
inline ::exception::exception * fesp(::aura::application * papp,::file::exception::e_cause cause = ::file::exception::none,LONG lOsError = -1,const char * lpszArchiveName = NULL)
{
   return canew(::file::exception(papp,cause,lOsError,lpszArchiveName));
}
inline ::file::exception_sp fesp(::file::exception * p) { return p; }

CLASS_DECL_AURA void throw_file_exception(::aura::application * papp,::file::exception::e_cause cause,LONG lOsError,const char * lpszFileName = NULL);



