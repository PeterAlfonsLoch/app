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
         ImageKey();
         ImageKey(const ImageKey & key);
         string      m_strPath;
         int32_t         m_iIcon;
         string      m_strExtension;

         operator uint32_t () const
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




      class CLASS_DECL_CORE ImageSet :
         virtual public ::object
      {
      protected:

         mutex                                                    m_mutex;
         sp(image_list)                                           m_pil16;
         sp(image_list)                                           m_pil48;
         sp(image_list)                                           m_pil48Hover;
         map < ImageKey, const ImageKey &, int32_t, int32_t >     m_imagemap;


      public:

#ifdef WINDOWSEX


         IShellFolder *   m_pshellfolder;


#endif

         ImageSet(sp(::base::application) papp);
         virtual ~ImageSet();

#ifdef WINDOWSEX
         bool GetIcon(oswindow oswindow, const char * lpcsz, const wchar_t * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
         bool GetIcon(oswindow oswindow, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const wchar_t * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
         bool GetIcon(oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const wchar_t * lpcszExtra, EIcon eicon, HICON * phicon16, HICON * phicon48);
#endif

#ifdef WINDOWSEX
         int32_t GetImage(oswindow oswindow, IShellFolder * lpsf, const char * pszPath, LPITEMIDLIST lpiidlChild, const wchar_t * lpcszExtra, EIcon eicon);
#endif
         int32_t GetImage(const char * lpcsz, EFileAttribute eattribute, EIcon eicon) ;
         int32_t GetImage(oswindow oswindow, const char * lpcsz, const wchar_t * lpcszExtra, EIcon eicon, bool bFolder);
         int32_t GetImageByExtension(oswindow oswindow, const char * lpcsz, EIcon eicon, bool bFolder);
#ifdef WINDOWSEX
         int32_t GetImage(oswindow oswindow, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const wchar_t * lpcszExtra, EIcon eicon);
         int32_t GetImage(oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const wchar_t * lpcszExtra, EIcon eicon);
#endif


         inline sp(image_list) GetImageList16()
         {
            return m_pil16;
         }
         inline sp(image_list) GetImageList48()
         {
            return m_pil48;
         }
         inline sp(image_list) GetImageList48Hover()
         {
            return m_pil48Hover;
         }

         void initialize();

      };


//      string CLASS_DECL_CORE _017FilePathGetParent(const char * lpcsz);

#ifdef WINDOWSEX
      HICON CLASS_DECL_CORE CalcIcon(LPITEMIDLIST lpiidl, const char * lpcszExtra, int32_t cx, int32_t cy);
      bool CLASS_DECL_CORE _017HasSubFolder(sp(::base::application) papp, LPITEMIDLIST lpiidl, const char * lpcszExtra);
#endif
      EFolder CLASS_DECL_CORE GetFolderType(sp(::base::application) papp, const wchar_t * lpcszPath);
      EFolder CLASS_DECL_CORE GetFolderType(sp(::base::application) papp, const char * lpcszPath);
//      void CLASS_DECL_CORE GetChildren(stringa & stra, const char * lpcszPath);
#ifdef WINDOWSEX
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListGetLast(LPITEMIDLIST lpiidl);
      int32_t CLASS_DECL_CORE _017ItemIDListGetLen(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListDup(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl);
      LPITEMIDLIST CLASS_DECL_CORE _017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl);
      bool CLASS_DECL_CORE _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2);
      void CLASS_DECL_CORE _017ItemIDListParsePath(LPITEMIDLIST * lpiidl, const char * lpcsz);

      void CLASS_DECL_CORE _017ItemIDListFree(LPITEMIDLIST lpiidl);
#endif
   } // namespace _shell

} // namespace filemanager
