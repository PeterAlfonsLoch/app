#pragma once


class icon_key
{
public:
   icon_key();
   icon_key(const icon_key & key);
   string      m_strPath;
   int         m_iIcon;
   string      m_strExtension;

   operator DWORD () const
   {
      return m_iIcon;
   }
   bool operator == (const icon_key & key) const;
};


class icon
{
public:
   icon();
   HICON         m_hicon;
   int         m_iImage;
};