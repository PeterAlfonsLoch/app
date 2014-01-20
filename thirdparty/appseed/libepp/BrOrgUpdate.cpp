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
/* $Id: BrOrgUpdate.cpp 1001 2009-01-23 09:39:13Z rafael $ */
#include "StdAfx.h"


namespace libepp
{

   void BrOrgUpdate::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      ContactUpdate::set_xml_template(pparser, xml_template);

      string_to_string_map to_parse;

      to_parse["organization"] = su.esc_xml_markup(get_command()->get_organization());

      string_to_string_map contact_list;

      to_parse["brorg_add"] = pparser->get_contacts_xml("brorg:add", "brorg:contact", get_command()->get_contact_list_add());

      to_parse["brorg_rem"] = pparser->get_contacts_xml("brorg:rem", "brorg:contact", get_command()->get_contact_list_rem());

      bool printChanges = false;

      string changes = "<brorg:chg>";

      bool responsible_f = get_command()->get_responsible_f();
      if (responsible_f == true) 
      {
         printChanges = true;

         string responsible = get_command()->get_responsible();
         changes += "<brorg:responsible>" + su.esc_xml_markup(responsible) + "</brorg:responsible>";
      }

      string exDate = get_command()->get_exDate();
      if (exDate != "") 
      {
         printChanges = true;
         changes += "<brorg:exDate>" + su.esc_xml_markup(exDate) + "</brorg:exDate>";
      }

      changes += "</brorg:chg>";
      if (printChanges == true) 
      {
         to_parse["brorg_chg"] = changes;
      }
      else 
      {
         to_parse["brorg_chg"] = "";
      }

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
