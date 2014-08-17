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
/* $Id: AsnUpdate.cpp 986 2008-12-30 12:32:38Z eduardo $ */

#include "StdAfx.h"

namespace libepp 
{

   void AsnUpdate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      Action::set_xml_template_common(xml_template);
      string_to_string_map to_parse;

      // ASN
      to_parse["asn"] = gen::str::itoa(get_command()->get_asn());

      // asn:chg (Organization)
      to_parse["asn_chg"] = "";
      if (get_command()->get_organization() != "") {
         to_parse["asn_chg"] =
            "<asn:chg>"
            "<asn:organization>" +
            su.esc_xml_markup(get_command()->get_organization()) +
            "</asn:organization>"
            "</asn:chg>";
      }

      // asn:add (Contacts)
      to_parse["asn_add"] = pparser->get_contacts_xml("asn:add", "asn:contact", get_command()->get_contacts_add());

      // asn:rem (Contacts)
      to_parse["asn_rem"] = pparser->get_contacts_xml("asn:rem", "asn:contact", get_command()->get_contacts_rem());

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
