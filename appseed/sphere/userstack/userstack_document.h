#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE document :
      public ::user::document
   {
   public:


      document(::aura::application * papp);
      virtual ~document();


      virtual bool on_new_document();

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

#endif

   };


} // namespace userstack


