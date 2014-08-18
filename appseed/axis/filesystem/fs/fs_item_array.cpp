#include "framework.h"


namespace fs
{


   var item_array::get_var_file() const
   {
      if(this->get_count() <= 0)
         return ::var(::var::type_empty);
      else if(this->get_count() == 1)
         return this->element_at(0)->m_strPath;
      else
      {
         class var var;
         for(index i = 0; i < this->get_count(); i++)
         {
            var.stra().add(this->element_at(i)->m_strPath);
         }
         return var;
      }
   }

   var item_array::get_var_query() const
   {
      if(this->get_count() <= 0)
         return ::var(::var::type_empty);
      else if(this->get_count() == 1)
      {
         class var var;
         var["FileManagerItem_flags"] = new flags < e_flag >(this->element_at(0)->m_flags);
         return var;
      }
      else
      {
         class var var;
         for(index i = 0; i < this->get_count(); i++)
         {
            class var varPropSet;
            varPropSet["FileManagerItem_flags"] = new flags < e_flag > (this->element_at(i)->m_flags);
            var.vara().add(varPropSet);
         }
         return var;
      }
   }


} // namespace fs

