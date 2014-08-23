#pragma once


namespace xml
{

   inline disp_option::disp_option(sp(::aura::application) pbaseapp)
   {
      newline = true;
      reference_value = true;
      m_pentities = &pbaseapp->m_paurasystem->m_pxml->m_entities;
      tab_base = 0;
      value_quotation_mark = '"';
   }


} // namespace xml


