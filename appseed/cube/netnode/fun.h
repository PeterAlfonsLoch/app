#pragma once


class CLASS_DECL_CA2_CUBE fun :
   virtual public ptr
{
public:

   class CLASS_DECL_CA2_CUBE user :
      virtual public ptr
   {
   public:
      int      m_iId;
      int      m_iImage;
      string   m_strName;
      string   m_strFirstName;
      string   m_strLastName;
      string   m_strEmail;
      int      m_iMergeId;
      string   m_strCurrentBoard;
      comparable_array < user * > m_userptraMerge;
      void prepare();
      double get_credit();
      bool votagus(const char * pszId);
   };

   string key1_generate();
   string key1_generate_sessid();

   user * get_user(int iId, bool bGetMergeAccounts = true);
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
};

