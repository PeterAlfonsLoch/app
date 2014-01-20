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
/* $Id: BrOrgCheck.cpp 961 2008-12-11 15:11:25Z eduardo $ */

#include "StdAfx.h"

namespace libepp
{

   void BrOrgCheck::set_xml_template(DomParser * pparser, const char * xml_template)
   {
      StrUtil su(get_app());
      ContactCheck::set_xml_template(pparser, xml_template);

      string_to_string_map to_parse;

      string_to_string_map organization_list = get_command()->get_organization_list();

      for(POSITION pos = organization_list.get_start_position(); pos != NULL;) 
      {
         string strKey;
         string strValue;
         organization_list.get_next_assoc(pos, strKey, strValue);
         to_parse["organization_list"] += "<brorg:cd>";
         to_parse["organization_list"] += "<brorg:id>" + System.xml().special_chars(strKey) + "</brorg:id>";
         to_parse["organization_list"] += "<brorg:organization>" + System.xml().special_chars(strValue) + "</brorg:organization>";
         to_parse["organization_list"] += "</brorg:cd>";      
      }

      _xml = su.parse(_xml, to_parse, "$(", ")$");
   }

} // namespace libepp
