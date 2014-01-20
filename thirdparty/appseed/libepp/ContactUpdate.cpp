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
/* $Id: ContactUpdate.cpp 756 2006-06-09 17:42:34Z koji $ */
#include "StdAfx.h"


namespace libepp 
{

   void ContactUpdate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      Action::set_xml_template_common(xml_template);
      string_to_string_map to_parse;

      to_parse["id"] = su.esc_xml_markup(get_command()->get_common_data().get_id());

      stringa status_list_add = get_command()->get_status_list_add();
      stringa status_list_rem = get_command()->get_status_list_rem();
      if(status_list_add.has_elements())
      {
         to_parse["add"] = "<contact:add>";
         for(int i = 0; i < status_list_add.get_size(); i++)
         {
            to_parse["add"] += "<contact:status s='" + su.esc_xml_markup(status_list_add[i]) + "'/>";
         }
         to_parse["add"] += "</contact:add>";
      }
      else
         to_parse["add"] = "";

      if(status_list_rem.has_elements())
      {
         to_parse["rem"] = "<contact:rem>";
         for(int i = 0; i < status_list_rem.get_size(); i++) 
         {
            to_parse["rem"] += "<contact:status s='" + su.esc_xml_markup(status_list_rem[i]) + "'/>";
         }
         to_parse["rem"] += "</contact:rem>";
      }
      else
         to_parse["rem"] = "";

      to_parse["chg"] = "";

      CommonData::Disclose disclose = get_command()->get_common_data().get_disclose();

