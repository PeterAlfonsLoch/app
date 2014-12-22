#pragma once


namespace fs
{


   class CLASS_DECL_AXIS item :
      virtual public element
   {
   public:


      string                     m_strPath;
      flags < e_flag >           m_flags;


      item();
      item(const item & item);
      item(const string & strPath);
      item(const string & strPath, const flags < e_flag > & flags);


   };


} // namespace fs



