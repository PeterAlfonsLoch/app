#pragma once

namespace projection
{

   class CLASS_DECL_CA2_PROJECTION document :
      public ::userbase::document
   {
   public:


      visual::dib_sp      m_spdib;


      document(::ca::application * papp);
	   virtual ~document();

      
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);

   };

} // namespace projection