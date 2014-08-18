#pragma once


namespace str
{


   inline CLASS_DECL_AXIS string         from(const id & id)
   {

      return id;

   }

   inline CLASS_DECL_AXIS string &       from(string & str, const id & id)
   {

      str = id;

      return str;

   }



} // namespace str


inline static string log_level_name(::axis::log::e_level elevel)
{
   switch (elevel)
   {
   case ::axis::log::level_warning:
      return "warning";
   case ::axis::log::level_error:
      return "error";
   case ::axis::log::level_fatal:
      return "fatal";
   case ::axis::log::level_info:
      return "info";
   default:
      return "undefined log error";
   }
}






/*
inline dump_context & dump_context::operator<<(const string & str)
{
*this << static_cast< const char * >( str );
return *this;
}

*/


