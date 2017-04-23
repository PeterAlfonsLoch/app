#pragma once


namespace str
{


   CLASS_DECL_AURA void replace_tab(strsize iOffset, string & strParam, int iWidth, array < strsize * > intptra = array < strsize * >(), strsize_array * piaTab = NULL);
   CLASS_DECL_AURA void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab);


} // namespace str
