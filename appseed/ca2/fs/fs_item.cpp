#include "StdAfx.h"


namespace fs
{


   item::item()
   {
   }

   item::item(const item & item)
   {
      m_strPath         = item.m_strPath;
      m_flags           = item.m_flags;
   }


   item::item(const list_item & listitem)
   {
      m_strPath         = listitem.m_strPath;
      m_flags           = listitem.m_flags;
   }


} // namespace fs
