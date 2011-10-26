// Alá Telmo Friesen Son God view
// translucid click-through window
// applications:
//    non-intrusive md5
//    non-intrusive notifications

#pragma once

namespace md5
{

   class document;

   class CLASS_DECL_CA2_MD5 view :
      virtual public ::userbase::view
   {
   public:


      view(::ca::application * papp);
	   virtual ~view();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);

      document * get_document();

   };

} // namespace md5