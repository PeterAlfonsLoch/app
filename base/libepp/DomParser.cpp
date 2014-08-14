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
/* $Id: DomParser.cpp 1076 2010-08-03 18:55:45Z rafael $ */

#include "StdAfx.h"


namespace libepp
{

   DomParser::DomParser(::ca::application * papp) :
      ca(papp),
      DomParserCommon(papp)
   {
   }

   void DomParser::parse_command(const char *xml_payload)
   {
      // ca2 - presumabily, developers should ensure this => - always work with utf8 since input to output
      //      string utf8_xml_payload;
      //    StrUtil::iso88591_to_utf8(xml_payload, utf8_xml_payload);
      //parse(utf8_xml_payload);
      parse(xml_payload);
   }

   void DomParser::parse_login_response(const char *xml_payload, Response *response)
   {
      parse_response(xml_payload, response);
   }

   void DomParser::parse_logout_response(const char *xml_payload, Response *response)
   {
      parse_response(xml_payload, response);
   }

   void DomParser::parse_greeting(const char *xml_payload, Greeting *greeting)
   {
      xml::node *n = parse(xml_payload);

      fill_greeting(n, greeting);
   }

   void DomParser::parse_contact_check_response(const char *xml_payload, 
      ContactCheckResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_contact_check_response(n, response);
   }

   void DomParser::parse_contact_create_response(const char *xml_payload,
      ContactCreateResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_contact_create_response(n, response);
   }

   void DomParser::parse_contact_info_response(const char *xml_payload,
      ContactInfoResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_contact_info_response(n, response);
   }

   void DomParser::parse_contact_transfer_response(const char *xml_payload,
      ContactTransferResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_contact_transfer_response(n, response);
   }

