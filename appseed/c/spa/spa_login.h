#pragma once


namespace spa
{

   class plugin;

} // namespace spa


class CLASS_DECL_c spa_login :
   public simple_ui
{
public:



   enum e_result
   {
      result_ok,
      result_wrong_password,
      result_fail,
      result_registration_deferred,
   };

   class CLASS_DECL_c callback
   {
   public:

       virtual void login_result(e_result eresult);

   };

   simple_label         m_labelUser;
   simple_edit_box      m_editUser;
   simple_label         m_labelPassword;
   simple_password      m_password;
   simple_tap           m_tap;

   vsstring             m_strPasshash;

   callback *           m_pcallback;
   vsstring             m_strKeyHash;

   
   spa_login();
   virtual ~spa_login();


   virtual void on_action(const char * pszId);

   void initialize();

   void defer_translate(::spa::plugin * pplugin);

   void start_login();

   static uint32_t WINAPI thread_proc_login(LPVOID lpParam);

   e_result login();

   vsstring calc_key_hash();


   virtual void login_result(e_result eresult);

   virtual void authentication_succeeded();

   virtual void authentication_failed();


};