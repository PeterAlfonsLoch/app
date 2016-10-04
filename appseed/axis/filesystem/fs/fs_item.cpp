//#include "framework.h"


namespace fs
{


   item::item()
   {

   }


   item::item(const item & item)
   {

      m_filepath        = item.m_filepath;

      m_flags           = item.m_flags;

   }


   item::item(const ::file::path & filepath)
   {
      
      m_filepath        = filepath;

   }

   item::item(const ::file::path & filepath,const cflag < e_flag > & flags)
   {

      m_filepath        = filepath;

      m_flags           = flags;

   }

   
   item::~item()
   {


   }


} // namespace fs
