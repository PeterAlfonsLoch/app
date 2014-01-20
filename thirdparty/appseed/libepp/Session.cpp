/* 
* libepp-nicbr 1.10 on 2010-14-10 2009 Registro.br
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
* 1. Redistribution of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY REGISTRO.BR ``AS IS AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIE OF FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL REGISTRO.BR BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*/
/* $Id: session.cpp 1059 2010-07-05 20:50:08Z rafael $ */
#include "StdAfx.H"

#define random() rand()

/*#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>*/

/*
#include "session.H"
#include "EppException.H"
#include "IoException.H"
#include "StrUtil.H"
#include "FileUtil.H"
#include "Login.H"
#include "Hello.H"
*/

namespace libepp
{

   session::session(::ca::application * papp, const char *server, const int port, const char *templates_dir) : 
      ca(papp),
      _server(server), 
      _port(port),
      m_socket(papp)
   {
      try
      {    
         _parser = new DomParser(get_app());
         _greeting = new Greeting();
         _cert_common_name_check_enabled = false;
         read_templates(templates_dir);
         srandomdev();
      }
      catch (const GeneralException &e)
      {
         throw; 
      }
   }

   session::~session()
   {
   }

   void session::enable_xml_validation(const char *schemas_dir)
   {
      if (schemas_dir == "")
         _parser->enable_validation();
      else
         _parser->enable_validation(schemas_dir);
   }

   void session::disable_xml_validation()
   {
      _parser->disable_validation();
   }

   void session::enable_cert_common_name_check()
   {
      _cert_common_name_check_enabled = true;
   }

   void session::disable_cert_common_name_check()
   {
      _cert_common_name_check_enabled = false;
   }

   void session::connect(const char * pszCat) 
   {
      try
      {
         m_psocket = new sockets::tls_socket(m_socket.m_handler);
         m_socket.handle(m_psocket);
         m_psocket->open(_server, _port);
         m_psocket->enable_cert_common_name_check(_cert_common_name_check_enabled);
         m_psocket->m_strCat = pszCat;
         //m_socket.connect(client_cert_file, root_ca_file, pem_passphrase);
         string greeting;
         m_socket.read_payload_v1(greeting);
         _last_response = greeting;
         _parser->parse_greeting(greeting, _greeting.get_p());
      }
      catch (const GeneralException &e) 
      {
         throw;  
      }
   }

   void session::disconnect()
   {
      m_psocket->close();
      //m_socket.disconnect();
   }

   void session::send_hello()
   {
      Hello hello;
      string greeting;
      try {
         _last_command = hello.get_xml_format();
         m_socket.write_payload_v1(hello.get_xml_format());
         m_socket.read_payload_v1(greeting);
         _last_response = greeting;
         _parser->parse_greeting(greeting, _greeting.get_p());
      } catch (const GeneralException &e) {
         throw;  
      }
   }

   Greeting *session::get_greeting() 
   {
      return _greeting.get_p();
   }

   void session::process_action(Action *client_action, 
      const string clTRID)
   {
      try 
      {
         // Check Client Transaction ID
         string cmd_clTRID = clTRID;
         if (cmd_clTRID == "")
            cmd_clTRID = gen::str::itoa(random());

         // XML Construction
         string xml_template = _templates[client_action->who_am_i()];
         client_action->get_command()->set_clTRID(cmd_clTRID);
         client_action->set_xml_template(_parser, xml_template);   

         // Store command in XML format 
         _last_command = client_action->get_xml();

         // Write Command
         m_socket.write_payload_v1(client_action->get_xml());      

         // Read Command
         string xml_payload;    
         m_socket.read_payload_v1(xml_payload);

         // Store response in XML format (directly from wire)
         _last_response = xml_payload;

         // XML Parse
         client_action->set_response(xml_payload, _parser);    

         // Client Transaction ID Check
         string response_clTRID = client_action->get_response()->get_clTRID();
         if (cmd_clTRID != response_clTRID) {
            throw EppException(EppException::INVALID_CLTRID, 
               "Invalid Client Transaction ID in the response");
         }
      }
      catch (const GeneralException &e) 
      {
         throw;
      }
   }

