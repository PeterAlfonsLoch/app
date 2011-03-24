#pragma once


namespace veriview
{

   class CLASS_DECL_CA2_CUBE view :
      virtual public html_view
   {
   public:
      view(::ca::application * papp);
      virtual ~view();
      
   };


} // namespace veriview