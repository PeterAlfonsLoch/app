#include "StdAfx.h"


namespace fs
{


   var item_array::get_var_file() const
   {
      if(get_count() <= 0)
         return gen::g_emptyconst;
      else if(get_count() == 1)
         return element_at(0).m_strPath;
      else
      {
         class var var;
         for(index i = 0; i < get_count(); i++)
         {
            var.stra().add(element_at(i).m_strPath);
         }
         return var;
      }
   }
  
   var item_array::get_var_query() const
   {
      if(get_count() <= 0)
         return gen::g_emptyconst;
      else if(get_count() == 1)
      {
         class var var;
         var["FileManagerItem_flags"] = new flags < e_flag >(element_at(0).m_flags);
         return var;
      }
      else
      {
         class var var;
         for(index i = 0; i < get_count(); i++)
         {
            class var varPropSet;
            varPropSet["FileManagerItem_flags"] = new flags < e_flag > (element_at(i).m_flags);
            var.vara().add(varPropSet);
         }
         return var;
      }
   }


} // namespace fs

