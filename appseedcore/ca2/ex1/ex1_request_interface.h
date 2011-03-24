#pragma once


class var;


namespace ex1
{

   class CLASS_DECL_ca request_interface :
      virtual public ::ca::object
   {
   public:


      // semantics defined by the requested object - request_interface implementator
      virtual void request(var & varFile, var & varQuery);
      // main loosely coupled semantics :
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects, or Url, of cached, downloaded, dowloading or queuing files to be opened
      // varQuery  : more ellaborated requests for the requested object - syntax and semantic defined by requested object - request_interface implementator

      virtual void on_request(var & varFile, var & varQuery);
   };

} // namespace ex1