#pragma once


class CLASS_DECL_CA2_CUBE secure :
   virtual public ptr
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