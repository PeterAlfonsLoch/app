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
/* $Id: DomainUpdate.cpp 1073 2010-07-22 16:48:52Z eduardo $ */

#include "StdAfx.h"

#include "DomainUpdate.H"
#include "StrUtil.H"

namespace libepp
{

   void DomainUpdate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      Action::set_xml_template_common(xml_template);
      string_to_string_map to_parse;

      //name
      to_parse["name"] = su.esc_xml_markup(get_command()->get_name());

      //aux containers and iterators
      NameServerArray ns_cnt;
      string_to_string_map contact_cnt;
      comparable_array<struct DomainUpdateCommand::Status> status_cnt;

      //stuff to add
      ns_cnt = get_command()->get_nameserver_add();
      contact_cnt = get_command()->get_contact_add();
      status_cnt = get_command()->get_status_add();

      to_parse["add"] = "";
      if(ns_cnt.has_elements() || contact_cnt.has_elements() || status_cnt.has_elements())
      {

         to_parse["add"] = "<domain:add>";

         //nameservers to add
         if (ns_cnt.has_elements())
         {
            to_parse["add"] += ns_cnt.get_xml(get_app());
         }

         //contacts to add
         to_parse["add"] += pparser->get_contacts_xml("domain:contact", contact_cnt);

         //status to add
         if (status_cnt.has_elements()) 
         {
            for(int i = 0; i < status_cnt.get_count(); i++) 
            {
               DomainUpdateCommand::Status & status = status_cnt[i];
               to_parse["add"] += "<domain:status s='" + su.esc_xml_markup(status.s) + "' lang='" + su.esc_xml_markup(status.lang) + "'>" + su.esc_xml_markup(status.msg) + "</domain:status>";
            }
         }

         to_parse["add"] += "</domain:add>";
      }

      //stuff to remove
      ns_cnt = get_command()->get_nameserver_rem();
      contact_cnt = get_command()->get_contact_rem();
      status_cnt = get_command()->get_status_rem();

      to_parse["rem"] = "";
      if(ns_cnt.has_elements() || contact_cnt.has_elements() || status_cnt.has_elements()) 
      {

         to_parse["rem"] = "<domain:rem>";

         //nameservers to remove
         if(ns_cnt.has_elements()) 
         {
            to_parse["rem"] += ns_cnt.get_xml(get_app());
         }

         //contacts to remove
         to_parse["rem"] += pparser->get_contacts_xml("domain:contact", contact_cnt);

         //status to remove
         if (status_cnt.has_elements()) 
         {
            for(int i = 0; i < status_cnt.get_count(); i++) 
            {
               DomainUpdateCommand::Status & status = status_cnt[i];
               to_parse["rem"] += "<domain:status s='" + su.esc_xml_markup(status.s) + "'/>";
            }
         }

         to_parse["rem"] += "</domain:rem>";
      }

      //stuff to change
      to_parse["chg"] = "";
      bool registrant_f = get_command()->get_registrant_f();
      AuthInfo authInfo = get_command()->get_authInfo();

      if (registrant_f || authInfo.get_pw_f() || authInfo.get_roid_f()) 
      {
         //registrant
         string registrant_str = su.esc_xml_markup(get_command()->get_registrant());

         if (registrant_f) 
         {
            registrant_str = "<domain:registrant>" + registrant_str + "</domain:registrant>";
         }

         //authInfo
         string auth_info_str = "";

         if (authInfo.get_pw_f()) 
         {
            auth_info_str = "<domain:authInfo>";
            if (authInfo.get_pw() == "\"\"") 
            {
               auth_info_str += "<domain:NULL/>";
            }
            else 
            {
               auth_info_str += "<domain:pw>" + su.esc_xml_markup(authInfo.get_pw()) + "</domain:pw>";
            }
            auth_info_str += "</domain:authInfo>";
         }

         to_parse["chg"] = "<domain:chg>" + registrant_str + auth_info_str + "</domain:chg>";
      }

      to_parse["ext_begin"] = "";
      to_parse["ext_end"] = "";
      to_parse["ds_ext"] = "";

