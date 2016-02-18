#pragma once




namespace fs
{


   class CLASS_DECL_AXIS item :
      virtual public object
   {
   public:


      ::file::path               m_strPath;
      cflag < e_flag >           m_flags;


      item();
      item(const item & item);
      item(const string & strPath);
      item(const string & strPath, const cflag < e_flag > & flags);
      virtual ~item();


   };


} // namespace fs



