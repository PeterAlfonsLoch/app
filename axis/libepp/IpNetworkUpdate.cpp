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
/* $Id: IpNetworkUpdate.cpp 1010 2009-03-12 17:50:50Z eduardo $ */
#include "StdAfx.H"


namespace libepp 
{

   void IpNetworkUpdate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      Action::set_xml_template_common(xml_template);
      string_to_string_map to_parse;

      // Roid
      to_parse["roid"] = su.esc_xml_markup(get_command()->get_roid());

      // ipnetwork:chg (Organization and Allocation Type)
      to_parse["ipnetwork_chg"] = "";
      if (get_command()->get_organization() != "" || 
         get_command()->get_allocType() != "") {
            to_parse["ipnetwork_chg"] = "<ipnetwork:chg>";
            if (get_command()->get_organization() != "") {
               to_parse["ipnetwork_chg"] += "<ipnetwork:organization>" +
                  su.esc_xml_markup(get_command()->get_organization()) +
                  "</ipnetwork:organization>";
            }
            if (get_command()->get_allocType() != "") {
               to_parse["ipnetwork_chg"] += "<ipnetwork:allocType>" +
                  su.esc_xml_markup(get_command()->get_allocType()) +
                  "</ipnetwork:allocType>";
            }
            to_parse["ipnetwork_chg"] += "</ipnetwork:chg>";
      }

      // ipnetwork:add (Contacts and Reverse DNS)
      to_parse["ipnetwork_add"] = "";
      comparable_array<ReverseDns> reverseDns_add = get_command()->get_reverseDns_add();
      string_to_string_map contacts_add =
         get_command()->get_contacts_add();
      if(contacts_add.has_elements() || reverseDns_add.has_elements()) 
      {
         to_parse["ipnetwork_add"] = "<ipnetwork:add>";

         to_parse["ipnetwork_add"] += pparser->get_contacts_xml("ipnetwork:contact", contacts_add);

         for (unsigned int i = 0; i < reverseDns_add.get_size(); i++) 
         {
            IpRange ipRange = reverseDns_add[i].ipRange;

            to_parse["ipnetwork_add"] += "<ipnetwork:reverseDNS>";

            if (ipRange.get_version() != "") 
            {
               to_parse["ipnetwork_add"] += "<ipnetwork:ipRange version='" + 
                  su.esc_xml_markup(ipRange.get_version()) + "'>";
            }
            else 
            {
               to_parse["ipnetwork_add"] += "<ipnetwork:ipRange>";
            }

            to_parse["ipnetwork_add"] += "<ipnetwork:startAddress>" + 
               su.esc_xml_markup(ipRange.get_ipBegin()) + "</ipnetwork:startAddress>";
            to_parse["ipnetwork_add"] += "<ipnetwork:endAddress>" + 
               su.esc_xml_markup(ipRange.get_ipEnd()) + "</ipnetwork:endAddress>";
            to_parse["ipnetwork_add"] += "</ipnetwork:ipRange>";

            stringa nameservers = reverseDns_add[i].nameservers;
            int nameserversSize = nameservers.get_size();

            for (int j = 0; j < nameserversSize; j++) 
            {
               to_parse["ipnetwork_add"] += "<ipnetwork:hostName>" + 
                  su.esc_xml_markup(nameservers[j]) + "</ipnetwork:hostName>";
            }

            to_parse["ipnetwork_add"] += "</ipnetwork:reverseDNS>";
         }

         to_parse["ipnetwork_add"] += "</ipnetwork:add>";
      }

      // ipnetwork:rem (Contacts and Reverse DNS)
      to_parse["ipnetwork_rem"] = "";
      comparable_array<ReverseDns> reverseDns_rem = get_command()->get_reverseDns_rem();
      string_to_string_map contacts_rem =
         get_command()->get_contacts_rem();
      if(contacts_rem.has_elements() || reverseDns_rem.has_elements()) 
      {
         to_parse["ipnetwork_rem"] = "<ipnetwork:rem>";

         to_parse["ipnetwork_rem"] += pparser->get_contacts_xml("ipnetwork:contact", contacts_rem);

         for (unsigned int i = 0; i < reverseDns_rem.get_size(); i++) 
         {
            IpRange ipRange = reverseDns_rem[i].ipRange;

            to_parse["ipnetwork_rem"] += "<ipnetwork:reverseDNS>";

            if (ipRange.get_version() != "")
            {
               to_parse["ipnetwork_rem"] += "<ipnetwork:ipRange version='" + su.esc_xml_markup(ipRange.get_version()) + "'>";
            } 
            else
            {
               to_parse["ipnetwork_rem"] += "<ipnetwork:ipRange>";
            }

            to_parse["ipnetwork_rem"] += "<ipnetwork:startAddress>" + su.esc_xml_markup(ipRange.get_ipBegin()) + "</ipnetwork:startAddress>";
            to_parse["ipnetwork_rem"] += "<ipnetwork:endAddress>" + su.esc_xml_markup(ipRange.get_ipEnd()) + "</ipnetwork:endAddress>";
            to_parse["ipnetwork_rem"] += "</ipnetwork:ipRange>";

            stringa nameservers = reverseDns_rem[i].nameservers;
            int nameserversSize = nameservers.get_size();

            for (int j = 0; j < nameserversSize; j++) 
            {
               to_parse["ipnetwork_rem"] += "<ipnetwork:hostName>" + su.esc_xml_markup(nameservers[j]) + "</ipnetwork:hostName>";
            }

            to_parse["ipnetwork_rem"] += "</ipnetwork:reverseDNS>";
         }

         to_parse["ipnetwork_rem"] += "</ipnetwork:rem>";
      }

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp

