#pragma once


class icon_key
{
public:
   icon_key();
   icon_key(const icon_key & key);
   string      m_strPath;
   int32_t         m_iIcon;
   string      m_strExtension;

   operator uint32_t () const
   {
      return m_iIcon;
   }
   bool operator == (const icon_key & key) const;
};


class icon
{
public:
   icon();
   ::visual::icon *         m_hicon;
   int32_t         m_iImage;
};