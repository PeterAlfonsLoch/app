#pragma once


namespace userstack
{


   class view;


   class CLASS_DECL_sphere document :
      public ::user::object
   {
   public:


      document(sp(::base::application) papp); 
      virtual ~document();


      virtual bool on_new_document();
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

#endif

   };


} // namespace userstack


