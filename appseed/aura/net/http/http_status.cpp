#include "framework.h"


namespace http
{


   bool succeeded(e_status estatus)
   {

      switch (estatus)
      {
      case status_ok:
      case status_unchanged:
         return true;
      default:
         break;
      }

      return false;

   }


   bool status_succeeded(int64_t i)
   {

      return succeeded((e_status) i);

   }


   bool failed(e_status estatus)
   {
      
      return !succeeded(estatus);

   }


   bool status_failed(int64_t i)
   {

      return !status_succeeded(i);

   }

   CLASS_DECL_AURA string conn_status(property_set & set)
   {

      e_status estatus = (e_status)set["get_status"].int32();

      string str;

      if (estatus == status_ok)
      {

         str = "OK: ";

      }
      else if (estatus == status_connection_timed_out)
      {

         str = "ERROR: HTTP_CONNECTION_ERROR: Connection Time Out";

      }
      else if (estatus == status_timed_out)
      {

         str = "ERROR: HTTP_CONNECTION_ERROR: Timed Out";

      }
      else if (estatus == status_unchanged)
      {

         str = "ERROR: HTTP_CONNECTION_ERROR: Unknown error, ";

      }
      else
      {

         str = "ERROR: HTTP_CONNECTION_ERROR: ";

      }

      if (str.has_char())
      {

         str += ", ";

      }

      str += "HTTP_STATUS_CODE: " + set["get_attrs"]["http_status_code"].get_string();

      str += ", HTTP_STATUS: \"" + set["get_attrs"]["http_status"].get_string() + "\"";

      return str;

   }




} // namespace http
















