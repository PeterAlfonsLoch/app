#pragma once


namespace gen
{


   namespace str
   {


      inline CLASS_DECL_ca string         itoa(const id & id)
      {

         if(!id.is_number())
            throw simple_exception("invalid_conversion");

         return i64toa(id.m_i);

      }

      inline CLASS_DECL_ca string &       itoa(string & str, const id & id)
      {

         if(!id.is_number())
            throw simple_exception("invalid_conversion");

         return i64toa(str, id.m_i);

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
