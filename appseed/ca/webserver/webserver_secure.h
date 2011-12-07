#pragma once


namespace webserver
{


   class CLASS_DECL_ca secure :
      virtual public dynamic_source::ptr
   {
   public:
      secure();

      void ensure();
      void logout();
      bool login_check();
      void login();


      bool votagus_is_in();
      bool votagus_automatic_login();
      bool votagus_optional_login();

   };


} // namespace webserver


