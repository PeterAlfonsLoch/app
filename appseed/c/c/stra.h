#pragma once


class CLASS_DECL_c stra_dup :
   virtual public simple_array < vsstring >
{
public:

   stra_dup();
   ~stra_dup();



   bool spa_insert(const char * psz);
   void add_tokens(const char * psz, const char * pszSeparator);
   void trim();
   void remove_empty();
   count  remove(const char * psz);
   index  find_ci(const char * psz, index iStart = 0);
   count  add_unique_ci(const char * psz);

   vsstring encode_v16();
   void decode_v16(const char * psz);

};
