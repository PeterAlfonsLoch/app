#include "framework.h"


namespace aura
{


   savings::savings(sp(::aura::application) papp) :
      element(papp)
   {

   }

   savings::~savings()
   {

   }

   void savings::save(e_resource eresource)
   {
      m_eresourceflagsShouldSave.signalize(eresource);
   }

   void savings::try_to_save(e_resource eresource)
   {
      m_eresourceflagsShouldSave.signalize(eresource);
   }

   void savings::use(e_resource eresource)
   {
      m_eresourceflagsShouldSave.unsignalize(eresource);
   }

   void savings::may_use(e_resource eresource)
   {
      m_eresourceflagsShouldSave.unsignalize(eresource);
   }

   bool savings::should_save(e_resource eresource)
   {
      return m_eresourceflagsShouldSave.is_signalized(eresource);
   }

   bool savings::is_trying_to_save(e_resource eresource)
   {
      return m_eresourceflagsShouldSave.is_signalized(eresource);
   }

   void savings::warn(e_resource eresource)
   {
      m_eresourceflagsWarning.signalize(eresource);
   }

   void savings::clear_warning(e_resource eresource)
   {
      m_eresourceflagsWarning.unsignalize(eresource);
   }

   bool savings::is_warning(e_resource eresource)
   {
      return m_eresourceflagsWarning.is_signalized(eresource);
   }

} // namespace core
