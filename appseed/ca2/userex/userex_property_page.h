#pragma once


namespace userex
{


   class property_sheet;


   class CLASS_DECL_ca2  property_page:
      virtual public ::userex::pane_tab_view
   {
   public:


      property_page(::ca::applicationsp papp);
      virtual ~property_page();


   };


} // namespace userex



