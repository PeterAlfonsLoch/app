#pragma once

namespace netnode
{
   class database;
} // namespace netnode


namespace database
{

   class CLASS_DECL_CA2_CUBE string_integer :
      virtual public ptr
   {    
   public:
      string_integer(netnode::database * pdatabase = NULL, const char * pszTable = NULL);

      using ptr::get;
      bool get(const char * psz, __int64 & n);
      void set(const char * psz, __int64 n);

      string m_strTable;
      netnode::database * m_pdatabase;
   };

} // namespace database
