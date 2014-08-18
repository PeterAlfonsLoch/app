#include "framework.h"


namespace file
{

      serializable::serializable()
      {
      }

      serializable::serializable(const serializable & s)
      {

         m_pbaseapp = s.m_pbaseapp;

      }
      #ifdef MOVE_SEMANTICS
      serializable::serializable(serializable && s)
      {

         m_pbaseapp = s.m_pbaseapp;

      }
      #endif


} // namespace file




