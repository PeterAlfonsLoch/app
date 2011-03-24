#pragma once


namespace fontopus
{

   
   class contact_list;


   class CLASS_DECL_ca user :
      public ::radix::object
   {
   public:

         
      ::http::cookies *             m_phttpcookies;

      string                        m_strLogin;
      string                        m_strName;
      string                        m_strPathPrefix;
      string                        m_strPath;
      string                        m_strDataPath;
      string                        m_strAppDataPath;
      string                        m_strSessid;
      string                        m_strFunUserId;

      contact_list *                m_pcontactlist;

      ::ca5::user::presence *       m_ppresence;


      user(::ca::application * papp);
      virtual ~user();

      virtual void start_veiev_synch();
         

      DECL_GEN_SIGNAL(veiev_synch);
      DECL_GEN_VSIGNAL(on_end_veiev_synch);


   };

} // namespace fontopus


#define AppUser(pcaapp) (*App(pcaapp).get_user())
#define ApplicationUser (AppUser(m_papp))

