#include "framework.h"


namespace fs
{


   list_item::list_item()
   {
      m_iIndex = -1;
      m_iArrange = -1;
   }

   list_item::list_item(const list_item & listitem)
   {
      operator = (listitem);
   }

   index list_item::CompareArrangeByName(const list_item & item) const
   {
   /*   if(m_iCsidl >= 0)
      {
         if(item.m_iCsidl >= 0)
         {
            return Shell::GetCSIDLSort(m_iCsidl) - Shell::GetCSIDLSort(item.m_iCsidl);
         }
         else
         {
            return -1;
         }
      }
      else if(item.m_iCsidl >= 0)
      {
         return 1;
      }*/
      if(item.IsFolder())
      {
         if(IsFolder())
         {
            return m_strName.CompareNoCase(item.m_strName);
         }
         else
         {
            return 1;
         }
      }
      else
      {
         if(IsFolder())
         {
            return -1;
         }
         else
         {
            return m_strName.CompareNoCase(item.m_strName);
         }
      }
   }

   index list_item::CompareArrangeByName(list_item & itema, list_item & itemb)
   {
      return itema.CompareArrangeByName(itemb);
   }

   index list_item::GetIndex() const
   {
      return m_iIndex;
   }

   bool list_item::IsFolder() const
   {
      if(m_flags.is_signalized(FlagFolderEx001Calc))
         return m_flags.is_signalized(FlagFolderEx001);
      else
      {
         bool bFolderEx001 = m_flags.is_signalized(FlagFolder) || m_flags.is_signalized(FlagInZip);
         const_cast < list_item * > (this)->m_flags.signalize(FlagFolderEx001Calc);
         if(bFolderEx001)
         {
            const_cast < list_item * > (this)->m_flags.signalize(FlagFolderEx001);
         }
         return m_flags.is_signalized(FlagFolderEx001);
      }
   }

   list_item & list_item::operator = (const list_item & item)
   {

      if(&item == this)
         return *this;

      m_strPath   = item.m_strPath;
      m_strName   = item.m_strName;
      m_iImage    = item.m_iImage;
      m_iIndex    = item.m_iIndex;
      m_iArrange  = item.m_iArrange;
      m_flags     = item.m_flags;

      return *this;

   }


} // namespace fs



template <> 
::fs::item cast < ::fs::item > (::fs::list_item & item)
{
   ::fs::item itemT;
   itemT.m_strPath = item.m_strPath;
   itemT.m_flags = item.m_flags;
   return itemT;
}