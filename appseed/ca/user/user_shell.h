#pragma once

#ifdef WINDOWS
#include <shlobj.h>
#endif

namespace filemanager
{

#ifdef WINDOWS
   class CLASS_DECL_ca Shell
   {
   public:


      static index  GetCSIDLSort(index iCsidl);
      static index  GetCSIDL(LPITEMIDLIST lpiidl);
      static void GetAscendants(LPITEMIDLIST lpiidl, base_array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
      static void Free(base_array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);


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
         ImageKey();
         ImageKey(const ImageKey & key);
         string      m_strPath;
         int         m_iIcon;
         string      m_strExtension;

         operator DWORD () const
         {
            return m_iIcon;
         }
         bool operator == (const ImageKey & key) const;
      };


      inline UINT HashKey(ImageKey & key)
      {
         // default identity hash - works for most primitive values
         return (UINT) ::HashKey((const char *) key.m_strPath) | key.m_iIcon;
      }




      class CLASS_DECL_ca ImageSet :
         virtual public ::radix::object
      {
      protected:


         image_list *            m_pil16;
         image_list *            m_pil48;
         image_list *            m_pil48Hover;
         ::collection::map < ImageKey, const ImageKey &, int, int > m_imagemap;


      public:

#ifdef WINDOWS


         IShellFolder *   m_pshellfolder;


#endif

         ImageSet(::ca::application * papp);
         ~ImageSet();

         bool GetIcon(HWND hwnd, const char * lpcsz, const wchar_t * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
#ifdef WINDOWS
         bool GetIcon(HWND hwnd, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const wchar_t * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
         bool GetIcon(HWND hwnd, LPITEMIDLIST lpiidlAbsolute, const wchar_t * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
#endif

#ifdef WINDOWS
         int GetImage(HWND hwnd, IShellFolder * lpsf, const char * pszPath, LPITEMIDLIST lpiidlChild, const wchar_t * lpcszExtra, EIcon eicon);
#endif
         int GetImage(const char * lpcsz, EFileAttribute eattribute, EIcon eicon) ;
         int GetImage(HWND hwnd, const char * lpcsz, const wchar_t * lpcszExtra, EIcon eicon, bool bFolder);
         int GetImageByExtension(HWND hwnd, const char * lpcsz, EIcon eicon, bool bFolder);
#ifdef WINDOWS
         int GetImage(HWND hwnd, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const wchar_t * lpcszExtra, EIcon eicon);
         int GetImage(HWND hwnd, LPITEMIDLIST lpiidlAbsolute, const wchar_t * lpcszExtra, EIcon eicon);
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


      string CLASS_DECL_ca _017FilePathGetParent(const char * lpcsz);

#ifdef WINDOWS
      HICON CLASS_DECL_ca CalcIcon(LPITEMIDLIST lpiidl, const char * lpcszExtra, int cx, int cy);
      bool CLASS_DECL_ca _017HasSubFolder(::ca::application * papp, LPITEMIDLIST lpiidl, const char * lpcszExtra);
#endif
      EFolder CLASS_DECL_ca GetFolderType(::ca::application * papp, const wchar_t * lpcszPath);
      EFolder CLASS_DECL_ca GetFolderType(::ca::application * papp, const char * lpcszPath);
      void CLASS_DECL_ca GetChildren(stringa & stra, const char * lpcszPath);
#ifdef WINDOWS
      LPITEMIDLIST CLASS_DECL_ca _017ItemIDListGetLast(LPITEMIDLIST lpiidl);
      int CLASS_DECL_ca _017ItemIDListGetLen(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_ca _017ItemIDListDup(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_ca _017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_ca _017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl);
      bool CLASS_DECL_ca _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2);
      void CLASS_DECL_ca _017ItemIDListParsePath(LPITEMIDLIST * lpiidl, const char * lpcsz);

      void CLASS_DECL_ca _017ItemIDListFree(LPITEMIDLIST lpiidl);
#endif
   } // namespace _shell

} // namespace filemanager
