#pragma once


namespace webserver
{


   namespace kar
   {


      class CLASS_DECL_ca body_page :
         virtual public dynamic_source::ptr
      {
      public:


         gen::property_set m_params;


         body_page();


         virtual bool has_param(const char * paramName);


      };


   } // namespace kar


} // namespace webserver