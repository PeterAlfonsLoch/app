#pragma once


namespace primitive
{


   class CLASS_DECL_BASE command :
      virtual public ::object
   {
   public:


      command(sp(::base::application) papp);
      virtual ~command();

      virtual var run();


      virtual void on_request(sp(::create_context) pcreationcontext);


      virtual string get_description();


   };


} // namespace primitive

