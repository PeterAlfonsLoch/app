#pragma once

namespace ca5
{

   namespace user
   {

      class CLASS_DECL_ca presence_central_container :
         virtual public ::radix::object
      {
      public:


         presence_central * m_pcentral;


         presence_central_container();
         virtual ~presence_central_container();

         virtual bool initialize_central_container(::ca::application * papp);
         virtual bool finalize_central_container();

         virtual bool is_initialized();

      };

   } // namespace user

} // namespace ca5