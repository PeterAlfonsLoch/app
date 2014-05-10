#pragma once


namespace userex
{


   class property_sheet;


   class CLASS_DECL_CORE  property_page:
      virtual public ::userex::pane_tab_view
   {
   public:


      property_page(sp(::base::application) papp);
      virtual ~property_page();


   };


} // namespace userex