      if (!get_command()->get_common_data().get_postal_info().is_empty() ||
         get_command()->get_common_data().get_voice_f() ||
         get_command()->get_common_data().get_fax_f() ||
         get_command()->get_common_data().get_email_f() ||
         get_command()->get_authInfo().get_pw() != "" ||
         disclose.name_int || disclose.name_loc || disclose.org_int ||
         disclose.org_loc || disclose.addr_int || disclose.addr_loc ||
         disclose.voice || disclose.fax || disclose.email) 
      {
         comparable_array<PostalInfo> postal_info = get_command()->get_common_data().get_postal_info();
         string pf_str;
         string org;
         string str1;
         string str2;
         string str3;
         string sp;
         string pc;
         string name;
         for (int i = 0; i < (int) postal_info.get_size(); i++) 
         {
            if (!postal_info[i].get_name_f()) 
            {
               name = "";
            }
            else 
            {
               name = "<contact:name>" + su.esc_xml_markup(postal_info[i].get_name()) + "</contact:name>";
            }

            if (!postal_info[i].get_org_f()) 
            {
               org = "";
            }
            else 
            {
               org = "<contact:org>" + su.esc_xml_markup(postal_info[i].get_org()) + "</contact:org>";
            }

            if (!postal_info[i].get_str1_f()) 
            {
               str1 = "";
            } 
            else 
            {
               str1 = "<contact:street>" + su.esc_xml_markup(postal_info[i].get_str1()) + "</contact:street>";
            }

            if (!postal_info[i].get_str2_f()) 
            {
               str2 = "";
            }
            else 
            {
               str2 = "<contact:street>" + su.esc_xml_markup(postal_info[i].get_str2()) + "</contact:street>";
            }

            if (!postal_info[i].get_str3_f()) 
            {
               str3 = "";
            }
            else 
            {
               str3 = "<contact:street>" + su.esc_xml_markup(postal_info[i].get_str3()) + "</contact:street>";
            }

            if (!postal_info[i].get_sp_f())
            {
               sp = "";
            }
            else 
            {
               sp = "<contact:sp>" + su.esc_xml_markup(postal_info[i].get_sp()) + "</contact:sp>";
            }

            if (!postal_info[i].get_pc_f()) 
            {
               pc = "";
            }
            else 
            {
               pc = "<contact:pc>" + su.esc_xml_markup(postal_info[i].get_pc()) + "</contact:pc>";
            }

            pf_str += "<contact:postalInfo type='" + 
               su.esc_xml_markup(postal_info[i].get_type()) +
               "'>" + name + org + "<contact:addr>" + str1 + str2 + str3 +
               "<contact:city>" + su.esc_xml_markup(postal_info[i].get_city()) +
               "</contact:city>" + sp + pc + "<contact:cc>" +
               su.esc_xml_markup(postal_info[i].get_cc()) + 
               "</contact:cc></contact:addr></contact:postalInfo>";
         }

         CommonData::Phone voice;
         voice = get_command()->get_common_data().get_voice();
         string voice_str("");
         if (get_command()->get_common_data().get_voice_f()) 
         {
            if (strcmp(voice.ext, "") == 0)
               voice_str = "<contact:voice>" + su.esc_xml_markup(voice.number) +
               "</contact:voice>";
            else
               voice_str = "<contact:voice x='" + su.esc_xml_markup(voice.ext) +
               "'>" + su.esc_xml_markup(voice.number) + "</contact:voice>";
         }

         CommonData::Phone fax;
         fax = get_command()->get_common_data().get_fax();
         string fax_str("");
         if (get_command()->get_common_data().get_fax_f()) 
         {
            if (strcmp(fax.ext, "") == 0)
               fax_str = "<contact:fax>" + su.esc_xml_markup(fax.number) + "</contact:fax>";
            else
               fax_str = "<contact:fax x='" + su.esc_xml_markup(fax.ext) + "'>" + su.esc_xml_markup(fax.number) + "</contact:fax>";
         }

         string email;
         if (get_command()->get_common_data().get_email_f()) 
         {
            email = "<contact:email>" + su.esc_xml_markup(get_command()->get_common_data().get_email()) + "</contact:email>";
         }

         AuthInfo authInfo;
         authInfo = get_command()->get_authInfo();
         string auth_info_str = "";
         if (authInfo.get_pw() != "") 
         {
            auth_info_str = "<contact:authInfo>";
            if (strcmp(authInfo.get_roid(), "") == 0) 
            {
               auth_info_str += "<contact:pw>" + su.esc_xml_markup(authInfo.get_pw()) + "</contact:pw>";
            }
            else 
            {
               auth_info_str += "<contact:pw roid='" + su.esc_xml_markup(authInfo.get_roid()) + "'>" + su.esc_xml_markup(authInfo.get_pw()) + "</contact:pw>";
            }
            auth_info_str += "</contact:authInfo>";
         }

         string disclose_total("");
         if (disclose.is_set()) 
         {
            string disclose_str;
            if (disclose.name_int) 
            {
               disclose_str += "<contact:name type =\"int\"/>";
            }
            if (disclose.name_loc) 
            {
               disclose_str += "<contact:name type=\"loc\"/>";
            }
            if (disclose.org_int) 
            {
               disclose_str += "<contact:org type=\"int\"/>";
            }
            if (disclose.org_loc) 
            {
               disclose_str += "<contact:org type=\"loc\"/>";
            }
            if (disclose.addr_int) 
            {
               disclose_str += "<contact:addr type=\"int\"/>";
            }
            if (disclose.addr_loc) 
            {
               disclose_str += "<contact:addr type=\"loc\"/>";
            }
            if (disclose.voice) 
            {
               disclose_str += "<contact:voice/>";
            }
            if (disclose.fax) 
            {
               disclose_str += "<contact:fax/>";
            }
            if (disclose.email) 
            {
               disclose_str += "<contact:email/>";
            }

            disclose_total = "<contact:disclose flag='" +  gen::str::itoa(disclose.flag) + "'>" + disclose_str + "</contact:disclose>";
         }

         to_parse["chg"] = "<contact:chg>" + pf_str +  voice_str + fax_str +  email + auth_info_str + disclose_total + "</contact:chg>";
      }

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
