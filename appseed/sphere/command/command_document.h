#pragma once


namespace command
{


   class CLASS_DECL_sphere document :
      public ::user::object
   {
   public:


      document(sp(::base::application) papp);
	   virtual ~document();

   
      DECL_GEN_VSIGNAL(data_on_after_change);


	   virtual bool on_new_document();

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      bool on_open_document(var varFile);


   };


} // namespace command



