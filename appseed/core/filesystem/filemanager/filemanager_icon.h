#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE icon_key
   {
   public:


      int32_t     m_iIcon;
      string      m_strPath;
      string      m_strExtension;


      icon_key();
      icon_key(const icon_key & key);


      operator uint32_t () const
      {
         return m_iIcon;
      }

      bool operator == (const icon_key & key) const;


   };


   class CLASS_DECL_CORE icon
   {
   public:

      
      int32_t                 m_iImage;
      ::visual::icon *        m_picon;

      icon();


   };



} // namespace filemanager

















