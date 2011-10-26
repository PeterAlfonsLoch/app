#pragma once

namespace bisba
{

   class document;

   class CLASS_DECL_CA2_BISBA view :
      public ::userbase::view
   {
   public:


      string m_strServer;


      view(::ca::application * papp);
	   virtual ~view();

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();

   };

} // namespace bisba
