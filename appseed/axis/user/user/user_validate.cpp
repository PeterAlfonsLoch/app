//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{

   ////////////////////////////////////////////////////////////
   //
   //   return nok rules
   //
   //   m_iMin - integer min
   //   m_iMax - integer max
   //
   stringa validate::ok(const var & val)
   {

      stringa stra;

      if(m_rules.has_property("m_iMin"))
      {

         if(val.int64() < m_rules[m_iMin].int64())
         {
            
            stra.add("m_iMin");

         }

      }

      return stra;

   }


}
