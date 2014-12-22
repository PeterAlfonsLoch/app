#include "framework.h"


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


   item::item(const string & strPath)
   {
      
      m_strPath         = strPath;

   }

   item::item(const string & strPath,const flags < e_flag > & flags)
   {

      m_strPath         = strPath;

      m_flags           = flags;

   }


} // namespace fs
