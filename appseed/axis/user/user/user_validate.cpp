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
   stringa validate::nok(const var & val)
   {

      stringa stra;

      if(m_rules.has_property("natural"))
      {

         if(val.get_string().is_empty())
         {

            stra.add("You should enter non negative integer.");

         }
         else
         {

            string str = val.get_string();

            for(index i = 0; i < str.length(); i++)
            {

               if(!isdigit_dup(str[i]))
               {

                  stra.add("You should enter non negative integer.");

                  break;

               }

            }

         }

      }

      if(m_rules.has_property("m_iMin"))
      {

         if(val.int64() < m_rules["m_iMin"].int64())
         {

            string strText = "You should enter an integer greater or equal " + m_rules["m_iMin"].get_string();
            
            stra.add(strText);

         }

      }

      if(m_rules.has_property("m_iMax"))
      {

         if(val.int64() > m_rules["m_iMax"].int64())
         {

            string strText = "You should enter an integer lesser or equal " + m_rules["m_iMax"].get_string();

            stra.add(strText);

         }

      }


      return stra;

   }


}
