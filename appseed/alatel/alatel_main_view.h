#pragma once


namespace alatel
{

   class document;

   class CLASS_DECL_CA2_ALARM main_view :
      virtual public ::userbase::view
   {
   public:


      
      main_view(::ca::application * papp);
	   virtual ~main_view();


   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);


   };


} // namespace alatel


