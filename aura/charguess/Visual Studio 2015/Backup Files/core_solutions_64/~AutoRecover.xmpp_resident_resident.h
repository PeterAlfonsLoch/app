#pragma once


namespace xmpp_resident
{


   class irc_socket;
   class im_stream_view;
   class resident;


   class CLASS_DECL_CORE_XMPP_RESIDENT plugin:
      virtual public object
   {

      resident *m_p;

      plugin(::aura::application * papp,object * p);
      virtual ~plugin();

      virtual string on_pres(string strUser, string strType);


   };
   
   



   class CLASS_DECL_CORE_XMPP_RESIDENT resident :
      virtual public ::xmpp::bot::xmpp_bot,
      virtual public ::xmpp_client::client,
      virtual public ::database::client
   {
   public:


      sp(tts::speaker)              m_pspeaker;

      sp(introjection::compiler)    m_pcompiler;


      resident(::aura::application * papp);


      void register_functions(tinyjs * pjs) override;

      string get_user_data(string strUser, string id);
      void set_user_data(string strUser, string id, string data);

      virtual string on_pres(string strUser,string strType);




   };




} // namespace irc