   void session::runXML(const string& input)
   {
      try
      {
         // Store command in XML format 
         _last_command = input;

         // Write Command
         m_socket.write_payload_v1(input);

         // Read Command
         string xml_payload;    
         m_socket.read_payload_v1(xml_payload);

         // Store response in XML format (directly from wire)
         _last_response = xml_payload;
      }
      catch (const GeneralException &e) 
      {
         throw;
      }
   }

   void session::read_template(enum ActionType eactiontype, const char * pszTemplateName)
   {
      _templates[eactiontype] = Application.file().as_string(Application.dir().matter(System.dir().path("templates", string(pszTemplateName) + ".xml")));
   }

   void session::read_templates(const char *templates_dir)
   {
      try
      {
         read_template(LOGIN                 , "login");
         read_template(LOGOUT                , "logout");
         read_template(POLL                  , "poll");
         read_template(CONTACT_CHECK         , "contact_check");
         read_template(CONTACT_CREATE        , "contact_create");
         read_template(CONTACT_INFO          , "contact_info");
         read_template(CONTACT_TRANSFER      , "contact_transfer");
         read_template(CONTACT_UPDATE        , "contact_update");
         read_template(DOMAIN_CHECK          , "domain_check");
         read_template(DOMAIN_CREATE         , "domain_create");
         read_template(DOMAIN_INFO           , "domain_info");
         read_template(DOMAIN_RENEW          , "domain_renew");
         read_template(DOMAIN_UPDATE         , "domain_update");
         read_template(DOMAIN_DELETE         , "domain_delete");
         read_template(BR_DOMAIN_CHECK       , "br_domain_check");
         read_template(BR_DOMAIN_INFO        , "br_domain_info");
         read_template(BR_DOMAIN_CREATE      , "br_domain_create");
         _templates[BR_DOMAIN_RENEW]         = _templates[DOMAIN_RENEW];
         read_template(BR_DOMAIN_UPDATE      , "br_domain_update");
         read_template(BR_ORG_CHECK          , "br_org_check");
         read_template(BR_ORG_INFO           , "br_org_info");
         read_template(BR_ORG_CREATE         , "br_org_create");
         read_template(BR_ORG_UPDATE         , "br_org_update");
         read_template(IP_NETWORK_CREATE     , "ipnetwork_create");
         read_template(IP_NETWORK_CHECK      , "ipnetwork_check");
         read_template(IP_NETWORK_DELETE     , "ipnetwork_delete");
         read_template(IP_NETWORK_RENEW      , "ipnetwork_renew");
         read_template(IP_NETWORK_TRANSFER   , "ipnetwork_transfer");
         read_template(IP_NETWORK_INFO       , "ipnetwork_info");
         read_template(IP_NETWORK_UPDATE     , "ipnetwork_update");
         read_template(ASN_CHECK             , "asn_check");
         read_template(ASN_CREATE            , "asn_create");
         read_template(ASN_DELETE            , "asn_delete");
         read_template(ASN_RENEW             , "asn_renew");
         read_template(ASN_TRANSFER          , "asn_transfer");
         read_template(ASN_INFO              , "asn_info");
         read_template(ASN_UPDATE            , "asn_update");
      }
      catch(const IoException &e) 
      {
         throw;
      }
   }

   string session::get_last_command() const
   {
      return _last_command;
   }

   string session::get_last_response() const
   {
      return _last_response;
   }

   string session::get_server() const
   {
      return _server;
   }

   int session::get_port() const
   {
      return _port;
   }

   void session::set_server(const char *server)
   {
      _server = server;
   }

   void session::set_port(const int &port)
   {
      _port = port;
   }

} // namespace libepp

