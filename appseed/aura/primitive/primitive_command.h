#pragma once


namespace primitive
{


   class CLASS_DECL_AURA command :
      virtual public ::object
   {
   public:


      command(sp(::aura::application) papp);
      virtual ~command();

      virtual var run();


      virtual void on_request(sp(::create_context) pcreationcontext);


      virtual string get_description();


   };


} // namespace primitive