   void DomParser::parse_contact_update_response(const char *xml_payload,
      Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_domain_check_response(const char *xml_payload,
      DomainCheckResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_domain_check_response(n, response);
   }

   void DomParser::parse_domain_create_response(const char *xml_payload,
      DomainCreateResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_domain_create_response(n, response);
   }

   void DomParser::parse_domain_info_response(const char *xml_payload, 
      DomainInfoResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_domain_info_response(n, response);
   }

   void DomParser::parse_domain_transfer_response(const char *xml_payload, 
      DomainTransferResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_domain_transfer_response(n, response);
   }

   void DomParser::parse_domain_renew_response(const char *xml_payload,
      DomainRenewResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_domain_renew_response(n, response);
   }

   void DomParser::parse_domain_update_response(const char *xml_payload,
      Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_domain_delete_response(const char *xml_payload, 
      Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_ipnetwork_create_response(const char *xml_payload, 
      IpNetworkCreateResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_ipnetwork_create_response(n, response);
   }

   void DomParser::parse_ipnetwork_check_response(const char *xml_payload, 
      IpNetworkCheckResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_ipnetwork_check_response(n, response);
   }

   void DomParser::parse_ipnetwork_delete_response(const char *xml_payload, 
      Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_ipnetwork_renew_response(const char *xml_payload, 
      IpNetworkRenewResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_ipnetwork_renew_response(n, response);
   }

   void DomParser::parse_ipnetwork_transfer_response(const char *xml_payload, 
      IpNetworkTransferResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_ipnetwork_transfer_response(n, response);
   }

   void DomParser::parse_ipnetwork_info_response(const char *xml_payload, 
      IpNetworkInfoResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_ipnetwork_info_response(n, response);
   }

   void DomParser::parse_ipnetwork_update_response(const char *xml_payload, 
      Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_asn_check_response(const char *xml_payload, AsnCheckResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_asn_check_response(n, response);
   }

   void DomParser::parse_asn_create_response(const char *xml_payload, 
      AsnCreateResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_asn_create_response(n, response);
   }

   void DomParser::parse_asn_update_response(const char *xml_payload, 
      Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_asn_delete_response(const char *xml_payload, Response *response)
   {
      return parse_response(xml_payload, response);
   }

   void DomParser::parse_asn_renew_response(const char *xml_payload, AsnRenewResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_asn_renew_response(n, response);
   }

   void DomParser::parse_asn_transfer_response(const char *xml_payload, 
      AsnTransferResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_asn_transfer_response(n, response);
   }

   void DomParser::parse_asn_info_response(const char *xml_payload, AsnInfoResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_asn_info_response(n, response);
   }

   void DomParser::parse_poll_response(const char *xml_payload, PollResponse *response)
   {
      xml::node *n = parse(xml_payload);

      fill_poll_response(n, response);
   }

   void DomParser::parse_response(const char *xml_payload, Response *response)
   {
      xml::node *n = parse(xml_payload);

      fill_response(n, response);
   }

   void DomParser::get_extValue_info(xml::node *n, string &value, string &xmlns,
      string &reason)
   {
      xml::node *child;
      string elem_name;
      for(int i = 0; i < n->get_children_count(); i++) 
      {
         child = n->child_at(i);
         if(child->get_type() != xml::node_element) 
         {
            continue;
         }
         elem_name = str_transcode(child->get_name());
         if(elem_name == "value") 
         {
            value = str_transcode(child->get_text());
            xmlns = get_xmlns(child);
         }
         else if (elem_name == "reason") 
         {
            reason = str_transcode(child->get_text());
         }
      }
   }

   void DomParser::fill_result(xml::node *n, Response *response)
   {
      string msg, lang, value, xmlns, reason, elem_name;
      Response::ResultCode code;

      code = (Response::ResultCode) (int) n->attr("code");
      xml::node *child;
      for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
      {
         if (child->get_type() == xml::node_element)
         {
            elem_name = str_transcode(child->get_name());
            if (elem_name == "msg" && msg == "") 
            {
               lang = child->attr("lang");
               msg = str_transcode(child->get_text());
               response->insert_result(code, msg);
            } 
            else if (elem_name == "value") 
            {
               if (code != Response::UNSET && msg.has_char()) 
               {
                  value = str_transcode(child->get_text());
                  xmlns = get_xmlns(child);
                  if (value.has_char() && xmlns.has_char()) 
                  {
                     response->insert_result(code, msg, value, xmlns);
                  }
               }
            } 
            else if (elem_name == "extValue" && msg.has_char()) 
            {
               value = xmlns = reason = "";
               get_extValue_info(child, value, xmlns, reason);
               if (value.has_char() && xmlns.has_char()) 
               {
                  response->insert_result(code, msg, value, xmlns, reason);
               }
            }
         }
      }
   }

   void DomParser::fill_response(xml::node *n, Response *response)
   {  
      bool look_children = false;
      if (n->get_type() == xml::node_element) 
      {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response") 
         {
            look_children = true;
         }
         else if (elem_name == "result") 
         {
            fill_result(n, response);
         }
         else if (elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if (elem_name == "svTRID") 
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if (elem_name == "trID")
         {
            look_children = true;
         }
         else if (elem_name == "extension")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:updData")
         {
            fill_brdomain_update_response(n, (BrDomainUpdateResponse *) response);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_response(child, response);
         }    
      }
   }

   void DomParser::fill_greeting(xml::node *n, Greeting *greeting)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "greeting")
         {
            look_children = true;
         }
         else if(elem_name == "svID")
         {
            greeting->set_svID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svDate")
         {
            greeting->set_svDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "svcMenu")
         {
            look_children = true;
         }
         else if(elem_name == "version")
         {
            greeting->set_version(str_transcode(n->get_text()));
         }
         else if(elem_name == "lang")
         {
            greeting->set_lang(str_transcode(n->get_text()));
         }
         else if(elem_name == "objURI")
         {
            greeting->set_objURI(str_transcode(n->get_text()));
         }
         else if(elem_name == "svcExtension")
         {
            look_children = true;
         }
         else if(elem_name == "extURI")
         {
            greeting->set_extURI(str_transcode(n->get_text()));
         }
         else if(elem_name == "dcp")
         {
            look_children = true;
         }
         else if(elem_name == "access")
         {
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() == xml::node_element) {
                     string e_name = str_transcode(child->get_name());
                     if (e_name == "all")
                     {
                        greeting->set_access(Greeting::ALL);
                     }
                     else if(e_name == "none")
                     {
                        greeting->set_access(Greeting::NONE_AC);
                     }
                     else if(e_name == "NULL")
                     {
                        greeting->set_access(Greeting::NULL_AC);
                     }
                     else if(e_name == "other")
                     {
                        greeting->set_access(Greeting::OTHER_AC);
                     }
                     else if(e_name == "personal")
                     {
                        greeting->set_access(Greeting::PERSONAL);
                     }
                     else if(e_name == "personalAndOther")
                     {
                        greeting->set_access(Greeting::PERSONAL_AND_OTHER);
                     }
                  }
            }
         }
         else if(elem_name == "statement")
         {
            look_children = true;
         }
         else if(elem_name == "purpose")
         {
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() == xml::node_element) {
                     string e_name = str_transcode(child->get_name());
                     if (e_name == "admin")
                     {
                        greeting->set_purpose(Greeting::ADMIN);
                     }
                     else if(e_name == "contact")
                     {
                        greeting->set_purpose(Greeting::CONTACT);
                     }
                     else if(e_name == "other")
                     {
                        greeting->set_purpose(Greeting::OTHER_PR);
                     }
                     else if(e_name == "prov")
                     {
                        greeting->set_purpose(Greeting::PROV);
                     }
                  }
            }      
         }
         else if(elem_name == "recipient")
         {
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() == xml::node_element) {
                     string e_name = str_transcode(child->get_name());
                     if (e_name == "other")
                     {
                        greeting->set_recipient(Greeting::OTHER_RC);
                     }
                     else if(e_name == "ours")
                     {
                        greeting->set_recipient(Greeting::OURS);
                        xml::node *recDesc = child->first_child();
                        if (recDesc && recDesc->get_type() == xml::node_element) {
                           if (str_transcode(recDesc->get_name()) == "recDesc")
                           {
                              greeting->set_recDesc(str_transcode(recDesc->get_text()));
                           }
                        }
                     }
                     else if(e_name == "public")
                     {
                        greeting->set_recipient(Greeting::PUBLIC);
                     }
                     else if(e_name == "same")
                     {
                        greeting->set_recipient(Greeting::SAME);
                     }
                     else if(e_name == "unrelated")
                     {
                        greeting->set_recipient(Greeting::UNRELATED);
                     }
                  }
            }
         }
         else if(elem_name == "retention")
         {
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() == xml::node_element) {
                     string e_name = str_transcode(child->get_name());
                     if (e_name == "business")
                     {
                        greeting->set_retention(Greeting::BUSINESS);
                     }
                     else if(e_name == "indefinite")
                     {
                        greeting->set_retention(Greeting::INDEFINITE);
                     }
                     else if(e_name == "legal")
                     {
                        greeting->set_retention(Greeting::LEGAL);
                     }
                     else if(e_name == "none")
                     {
                        greeting->set_retention(Greeting::NONE_RT);
                     }
                     else if(e_name == "stated")
                     {
                        greeting->set_retention(Greeting::STATED);
                     }
                  }
            }      
         }
         else if(elem_name == "expiry")
         {
            look_children = true;
         }
         else if(elem_name == "absolute")
         {
            greeting->set_expiry(0, str_transcode(n->get_text()));
         }
         else if(elem_name == "relative")
         {
            greeting->set_expiry(1, str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_greeting(child, greeting);
         }
      }
   }

   void DomParser::fill_contact_check_response(xml::node *n, ContactCheckResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:chkData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:cd")
         {
            xml::node *child;
            string id, avail, reason;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string e_name = str_transcode(child->get_name());
                  if (e_name == "contact:id")
                  {
                     if(child->attr("avail").has_char())
                     {
                        avail = child->attr("avail");
                     }
                     id = str_transcode(child->get_text());
                  }
                  else if(e_name == "contact:reason")
                  {
                     reason = str_transcode(child->get_text());
                  }
            }
            response->insert_availability(id, avail, reason);
         }
         else if(elem_name == "extension")
         {
            look_children = true;
         }
         else if(elem_name == "brorg:chkData")
         {
            //brorg extension
            fill_brorg_check_response(n, (BrOrgCheckResponse*) response);
         }
      }  

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_contact_check_response(child, response);
         }
      }
   }

   void DomParser::fill_contact_info_response(xml::node *n, ContactInfoResponse *response)
   {
      string str;

      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         CommonData common = response->get_common_data();
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:infData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:id")
         {
            common.set_id(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:status")
         {
            if(n->attr("s").has_char())
            {
               response->insert_status(n->attr("s"));
            }
         }
         else if(elem_name == "contact:postalInfo")
         {
            PostalInfo pi;
            fill_postal_info(n, &pi);

            common.insert_postal_info(pi);
         }
         else if(elem_name == "contact:voice")
         {
            struct CommonData::Phone phone;
            if(n->attr("x").has_char())
            {
               phone.ext = n->attr("x");
            }

            phone.number = str_transcode(n->get_text());
            common.set_voice(phone);
         }
         else if(elem_name == "contact:fax")
         {

            struct CommonData::Phone phone;
            if(n->attr("x").has_char())
            {
               phone.ext = n->attr("x");
            }

            phone.number = str_transcode(n->get_text());
            common.set_fax(phone);
         }
         else if(elem_name == "contact:email")
         {
            string email = str_transcode(n->get_text());
            common.set_email(email);
         }
         else if(elem_name == "contact:clID")
         {
            response->set_clID(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:crID")
         {
            response->set_crID(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:upID")
         {
            response->set_upID(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:upDate")
         {
            response->set_upDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:trDate")
         {
            response->set_trDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:authInfo")
         {

            AuthInfo authInfo;

            if(n->attr("roid").has_char()) 
            {
               authInfo.set_roid(n->attr("roid"));
            }

            xml::node *child;
            for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
            {
               if (child->get_type() != xml::node_element) 
               {
                  continue;
               }
               string e_name = str_transcode(child->get_name());
               if (e_name == "contact:pw") 
               {
                  authInfo.set_pw(str_transcode(child->get_text()));
                  break;
               }
            }
            response->set_authInfo(authInfo);
         } 
         else if (elem_name == "contact:disclose")
         {
            CommonData::Disclose disc;

            bool has_flag = false;
            if(n->attr("flag").has_char()) 
            {
               has_flag = true;
               if(n->attr("flag") == "0") 
               {
                  disc.flag = false;
               }
               else 
               {
                  disc.flag = true;
               }
            }

            if (has_flag) 
            {
               xml::node *child;
               for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
               {
                  if (child->get_type() != xml::node_element)
                  {
                     continue;
                  }
                  string e_name = str_transcode(child->get_name());
                  if (e_name == "contact:name") 
                  {
                     if(n->find_attr("loc") != NULL) 
                     {
                        disc.name_loc = true;
                     }
                     else if (n->find_attr("int") != NULL) 
                     {
                        disc.name_int = true;
                     }
                  }
                  else if (e_name == "contact:org") 
                  {
                     if(n->find_attr("loc") != NULL) 
                     {
                        disc.org_loc = true;
                     }
                     else if (n->find_attr("int") != NULL) 
                     {
                        disc.org_int = true;
                     }
                  } 
                  else if (e_name == "contact:addr") 
                  {
                     if(n->find_attr("loc") != NULL) 
                     {
                        disc.addr_loc = true;
                     }
                     else if (n->find_attr("int") != NULL) 
                     {
                        disc.addr_int = true;
                     }
                  } 
                  else if (e_name == "contact:voice") 
                  {
                     disc.voice = true;
                  }
                  else if (e_name == "contact:fax") 
                  {
                     disc.fax = true;
                  }
                  else if (e_name == "contact:email") 
                  {
                     disc.email = true;
                  }
               }
               common.set_disclose(disc);
            }
         }
         else if (elem_name == "extension") 
         {
            look_children = true;
         }
         else if (elem_name == "brorg:infData") 
         {
            fill_brorg_info_response(n, (BrOrgInfoResponse *) response);
         }

         response->set_common_data(common);
      }

      if (look_children) 
      {
         xml::node *child;
         for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
         {
            fill_contact_info_response(child, response);
         }
      }
   }

   void DomParser::fill_contact_transfer_response(xml::node *n, ContactTransferResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:trnData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:id")
         {
            response->set_id(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:trStatus")
         {
            response->set_trStatus(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:reID")
         {
            response->set_reID(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:reDate")
         {
            response->set_reDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:acID")
         {
            response->set_acID(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:acDate")
         {
            response->set_acDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_contact_transfer_response(child, response);
         }
      }
   }

   void DomParser::fill_contact_create_response(xml::node *n, ContactCreateResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:creData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:id")
         {
            response->set_id(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "extension")
         {
            look_children = true;
         }
         else if(elem_name == "brorg:creData")
         {
            fill_brorg_create_response(n, (BrOrgCreateResponse*) response);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_contact_create_response(child, response);
         }
      }
   }

   void DomParser::fill_contact_pandata_response(xml::node *n, PanDataResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "contact:panData")
         {
            look_children = true;
         }
         else if(elem_name == "contact:id")
         {
            response->set_object_id(str_transcode(n->get_text()));
            // attribute
            if(n->attr("paResult") == "1")
            {
               response->set_paResult(true);
            }

         }
         else if(elem_name == "contact:paTRID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "contact:paDate")
         {
            response->set_paDate(str_transcode(n->get_text()));
         }

         if (look_children)
         {
            xml::node *child;
            for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
            {
                  fill_contact_pandata_response(child, response);
            }
         }
      }
   }

   void DomParser::fill_domain_check_response(xml::node *n, DomainCheckResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:chkData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:cd")
         {
            xml::node *child;
            string name, avail, reason;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string e_name = str_transcode(child->get_name());
                  if (e_name == "domain:name")
                  {
                     if(child->attr("avail").has_char())
                     {
                        avail = child->attr("avail");
                     }
                     name = str_transcode(child->get_text());
                  }
                  else if(e_name == "domain:reason")
                  {
                     reason = str_transcode(child->get_text());
                  }
            }
            response->insert_availability(name, avail, reason);
         }
         else if(elem_name == "extension") 
         {
            look_children = true;
         }
         else if (elem_name == "brdomain:chkData") 
         {
            //brdomain extension
            fill_brdomain_check_response(n, (BrDomainCheckResponse*) response);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_domain_check_response(child, response);
         }
      }
   }

   void DomParser::fill_domain_info_response(xml::node *n, DomainInfoResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:infData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:name")
         {
            response->set_name(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:status")
         {
            if(n->attr("s").has_char())
            {
               response->insert_status(n->attr("s"));
            }
         }
         else if(elem_name == "domain:registrant")
         {
            response->set_registrant(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:contact")
         {
            response->insert_contact(n->attr("type"), str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:ns")
         {
            look_children = true;
         }
         else if(elem_name == "domain:hostAttr")
         {
            NameServer ns;
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string e_name = str_transcode(child->get_name());
                  if (e_name == "domain:hostName")
                  {
                     ns.name = str_transcode(child->get_text());
                  }
                  else if(e_name == "domain:hostAddr")
                  {
                     NSIPAddr ip;
                     ip.addr = str_transcode(child->get_text());
                     ip.version = child->attr("ip");
                     ns.ips.add(ip);
                  }
            }
            response->insert_nameserver(ns);
         }
         else if (elem_name == "domain:clID")
         {
            response->set_clID(str_transcode(n->get_text()));
         }
         else if (elem_name == "domain:crID")
         {
            response->set_crID(str_transcode(n->get_text()));
         }
         else if (elem_name == "domain:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if (elem_name == "domain:upID")
         {
            response->set_upID(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:upDate")
         {
            response->set_upDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:trDate")
         {
            response->set_trDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:authInfo")
         {
            AuthInfo authInfo;
            authInfo.set_roid(n->attr("roid"));
            authInfo.set_pw(str_transcode(n->get_text()));
            response->set_authInfo(authInfo);
         }
         else if(elem_name == "domain:host")
         {
            // Ignored
         }
         else if(elem_name == "domain:hostObj")
         {
            // Ignored
         }
         else if(elem_name == "extension")
         {
            look_children = true;
         }
         else if (elem_name == "brdomain:infData") 
         {
            //brdomain extension
            fill_brdomain_info_response(n, (BrDomainInfoResponse *) response);
         }
         else if (elem_name == "secDNS:infData") 
         {
            look_children = true;
         }
         else if (elem_name == "secDNS:dsData") 
         {
            DSInfo dsInfo(get_app());
            fill_ds_info(n, &dsInfo);
            response->add_dsInfo(dsInfo);
         }
         else if (elem_name == "secDNS:keyData")
         {
            KeyData keyData;
            fill_key_data(n, &keyData);
            response->add_keyData(keyData);
         }
      }

      if (look_children) 
      {
         xml::node *child;
         for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
         {
            fill_domain_info_response(child, response);
         }
      }
   }

   void DomParser::fill_domain_transfer_response(xml::node *n, DomainTransferResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) 
      {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response") 
         {
            look_children = true;
         }
         else if (elem_name == "result") 
         {
            fill_result(n, (Response *)response);
         }
         else if (elem_name == "trID") 
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:trnData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:name")
         {
            response->set_name(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:trStatus")
         {
            response->set_trStatus(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:reID")
         {
            response->set_reID(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:reDate")
         {
            response->set_reDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:acID")
         {
            response->set_acID(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:acDate")
         {
            response->set_acDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_domain_transfer_response(child, response);
         }
      }
   }

   void DomParser::fill_domain_create_response(xml::node *n, DomainCreateResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:creData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:name")
         {
            response->set_name(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "extension")
         {
            look_children = true;
         } 
         else if (elem_name == "brdomain:creData") 
         {
            fill_brdomain_create_response(n, (BrDomainCreateResponse *) response);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_domain_create_response(child, response);
         }
      }
   }

   void DomParser::fill_domain_renew_response(xml::node *n, DomainRenewResponse *response) 
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:renData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:name")
         {
            response->set_name(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "extension")
         {
            look_children = true;
         }
         else if (elem_name == "brdomain:renData") 
         {
            //brdomain extension
            fill_brdomain_renew_response(n, (BrDomainRenewResponse*) response);
         }    
      }      

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_domain_renew_response(child, response);
         }
      }
   }

   void DomParser::fill_domain_pandata_response(xml::node *n, PanDataResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "domain:panData")
         {
            look_children = true;
         }
         else if(elem_name == "domain:name")
         {
            response->set_object_id(str_transcode(n->get_text()));
            // attribute
            if(n->attr("paResult") == "1")
            {
               response->set_paResult(true);
            }

         }
         else if(elem_name == "domain:paTRID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "domain:paDate")
         {
            response->set_paDate(str_transcode(n->get_text()));
         }

         if (look_children) {
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  fill_domain_pandata_response(child, response);
            }
         }
      }
   }

   void DomParser::fill_ipnetwork_create_response(xml::node *n, IpNetworkCreateResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:creData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:ipRange")
         {
            response->set_ipRange(fill_ipRange(n));
         }
         else if(elem_name == "ipnetwork:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_ipnetwork_create_response(child, response);
         }
      }
   }

   void DomParser::fill_ipnetwork_check_response(xml::node *n, IpNetworkCheckResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:chkData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:cd")
         {
            xml::node *child;

            IpRange ipRange;
            string reason = "";
            string reason_lang = "";

            for (child = n->first_child(); child != 0; 
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }

                  string e_name = str_transcode(child->get_name());
                  if (e_name == "ipnetwork:ipRange")
                  {
                     ipRange = fill_ipRange(child);
                  }
                  else if(e_name == "ipnetwork:reason")
                  {
                     string lang = child->attr("lang");

                     if (lang.has_char())
                     {
                        reason_lang = lang;
                     }

                     reason = str_transcode(child->get_text());
                  }
            }

            response->insert_availability(ipRange, reason, reason_lang);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_ipnetwork_check_response(child, response);
         }
      }
   }

   void DomParser::fill_ipnetwork_renew_response(xml::node *n, IpNetworkRenewResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:renData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:exDate")
         {
            response->set_expDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_ipnetwork_renew_response(child, response);
         }
      }
   }

   void DomParser::fill_ipnetwork_transfer_response(xml::node *n, 
      IpNetworkTransferResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:trnData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:trStatus")
         {
            response->set_trStatus(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:reID")
         {
            response->set_reId(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:reDate")
         {
            response->set_reDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:acID")
         {
            response->set_acId(str_transcode(n->get_text()));
         }
         else if(elem_name == "ipnetwork:acDate")
         {
            response->set_acDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_ipnetwork_transfer_response(child, response);
         }
      }
   }

   void DomParser::fill_ipnetwork_info_response(xml::node *n, IpNetworkInfoResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:infData")
         {
            look_children = true;
         }
         else if(elem_name == "ipnetwork:ipRange")
         {
            response->set_ipRange(fill_ipRange(n));
         }
         else if(elem_name == "ipnetwork:ipRangeInfo")
         {
            IpNetworkInfoResponse::IpRangeInfo ipRangeInfo;
            xml::node *child;

            for (child = n->first_child(); child != 0; 
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }

                  string e_name = str_transcode(child->get_name());
                  if (e_name == "ipnetwork:roid")
                  {
                     ipRangeInfo.set_roid(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:organization")
                  {
                     ipRangeInfo.set_organization(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:allocType")
                  {
                     ipRangeInfo.set_allocType(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:contact")
                  {
                     ipRangeInfo.insert_contact(child->attr("type"), str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:asn")
                  {
                     int asn = atoi(str_transcode(child->get_text()));
                     ipRangeInfo.set_asn(asn);
                  }
                  else if(e_name == "ipnetwork:reverseDNS")
                  {
                     ipRangeInfo.insert_reverseDns(fill_reverseDns(child));
                  }
                  else if(e_name == "ipnetwork:parentNetwork")
                  {
                     IpNetworkInfoResponse::Network parentNetwork;
                     xml::node *blockChild;

                     for (blockChild = child->first_child(); blockChild != 0; 
                        blockChild = blockChild->get_next_sibling()) {
                           if (blockChild->get_type() != xml::node_element) {
                              continue;
                           }

                           string block_e_name = str_transcode(blockChild->get_name());
                           if (block_e_name == "ipnetwork:ipRange")
                           {
                              parentNetwork.set_ipRange(fill_ipRange(blockChild));
                           }
                           else if(block_e_name == "ipnetwork:roid")
                           {
                              parentNetwork.set_roid(str_transcode(blockChild->get_text()));
                           }
                     }

                     ipRangeInfo.set_parentNetwork(parentNetwork);
                  }
                  else if(e_name == "ipnetwork:childNetwork")
                  {
                     IpNetworkInfoResponse::Network childNetwork;
                     xml::node *blockChild;

                     for (blockChild = child->first_child(); blockChild != 0; 
                        blockChild = blockChild->get_next_sibling()) {
                           if (blockChild->get_type() != xml::node_element) {
                              continue;
                           }

                           string block_e_name = str_transcode(blockChild->get_name());
                           if (block_e_name == "ipnetwork:ipRange")
                           {
                              childNetwork.set_ipRange(fill_ipRange(blockChild));
                           }
                           else if(block_e_name == "ipnetwork:roid")
                           {
                              childNetwork.set_roid(str_transcode(blockChild->get_text()));
                           }
                     }

                     ipRangeInfo.insert_childNetwork(childNetwork);
                  }
                  else if(e_name == "ipnetwork:clID")
                  {
                     ipRangeInfo.set_clId(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:crID")
                  {
                     ipRangeInfo.set_crId(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:crDate")
                  {
                     ipRangeInfo.set_crDate(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:exDate")
                  {
                     ipRangeInfo.set_exDate(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:upID")
                  {
                     ipRangeInfo.set_upId(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:upDate")
                  {
                     ipRangeInfo.set_upDate(str_transcode(child->get_text()));
                  }
                  else if(e_name == "ipnetwork:trDate")
                  {
                     ipRangeInfo.set_trDate(str_transcode(child->get_text()));
                  }
            }

            response->insert_ipRangeInfo(ipRangeInfo);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_ipnetwork_info_response(child, response);
         }
      }
   }

   void DomParser::fill_asn_check_response(xml::node *n, AsnCheckResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:chkData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:cd")
         {
            xml::node *child;

            int asn = 0;
            bool available = false;
            string reason = "";
            string reason_lang = "";

            for (child = n->first_child(); child != 0; 
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }

                  string e_name = str_transcode(child->get_name());
                  if (e_name == "asn:number")
                  {
                     if(child->attr("avail") == "1")
                     {
                        available = true;
                     } else {
                        available = false;
                     }

                     asn = atoi(str_transcode(child->get_text()));
                  }
                  else if(e_name == "asn:reason")
                  {
                     if(child->attr("lang").has_char())
                     {
                        reason_lang = child->attr("lang");
                     }

                     reason = str_transcode(child->get_text());
                  }
            }

            response->insert_availability(asn, available, reason, reason_lang);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_asn_check_response(child, response);
         }
      }
   }

   void DomParser::fill_asn_create_response(xml::node *n, AsnCreateResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:creData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:number")
         {
            response->set_asn(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "asn:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_asn_create_response(child, response);
         }
      }
   }

   void DomParser::fill_asn_renew_response(xml::node *n, AsnRenewResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:renData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:number")
         {
            response->set_asn(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "asn:exDate")
         {
            response->set_expDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_asn_renew_response(child, response);
         }
      }
   }

   void DomParser::fill_asn_transfer_response(xml::node *n, AsnTransferResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:trnData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:number")
         {
            response->set_asn(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "asn:trStatus")
         {
            response->set_trStatus(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:reID")
         {
            response->set_reId(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:reDate")
         {
            response->set_reDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:acID")
         {
            response->set_acId(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:acDate")
         {
            response->set_acDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_asn_transfer_response(child, response);
         }
      }
   }

   void DomParser::fill_asn_info_response(xml::node *n, AsnInfoResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response")
         {
            look_children = true;
         }
         else if(elem_name == "result")
         {
            fill_result(n, (Response *)response);
         }
         else if(elem_name == "trID")
         {
            look_children = true;
         }
         else if(elem_name == "clTRID")
         {
            response->set_clTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "svTRID")
         {
            response->set_svTRID(str_transcode(n->get_text()));
         }
         else if(elem_name == "resData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:infData")
         {
            look_children = true;
         }
         else if(elem_name == "asn:number")
         {
            response->set_asn(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "asn:roid")
         {
            response->set_roid(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:organization")
         {
            response->set_organization(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:contact")
         {
            response->insert_contact(n->attr("type"), str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:clID")
         {
            response->set_clId(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:crID")
         {
            response->set_crId(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:crDate")
         {
            response->set_crDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:upID")
         {
            response->set_upId(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:upDate")
         {
            response->set_upDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "asn:trDate")
         {
            response->set_trDate(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_asn_info_response(child, response);
         }
      }
   }

   void DomParser::fill_poll_response(xml::node *n, PollResponse *poll_response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) 
      {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "epp" || elem_name == "response") 
         {
            look_children = true;
         }
         else if (elem_name == "result") 
         {
            fill_result(n, (Response *)poll_response);
         }
         else if (elem_name == "trID") 
         {
            look_children = true;
         }
         else if (elem_name == "clTRID") 
         {
            poll_response->set_clTRID(str_transcode(n->get_text()));
         }
         else if (elem_name == "svTRID")
         {
            poll_response->set_svTRID(str_transcode(n->get_text()));
         } 
         else if (elem_name == "msgQ") 
         {
            look_children = true;

            if(n->attr("count").has_char()) 
            {
               poll_response->set_count(n->attr("count"));
            }
            if(n->attr("id").has_char()) 
            {
               poll_response->set_id(n->attr("id"));
            }
         } 
         else if (elem_name == "qDate") 
         {
            poll_response->set_qDate(str_transcode(n->get_text()));
         }
         else if (elem_name == "msg") 
         {

            // Get the attribute lang
            if(n->attr("lang").has_char()) 
            {
               poll_response->set_lang(n->attr("lang"));
            }

            // Run thru the child elements, getting the attributes and 
            // text content
            xml::node *child;
            int child_count = 0;
            collection::string_map < PollResponse::MsgContent > content;
            for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
            {
               if (child->get_type() == xml::node_element) 
               {
                  child_count++;
                  PollResponse::MsgContent msg_content;
                  string child_name = str_transcode(child->get_name());
                  string child_text_content = str_transcode(child->get_text());
                  msg_content.value = child_text_content;
                  msg_content.attributes = child->attrs();
                  content[child_name] = msg_content;
               }
            }
            poll_response->set_content(content);

            // If there were no child elements, get text content
            if (child_count == 0) 
            {
               string msg_text_content = str_transcode(n->get_text());
               if (msg_text_content.has_char()) 
               {
                  poll_response->set_text(msg_text_content);
               }
            }

         } 
         else if (elem_name == "resData")
         { // resDatas
            look_children = true;
         }
         else if (elem_name == "domain:panData") 
         {
            gen::scoped_ptr < PanDataResponse > response = new PanDataResponse();
            fill_domain_pandata_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), DOMAIN_PANDATA);
         } 
         else if (elem_name == "contact:panData")
         {
            gen::scoped_ptr<PanDataResponse> response = new PanDataResponse();
            fill_contact_pandata_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), CONTACT_PANDATA);
         }
         else if (elem_name == "contact:chkData")
         {
            gen::scoped_ptr<ContactCheckResponse> response = new ContactCheckResponse();
            fill_contact_check_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), CONTACT_CHECK);
         }
         else if (elem_name == "contact:infData")
         {
            gen::scoped_ptr<ContactInfoResponse> response =  new ContactInfoResponse();
            fill_contact_info_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), CONTACT_INFO);      
         }
         else if (elem_name == "contact:trnData")
         {
            gen::scoped_ptr<ContactTransferResponse> response = new ContactTransferResponse();
            fill_contact_transfer_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), CONTACT_TRANSFER);
         }
         else if (elem_name == "contact:creData")
         {
            gen::scoped_ptr<ContactCreateResponse> response = new ContactCreateResponse();
            fill_contact_create_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), CONTACT_CREATE);
         }
         else if (elem_name == "domain:chkData")
         {
            gen::scoped_ptr<DomainCheckResponse> response = new DomainCheckResponse();
            fill_domain_check_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), DOMAIN_CHECK);
         }
         else if (elem_name == "domain:infData")
         {
            gen::scoped_ptr<DomainInfoResponse> response = new DomainInfoResponse(get_app());
            fill_domain_info_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), DOMAIN_INFO);
         }
         else if (elem_name == "domain:trnData")
         {
            gen::scoped_ptr<DomainTransferResponse> response = new DomainTransferResponse();
            fill_domain_transfer_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), DOMAIN_TRANSFER);
         }
         else if (elem_name == "domain:creData")
         {
            gen::scoped_ptr<DomainCreateResponse> response = new DomainCreateResponse();
            fill_domain_create_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), DOMAIN_CREATE);
         }
         else if (elem_name == "domain:renData")
         {
            gen::scoped_ptr<DomainRenewResponse> response = new DomainRenewResponse();
            fill_domain_renew_response(n, response.get_p());
            poll_response->set_response((Response *) response.detach(), DOMAIN_RENEW);

         }
         else if (elem_name == "extension")
         {  // extensions
            look_children = true;
         }
         else if (elem_name == "brorg:panData")
         {
            if (poll_response->get_response_type() == CONTACT_PANDATA) {
               PanDataResponse *parent = (PanDataResponse *) poll_response->get_response();
               gen::scoped_ptr<BrOrgPanDataResponse> extension_response = new BrOrgPanDataResponse();
               extension_response->copy_parent_data(*parent);
               fill_brorg_pandata_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  BR_ORG_PANDATA);
            }
         }
         else if (elem_name == "brdomain:panData")
         {
            if (poll_response->get_response_type() == DOMAIN_PANDATA) {
               PanDataResponse *parent = (PanDataResponse *) poll_response->get_response();
               gen::scoped_ptr<BrDomainPanDataResponse> extension_response(new BrDomainPanDataResponse());
               extension_response->copy_parent_data(*parent);
               fill_brdomain_pandata_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(),
                  BR_DOMAIN_PANDATA);
            }
         } 
         else if (elem_name == "brorg:infData")
         {
            if (poll_response->get_response_type() == CONTACT_INFO) {
               ContactInfoResponse *parent = (ContactInfoResponse *) poll_response->get_response();
               gen::scoped_ptr<BrOrgInfoResponse> extension_response = new BrOrgInfoResponse();
               extension_response->copy_parent_data(*parent);
               fill_brorg_info_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(),
                  BR_ORG_INFO);
            }
         }
         else if (elem_name == "brdomain:chkData")
         {
            if (poll_response->get_response_type() == DOMAIN_CHECK) {
               DomainCheckResponse *parent = (DomainCheckResponse *) poll_response->get_response();
               gen::scoped_ptr<BrDomainCheckResponse> extension_response = new BrDomainCheckResponse();
               extension_response->copy_parent_data(*parent);
               fill_brdomain_check_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(),
                  BR_DOMAIN_CHECK);
            }
         }
         else if (elem_name == "brdomain:infData")
         {
            if (poll_response->get_response_type() == DOMAIN_INFO) {
               DomainInfoResponse *parent = (DomainInfoResponse *) poll_response->get_response();
               gen::scoped_ptr<BrDomainInfoResponse> extension_response = new BrDomainInfoResponse();
               extension_response->copy_parent_data(*parent);
               fill_brdomain_info_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(),
                  BR_DOMAIN_INFO);
            }
         }
         else if (elem_name == "brdomain:creData")
         {
            if (poll_response->get_response_type() == DOMAIN_CREATE) {
               DomainCreateResponse *parent = (DomainCreateResponse *) poll_response->get_response();
               gen::scoped_ptr<BrDomainCreateResponse> extension_response = new BrDomainCreateResponse();
               extension_response->copy_parent_data(*parent);
               fill_brdomain_create_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(),
                  BR_DOMAIN_CREATE);
            }
         }
         else if (elem_name == "brdomain:renData")
         {
            if (poll_response->get_response_type() == DOMAIN_RENEW) {
               DomainRenewResponse *parent = (DomainRenewResponse *) poll_response->get_response();
               gen::scoped_ptr<BrDomainRenewResponse> extension_response = new BrDomainRenewResponse();
               extension_response->copy_parent_data(*parent);
               fill_brdomain_renew_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(),
                  BR_DOMAIN_RENEW);
            }
         }
         else if (elem_name == "brdomain:updData")
         {
            if (poll_response->get_response_type() == DOMAIN_UPDATE) {
               gen::scoped_ptr<BrDomainUpdateResponse> extension_response = new BrDomainUpdateResponse();
               fill_brdomain_update_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  BR_DOMAIN_UPDATE);
            }
         }
         else if (elem_name == "ipnetwork:create")
         {
            if (poll_response->get_response_type() == IP_NETWORK_CREATE) {
               gen::scoped_ptr<IpNetworkCreateResponse> extension_response = new IpNetworkCreateResponse();
               fill_ipnetwork_create_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  IP_NETWORK_CREATE);
            }
         }
         else if (elem_name == "ipnetwork:delete")
         {
            if (poll_response->get_response_type() == IP_NETWORK_DELETE) {
               gen::scoped_ptr<Response> extension_response = new Response();
               fill_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  IP_NETWORK_DELETE);
            }
         }
         else if (elem_name == "ipnetwork:renew")
         {
            if (poll_response->get_response_type() == IP_NETWORK_RENEW) {
               gen::scoped_ptr<IpNetworkRenewResponse> extension_response = new IpNetworkRenewResponse();
               fill_ipnetwork_renew_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  IP_NETWORK_RENEW);
            }
         }
         else if (elem_name == "ipnetwork:transfer")
         {
            if (poll_response->get_response_type() == IP_NETWORK_TRANSFER) {
               gen::scoped_ptr<IpNetworkTransferResponse> extension_response = new IpNetworkTransferResponse();
               fill_ipnetwork_transfer_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  IP_NETWORK_TRANSFER);
            }
         }
         else if (elem_name == "ipnetwork:check")
         {
            if (poll_response->get_response_type() == IP_NETWORK_CHECK) {
               gen::scoped_ptr<IpNetworkCheckResponse> extension_response = new IpNetworkCheckResponse();
               fill_ipnetwork_check_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  IP_NETWORK_CHECK);
            }
         }
         else if (elem_name == "ipnetwork:info")
         {
            if (poll_response->get_response_type() == IP_NETWORK_INFO) {
               gen::scoped_ptr<IpNetworkInfoResponse> extension_response = new IpNetworkInfoResponse();
               fill_ipnetwork_info_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  IP_NETWORK_INFO);
            }
         }
         else if (elem_name == "asn:create")
         {
            if (poll_response->get_response_type() == ASN_CREATE) {
               gen::scoped_ptr<AsnCreateResponse> extension_response = new AsnCreateResponse();
               fill_asn_create_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  ASN_CREATE);
            }
         }
         else if (elem_name == "asn:delete")
         {
            if (poll_response->get_response_type() == ASN_DELETE) {
               gen::scoped_ptr<Response> extension_response = new Response();
               fill_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  ASN_DELETE);
            }
         }
         else if (elem_name == "asn:renew")
         {
            if (poll_response->get_response_type() == ASN_RENEW) {
               gen::scoped_ptr<AsnRenewResponse> extension_response = new AsnRenewResponse();
               fill_asn_renew_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  ASN_RENEW);
            }
         }
         else if (elem_name == "asn:transfer")
         {
            if (poll_response->get_response_type() == ASN_TRANSFER) {
               gen::scoped_ptr<AsnTransferResponse> extension_response = new AsnTransferResponse();
               fill_asn_transfer_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  ASN_TRANSFER);
            }
         }
         else if (elem_name == "asn:check")
         {
            if (poll_response->get_response_type() == ASN_CHECK) {
               gen::scoped_ptr<AsnCheckResponse> extension_response = new AsnCheckResponse();
               fill_asn_check_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  ASN_CHECK);
            }
         }
         else if (elem_name == "asn:info")
         {
            if (poll_response->get_response_type() == ASN_INFO) {
               gen::scoped_ptr<AsnInfoResponse> extension_response = new AsnInfoResponse();
               fill_asn_info_response(n, extension_response.get_p());
               poll_response->set_response((Response *) extension_response.detach(), 
                  ASN_INFO);
            }
         }
      }

      if (look_children) 
      {
         xml::node *child;
         for (child = n->first_child(); child != 0; child = child->get_next_sibling()) 
         {
            fill_poll_response(child, poll_response);
         }
      }
   }

   void DomParser::fill_brorg_info_response(xml::node *n, BrOrgInfoResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) 
      {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brorg:infData") 
         {
            look_children = true;
         }
         else if(elem_name == "brorg:organization")
         {
            response->set_organization(str_transcode(n->get_text()));
         }
         else if(elem_name == "brorg:responsible")
         {
            response->set_responsible(str_transcode(n->get_text()));
         }
         else if(elem_name == "brorg:contact")
         {
            string id = str_transcode(n->get_text());
            string type = n->attr("type");
            response->insert_contact(type, id);
         }
         else if(elem_name == "brorg:proxy")
         {
            response->set_proxy(str_transcode(n->get_text()));
         }
         else if(elem_name == "brorg:domainName")
         {
            response->insert_domainName(str_transcode(n->get_text()));
         }
         else if(elem_name == "brorg:exDate")
         {
            response->set_exDate(str_transcode(n->get_text()));
         }
         else if(elem_name == "brorg:asNumber")
         {
            response->insert_asn(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "brorg:ipRange")
         {
            response->insert_ipRange(fill_brorg_ipRange(n));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brorg_info_response(child, response);
         }
      }
   }

   void DomParser::fill_brorg_check_response(xml::node *n, BrOrgCheckResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brorg:chkData")
         {
            look_children = true;
         }
         else if(elem_name == "brorg:ticketInfo")
         {
            string org;

            struct BrOrgCheckResponse::Unavailability unavail;
            unavail.tkt_num = 0;
            unavail.tkt_fqdn = "";
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  elem_name = str_transcode(child->get_name());
                  if (elem_name == "brorg:organization")
                  {
                     org = str_transcode(child->get_text());
                  }
                  else if(elem_name == "brorg:domainName")
                  {
                     unavail.tkt_fqdn = str_transcode(child->get_text());
                  }
                  else if(elem_name == "brorg:ticketNumber")
                  {
                     unavail.tkt_num = 
                        atoi(str_transcode(child->get_text()));
                  } 
            }

            response->insert_unavailability(org, unavail);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brorg_check_response(child, response);
         }
      }
   }

   void DomParser::fill_brorg_pandata_response(xml::node *n, BrOrgPanDataResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brorg:panData")
         {
            look_children = true;
         }
         else if(elem_name == "brorg:organization")
         {
            response->set_organization(str_transcode(n->get_text()));
         }
         else if(elem_name == "brorg:reason")
         {

            // Get the lang attribute
            if(n->attr("lang").has_char())
            {
               response->set_reason_lang(n->attr("lang"));
            }

            response->set_reason(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brorg_pandata_response(child, response);
         }
      }
   }

   void DomParser::fill_brorg_create_response(xml::node *n, BrOrgCreateResponse *response)
   {
      bool look_children = false;

      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brorg:creData")
         {
            look_children = true;
         }
         else if(elem_name == "brorg:organization")
         {
            response->set_organization(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brorg_create_response(child, response);
         }
      }
   }
   void DomParser::fill_brdomain_check_response(xml::node *n, BrDomainCheckResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brdomain:chkData")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:cd")
         {
            string domain;

            // attributes
            struct BrDomainCheckResponse::Unavailability unavail;
            unavail.hasConcurrent = false;
            unavail.inReleaseProcess = false;
            if(n->attr("hasConcurrent") == "1")
            {
               unavail.hasConcurrent = true;
            }
            if(n->attr("inReleaseProcess") == "1")
            {
               unavail.inReleaseProcess = true;
            }

            unavail.organization = "";
            unavail.equivalentName = "";
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  elem_name = str_transcode(child->get_name());
                  if (elem_name == "brdomain:name")
                  {
                     domain = str_transcode(child->get_text());
                  }
                  else if(elem_name == "brdomain:organization")
                  {
                     unavail.organization = str_transcode(child->get_text());
                  }
                  else if(elem_name == "brdomain:equivalentName")
                  {
                     unavail.equivalentName = str_transcode(child->get_text());
                  }
                  else if(elem_name == "brdomain:ticketNumber")
                  {
                     unavail.tickets.add(atoi(str_transcode(
                        child->get_text())));
                  }
            }

            response->insert_unavailability(domain, unavail);
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brdomain_check_response(child, response);
         }
      }
   }

   void DomParser::fill_brdomain_info_response(xml::node *n, BrDomainInfoResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brdomain:infData")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:ticketNumber")
         {
            response->set_ticketNumber(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "brdomain:organization")
         {
            response->set_organization(str_transcode(n->get_text()));
         }
         else if(elem_name == "brdomain:releaseProcessFlags")
         {

            struct ReleaseProcessFlags rpf;
            rpf.flag1 = 0;
            rpf.flag2 = 0;
            rpf.flag3 = 0;

            if(n->attr("flag1") == "1")
            {
               rpf.flag1 = 1;
            }
            if(n->attr("flag2") == "1")
            {
               rpf.flag2 = 1;
            }
            if(n->attr("flag3") == "1")
            {
               rpf.flag3 = 1;
            }
            response->set_releaseProcessFlags(rpf);

         }
         else if(elem_name == "brdomain:pending")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:doc")
         {
            struct PendingDoc pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:doc child elements
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string curr_name = str_transcode(child->get_name());
                  if (curr_name == "brdomain:docType")
                  {
                     pend.docType = str_transcode(child->get_text());
                  }
                  else if(curr_name == "brdomain:limit")
                  {
                     pend.limit = str_transcode(child->get_text());
                  }
                  else if(curr_name == "brdomain:description")
                  {
                     string_to_string_map description_attributes;
                     pend.description_lang = child->attr("lang");
                     pend.description = str_transcode(child->get_text());
                  }
            }

            response->insert_doc_pending(pend);

         }
         else if(elem_name == "brdomain:dns")
         {
            struct PendingDns pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:dns child elements
            pend.hostName = n->get_child_text("brdomain:hostName");
            pend.limit    = n->get_child_text("brdomain:limit");

            response->insert_dns_pending(pend);

         }
         else if(elem_name == "brdomain:releaseProc")
         {

            struct PendingReleaseProc pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:releaseProc child element
            pend.limit = n->get_child_text("brdomain:limit");

            response->set_rel_pending(pend);

         }
         else if(elem_name == "brdomain:ticketNumberConc")
         {

            int tkt = atoi(str_transcode(n->get_text()));
            response->insert_concurrent_ticket(tkt);

         }
         else if(elem_name == "brdomain:publicationStatus")
         {
            // attribute
            response->set_publication_flag(n->attr("publicationFlag"));
            look_children = true;

         }
         else if(elem_name == "brdomain:onHoldReason")
         {

            response->insert_onhold_reason(str_transcode(n->get_text()));

         }
         else if(elem_name == "brdomain:autoRenew")
         {
            response->set_active(atoi(n->attr("active")));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brdomain_info_response(child, response);
         }
      }
   }

   void DomParser::fill_brdomain_create_response(xml::node *n, BrDomainCreateResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brdomain:creData")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:ticketNumber")
         {
            response->set_ticketNumber(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "brdomain:pending")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:doc")
         {
            struct PendingDoc pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:doc child elements
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string curr_name = str_transcode(child->get_name());
                  if (curr_name == "brdomain:docType")
                  {
                     pend.docType = str_transcode(child->get_text());
                  }
                  else if(curr_name == "brdomain:limit")
                  {
                     pend.limit = str_transcode(child->get_text());
                  }
                  else if(curr_name == "brdomain:description")
                  {
                     string_to_string_map description_attributes;
                     pend.description_lang = child->attr("lang");
                     pend.description = str_transcode(child->get_text());
                  }
            }

            response->insert_doc_pending(pend);

         }
         else if(elem_name == "brdomain:dns")
         {
            struct PendingDns pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:dns child elements
            pend.hostName = n->get_child_text("brdomain:hostName");
            pend.limit    = n->get_child_text("brdomain:limit");

            response->insert_dns_pending(pend);

         }
         else if(elem_name == "brdomain:releaseProc")
         {

            struct PendingReleaseProc pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:releaseProc child element
            pend.limit = n->get_child_text("brdomain:limit");

            response->set_rel_pending(pend);

         }
         else if(elem_name == "brdomain:ticketNumberConc")
         {

            int tkt = atoi(str_transcode(n->get_text()));
            response->insert_concurrent_ticket(tkt);

         } 
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brdomain_create_response(child, response);
         }
      }
   }

   void DomParser::fill_brdomain_renew_response(xml::node *n, BrDomainRenewResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brdomain:renData")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:publicationStatus")
         {
            // attribute
            response->set_publication_flag(n->attr("publicationFlag"));
            look_children = true;
         }
         else if(elem_name == "brdomain:onHoldReason")
         {
            response->insert_onhold_reason(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brdomain_renew_response(child, response);
         }
      }
   }

   void DomParser::fill_brdomain_update_response(xml::node *n, BrDomainUpdateResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brdomain:updData")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:ticketNumber")
         {
            response->set_ticketNumber(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "brdomain:pending")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:doc")
         {
            struct PendingDoc pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:doc child elements
            xml::node *child;
            for (child = n->first_child(); child != 0;
               child = child->get_next_sibling()) {
                  if (child->get_type() != xml::node_element) {
                     continue;
                  }
                  string curr_name = str_transcode(child->get_name());
                  if (curr_name == "brdomain:docType")
                  {
                     pend.docType = str_transcode(child->get_text());
                  }
                  else if(curr_name == "brdomain:limit")
                  {
                     pend.limit = str_transcode(child->get_text());
                  }
                  else if(curr_name == "brdomain:description")
                  {
                     string_to_string_map description_attributes;
                     pend.description_lang = child->attr("lang");
                     pend.description = str_transcode(child->get_text());
                  }
            }

            response->insert_doc_pending(pend);

         }
         else if(elem_name == "brdomain:dns")
         {
            struct PendingDns pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:dns child elements
            pend.hostName = n->get_child_text("brdomain:hostName");
            pend.limit    = n->get_child_text("brdomain:limit");

            response->insert_dns_pending(pend);

         }
         else if(elem_name == "brdomain:releaseProc")
         {

            struct PendingReleaseProc pend;

            // attribute
            pend.status = n->attr("status");

            // brdomain:releaseProc child element
            pend.limit = n->get_child_text("brdomain:limit");

            response->set_rel_pending(pend);

         }
         else if(elem_name == "brdomain:hostStatus")
         {
            struct HostStatus hs;
            hs.host = n->get_child_text("brdomain:hostName");
            hs.status =  n->get_child_text("brdomain:dnsAnswer");
            response->insert_host_status(hs);

         }
         else if(elem_name == "brdomain:publicationStatus")
         {
            // attribute
            response->set_publication_flag(n->attr("publicationFlag"));
            look_children = true;

         }
         else if(elem_name == "brdomain:onHoldReason")
         {

            response->insert_onhold_reason(str_transcode(n->get_text()));

         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brdomain_update_response(child, response);
         }
      }

   }

   void DomParser::fill_brdomain_pandata_response(xml::node *n, BrDomainPanDataResponse *response)
   {
      bool look_children = false;
      if (n->get_type() == xml::node_element) {
         string elem_name = str_transcode(n->get_name());
         if (elem_name == "brdomain:panData")
         {
            look_children = true;
         }
         else if(elem_name == "brdomain:ticketNumber")
         {
            response->set_ticketNumber(atoi(str_transcode(n->get_text())));
         }
         else if(elem_name == "brdomain:reason")
         {
            // Get the lang attribute
            if(n->attr("lang").has_char())
            {
               response->set_reason_lang(n->attr("lang"));
            }

            response->set_reason(str_transcode(n->get_text()));
         }
      }

      if (look_children) {
         xml::node *child;
         for (child = n->first_child(); child != 0;
            child = child->get_next_sibling()) {
               fill_brdomain_pandata_response(child, response);
         }
      }
   }

   string DomParser::get_contacts_xml(const char * pszEnclose, const char * pszTag, string_to_string_map & contacts, bool bEmptyIfNoElements)
   {

      if(bEmptyIfNoElements && contacts.is_empty())
         return "";

      string strEnclose(pszEnclose);
      string str;

      str += "<" + strEnclose + ">";
      str += get_contacts_xml(pszTag, contacts, bEmptyIfNoElements);
      str += "</" + strEnclose + ">";

      return str;

   }

   string DomParser::get_contacts_xml(const char * pszTag, string_to_string_map & contacts, bool bEmptyIfNoElements)
   {

      if(bEmptyIfNoElements && contacts.is_empty())
         return "";

      string str;
      string strTag(pszTag);

      for(POSITION pos = contacts.get_start_position(); pos != NULL; ) 
      {
         string strKey;
         string strValue;
         contacts.get_next_assoc(pos, strKey, strValue);
         str += "<";
         str += strTag;
         str += " type='" + System.xml().special_chars(strKey) + "'>" + System.xml().special_chars(strValue);
         str += "</";
         str += strTag;
         str += ">";
      }

      return str;

   }


} // namespace libepp

