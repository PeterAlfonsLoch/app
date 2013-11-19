#pragma once


#include "base/user/simple/simple_label.h"
#include "base/user/simple/simple_edit_box.h"
#include "base/user/simple/simple_password.h"
#include "base/user/simple/simple_tap.h"


namespace spa
{


   class style;



   class CLASS_DECL_BASE login :
      public ::simple_ui
   {
   public:



      enum e_result
      {

         result_ok,
         result_wrong_password,
         result_fail,
         result_registration_deferred

      };

      class CLASS_DECL_BASE callback
      {
      public:

         virtual void login_result(e_result eresult);

      };

      simple_label         m_labelUser;
      simple_edit_box      m_editUser;
      simple_label         m_labelPassword;
      simple_password      m_password;
      simple_tap           m_tap;

      string               m_strPasshash;

      callback *           m_pcallback;
      string               m_strKeyHash;
      string               m_strSessId;
      string               m_strSecureId;
      string               m_strLoginUrl;
      string               m_strFontopusServer;
      string               m_strRequestingServer;


      login(int left, int top);
      virtual ~login();


      virtual bool on_action(const char * pszId);

      void initialize();

      void defer_translate(::spa::style * pstyle);

      void start_login();

      static uint32_t thread_proc_login(void * lpParam);

      e_result perform_login();

      string calc_key_hash();


      virtual void login_result(e_result eresult);

      virtual void authentication_succeeded();

      virtual void authentication_failed();

      virtual void layout();

      virtual spa::login::e_result process_response(string strResponse);

   };






} // namespace spa




