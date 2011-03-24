#include "StdAfx.h"

namespace database
{    

   string_integer::string_integer(netnode::database * pdatabase, const char * pszTable)
   {
      m_strTable = pszTable;
      if(m_strTable.is_empty())
         m_strTable = "string_integer_map";
      m_pdatabase = pdatabase;
      if(m_pdatabase == NULL)
         m_pdatabase = &musicdb();
   }

   bool string_integer::get(const char * stringkey, __int64 & n)
   {
      gprop("smm") = m_strTable;
      gprop("stringkey") = stringkey;
      string sql = eval("SELECT $smm.value FROM $smm WHERE $smm.key = '$stringkey'");
      var result = m_pdatabase->query_item(sql);
      if(!result)
         return false;
      n = (int) result;
      return true;
   }

   void string_integer::set(const char * stringkey, __int64 n)
   {
      gprop("smm") = m_strTable;
      gprop("stringkey") = stringkey;
      gprop("intvalue") = (int) n;
      string sql = eval("REPLACE INTO $smm (`key`, `value`) VALUES ('$stringkey', '$intvalue');");
      m_pdatabase->query(sql);
   }

} // namespace database
