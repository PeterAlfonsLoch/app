#pragma once


namespace fs
{


   class CLASS_DECL_ca2 list_item :
      virtual public ::ca::ca
   {
   public:


      string                           m_strPath;
      string                           m_strName;
      index                            m_iImage;
      index                            m_iIndex;
      index                            m_iArrange;
      flags < e_flag >                 m_flags;


      list_item(::ca::application * papp);
      list_item(const list_item & item);

      static index CompareArrangeByName(list_item & pitema, list_item & itemb);
      index CompareArrangeByName(const list_item & item) const;
      index GetIndex() const;
      bool IsFolder() const;

      list_item & operator = (const list_item & item);

   };


} // namespace fs


template < class T >
T cast (::fs::list_item & item)
{
   return T(item);
}


template <>
CLASS_DECL_ca2 ::fs::item cast < ::fs::item > (::fs::list_item & item);
