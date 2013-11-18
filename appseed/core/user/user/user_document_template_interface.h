#pragma once


namespace user
{

   class CLASS_DECL_CORE document_template_interface  
   {
   public:
      virtual void reload_template() = 0;
      document_template_interface();
      virtual ~document_template_interface();

   };

} // namespace user

