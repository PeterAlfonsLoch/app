#pragma once


namespace gen
{


   namespace str
   {


      inline CLASS_DECL_ca string         from(const id & id)
      {

         if(id.is_null() || id.is_empty())
            return "";

         if(id.is_text())
            return *id.m_pstr;

         return from(id.m_i);

      }

      inline CLASS_DECL_ca string &       from(string & str, const id & id)
      {

         if(id.is_null() || id.is_empty())
         {
            str.Empty();
         }
         else if(id.is_text())
         {
            str = *id.m_pstr;
         }
         else
         {
            from(str, id.m_i);
         }

         return str;

      }


      inline bool CLASS_DECL_ca begins_eat(var & var, const char * lpcszPrefix)
      {

         return begins_eat(var.get_ref_string(), lpcszPrefix);

      }

      inline bool CLASS_DECL_ca begins_eat_ci(var & var, const char * lpcszPrefix) // case insensitive
      {

         return begins_eat_ci(var.get_ref_string(), lpcszPrefix);

      }

      inline bool CLASS_DECL_ca begins_eat_ci(var & var, const char * lpcszPrefix, const char * pszSeparator) // case insensitive
      {

         return begins_eat_ci(var.get_ref_string(), lpcszPrefix, pszSeparator);

      }

      inline bool CLASS_DECL_ca begins_eat(gen::property & property, const char * lpcszPrefix)
      {

         return begins_eat(property.m_var, lpcszPrefix);

      }

      inline bool CLASS_DECL_ca begins_eat_ci(gen::property & property, const char * lpcszPrefix) // case insensitive
      {

         return begins_eat_ci(property.m_var, lpcszPrefix);

      }

      inline bool CLASS_DECL_ca begins_eat_ci(gen::property & property, const char * lpcszPrefix, const char * pszSeparator) // case insensitive
      {

         return begins_eat_ci(property.m_var, lpcszPrefix, pszSeparator);

      }



   } // namespace str


} // namespace gen






   inline dump_context& dump_context::operator<<(const string & str)
   {
      *this << static_cast< const char * >( str );
      return *this;
   }
