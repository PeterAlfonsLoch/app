#include "framework.h"


namespace net
{


   email::email(sp(::aura::application) papp) :
      element(papp)
   {
   }

   void email::prepare_headers()
   {
      m_strHeaders += "From: =?utf-8?B?" + System.base64().encode(m_strSenderName) + "?= <" + m_addressSender.to_string() + ">\r\n";
      m_strHeaders += "To: =?utf-8?B?" + System.base64().encode(m_strRecipientName) + "?= <" + m_addressRecipient.to_string() + ">\r\n";
   }


} // namespace net

