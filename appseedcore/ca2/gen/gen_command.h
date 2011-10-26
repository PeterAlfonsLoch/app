#pragma once


namespace gen
{


   class CLASS_DECL_ca command :
      virtual public ::radix::object,
      virtual public ::ex1::request_interface
   {
   public:

      
      command(::ca::application * papp);
      virtual ~command();

      virtual var run();


      virtual void on_request(::ca::create_context * pcreationcontext);


      virtual string get_description();


   };


} // namespace command