      /////////////////////////////////////////////////////////////////////////////
      // secDNS Extension Mapping - RFC 4310/5910
      if (get_command()->has_extension()) 
      {
         to_parse["ext_begin"] = "<extension>";
         to_parse["ext_end"] = "</extension>";

         // DNSSEC Extension
         if (get_command()->has_secdns_extension())
         {
            ds_info_array ds_add_list = get_command()->get_ds_add();
            ds_info_array ds_rem_list = get_command()->get_ds_rem_1_1();
            uint_array ds_rem_list_1_0 = get_command()->get_ds_rem();
            ds_info_array ds_chg_list = get_command()->get_ds_chg();
            collection::list < KeyData > dnskey_add_list = get_command()->get_dnskey_add();
            collection::list < KeyData > dnskey_rem_list = get_command()->get_dnskey_rem();

            if (get_command()->get_secDnsVersion() == "1.0")
            {
               to_parse["ds_ext"] += "<secDNS:update ";
               if (get_command()->isUrgent()) 
               {
                  to_parse["ds_ext"] += "urgent=\"1\" ";
               }
               to_parse["ds_ext"] += "xmlns:secDNS=\"urn:ietf:params:xml:ns:secDNS-1.0\" xsi:schemaLocation=\"urn:ietf:params:xml:ns:secDNS-1.0 secDNS-1.0.xsd\">";

               if(ds_add_list.has_elements()) 
               {
                  // DS Add List
                  to_parse["ds_ext"] += "<secDNS:add>";
                  for(int i = 0; i < ds_add_list.get_count(); i++) 
                  {
                     to_parse["ds_ext"] += ds_add_list[i].get_xml_format();
                  }
                  to_parse["ds_ext"] += "</secDNS:add>";
               } 
               else if (ds_rem_list_1_0.has_elements()) 
               {
                  // DS Remove list
                  to_parse["ds_ext"] += "<secDNS:rem>";
                  for(int i = 0; i < ds_rem_list_1_0.get_count(); i++) 
                  {
                     to_parse["ds_ext"] += "<secDNS:keyTag>" + gen::str::itoa(ds_rem_list_1_0[i]) + "</secDNS:keyTag>";
                  }
                  to_parse["ds_ext"] += "</secDNS:rem>";
               }
               else if (ds_chg_list.has_elements()) 
               {
                  // DS Change List
                  to_parse["ds_ext"] += "<secDNS:chg>";
                  for(int i = 0; i < ds_chg_list.get_count(); i++) 
                  {
                     to_parse["ds_ext"] += ds_chg_list[i].get_xml_format();
                  }
                  to_parse["ds_ext"] += "</secDNS:chg>";
               }

               to_parse["ds_ext"] += "</secDNS:update>";
            } 
            else if (get_command()->get_secDnsVersion() == "1.1") 
            {
               to_parse["ds_ext"] += "<secDNS:update ";
               if (get_command()->isUrgent()) 
               {
                  to_parse["ds_ext"] += "urgent=\"true\" ";
               }
               to_parse["ds_ext"] += "xmlns:secDNS=\"urn:ietf:params:xml:ns:secDNS-1.1\" xsi:schemaLocation=\"urn:ietf:params:xml:ns:secDNS-1.1 secDNS-1.1.xsd\">";

               // alternative "remove all" option
               if (get_command()->getRemoveAll()) 
               {
                  to_parse["ds_ext"] += "<secDNS:rem><secDNS:all>true</secDNS:all></secDNS:rem>";
               }

               // prioritizes KeyData over DSInfo
               if(dnskey_add_list.has_elements() || (dnskey_rem_list.has_elements() && !get_command()->getRemoveAll())) 
               {
                  if(dnskey_rem_list.has_elements() && !get_command()->getRemoveAll()) 
                  {
                     to_parse["ds_ext"] += "<secDNS:rem>";
                     for(POSITION pos = dnskey_rem_list.get_head_position(); pos != NULL;) 
                     {
                        to_parse["ds_ext"] += dnskey_rem_list.get_next(pos).get_xml_format();
                     }
                     to_parse["ds_ext"] += "</secDNS:rem>";
                  }

                  if(dnskey_add_list.has_elements()) 
                  {
                     to_parse["ds_ext"] += "<secDNS:add>";
                     for(POSITION pos = dnskey_add_list.get_head_position(); pos != NULL; )
                     {
                        to_parse["ds_ext"] += dnskey_add_list.get_next(pos).get_xml_format();
                     }
                     to_parse["ds_ext"] += "</secDNS:add>";
                  }
               }
               else if (ds_add_list.has_elements() || (ds_rem_list.has_elements() && !get_command()->getRemoveAll())) 
               {
                  if(ds_rem_list.has_elements() && !get_command()->getRemoveAll())
                  {
                     to_parse["ds_ext"] += "<secDNS:rem>";
                     for(int i = 0; i < ds_rem_list.get_count(); i++) 
                     {
                        to_parse["ds_ext"] += ds_rem_list[i].get_xml_format(get_command()->get_secDnsVersion());
                     }
                     to_parse["ds_ext"] += "</secDNS:rem>";
                  }

                  if(ds_add_list.has_elements()) 
                  {
                     to_parse["ds_ext"] += "<secDNS:add>";
                     for(int i = 0; i < ds_add_list.get_count(); i++) 
                     {
                        to_parse["ds_ext"] += ds_add_list[i].get_xml_format(get_command()->get_secDnsVersion());
                     }
                     to_parse["ds_ext"] += "</secDNS:add>";
                  }
               }

               if (get_command()->get_max_sig_life() > 0) 
               {
                  to_parse["ds_ext"] += "<secDNS:chg>";
                  to_parse["ds_ext"] += "<secDNS:maxSigLife>" + gen::str::itoa(get_command()->get_max_sig_life()) + "</secDNS:maxSigLife>";
                  to_parse["ds_ext"] += "</secDNS:chg>";
               }

               to_parse["ds_ext"] += "</secDNS:update>";
            }
         }
      }

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
