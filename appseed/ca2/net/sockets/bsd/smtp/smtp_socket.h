#pragma once

class CLASS_DECL_ca2 email :
   virtual public ::ca::object
{
public:
   email(sp(::ca::application) papp);

   class CLASS_DECL_ca2 address
   {
   public:
      address();
      address(const char * psz);
      address(const address & addr);
      string get_name() const { return m_name; }
      string get_domain() const { return m_domain; }
      string get_top_domain() const { return m_top; }
      string get_sub_domain() const { return m_sub; }

      string to_string() const { return m_name + "@" + m_domain; }

      address & operator = (const char * psz);
      address & operator = (const address & addr);

   private:
      string m_name;
      string m_domain;
      string m_top;
      string m_sub;
   };


   string m_strSenderName;
   address m_addressSender;
   string m_strRecipientName;
   address m_addressRecipient;
   string m_strSubject;
   string m_strHeaders;
   string m_strBody;

   void prepare_headers();
};



namespace sockets
{
   /** Smtp server base class. */
   class CLASS_DECL_ca2 smtp_socket : public tcp_socket
   {
   public:
      typedef enum {
         SMTP_NO_HELLO,
         SMTP_NAME_TOO_LONG,
         SMTP_DOMAIN_TOO_LONG,
         SMTP_QUIT
      } reason_t;


      enum e_state
      {
         state_initial,
         state_hello,
         state_auth,
         state_auth_login,
         state_auth_login_username,
         state_auth_login_password,
         state_sender,
         state_recipient,
         state_data,
         state_body,
         state_sent,
         state_quit,
         state_end
      };

      e_state m_estate;

      email m_email;


   public:
      smtp_socket(socket_handler_base&);


      void OnLine(const string &);

      /** \return 'false' to abort */
      //virtual bool OnHello(const string & domain) = 0;

      /** \return 'false' to abort */
      //virtual bool OnMailFrom(const EmailAddress& addr) = 0;

      /** \return 'false' to abort */
      //virtual bool OnRcptTo(const EmailAddress& addr) = 0;

      //virtual void OnHeader(id idKey, const string & value) = 0;

      //virtual void OnHeaderComplete() = 0;

      //virtual void OnData(const string & line) = 0;

      /** \return 'false' if message write failed (message will probably be resent) */
      //virtual bool OnDataComplete() = 0;

      //virtual void OnRset() = 0;

      //virtual void OnAbort(reason_t) = 0;

      //virtual void OnNotSupported(const string & cmd, const string & arg) = 0;
   
   };

} // namespace sockets



