#pragma once

namespace hellomultiverse
{

   class CLASS_DECL_CA2_HELLOMULTIVERSE document :
      public ::userbase::document
   {
   public:


      document(::ca::application * papp);
	   virtual ~document();

      
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);

   };

} // namespace hellomultiverse