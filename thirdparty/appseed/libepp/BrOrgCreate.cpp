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
/* $Id: BrOrgCreate.cpp 1021 2009-05-11 18:56:22Z eduardo $ */
#include "StdAfx.h"


namespace libepp 
{

   void BrOrgCreate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      ContactCreate::set_xml_template(pparser, xml_template);

      string_to_string_map to_parse;

      to_parse["organization"] = su.esc_xml_markup(get_command()->get_organization());

      string_to_string_map contact_list = get_command()->get_contact_list();
      to_parse["brorg_contact_list"] = pparser->get_contacts_xml("brorg:contact", contact_list);

      to_parse["responsible"] = "";
      bool responsible_f = get_command()->get_responsible_f();
      if (responsible_f == true) 
      {
         string responsible = get_command()->get_responsible();
         to_parse["responsible"] = "<brorg:responsible>" + System.xml().special_chars(responsible) + "</brorg:responsible>";
      }

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
