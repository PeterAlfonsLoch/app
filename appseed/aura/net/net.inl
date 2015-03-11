#pragma once;


namespace url
{
   

   inline url & url::operator = (const var & var) { return operator = (var.get_string()); }
   inline url & url::operator += (const var & var) { return operator = (var.get_string()); }


} // namespace net





