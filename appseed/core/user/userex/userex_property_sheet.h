#pragma once


namespace userex
{


   class CLASS_DECL_CORE property_sheet :
      virtual public ::form_view
   {
   public:


      property_sheet(sp(::axis::application) papp);
      virtual ~property_sheet();

   };


} // namespace userex


