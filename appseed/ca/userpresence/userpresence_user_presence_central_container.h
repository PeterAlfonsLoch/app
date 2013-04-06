#pragma once

namespace userpresence
{

   class CLASS_DECL_ca presence_central_container :
      virtual public ::ca::object
   {
   public:


      presence_central *      m_pcentral;
      bool                    m_bUserPresenceFeatureRequired;


      presence_central_container();
      virtual ~presence_central_container();

      virtual bool initialize_central_container(sp(::ca::application) papp);
      virtual bool finalize_central_container();

      virtual bool is_initialized();

   };

} // namespace userpresence