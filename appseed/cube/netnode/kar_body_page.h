#pragma once

namespace kar
{

   class CLASS_DECL_CA2_CUBE body_page :
      virtual public ptr
   {
   public:
      body_page();

      gen::property_set m_params;

      virtual bool has_param(const char * paramName);

   };
   
} // namespace kar
