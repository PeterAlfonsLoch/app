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
/* $Id: DomainCreate.cpp 1061 2010-07-06 20:33:42Z eduardo $ */
#include "StdAfx.h"


namespace libepp 
{

   void DomainCreate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      Action::set_xml_template_common(xml_template);
      string_to_string_map to_parse;

      //name
      to_parse["name"] = su.esc_xml_markup(get_command()->get_name());

      //period
      RegistrationPeriod period = get_command()->get_period();
      to_parse["period"] = "";
      if (period.time > 0) 
      {
         to_parse["period"] = "<domain:period unit='" + su.esc_xml_markup(period.unit) + "'>" + gen::str::itoa(period.time) + "</domain:period>";
      }

      //nameservers
      NameServerArray nss = get_command()->get_nameservers();
      to_parse["nameservers"] = "";
      if(nss.has_elements()) 
      {
         to_parse["nameservers"] = "<domain:ns>";
         for(int i = 0; i < nss.get_count(); i++)
         {
            NameServer & server = nss[i];
            to_parse["nameservers"] += "<domain:hostAttr>";
            to_parse["nameservers"] += "<domain:hostName>" + su.esc_xml_markup(server.name) + "</domain:hostName>";
            for(int j = 0; j < server.ips.get_count(); j++) 
            {
               NSIPAddr & addr = server.ips[j];
               to_parse["nameservers"] += "<domain:hostAddr";
               if(addr.version != "") 
               {
                  to_parse["nameservers"] += " ip='" + su.esc_xml_markup(addr.version) + "'";
               }
               to_parse["nameservers"] += ">" + su.esc_xml_markup(addr.addr) + "</domain:hostAddr>";
            }
            to_parse["nameservers"] += "</domain:hostAttr>";
         }

         to_parse["nameservers"] += "</domain:ns>";
      }

      //registrant
      to_parse["registrant"] = "";
      if (get_command()->get_registrant() != "") 
      {
         to_parse["registrant"] = "<domain:registrant>" + su.esc_xml_markup(get_command()->get_registrant()) + "</domain:registrant>";
      }

      //other contacts
      to_parse["other_contacts"] = pparser->get_contacts_xml("domain:contact", get_command()->get_contacts());

      //auth info
      AuthInfo authInfo;
      authInfo = get_command()->get_authInfo();
      string auth_info_str;
      auth_info_str = "<domain:authInfo><domain:pw>" + su.esc_xml_markup(authInfo.get_pw()) + "</domain:pw></domain:authInfo>";
      to_parse["auth_info"] = auth_info_str;

      to_parse["ext_begin"] = "";
      to_parse["ext_end"] = "";
      to_parse["ds_ext"] = "";

      /////////////////////////////////////////////////////////////////////////////
      // secDNS Extension Mapping - RFC 4310/5910
      if (get_command()->has_extension()) 
      {
         to_parse["ext_begin"] = "<extension>";
         to_parse["ext_end"] = "</extension>";

         if (get_command()->has_secdns_extension())
         {
            ds_info_array ds_info_list = get_command()->get_dsInfo();
            collection::list < KeyData > dnskey_data_list = get_command()->get_keyDataList();

            if (get_command()->get_secDnsVersion() == "1.0") 
            {
               to_parse["ds_ext"] +=  "<secDNS:create xmlns:secDNS=\"urn:ietf:params:xml:ns:secDNS-1.0\" xsi:schemaLocation=\"urn:ietf:params:xml:ns:secDNS-1.0 secDNS-1.0.xsd\">";

               
               for(int i = 0; i < ds_info_list.get_count(); i++) 
               {
                  DSInfo & info = ds_info_list[i];
                  to_parse["ds_ext"] += info.get_xml_format(get_command()->get_secDnsVersion());
               }

               to_parse["ds_ext"] += "</secDNS:create>";

            }
            else if (get_command()->get_secDnsVersion() == "1.1") 
            {
               to_parse["ds_ext"] +=  "<secDNS:create xmlns:secDNS=\"urn:ietf:params:xml:ns:secDNS-1.1\" xsi:schemaLocation=\"urn:ietf:params:xml:ns:secDNS-1.1 secDNS-1.1.xsd\">";

               if (get_command()->get_max_sig_life() > 0) 
               {
                  to_parse["ds_ext"] += "<secDNS:maxSigLife>" + gen::str::itoa(get_command()->get_max_sig_life()) + "</secDNS:maxSigLife>";
               }

               // prioritizes KeyData over DSInfo
               if (!dnskey_data_list.is_empty()) 
               {
                  for(POSITION pos = dnskey_data_list.get_head_position(); pos != NULL;)
                  {
                     KeyData & data = dnskey_data_list.get_next(pos);
                     to_parse["ds_ext"] += data.get_xml_format();
                  }
               } 
               else 
               {
                  for(int i = 0; i < ds_info_list.get_count(); i++) 
                  {
                     DSInfo & info = ds_info_list[i];
                     to_parse["ds_ext"] += info.get_xml_format(get_command()->get_secDnsVersion());
                  }
               }

               to_parse["ds_ext"] += "</secDNS:create>";
            }
         }
      }
      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
