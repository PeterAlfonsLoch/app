#include "framework.h"


namespace file
{

      serializable::serializable()
      {
      }

      serializable::serializable(const serializable & s)
      {

         m_pauraapp = s.m_pauraapp;

      }
      #ifdef MOVE_SEMANTICS
      serializable::serializable(serializable && s)
      {

         m_pauraapp = s.m_pauraapp;

      }
      #endif


} // namespace file




