#include "framework.h"

namespace database
{

   update_hint::update_hint()
   {
   }

   update_hint::~update_hint()
   {
   }

   flags < update_hint::e_update > & update_hint::GetUpdateFlags()
   {
      return m_flagsupdate;
   }

   void update_hint::add_self(client * lpvoid)
   {
      m_selfa.add_unique(lpvoid);
   }

   bool update_hint::has_self(client * lpvoid)
   {
      return m_selfa.find_first(lpvoid) >= 0;
   }

} // namespace database

