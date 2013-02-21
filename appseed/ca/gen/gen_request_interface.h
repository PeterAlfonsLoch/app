#pragma once


class var;


namespace ca
{

   
   class application_bias;
   class create_context;


} // namespace ca


namespace gen
{


   class command_line;


} // namespace gen


namespace gen
{


   class CLASS_DECL_ca request_interface :
      virtual public ::ca::ca
   {
   public:

      virtual void add_line(const char * pszCommandLine, ::ca::application_bias * pbiasCreate = NULL);
      virtual void add_line_uri(const char * pszCommandLine, ::ca::application_bias * pbiasCreate = NULL);

      virtual void add_fork(const char * pszCommandLine, ::ca::application_bias * pbiasCreate = NULL);
      virtual void add_fork_uri(const char * pszCommandLine, ::ca::application_bias * pbiasCreate = NULL);


      // semantics defined by the requested object - request_interface implementator
      virtual void request(var & varFile);
      virtual void request(var & varFile, var & varQuery);
      virtual void request(::gen::command_line * pcommandline);
      virtual void request(::ca::create_context * pcreatecontext);

      // another name for request
      virtual void create(::ca::create_context * pcreatecontext);


      // main loosely coupled semantics :
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects, or Url, of cached, downloaded, dowloading or queuing files to be opened
      // varQuery  : more ellaborated requests for the requested object - syntax and semantic defined by requested object - request_interface implementator
      // changed to create_context on sector 8J on 2011-09-12
      // virtual void on_request(gen::command_line * pcommandline);
      virtual void on_request(::ca::create_context * pcreatecontext);


   };


} // namespace gen

