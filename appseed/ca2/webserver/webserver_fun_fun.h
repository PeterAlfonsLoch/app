#pragma once


namespace webserver
{


   namespace fun
   {


      class user;


      class CLASS_DECL_ca fun :
         virtual public dynamic_source::ptr
      {
      public:


         string key1_generate();
         string key1_generate_sessid();

         class ::webserver::fun::user * get_user(int iId, bool bGetMergeAccounts = true);
         bool add_user_group(const char * pszUser, const char * pszGroup);
         int get_group_id(const char * pszGroup);

         bool is_active();

         var get_user_friend_id(int iId);
         var get_user_friend(int iId);

         void agenda_create_event(gen::property_set set);

         string get_user_string(const char * pszUser, const char * pszKey);
         void set_user_string(const char * pszUser, const char * pszKey, const char * pszValue);

         var get_status(const char * pszId);
         var set_status(const char * pszStatus);

         bool license_karfile(__int64 iKarFileId);

         __int64 get_active_user_count();


      };


   } // namespace fun


} // namespace webserver


