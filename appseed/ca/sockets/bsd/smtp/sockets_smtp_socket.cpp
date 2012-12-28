#include "framework.h"

namespace sockets
{

   smtp_socket::smtp_socket(socket_handler_base& h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      m_email(h.get_app())
   {
      SetLineProtocol();

   }


   void smtp_socket::OnLine(const string & line)
   {
      SetNonblocking(false);
      ::gen::parse pa(line);
      string code = pa.getword();

      code.make_upper();
      if(m_estate == state_initial)
      {
         if(code == "220")
         {
            m_estate = state_hello;
            //Send("HELO localhost\r\n");
            Send("EHLO account.ca2.cc\r\n");
         }
      }
      else if(m_estate == state_hello)
      {
         if(code == "250")
         {
            if(pa.getword().CompareNoCase("auth") == 0)
            {
               stringa stra;
               stra.explode(" ", pa.getrest());
               stra.trim();
               if(stra.contains_ci("login"))
               {
                  m_estate = state_auth_login;
                  Send("AUTH LOGIN\r\n");
               }
            }
            else
            {
               m_estate = state_sender;
               Send("MAIL FROM: " + m_email.m_addressSender.to_string() + "\r\n");
            }
         }
      }
      else if(m_estate == state_auth_login)
      {
         if(code == "334")
         {
            string strWord = pa.getword();
            string strRequest = System.base64().decode(strWord);
            string strResponse;
            if(gen::str::find_ci("username", strRequest) >= 0)
            {
               strResponse = System.base64().encode("2.25anos@carloscecyn.com");
               Send(strResponse + "\r\n");
            }
            else if(gen::str::find_ci("password", strRequest) >= 0)
            {
               strResponse = System.base64().encode("anos514Lund");
               Send(strResponse + "\r\n");
            }
         }
         else if(code == "235")
         {
            m_estate = state_sender;
            Send("MAIL FROM: " + m_email.m_addressSender.to_string() + "\r\n");
         }
      }
      else if(m_estate == state_sender)
      {
         if(code == "250")
         {
            m_estate = state_recipient;
            Send("RCPT TO: " + m_email.m_addressRecipient.to_string() + "\r\n");
         }
      }
      else if(m_estate == state_recipient)
      {
         if(code == "250")
         {
            m_estate = state_data;
            Send("DATA\r\n");
         }
      }
      else if(m_estate == state_data)
      {
         if(code.Mid(0, 1) == "3")
         {
            m_estate = state_body;
            Send("Subject:  =?utf-8?B?" + System.base64().encode(m_email.m_strSubject) + "?=\r\n");
            m_email.prepare_headers();
            Send(m_email.m_strHeaders);
            Send("Content-Type: text/plain; charset=\"utf-8\"\r\n");
            Send("\r\n");
            string strBody = m_email.m_strBody;
            strBody.replace("\r\n", "\n");
            stringa stra;
            stra.add_tokens(strBody, "\n", TRUE);
            for(int32_t i = 0; i < stra.get_count(); i++)
            {
               if(stra[i].Mid(0, 1) == ".")
               {
                  Send("." + stra[i] + "\r\n");
               }
               else
               {
                  Send(stra[i] + "\r\n");
               }
            }
            Send(".\r\n");
         }
      }
      else if(m_estate == state_body)
      {
         if(code == "250")
         {
            m_estate = state_quit;
            Send("QUIT\r\n");
         }
      }
      else if(m_estate == state_quit)
      {
         if(code == "221")
         {
            m_estate = state_end;
         }
      }
   }


} // namespace sockets

email::address::address()
{
}

email::address::address(const char * psz)
{
   operator = (psz);
}

email::address & email::address::operator= (const char * psz)
{
   string str_in(psz);
   string str = str_in;
   size_t i = str.find("<");
   if (i != -1)
      str = str.Mid(i + 1);
   i = str.find("@");
   if (i != -1)
   {
      m_name = str.Mid(0, i);
      str = str.Mid(i + 1);
      i = str.find(">");
      if (i != -1)
         str = str.Mid(0, i);
      m_domain = str;
   }
   while (m_name.get_length() && m_name[m_name.get_length() - 1] == ' ')
      m_name = m_name.Mid(0, m_name.get_length() - 1);
   while (m_domain.get_length() && m_domain[m_domain.get_length() - 1] == ' ')
      m_domain = m_domain.Mid(0, m_domain.get_length() - 1);
   while (m_name.get_length() && m_name[0] == ' ')
      m_name = m_name.Mid(1);
   while (m_domain.get_length() && m_domain[0] == ' ')
      m_domain = m_domain.Mid(1);
   m_top = m_domain;
   {
      for (int32_t i = 0; i < m_domain.get_length(); i++)
      {
         if (m_domain[i] == '.')
         {
            m_sub = m_top;
            m_top = m_domain.Mid(i + 1);
         }
      }
   }
   return *this;
}

email::email(::ca::application * papp) :
ca(papp)
{
}

void email::prepare_headers()
{
   m_strHeaders += "From: =?utf-8?B?" + System.base64().encode(m_strSenderName) + "?= <" + m_addressSender.to_string() + ">\r\n";
   m_strHeaders += "To: =?utf-8?B?" + System.base64().encode(m_strRecipientName) + "?= <" + m_addressRecipient.to_string() + ">\r\n";
}


email::address::address(const address & addr)
{
   operator = (addr);
}


email::address & email::address::operator = (const address & addr)
{
   if(this != &addr)
   {
      m_name = addr.m_name;
      m_domain = addr.m_domain;
      m_top = addr.m_top;
      m_sub = addr.m_sub;
   }
   return *this;
}
