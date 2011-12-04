#pragma once


namespace fs
{


   class CLASS_DECL_ca2 list_item
   {
   public:


      string                           m_strPath;
      string                           m_strName;
      index                            m_iImage;
      index                            m_iIndex;
      index                            m_iArrange;
      flags < e_flag >                 m_flags;


      list_item();
      list_item(const list_item & item);

      static index CompareArrangeByName(list_item & pitema, list_item & itemb);
      index CompareArrangeByName(const list_item & item) const;
      index GetIndex() const;
      bool IsFolder() const;

      list_item & operator = (const list_item & item);

   };


} // namespace fs