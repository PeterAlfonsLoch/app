#pragma once


class var;
class application_bias;
class create;
class command_line;


////class CLASS_DECL_AURA ::object :
//class CLASS_DECL_AURA object :
//   virtual public element
//   //class CLASS_DECL_AURA object :
//   //class CLASS_DECL_AURA object
//   //   virtual public ::object
//
//{
//public:
//
//   // OBJECT :: object :> is a ::object
//
//   virtual void add_line(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
//   virtual void add_line_uri(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
//
//   virtual void add_fork(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
//   virtual void add_fork_uri(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
//
//
//   // semantics defined by the requested object - ::object implementator
//   virtual void request_file(var & varFile);
//   virtual void request_file_query(var & varFile, var & varQuery);
//   virtual void request_command(sp(command_line) pcommandline);
//   virtual void request_create(sp(::create) pcreatecontext);
//
//   // another name for request
//   virtual void create(sp(::create) pcreatecontext);
//
//
//   // main loosely coupled semantics :
//   // varFile   : empty, one file path, many file paths, one file object, one or more file objects, or Url, of cached, downloaded, dowloading or queuing files to be opened
//   // varQuery  : more ellaborated requests for the requested object - syntax and semantic defined by requested object - ::object implementator
//   // virtual void on_request(sp(command_line) pcommandline);
//   virtual void on_request(sp(::create) pcreatecontext);
//
//   //mutex          *  m_pmutex;
//
//
//   // OBJECT :: object :> is a object
//
//   //object();
//   //object(const object & objectSrc);
//   //virtual ~object();
//
//
//   virtual void * get_os_data() const;
//
//
//   virtual void lock();
//   virtual bool lock(const duration & durationTimeout);
//   virtual bool unlock();
//   virtual bool unlock(LONG lCount,LPLONG lpPrevCount = NULL);
//
//
//   ///  \brief		abstract function to initialize a waiting action without a timeout
//   virtual void wait();
//
//   ///  \brief		*no more as of 2012-05-12* abstract function to initialize a waiting action with a timeout
//   ///  \param		duration time period to wait for item
//   ///  \return	waiting action result as wait_result
//   virtual wait_result wait(const duration & duration);
//
//
//   virtual bool is_locked() const;
//
//   property_set *     m_psetObject;
//
//
//   //object();
//   //object(const object & objectSrc);              // no implementation
//   //virtual ~object();  // virtual destructors are necessary
//
//
//   // OBJECT :: object :> is a object
//
//   void common_construct();
//
//   bool IsSerializable() const;
//
//
//   property & oprop(const char * psz);
//   property & oprop(const char * psz) const;
//   property_set & oprop_set();
//
//
//   virtual void assert_valid() const;
//   virtual void dump(dump_context & dumpcontext) const;
//
//   object & operator = (const object & objectSrc);       // no implementation
//
//
//   inline sp(::command_thread) command_thread();
//
//
//   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
//
//
//};
//
//
//
