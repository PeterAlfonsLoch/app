#include "StdAfx.h"



namespace i2com
{

/*msn_socket::msn_socket(::ca::application * papp)
: CAsyncSocket(papp)
{
}

msn_socket::~msn_socket()
{
}


void msn_socket::OnReceive(int nErrorCode)
{
char buf[4097];
   int nRead;


   while(true)
   {
      memset(buf, 0, sizeof(buf));
      nRead = Receive(buf, 4096);
      m_strRead += buf;
      if(nRead < 4096)
      {
         break;
      }
      else if(nRead == SOCKET_ERROR)
      {
         close();
         CAsyncSocket::OnReceive(nErrorCode);
         return;
      }
      
   }

//   TRACE(m_strRead);
   
   stringa stra;
   stra.add_tokens(m_strRead, "\r\n", false);
   if(m_estate == StateDispatch)
   {
      if(stra.get_size() == 3)
      {
         if(stra[2].Left(5) == "XFR 3")
         {
            string strLine1 = stra[0];
            string strLine2 = stra[1];
            string strLine3 = stra[2];
            int iFind = stra[2].find("NS");
            iFind += 2;
            while(isspace(stra[2][iFind]))
            {
               iFind++;
            }
            int iStart = iFind;
            while(!isspace(stra[2][iFind]))
            {
               iFind++;
            }
            m_strServer = stra[2].Mid(iStart, iFind - iStart + 1);
            close();
            m_strRead.Empty();
            stringa stra2;
            stra2.add_tokens(m_strServer, ":", false);
            create();
            Connect(stra2[0], atoi(stra2[1]));
         }
         else if(stra[2].Left(5) == "USR 3")
         {
            string strLine1 = stra[0];
            string strLine2 = stra[1];
            string strLine3 = stra[2];
            string strLine = stra[2];
            int iFind = 11;
            while(isspace(strLine[iFind]) && iFind < strLine.get_length())
            {
               iFind++;
            }
            int iStart = iFind;
            while(!isspace(strLine[iFind]) && iFind < strLine.get_length())
            {
               iFind++;
            }
            string strChal = strLine.Mid(iStart, iFind - iStart + 1);
            string strFile;
            strFile = System.file().time_square();
            gen::property_set post;
            gen::property_set headers;
            System.http().ms_download(
               "https://nexus.passport.com/rdr/pprdr.asp",
               strFile,
               NULL,
               post, headers, &ApplicationUser, "HTTP/1.0");
            string urls = headers["PassportURLs"];
            iFind = urls.find("DALogin=");
            iFind += 8;
            while(isspace(urls[iFind])&& iFind < urls.get_length())
            {
               iFind++;
            }
            iStart = iFind;
            while(urls[iFind] != ',' && iFind < urls.get_length())
            {
               iFind++;
            }
            string strLogin = "http://" + urls.Mid(iStart, iFind - iStart);
            string strAuth;
   Retry:
            headers.m_propertya.remove_all();
            strAuth.Format("Passport1.4 OrgVerb=GET,OrgURL=http%%3A%%2F%%2Fmessenger%%2Emsn%%2Ecom,sign-in=%s,pwd=%s,%s",
               System.url().url_encode(m_strUser), 
               System.url().url_encode(m_strPassword),
               strChal);
  //          headers.AddProperty("Authorization", 0);
//            headers["Authorization"]->get_value().set_string(strAuth);
            headers["Host"] = System.url().get_root(strLogin);
              strChal = System.url().url_decode(strChal);
              strChal.replace(",", "&");
              strChal = System.html().special_chars(strChal);
            string strPost = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<Envelope xmlns=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:wsse=\"http://schemas.xmlsoap.org/ws/2003/06/secext\" xmlns:saml=\"urn:oasis:names:tc:SAML:1.0:assertion\" xmlns:wsp=\"http://schemas.xmlsoap.org/ws/2002/12/policy\" xmlns:wsu=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\" xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/03/addressing\" xmlns:wssc=\"http://schemas.xmlsoap.org/ws/2004/04/sc\" xmlns:wst=\"http://schemas.xmlsoap.org/ws/2004/04/trust\">\
  <Header>\
    <ps:AuthInfo xmlns:ps=\"http://schemas.microsoft.com/Passport/SoapServices/PPCRL\" Id=\"PPAuthInfo\">\
      <ps:HostingApp>{7108E71A-9926-4FCB-BCC9-9A9D3F32E423}</ps:HostingApp>\
      <ps:BinaryVersion>4</ps:BinaryVersion>\
      <ps:UIVersion>1</ps:UIVersion>\
      <ps:Cookies></ps:Cookies>\
      <ps:RequestParams>AQAAAAIAAABsYwQAAAAzMDg0</ps:RequestParams>\
    </ps:AuthInfo>\
    <wsse:Security>\
       <wsse:UsernameToken Id=\"::fontopus::user\">\
       <wsse:Username>" + System.html().special_chars(m_strUser) + "</wsse:Username>\
         <wsse:Password>" + System.html().special_chars(m_strUser) + "</wsse:Password>\
       </wsse:UsernameToken>\
    </wsse:Security>\
  </Header>\
  <Body>\
    <ps:RequestMultipleSecurityTokens xmlns:ps=\"http://schemas.microsoft.com/Passport/SoapServices/PPCRL\" Id=\"RSTS\">\
      <wst:RequestSecurityToken Id=\"RST0\">\
        <wst:RequestType>http://schemas.xmlsoap.org/ws/2004/04/security/trust/Issue</wst:RequestType>\
        <wsp:AppliesTo>\
          <wsa:EndpointReference>\
            <wsa:Address>http://Passport.NET/tb</wsa:Address>\
          </wsa:EndpointReference>\
        </wsp:AppliesTo>\
      </wst:RequestSecurityToken>\
      <wst:RequestSecurityToken Id=\"RST1\">\
       <wst:RequestType>http://schemas.xmlsoap.org/ws/2004/04/security/trust/Issue</wst:RequestType>\
        <wsp:AppliesTo>\
          <wsa:EndpointReference>\
            <wsa:Address>messenger.msn.com</wsa:Address>\
          </wsa:EndpointReference>\
        </wsp:AppliesTo>\
        <wsse:PolicyReference URI=\"?" + strChal + "\"></wsse:PolicyReference>\
      </wst:RequestSecurityToken>\
    </ps:RequestMultipleSecurityTokens>\
  </Body>\
</Envelope>";

            System.http().ms_download(
               strLogin,
               strFile,
               NULL,
               strPost, 
               headers, 
               &ApplicationUser);
/* match our ticket */
            /*int iEnd;
            string strResp = Application.file().as_string(strFile);
            PcreUtil::find(strResp, 
               PcreUtil::CompileExpression("#<wsse\:BinarySecurityToken Id=\"PPToken1\">(.*)</wsse\:BinarySecurityToken>#", false),
               0, iStart, iEnd);
            
            string strT = strResp.Mid(iStart, iEnd);

/*            if(headers.has_property("Location"))
            {
               strLogin = headers["Location"]->get_value().get_string();
               goto Retry;
            }
            else if(headers.has_property("Authentication-Info"))
            {*/
              /* strAuth = headers["Authentication-Info"]->get_value().get_string();
               iFind = strAuth.find("from-PP='");
               iFind += 9;
               iStart = iFind;
               iFind = strAuth.find("'", iFind + 1);
               string strT = strAuth.Mid(iStart, iFind - iStart);
               m_estate = state_login;*/
               //string strLine;
  /*             strLine.Format("USR 4 TWN S %s", strT);
               send_line(strLine);
            //}
         }
      }
   }
   else
   {
      
   }
   TRACE("%s", buf);
   CAsyncSocket::OnReceive(nErrorCode);
}
void msn_socket::OnSend(int nErrorCode)
{
   CAsyncSocket::OnSend(nErrorCode);
}
void msn_socket::OnOutOfBandData(int nErrorCode)
{
   CAsyncSocket::OnOutOfBandData(nErrorCode);
}
void msn_socket::OnAccept(int nErrorCode)
{
   CAsyncSocket::OnAccept(nErrorCode);
}
void msn_socket::OnConnect(int nErrorCode)
{
   if(m_estate == StateDispatch || m_estate == state_login)
   {
      netnodeSend();
   }
   CAsyncSocket::OnConnect(nErrorCode);
}
void msn_socket::OnClose(int nErrorCode)
{
   CAsyncSocket::OnClose(nErrorCode);
}

void msn_socket::netnodeSend()
{
   if(m_estate == StateDispatch)
   {
      string strLine;
      strLine = "VER 1 MSNP8 CVR0";
      send_line(strLine);
      strLine.Format("CVR 2 0x0409 win 5.01 i386 MSNMSGR 5.0.0544 MSMSGS %s", m_strUser);
      send_line(strLine);
      strLine.Format("USR 3 TWN I %s", m_strUser);
      send_line(strLine);
   }
}

void msn_socket::get(const char * lpcsz, const char * lpcszHeaders)
{
}

void msn_socket::send_line(const char * pszLine)
{
   string strLine(pszLine);
   strLine += "\r\n";
   Send(strLine, strLine.get_length());
}


void msn_socket::login(const char * pszUser, const char * pszPassword)
{
   m_estate = StateDispatch;
   m_strUser = pszUser;
   m_strPassword = pszPassword;
   create();
   Connect("messenger.hotmail.com", 1863);
}

*/
} // namespace i2com