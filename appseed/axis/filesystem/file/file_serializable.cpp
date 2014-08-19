#include "framework.h"


namespace file
{

      serializable::serializable()
      {
      }

      serializable::serializable(const serializable & s)
      {

         m_paxisapp = s.m_paxisapp;

      }
      #ifdef MOVE_SEMANTICS
      serializable::serializable(serializable && s)
      {

         m_paxisapp = s.m_paxisapp;

      }
      #endif


} // namespace file




