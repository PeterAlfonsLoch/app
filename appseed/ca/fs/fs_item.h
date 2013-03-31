#pragma once


namespace fs
{


   class list_item;


   class CLASS_DECL_ca item :
      virtual public ::ca::ca
   {
   public:


      string                     m_strPath;
      flags < e_flag >           m_flags;


      item();
      item(const item & item);
      //item(const list_item & listitem);


   };


} // namespace fs