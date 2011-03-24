#pragma once


namespace veriview
{

   class CLASS_DECL_CA2_CUBE document :
      virtual public html_document
   {
   public:
      document(::ca::application * papp);
      virtual ~document();
      
   };


} // namespace veriview