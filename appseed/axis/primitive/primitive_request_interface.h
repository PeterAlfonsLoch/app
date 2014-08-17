#pragma once


class var;
class application_bias;
class create_context;
class command_line;


class CLASS_DECL_AXIS request_interface :
   virtual public element
{
public:

   virtual void add_line(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
   virtual void add_line_uri(const char * pszCommandLine, application_bias * pbiasCreate = NULL);

   virtual void add_fork(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
   virtual void add_fork_uri(const char * pszCommandLine, application_bias * pbiasCreate = NULL);


   // semantics defined by the requested object - request_interface implementator
   virtual void request_file(var & varFile);
   virtual void request_file_query(var & varFile, var & varQuery);
   virtual void request_command(sp(command_line) pcommandline);
   virtual void request_create(sp(::create_context) pcreatecontext);

   // another name for request
   virtual void create(sp(::create_context) pcreatecontext);


   // main loosely coupled semantics :
   // varFile   : empty, one file path, many file paths, one file object, one or more file objects, or Url, of cached, downloaded, dowloading or queuing files to be opened
   // varQuery  : more ellaborated requests for the requested object - syntax and semantic defined by requested object - request_interface implementator
   // virtual void on_request(sp(command_line) pcommandline);
   virtual void on_request(sp(::create_context) pcreatecontext);


};



