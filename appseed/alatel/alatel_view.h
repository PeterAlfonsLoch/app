// Alá Telmo Friesen Son God view
// translucid click-through window
// applications:
//    non-intrusive alatel
//    non-intrusive notifications

#pragma once

namespace alatel
{

   class document;

   class CLASS_DECL_CA2_ALARM view :
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


   };

} // namespace alatel