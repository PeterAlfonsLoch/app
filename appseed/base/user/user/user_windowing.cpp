//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"

namespace user
{


	critical_section * g_pcsImpl = NULL;
   map < oswindow,oswindow,::user::interaction_impl *,::user::interaction_impl * > * g_pmapImpl = NULL;
   map < ::user::interaction_impl *,::user::interaction_impl *, oswindow,oswindow > * g_pmapHandle = NULL;


   CLASS_DECL_BASE void init_windowing()
   {

      g_pcsImpl = new critical_section();

      g_pmapImpl = new map < oswindow,oswindow,::user::interaction_impl *,::user::interaction_impl * >;

      g_pmapHandle = new  map < ::user::interaction_impl *,::user::interaction_impl *,oswindow,oswindow >;

   }


   CLASS_DECL_BASE void term_windowing()
   {

      ::aura::del(g_pmapImpl);

      ::aura::del(g_pmapHandle);

      ::aura::del(g_pcsImpl);

   }


} // namespace user


CLASS_DECL_BASE ::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if (oswindow == NULL)
   {

      return NULL;

   }

#ifdef WINDOWSEX

   cslock slOsWindow(::user::g_pcsImpl);

   return ::user::g_pmapImpl->operator[](oswindow);

#else

   if (oswindow == NULL)
   {

      return NULL;

   }


   return oswindow->m_pui;

#endif

}


CLASS_DECL_BASE bool oswindow_assign(oswindow oswindow,::user::interaction_impl * pimpl)
{

   if (oswindow == NULL)
   {

      return false;

   }

   if (pimpl == NULL)
   {

      return false;

   }

   cslock slOsWindow(::user::g_pcsImpl);

   ::user::g_pmapImpl->set_at(oswindow, pimpl);

   ::user::g_pmapHandle->set_at(pimpl, oswindow);

   return true;

}


CLASS_DECL_BASE oswindow oswindow_remove(::user::interaction_impl * pimpl)
{

   ASSERT(pimpl != NULL);

   if (pimpl == NULL)
   {

      return NULL;

   }

   cslock slOsWindow(::user::g_pcsImpl);

   oswindow oswindow = ::user::g_pmapHandle->operator[](pimpl);

   ::user::g_pmapImpl->remove_key(oswindow);

   ::user::g_pmapImpl->remove_key(pimpl->m_oswindow);

   ::user::g_pmapHandle->remove_key(pimpl);

   return oswindow;

}

