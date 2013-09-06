#pragma once


namespace xml
{

   inline disp_option::disp_option(sp(base_application) papp)
   {
      newline = true;
      reference_value = true;
      m_pentities = &papp->m_pcasystem->m_pxml->m_entities;
      tab_base = 0;
      value_quotation_mark = '"';
   }


} // namespace xml


