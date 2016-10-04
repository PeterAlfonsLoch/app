#pragma once


namespace fs
{


   class CLASS_DECL_AXIS item :
      virtual public object
   {
   public:


      ::file::path               m_filepath;
      cflag < e_flag >           m_flags;


      item();
      item(const item & item);
      item(const ::file::path & filepath);
      item(const ::file::path & filepath, const cflag < e_flag > & flags);
      virtual ~item();


   };


} // namespace fs



