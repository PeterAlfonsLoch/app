#pragma once

#ifdef WINDOWSEX
#include <shlobj.h>
#endif


namespace filemanager
{

#ifdef WINDOWSEX
   class CLASS_DECL_CORE Shell
   {
   public:


      static index  GetCSIDLSort(index iCsidl);
      static index  GetCSIDL(LPITEMIDLIST lpiidl);
      static void GetAscendants(LPITEMIDLIST lpiidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
      static void Free(array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);


   };
#endif


   namespace _shell
   {
      enum EFileAttribute
      {
         FileAttributeNormal,
         FileAttributeDirectory,
      };

      enum EFolder
      {
         FolderNone,
         FolderFileSystem,
         FolderZip,
      };

      enum EIcon
      {
         IconNormal,
         IconOpen,


      };

      class ImageKey
      {
      public:

         char *                        m_pszPath;
         char *                        m_pszShellThemePrefix;
         cflag < EFileAttribute >      m_eattribute;
         cflag < EIcon >               m_eicon;
         int32_t                       m_iIcon;
         char *                        m_pszExtension;



         ImageKey();

         operator uint32_t () const
         {
            return m_iIcon;
         }

         bool operator == (const ImageKey & key) const;

         void set_path(const string & strPath, bool bSetExtension = true);
         void set_extension(const string & strPath);

      };

      class ImageKeyStore :
         public ImageKey
      {
      public:

         ImageKeyStore();
         ImageKeyStore(const ImageKey & key);
         ~ImageKeyStore();

      };


      inline bool ImageKey::operator == (const ImageKey & key) const
      {
         return m_eattribute == key.m_eattribute
            && m_eicon == key.m_eicon
            && m_iIcon == key.m_iIcon
            && strcmp(m_pszExtension, key.m_pszExtension) == 0
            && strcmp(m_pszShellThemePrefix, key.m_pszShellThemePrefix) == 0
            && strcmp(m_pszPath, key.m_pszPath) == 0;
      }




      class CLASS_DECL_CORE ImageSet :
         virtual public ::object
      {
      public:

         mutex                                                    m_mutex;
         sp(image_list)                                           m_pil16;
         sp(image_list)                                           m_pil48;
         sp(image_list)                                           m_pil48Hover;
         map < ImageKeyStore, const ImageKey &, int32_t, int32_t >     m_imagemap;

         string                                                   m_strShellThemePrefix;
         stringa                                                  m_straThemeableIconName;


      

#ifdef WINDOWSEX


         IShellFolder *   m_pshellfolder;


#endif

         ImageSet(::aura::application * papp);
         virtual ~ImageSet();

#ifdef WINDOWSEX
         bool GetIcon(oswindow oswindow, const char * lpcsz, const unichar * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
         bool GetIcon(oswindow oswindow, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
         bool GetIcon(oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
#endif

#ifdef WINDOWSEX
         int32_t GetImage(oswindow oswindow, IShellFolder * lpsf, const char * pszPath, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, EIcon eicon);
#endif
         int32_t GetImageFoo(oswindow oswindow, const string & strExtension, EFileAttribute eattribute, EIcon eicon, COLORREF crBk = 0);
         int32_t GetImage(oswindow oswindow, const string & strPath,EFileAttribute eattribute,EIcon eicon, COLORREF crBk = 0) ;
         int32_t GetImage(oswindow oswindow, ImageKey key, const unichar * lpcszExtra, COLORREF crBk);
         int32_t GetImageByExtension(oswindow oswindow, ImageKey & key, COLORREF crBk);
#ifdef WINDOWSEX
         int32_t GetImage(oswindow oswindow, ImageKey key, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, COLORREF crBk);
         int32_t GetImage(oswindow oswindow, ImageKey key, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, COLORREF crBk);
         int32_t GetFooImage(oswindow oswindow, ImageKey key, COLORREF crBk);
         void _017ItemIDListParsePath(oswindow oswindow, LPITEMIDLIST * lpiidl, const char * lpcsz);
#endif

         


         inline image_list * GetImageList16()
         {
            return m_pil16;
         }
         inline image_list * GetImageList48()
         {
            return m_pil48;
         }
         inline image_list * GetImageList48Hover()
         {
            return m_pil48Hover;
         }

         void initialize();

      };


//      string CLASS_DECL_CORE _017FilePathGetParent(const char * lpcsz);

#ifdef WINDOWSEX
      HICON CLASS_DECL_CORE CalcIcon(LPITEMIDLIST lpiidl, const char * lpcszExtra, int32_t cx, int32_t cy);
      bool CLASS_DECL_CORE _017HasSubFolder(::aura::application * papp, LPITEMIDLIST lpiidl, const char * lpcszExtra);
#endif
      EFolder CLASS_DECL_CORE GetFolderType(::aura::application * papp, const unichar * lpcszPath);
      EFolder CLASS_DECL_CORE GetFolderType(::aura::application * papp, const char * lpcszPath);
//      void CLASS_DECL_CORE GetChildren(stringa & stra, const char * lpcszPath);
#ifdef WINDOWSEX
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListGetLast(LPITEMIDLIST lpiidl);
      int32_t CLASS_DECL_CORE _017ItemIDListGetLen(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListDup(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl);
      bool CLASS_DECL_CORE _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2);
      

      void CLASS_DECL_CORE _017ItemIDListFree(LPITEMIDLIST lpiidl);
#endif
   } // namespace _shell

} // namespace filemanager


template <>
inline UINT HashKey<const filemanager::_shell::ImageKey &> (const filemanager::_shell::ImageKey & key)
{
   // default identity hash - works for most primitive values
   return (UINT)harmannieves_camwhite_hash(key.m_pszPath, 
                harmannieves_camwhite_hash(key.m_pszShellThemePrefix,
                harmannieves_camwhite_hash(key.m_pszExtension,
                key.m_iIcon | (((int) key.m_eicon) << 8) | (((int)key.m_eattribute) << 16))));
}
