#pragma once




class CLASS_DECL_BASE base_session :
   virtual public ::base::application
{
public:


   ::plane::session *                                       m_pplanesession;
   string_map < sp(::base::application) >                      m_mapApplication;
   sp(::userpresence::userpresence)                         m_puserpresence;
   sp(::ifs)                                                m_pifs;
   sp(::fs::remote_native)                                  m_prfs;
   bool                                                     m_bDrawCursor;


   ::visual::e_cursor                                       m_ecursor;
   ::visual::e_cursor                                       m_ecursorDefault;
   ::base::copydesk_sp                                      m_spcopydesk;


   sp(::fontopus::fontopus)                        m_pfontopus;


   base_session();

   inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }
   inline sp(::fontopus::fontopus)           fontopus()     { return m_pfontopus; }

   virtual bool is_session();


   
   ::base::copydesk & copydesk();

   virtual sp(::base::application) start_application(const char * pszType, const char * pszAppId, sp(::create_context) pcreatecontext);

   virtual ::visual::cursor * get_cursor();
   virtual void set_cursor(::visual::e_cursor ecursor);
   virtual void set_default_cursor(::visual::e_cursor ecursor);
   virtual ::visual::cursor * get_default_cursor();

   virtual COLORREF get_default_color(uint64_t ui);
   virtual ::fontopus::fontopus * create_fontopus();


   virtual ::fontopus::user * safe_get_user();


   virtual ::fontopus::user * get_user();
   virtual ::fontopus::user * create_current_user();


   virtual bool is_licensed(const char * pszId, bool bInteractive = true);


   virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);


};




