#include "framework.h"

#ifdef WINDOWS
#include <Shellapi.h>
#include <CommonControls.h>
#endif


namespace filemanager
{

   namespace _shell
   {

      string _017FilePathGetParent(const char * lpcsz);

#ifdef WINDOWSEX

      int32_t _017ItemIDListGetLen(LPITEMIDLIST lpiidl)
      {
         if(lpiidl == NULL)
            return 0;
         LPSHITEMID  lpshiid = (LPSHITEMID) lpiidl;
         LPSHITEMID  lpshiidLast = NULL;
         USHORT cb;
         int32_t iLen = 0;
         while(true)
         {
            cb = lpshiid->cb;
            iLen += cb;
            if(cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID) (((LPBYTE) lpshiid) + cb);
         }
         return iLen;
      }

   IShellFolder * _017GetShellFolder(LPITEMIDLIST lpiidlChild)
   {
      IShellFolder * lpsfDesktop;
      HRESULT hr;

      hr = SHGetDesktopFolder(&lpsfDesktop);

      if(hr != S_OK)
      {
         return NULL;
//         System.simple_message_box(NULL, "Failed to open desktop folder!");
      }

      if(SUCCEEDED(hr))
      {
         IShellFolder * lpsfParent = NULL;

         LPITEMIDLIST lpiidlParent = _017ItemIDListGetFolderParent(lpiidlChild);

         if(lpiidlParent == NULL)
         {
            return lpsfDesktop;
         }

         hr = lpsfDesktop->BindToObject(
            lpiidlParent,
            NULL,
            IID_IShellFolder,
            (void **) &lpsfParent);

         lpsfDesktop->Release();

         if(SUCCEEDED(hr))
         {
           return lpsfParent;
         }

         _017ItemIDListFree(lpiidlParent);

      }
      else
      {
         ASSERT(FALSE);
      }

      return NULL;
   }

      LPITEMIDLIST _017ItemIDListDup(LPITEMIDLIST lpiidl)
      {
         if(lpiidl == NULL)
            return NULL;

         LPMALLOC lpmalloc = NULL;
         HRESULT hr;

         hr = SHGetMalloc(&lpmalloc);

         int32_t iLen = _017ItemIDListGetLen(lpiidl);

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iLen + 2);

         memcpy(lpiidlRet, lpiidl, iLen);
         ((LPBYTE)lpiidlRet)[iLen] = 0;
         ((LPBYTE)lpiidlRet)[iLen + 1] = 0;

         lpmalloc->Release();

         return lpiidlRet;
      }

      int32_t _017ItemIDListIHash(LPITEMIDLIST lpiidl)
      {
         if(lpiidl == NULL)
            return 0;

         int32_t iLen = _017ItemIDListGetLen(lpiidl);


         int32_t iHash = 0;
         int32_t iRemain = iLen;
         uint32_t * lpdw = (uint32_t *) lpiidl;
         while(iRemain >= 4)
         {
            iHash += *lpdw;
            lpdw++;
            iRemain -= 4;
         }
         LPBYTE lpb = (LPBYTE) lpdw;
         while(iRemain > 0)
         {
            iHash += *lpb;
            lpb++;
            iRemain--;
         }
         return iHash;
      }

      LPITEMIDLIST _017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl)
      {

         LPMALLOC lpmalloc = NULL;
         HRESULT hr;

         hr = SHGetMalloc(&lpmalloc);

         int32_t iLenParent = _017ItemIDListGetLen(lpiidlParent);
         int32_t iLen = _017ItemIDListGetLen(lpiidl);

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iLenParent + iLen + 2);

         memcpy(lpiidlRet, lpiidlParent, iLenParent);
         memcpy(&(((LPBYTE)lpiidlRet)[iLenParent]), lpiidl, iLen);
         ((LPBYTE)lpiidlRet)[iLenParent + iLen] = 0;
         ((LPBYTE)lpiidlRet)[iLenParent + iLen + 1] = 0;

         lpmalloc->Release();

         return lpiidlRet;
      }

      LPITEMIDLIST _017ItemIDListGetLast(LPITEMIDLIST lpiidl)
      {

   if(lpiidl == NULL)
            return NULL;

         LPMALLOC lpmalloc = NULL;
         HRESULT hr;
         hr = SHGetMalloc(&lpmalloc);

         LPSHITEMID  lpshiid = (LPSHITEMID) lpiidl;
         LPSHITEMID  lpshiidLast = lpshiid;
         USHORT cb;

         while(true)
         {
            cb = *((USHORT *) lpshiid);
            if(cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID) (((LPBYTE) lpshiid) + cb);
         }
         int32_t iCount = *((USHORT *) lpshiidLast);

         if(iCount == 0)
            return NULL;

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iCount + 2);

         memcpy(lpiidlRet, lpshiidLast, iCount);

         *((USHORT *)&(((LPBYTE)lpiidlRet)[iCount])) = 0;

         lpmalloc->Release();

         return lpiidlRet;
      }

#endif

      string _017FilePathGetParent(const char * lpcsz)
      {
         stringa stra;
         stra.add("/");
         stra.add("\\");
         stringa stra2;
         stra2.add_smallest_tokens(lpcsz, stra, FALSE);
         string str;
         for(int32_t i = 0; i < stra2.get_size() - 1; i++)
         {
            str += stra2[i];
            str += "\\";
         }
         return str;
      }

#ifdef WINDOWSEX

      LPITEMIDLIST _017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl)
      {
         if(lpiidl == NULL)
            return NULL;

         LPMALLOC lpmalloc = NULL;
         HRESULT hr;
         hr = SHGetMalloc(&lpmalloc);

         LPSHITEMID  lpshiid = (LPSHITEMID) lpiidl;
         LPSHITEMID  lpshiidLast = lpshiid;
         USHORT cb;

         while(true)
         {
            cb = *((USHORT *) lpshiid);
            if(cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID) (((LPBYTE) lpshiid) + cb);
         }
         ::count iCount = ((LPBYTE)lpshiidLast) - ((LPBYTE) lpiidl);

         if(iCount == 0)
            return NULL;

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iCount + 2);

         memcpy(lpiidlRet, lpiidl, iCount);

         *((USHORT *)&(((LPBYTE)lpiidlRet)[iCount])) = 0;

         lpmalloc->Release();

         return lpiidlRet;
      }

        bool _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2)
      {
         if(lpiidl1 == NULL && lpiidl2 == NULL)
         {
            return true;
         }
         if(lpiidl1 == NULL || lpiidl2 == NULL)
         {
            return false;
         }


         LPSHITEMID  lpshiid1 = (LPSHITEMID) lpiidl1;
         LPSHITEMID  lpshiid2 = (LPSHITEMID) lpiidl2;
         USHORT cb1;
         USHORT cb2;

         while(true)
         {
            cb1 = *((USHORT *) lpshiid1);
            cb2 = *((USHORT *) lpshiid2);
            if(cb1 == 0 && cb2 == 0)
            {
               return true;
            }
            if(cb1 == 0 || cb2 == 0)
            {
               return false;
            }
            if(cb1 != cb2)
               return false;
            if(memcmp(lpshiid1, lpshiid2, cb1) != 0)
               return false;
            lpshiid1 = (LPSHITEMID) (((LPBYTE) lpshiid1) + cb1);
            lpshiid2 = (LPSHITEMID) (((LPBYTE) lpshiid2) + cb2);
         }
      }

      void _017ItemIDListParsePath(LPITEMIDLIST * lpiidl, const char * lpcsz)
      {
         HRESULT hr;
         LPMALLOC lpmalloc = NULL;
         IShellFolder * lpsfDesktop;
         hr = SHGetMalloc(&lpmalloc);


         hr = SHGetDesktopFolder(&lpsfDesktop);

         ULONG ulEaten;
         ULONG dwAttrib = SFGAO_FOLDER;

         wstring wstr = ::str::international::utf8_to_unicode(lpcsz);

         try
         {
            hr = lpsfDesktop->ParseDisplayName(
               NULL,
               NULL,
               (wchar_t *) (const wchar_t *) wstr,
               &ulEaten,
               lpiidl,
               &dwAttrib);
         }
         catch(...)
         {
         }

         lpsfDesktop->Release();
         lpmalloc->Release();

      }

      void _017ItemIDListFree( LPITEMIDLIST lpiidl)
      {
         LPMALLOC lpmalloc = NULL;

      SHGetMalloc(&lpmalloc);

         lpmalloc->Free(lpiidl);

      lpmalloc->Release();
   }

   bool _017HasSubFolder(sp(::base::application) papp, LPITEMIDLIST lpiidl, const char * lpcszExtra)
   {

      WCHAR szPath[_MAX_PATH * 10];

      SHGetPathFromIDListW(lpiidl, szPath);

      EFolder efolder = GetFolderType(papp, szPath);

      if(efolder == FolderNone)
      {

         return false;

      }
      else if(efolder == FolderZip)
      {

         string wstrPath;

         ::str::international::unicode_to_utf8(wstrPath, szPath);

         string wstrExtra(lpcszExtra);

         if(wstrExtra.get_length() > 0)
         {
            wstrPath += ":" + wstrExtra;
         }

         return zip::Util().HasSubFolder(papp, wstrPath);

      }
      else
      {

         stringa stra;

         sess(papp).dir().ls(::str::international::unicode_to_utf8(szPath), &stra);

         for(int32_t i = 0; i < stra.get_size(); i++)
         {

            efolder = GetFolderType(papp, stra[i]);

            if(efolder != FolderNone)
               return true;

         }

         return false;

      }

   }

#endif

   EFolder GetFolderType(sp(::base::application) papp, const char * lpcsz)
   {
      return GetFolderType(papp, ::str::international::utf8_to_unicode(lpcsz));
   }

   EFolder GetFolderType(sp(::base::application) papp, const wchar_t * lpcszPath)
   {

      string strPath;

      ::str::international::unicode_to_utf8(strPath, lpcszPath);

      if(dir::is(strPath))
      {
         return FolderFileSystem;
      }
      else if(zip::Util().IsUnzipable(papp, strPath))
      {
         return FolderZip;
      }
      else
      {
         return FolderNone;
      }

   }
/*
   void GetChildren(stringa & stra, const char * lpcszPath)
   {
      string wstrBase(lpcszPath);
      WIN32_FIND_DATAW fd;
      if(wstrBase.get_length() == 0)
      {
         wstrBase = "\\";
      }
      else
      {
         if(wstrBase.find('\\') >= 0)
         {
            if(wstrBase.Right(1) != "\\")
               wstrBase += "\\";
         }
         else if(wstrBase.find('/') >= 0)
         {
            if(wstrBase.Right(1) != "/")
               wstrBase += "/";
         }
         else
         {
            wstrBase += "\\";
         }
      }
      string wstrMask(wstrBase);
      wstrMask += "*.*";
      wstring wstr = ::str::international::utf8_to_unicode(lpcszPath);
      HANDLE h = ::FindFirstFileExW(wstr, FindExInfoStandard, &fd, FindExSearchNameMatch, NULL, 0);

      if(h == NULL)
         return;

      while(true)
      {
         stra.add(::str::international::unicode_to_utf8(fd.cFileName));
         if(!FindNextFileW(h, &fd))
            break;
      }

      stra.remove(".");
      stra.remove("..");
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         stra[i] = wstrBase + stra[i];
      }

      FindClose(h);

   }
*/

   ImageKey::ImageKey()
   {
      m_iIcon = 0x80000000;
   }

   ImageKey::ImageKey(const ImageKey & key)
   {
      m_strPath         = key.m_strPath;
      m_iIcon           = key.m_iIcon;
      m_strExtension    = key.m_strExtension;
   }


   bool ImageKey::operator == (const ImageKey & key) const
   {
      return m_iIcon == key.m_iIcon
         && m_strExtension == key.m_strExtension
         && m_strPath == key.m_strPath;
   }





   ImageSet::ImageSet(sp(::base::application) papp) :
      element(papp),
      m_mutex(papp)
   {
      m_pil16 = new image_list(papp);
      m_pil16->create(16, 16, 0, 10, 10);
      m_pil48 = new image_list(papp);
      m_pil48->create(48, 48, 0, 10, 10);
      m_pil48Hover = new image_list(papp);
      m_pil48Hover->create(48, 48, 0, 10, 10);
   }

   ImageSet::~ImageSet()
   {

   }

   void ImageSet::initialize()
   {

      single_lock sl(&m_mutex, true);

      m_pil16->add_matter("filemanager\\check_off_16.png");
      m_pil16->add_matter("filemanager\\check_on_16.png");
      m_pil48->add_matter("filemanager\\check_off_16.png");
      m_pil48->add_matter("filemanager\\check_on_16.png");
      m_pil48Hover->add_matter("filemanager\\check_off_16.png");
      m_pil48Hover->add_matter("filemanager\\check_on_16.png");

   }

   int32_t ImageSet::GetImage(oswindow oswindow, const char * lpcsz, EFileAttribute eattribute, EIcon eicon)
   {

      single_lock sl(&m_mutex, true);

      int32_t iImage = 0x80000000;

#ifdef WINDOWSEX

      ImageKey imagekey;

      string str(lpcsz);

      imagekey.m_strPath.Format(":%s:%d:%d", lpcsz, eattribute, eicon);

      imagekey.m_strExtension = str.Mid(str.reverse_find('.'));

      imagekey.m_iIcon = 0;

      if(m_imagemap.Lookup(imagekey,iImage))
         return iImage;

      iImage = GetImage(oswindow,lpcsz,NULL,eicon,eattribute == FileAttributeDirectory);

      m_imagemap.set_at(imagekey,iImage);

#endif

      return iImage;


   }


#ifdef WINDOWSEX

   int32_t ImageSet::GetImage(
      oswindow oswindow,
      IShellFolder * lpsf,
      LPITEMIDLIST lpiidlAbsolute,
      LPITEMIDLIST lpiidlChild,
      const wchar_t * lpcszExtra,
      EIcon eicon)
   {

      single_lock sl(&m_mutex, true);

      if(lpsf == NULL)
         return 0x80000000;
      int32_t iType;
      switch(eicon)
      {
      case IconNormal:
         iType = 0;
         break;
      case IconOpen:
         iType = GIL_OPENICON;
         break;
      default:
         // unexpected icon type
         ASSERT(FALSE);
         return 0x80000000;
      }


      WCHAR szFilePath[_MAX_PATH * 10];
      SHGetPathFromIDListW(
         lpiidlAbsolute,
         szFilePath);
      string strFilePath(szFilePath);

   //   WCHAR wszFilePath[_MAX_PATH * 10];
      SHGetPathFromIDListW(
         lpiidlAbsolute,
         szFilePath);

      CHAR szPath[_MAX_PATH * 10];
      string strPath;
      int32_t iImage = 0x80000000;

      HICON hicon16 = NULL;
      HICON hicon48 = NULL;
      HRESULT hrIconLocation;
      HRESULT hrExtract;
      ImageKey imagekey;


      string strPathEx(strFilePath);
      string strExtra;

      ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

      if(strExtra.get_length() > 0)
      {
         strPathEx += ":" + strExtra;
      }



      int32_t iIcon = 0x80000000;
      UINT uiFlags = 0;

      SHFILEINFO shfi16;
      SHFILEINFO shfi48;

      IExtractIcon * lpiextracticon = NULL;

      /*EFolder efolder = GetFolderType(wszFilePath);
      if(efolder !)
      {
         iconkey.m_iIcon         = 0x80000000;
         iconkey.m_strExtension  = "folder";
         iconkey.m_strPath.Empty();
      }
      else
      {
         int32_t iFind = item.m_strExtra.reverse_find(L'.');
         if(iFind >= 0)
         {
            ::str::international::UnicodeToOEM(strName, item.m_strExtra);
            iFind = strName.reverse_find('.');

            iconkey.m_iIcon         = 0x80000000;
            iconkey.m_strExtension  = strName.Mid(iFind);
            iconkey.m_strPath.Empty();

         }
      }*/
      if(SUCCEEDED(lpsf->GetUIObjectOf(
         oswindow,
         1,
         (LPCITEMIDLIST *) &lpiidlChild,
         IID_IExtractIcon,
         NULL,
         (void **) &lpiextracticon)))
      {
         if(SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
               iType,
               szPath,
               sizeof(szPath),
               &iIcon,
               &uiFlags)))
         {
            strPath = szPath;
            if(strPath == "*")
            {
               strsize iFind = strFilePath.reverse_find('.');

               imagekey.m_iIcon         = 0x80000000;
               imagekey.m_strExtension  = strFilePath.Mid(iFind);
               imagekey.m_strPath.Empty();
            }
            else
            {
               imagekey.m_strPath    = szPath;
               imagekey.m_iIcon      = iIcon;
               imagekey.m_strExtension.Empty();
            }
         }
      }
      if(imagekey.m_iIcon == 0x80000000)
      {
         string strTarget;
         //if(System.os().resolve_link(strTarget, strFilePath, System.window_from_os_data))
         if(System.os().resolve_link(strTarget, strFilePath, NULL))
         {

            wstring wstr = ::str::international::utf8_to_unicode(strTarget);

            LPITEMIDLIST lpiidl2 = NULL;

            uint32_t dwAttrib = 0;

//            unsigned long ulEaten;

            HRESULT hr;

            try
            {
               hr = SHParseDisplayName(
                  wstr,
                  NULL,
                  &lpiidl2,
                  0,
                  NULL);
            }
            catch(...)
            {
            }

            LPITEMIDLIST lpiidlChild2     = _017ItemIDListGetLast(lpiidl2);

            LPITEMIDLIST lpiidlParent2    = _017ItemIDListGetFolderParent(lpiidl2);

            int32_t iImage = GetImage(
               oswindow,
               lpsf,
               lpiidl2,
               lpiidlChild2,
               NULL,
               eicon);

            _017ItemIDListFree(lpiidlParent2);

            _017ItemIDListFree(lpiidlChild2);

            return iImage;

         }
      }
      if(!m_imagemap.Lookup(imagekey, iImage))
      {

         if(imagekey.m_iIcon == 0x80000000)
         {
            iImage = GetFooImage(oswindow,eicon, imagekey.m_strPath=="folder", imagekey.m_strExtension);
         }
         else
         {
            try
            {
               hicon16 = NULL;
               strPath.Truncate(0);
               strPath.free_extra();
               strPath = imagekey.m_strPath;
               iIcon = imagekey.m_iIcon;
               bool bExtract = false;
               //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
               //LPTSTR lpsz = (LPTSTR) ::GlobalLock(hglobal);
               //strcpy(lpsz, strPath);
               try
               {
                  if((hrIconLocation == S_FALSE || uiFlags & GIL_NOTFILENAME)
                     && lpiextracticon != NULL
                     && (NOERROR == (hrExtract = lpiextracticon->Extract(
                     strPath,
                     iIcon,
                     &hicon48,
                     &hicon16,
                     0x00100030)))
                     )
                  {
                     bExtract = true;
                     iImage = m_pil16->add_icon_os_data(hicon16);
/*                     HMODULE hmodule = ::LoadLibrary(strPath);
                     HICON hicon48_2;
                     if(hmodule != NULL)
                     {
                        hicon48_2 = (HICON) ::LoadImage(hmodule, MAKEINTRESOURCE(iIcon), IMAGE_ICON, 48, 48, LR_LOADTRANSPARENT);
                     }
                     if(hicon48_2 != NULL)
                     {
                        m_pil48Hover->add_icon_os_data(hicon48_2);
                     }
                     else*/
                     {
                        m_pil48Hover->add_icon_os_data(hicon48);
                     }
                     System.visual().imaging().Createcolor_blend_ImageList(
                        m_pil48,
                        m_pil48Hover,
                        RGB(255, 255, 240),
                        64);
                     m_imagemap.set_at(imagekey, iImage);
                  }
               }
               catch(...)
               {
               }
               //::GlobalUnlock(hglobal);
               //::GlobalFree(hglobal);
               if(!bExtract)
               {
                  if(imagekey.m_strPath.is_empty())
                  {
                     SHGetFileInfo(
                        (const char *) lpiidlAbsolute,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi16,
                        sizeof(shfi16),
                        SHGFI_PIDL
                        | SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_SMALLICON);
                     hicon16 = shfi16.hIcon;
                     SHGetFileInfo(
                        (const char *) lpiidlAbsolute,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi48,
                        sizeof(shfi48),
                        SHGFI_PIDL
                        | SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_LARGEICON);
                     hicon48 = shfi48.hIcon;
                     iImage = m_pil16->add_icon_os_data(hicon16);
                     IImageList * pil = NULL;
                     SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void **) &pil);
                     if(pil != NULL)
                     {
                        HICON hicon48;
                        pil->GetIcon(shfi48.iIcon, ILD_TRANSPARENT, &hicon48);
                        if(hicon48 == NULL)
                        {
                           m_pil48Hover->add_icon_os_data(shfi48.hIcon);
                        }
                        else
                        {
                           m_pil48Hover->add_icon_os_data(hicon48);
                        }
                        pil->Release();
                     }
                     else
                     {
                        m_pil48Hover->add_icon_os_data(shfi48.hIcon);
                     }
                     System.visual().imaging().Createcolor_blend_ImageList(
                        m_pil48,
                        m_pil48Hover,
                        RGB(255, 255, 240),
                        64);
                  }
                  else
                  {
                      ExtractIconEx(
                        imagekey.m_strPath,
                        imagekey.m_iIcon,
                        &hicon48,
                        &hicon16,
                        1);
                  }
                  if(hicon16 == NULL)
                  {
                        SHGetFileInfo(
                           "foo",
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi16,
                           sizeof(shfi16),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_SMALLICON);
                     hicon16 = shfi16.hIcon;
                  }
                  if(hicon48 == NULL)
                  {
                        SHGetFileInfo(
                           "foo",
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi48,
                           sizeof(shfi48),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_LARGEICON);
                     hicon48 = shfi48.hIcon;
                  }
                  iImage = m_pil16->add_icon_os_data(hicon16);
                  IImageList * pil = NULL;
                  SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void **) &pil);
                  if(pil != NULL)
                  {
                     HICON hicon48;
                     pil->GetIcon(shfi48.iIcon, ILD_TRANSPARENT, &hicon48);
                     if(hicon48 == NULL)
                     {
                        m_pil48Hover->add_icon_os_data(shfi48.hIcon);
                     }
                     else
                     {
                        m_pil48Hover->add_icon_os_data(hicon48);
                     }
                     pil->Release();
                  }
                  else
                  {
                     m_pil48Hover->add_icon_os_data(shfi48.hIcon);
                  }
                  System.visual().imaging().Createcolor_blend_ImageList(
                     m_pil48,
                     m_pil48Hover,
                     RGB(255, 255, 240),
                     64);
                  m_imagemap.set_at(imagekey, iImage);
               }
            }
            catch(...)
            {
            }
         }
      }

      if(lpiextracticon != NULL)
      {
         lpiextracticon->Release();
      }




      return iImage;
   }

   int32_t ImageSet::GetFooImage(oswindow oswindow,EIcon eicon,bool bFolder, const string & strExtension)
   {

      int32_t iImage;

      SHFILEINFO shfi16;

      SHFILEINFO shfi48;

      ImageKey imagekey;

      imagekey.m_iIcon         = 0x80000000;

      imagekey.m_strPath = "*foo";

      if(bFolder && !strExtension.has_char())
      {
         imagekey.m_strExtension  = "folder";
      }
      else
      {
         imagekey.m_strExtension  = strExtension;
      }

      imagekey.m_strPath.Empty();

      if(m_imagemap.Lookup(imagekey,iImage))
         return iImage;

      if(imagekey.m_strExtension == "folder")
      {
         SHGetFileInfo(
            "foo",
            FILE_ATTRIBUTE_DIRECTORY,
            &shfi16,
            sizeof(shfi16),
            SHGFI_USEFILEATTRIBUTES
            | SHGFI_ICON
            | SHGFI_SMALLICON);
         SHGetFileInfo(
            "foo",
            FILE_ATTRIBUTE_DIRECTORY,
            &shfi48,
            sizeof(shfi48),
            SHGFI_USEFILEATTRIBUTES
            | SHGFI_ICON
            | SHGFI_LARGEICON);
      }
      else
      {
         string strPath = "foo." + imagekey.m_strExtension;
         SHGetFileInfo(
            strPath,
            FILE_ATTRIBUTE_NORMAL,
            &shfi16,
            sizeof(shfi16),
            SHGFI_USEFILEATTRIBUTES
            | SHGFI_ICON
            | SHGFI_SMALLICON);
         SHGetFileInfo(
            strPath,
            FILE_ATTRIBUTE_NORMAL,
            &shfi48,
            sizeof(shfi48),
            SHGFI_USEFILEATTRIBUTES
            | SHGFI_ICON
            | SHGFI_LARGEICON);
      }
      iImage = m_pil16->add_icon_os_data(shfi16.hIcon);
      IImageList * pil = NULL;
      SHGetImageList(SHIL_EXTRALARGE,IID_IImageList,(void **)&pil);
      if(pil != NULL)
      {
         HICON hicon48;
         pil->GetIcon(shfi48.iIcon,ILD_TRANSPARENT,&hicon48);
         if(hicon48 == NULL)
         {
            m_pil48Hover->add_icon_os_data(shfi48.hIcon);
         }
         else
         {
            m_pil48Hover->add_icon_os_data(hicon48);
         }
         pil->Release();
      }
      else
      {
         m_pil48Hover->add_icon_os_data(shfi48.hIcon);
      }
      System.visual().imaging().Createcolor_blend_ImageList(
         m_pil48,
         m_pil48Hover,
         RGB(255,255,240),
         64);

      m_imagemap.set_at(imagekey,iImage);

      return iImage;

   }


#endif

   int32_t ImageSet::GetImageByExtension(oswindow oswindow, const char * pszPath, EIcon eicon, bool bFolder)
   {

      return GetFooImage(oswindow,eicon,bFolder,System.file().extension(pszPath));
      /*

      single_lock sl(&m_mutex, true);

      int32_t iImage = 0x80000000;

#ifdef WINDOWSEX

      if(pszPath == NULL)
         return 0x80000000;

      string strPath(pszPath);

      string strExtension = System.file().extension(strPath);

      int32_t iType;
      switch(eicon)
      {
      case IconNormal:
         iType = 0;
         break;
      case IconOpen:
         iType = GIL_OPENICON;
         break;
      default:
         // unexpected icon type
         ASSERT(FALSE);
         return 0x80000000;
      }



      HICON hicon16 = NULL;
      HICON hicon48 = NULL;
//      HRESULT hrIconLocation;
//      HRESULT hrExtract;
      ImageKey imagekey;


      string strExtra;


      int32_t iIcon = 0x80000000;
      UINT uiFlags = 0;

      SHFILEINFO shfi16;
      SHFILEINFO shfi48;


      imagekey.m_iIcon         = 0x80000000;
      if(bFolder && !strExtension.has_char())
      {
         imagekey.m_strExtension  = "folder";
      }
      else
      {
         imagekey.m_strExtension  = strExtension;
      }
      imagekey.m_strPath.Empty();

      if(!m_imagemap.Lookup(imagekey, iImage))
      {

         try
         {
            if(imagekey.m_strExtension == "folder")
            {
               SHGetFileInfo(
                  "foo",
                  FILE_ATTRIBUTE_DIRECTORY,
                  &shfi16,
                  sizeof(shfi16),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_SMALLICON);
               SHGetFileInfo(
                  "foo",
                  FILE_ATTRIBUTE_DIRECTORY,
                  &shfi48,
                  sizeof(shfi48),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_LARGEICON);
            }
            else
            {
               strPath = "foo." +imagekey.m_strExtension;
               SHGetFileInfo(
                  strPath,
                  FILE_ATTRIBUTE_NORMAL,
                  &shfi16,
                  sizeof(shfi16),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_SMALLICON);
               SHGetFileInfo(
                  strPath,
                  FILE_ATTRIBUTE_NORMAL,
                  &shfi48,
                  sizeof(shfi48),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_LARGEICON);
            }
            iImage = m_pil16->add_icon_os_data(shfi16.hIcon);
            m_pil48Hover->add_icon_os_data(shfi48.hIcon);
            System.visual().imaging().Createcolor_blend_ImageList(
               m_pil48,
               m_pil48Hover,
               RGB(255, 255, 240),
               64);

            m_imagemap.set_at(imagekey, iImage);
         }
         catch(...)
         {
         }

      }


#endif

      */

      //return iImage;

   }

#ifdef WINDOWSEX

   bool ImageSet::GetIcon(
      oswindow oswindow,
      IShellFolder * lpsf,
      LPITEMIDLIST lpiidlAbsolute,
      LPITEMIDLIST lpiidlChild,
      const wchar_t * lpcszExtra,
      EIcon eicon,
      HICON * phicon16,
      HICON * phicon48)
   {

      single_lock sl(&m_mutex, true);

      if(lpsf == NULL)
         return false;
      int32_t iType;
      switch(eicon)
      {
      case IconNormal:
         iType = 0;
         break;
      case IconOpen:
         iType = GIL_OPENICON;
         break;
      default:
         // unexpected icon type
         ASSERT(FALSE);
         return false;
      }


      WCHAR szFilePath[_MAX_PATH * 10];
      SHGetPathFromIDListW(
         lpiidlAbsolute,
         szFilePath);
      string strFilePath(szFilePath);

   //   WCHAR wszFilePath[_MAX_PATH * 10];
      SHGetPathFromIDListW(
         lpiidlAbsolute,
         szFilePath);

      CHAR szPath[_MAX_PATH * 10];
      string strPath;
   //   int32_t iImage = 0x80000000;

      HICON hicon16 = NULL;
      HICON hicon48 = NULL;
      HRESULT hrIconLocation;
      HRESULT hrExtract;
      ImageKey imagekey;


      string strPathEx(strFilePath);
      string strExtra;

      ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

      if(strExtra.get_length() > 0)
      {
         strPathEx += ":" + strExtra;
      }



      int32_t iIcon = 0x80000000;
      UINT uiFlags = 0;

      SHFILEINFO shfi16;
      SHFILEINFO shfi48;

      IExtractIcon * lpiextracticon = NULL;

      /*EFolder efolder = GetFolderType(wszFilePath);
      if(efolder !)
      {
         iconkey.m_iIcon         = 0x80000000;
         iconkey.m_strExtension  = "folder";
         iconkey.m_strPath.Empty();
      }
      else
      {
         int32_t iFind = item.m_strExtra.reverse_find(L'.');
         if(iFind >= 0)
         {
            ::str::international::UnicodeToOEM(strName, item.m_strExtra);
            iFind = strName.reverse_find('.');

            iconkey.m_iIcon         = 0x80000000;
            iconkey.m_strExtension  = strName.Mid(iFind);
            iconkey.m_strPath.Empty();

         }
      }*/
      if(SUCCEEDED(lpsf->GetUIObjectOf(
         oswindow,
         1,
         (LPCITEMIDLIST *) &lpiidlChild,
         IID_IExtractIcon,
         NULL,
         (void **) &lpiextracticon)))
      {
         if(SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
               iType,
               szPath,
               sizeof(szPath),
               &iIcon,
               &uiFlags)))
         {
            strPath = szPath;
            if(strPath == "*")
            {
               strsize iFind = strFilePath.reverse_find('.');

               imagekey.m_iIcon         = 0x80000000;
               imagekey.m_strExtension  = strFilePath.Mid(iFind);
               imagekey.m_strPath.Empty();
            }
            else
            {
               imagekey.m_strPath    = szPath;
               imagekey.m_iIcon      = iIcon;
               imagekey.m_strExtension.Empty();
            }
         }
      }
         if(Application.dir().is(::str::international::unicode_to_utf8(szFilePath)))
         {
            if(imagekey.m_iIcon == 0x80000000)
            {
               SHGetFileInfo(
                  "foo",
                  FILE_ATTRIBUTE_DIRECTORY,
                  &shfi16,
                  sizeof(shfi16),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_SMALLICON);
               SHGetFileInfo(
                  "foo",
                  FILE_ATTRIBUTE_DIRECTORY,
                  &shfi48,
                  sizeof(shfi48),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_LARGEICON);
            }
            else
            {
               strPath = "foo" + imagekey.m_strExtension;
               SHGetFileInfo(
                  strPath,
                  FILE_ATTRIBUTE_NORMAL,
                  &shfi16,
                  sizeof(shfi16),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_SMALLICON);
               SHGetFileInfo(
                  strPath,
                  FILE_ATTRIBUTE_NORMAL,
                  &shfi48,
                  sizeof(shfi48),
                  SHGFI_USEFILEATTRIBUTES
                  | SHGFI_ICON
                  | SHGFI_LARGEICON);
            }
            *phicon16 = shfi16.hIcon;
            *phicon48 = shfi48.hIcon;
         }
         else
         {
            try
            {
               hicon16 = NULL;
               strPath.Truncate(0);
               strPath.free_extra();
               strPath = imagekey.m_strPath;
               iIcon = imagekey.m_iIcon;
               bool bExtract = false;
               //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
               //LPTSTR lpsz = (LPTSTR) ::GlobalLock(hglobal);
               //strcpy(lpsz, strPath);
               try
               {
                  if((hrIconLocation == S_FALSE || uiFlags & GIL_NOTFILENAME)
                     && lpiextracticon != NULL
                     && (NOERROR == (hrExtract = lpiextracticon->Extract(
                     strPath,
                     iIcon,
                     &hicon48,
                     &hicon16,
                     0x00100030)))
                     )
                  {
                     bExtract = true;
                     *phicon16 = hicon16;
                     *phicon48 = hicon48;
                  }
               }
               catch(...)
               {
               }
               //::GlobalUnlock(hglobal);
               //::GlobalFree(hglobal);
               if(!bExtract)
               {
                  if(imagekey.m_strPath.is_empty())
                  {
                     SHGetFileInfo(
                        (const char *) lpiidlAbsolute,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi16,
                        sizeof(shfi16),
                        SHGFI_PIDL
                        | SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_SMALLICON);
                     hicon16 = shfi16.hIcon;
                     SHGetFileInfo(
                        (const char *) lpiidlAbsolute,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi48,
                        sizeof(shfi48),
                        SHGFI_PIDL
                        | SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_LARGEICON);
            hicon16 = shfi16.hIcon;
            hicon48 = shfi48.hIcon;
                  }
                  else
                  {
                      ExtractIconEx(
                        imagekey.m_strPath,
                        imagekey.m_iIcon,
                        &hicon48,
                        &hicon16,
                        1);
                  }
                  if(hicon16 == NULL)
                  {
                        SHGetFileInfo(
                           "foo",
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi16,
                           sizeof(shfi16),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_SMALLICON);
                     hicon16 = shfi16.hIcon;
                  }
                  if(hicon48 == NULL)
                  {
                        SHGetFileInfo(
                           "foo",
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi48,
                           sizeof(shfi48),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_LARGEICON);
                     hicon48 = shfi48.hIcon;
                  }
            *phicon16 = hicon16;
            *phicon48 = hicon48;
               }
            }
            catch(...)
            {
            }
         }

      if(lpiextracticon != NULL)
      {
         lpiextracticon->Release();
      }


      return true;

   }



   int32_t ImageSet::GetImage(
      oswindow oswindow,
      LPITEMIDLIST lpiidlAbsolute,
      const wchar_t * lpcszExtra,
      EIcon eicon)
   {


      single_lock sl(&m_mutex, true);

      IShellFolder  * lpsf = _017GetShellFolder(lpiidlAbsolute);


      LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(lpiidlAbsolute);
      int32_t iImage = GetImage(
         oswindow,
         lpsf,
         lpiidlAbsolute,
         lpiidlChild,
         lpcszExtra,
         eicon);

      lpsf->Release();

      _017ItemIDListFree(lpiidlChild);

      return iImage;
   }

#endif

   int32_t ImageSet::GetImage(
      oswindow oswindow,
      const char * psz,
      const wchar_t * lpcszExtra,
      EIcon eicon,
      bool bFolder)
   {

      single_lock sl(&m_mutex, true);

      string strPath(psz);

      int32_t iImage = 0x80000000;

      if(::str::ends_ci(strPath, ".core"))
      {
         string str = Application.file().as_string(strPath);
         if(::str::begins_eat_ci(str, "ca2prompt\r\n"))
         {
            str.trim();
#ifdef WINDOWSEX
            HICON hicon16 = (HICON) ::LoadImage(NULL, Application.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            HICON hicon48 = (HICON) ::LoadImage(NULL, Application.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
            iImage = m_pil16->add_icon_os_data(hicon16);
            m_pil48Hover->add_icon_os_data(hicon48);
            System.visual().imaging().Createcolor_blend_ImageList(
               m_pil48,
               m_pil48Hover,
               RGB(255, 255, 240),
               64);
#endif
         }
         return iImage;
      }
      // try to find "uifs:// http:// ftp:// like addresses"
      // then should show icon by extension or if is folder
      strsize iFind = ::str::find_ci("://", strPath);
      if(iFind >= 0)
      {
         string strProtocol = strPath.Left(iFind);
         int32_t i = 0;
         while(i < strProtocol.get_length() && isalnum(strProtocol[i]))
         {
            i++;
         }
         if(i > 0 && i == strProtocol.get_length())
         {
            // heuristically valid protocol
            return GetImageByExtension(oswindow, strPath, eicon, bFolder);
         }
         if(bFolder)
         {
            return GetImageByExtension(oswindow, strPath, eicon, bFolder);
         }
      }

#ifdef WINDOWSEX


      string str(psz);

      if(str == "foo")
      {

         iImage = GetFooImage(oswindow,eicon,bFolder,"");

      }
      else
      {

         if(::str::begins_eat(str,"foo."))
         {

            iImage = GetFooImage(oswindow,eicon,bFolder,str);

         }
         else
         {

            LPITEMIDLIST lpiidlAbsolute;

            _017ItemIDListParsePath(&lpiidlAbsolute,psz);

            iImage = GetImage(oswindow,lpiidlAbsolute,lpcszExtra,eicon);

            _017ItemIDListFree(lpiidlAbsolute);

         }

      }

#endif

      return iImage;

   }

      
#ifdef WINDOWSEX

   bool ImageSet::GetIcon(
      oswindow oswindow,
      const char * psz,
      const wchar_t * lpcszExtra,
      EIcon eicon,
      HICON * phicon16,
      HICON * phicon48)
   {

      single_lock sl(&m_mutex, true);

      
      LPITEMIDLIST lpiidlAbsolute;
      _017ItemIDListParsePath(&lpiidlAbsolute, psz);
      bool bGet = GetIcon(oswindow, lpiidlAbsolute, lpcszExtra, eicon, phicon16, phicon48);
      _017ItemIDListFree(lpiidlAbsolute);
      return bGet;

   }

   bool ImageSet::GetIcon(
      oswindow oswindow,
      LPITEMIDLIST lpiidlAbsolute,
      const wchar_t * lpcszExtra,
      EIcon eicon,
      HICON * phicon16,
      HICON * phicon48)
   {

      single_lock sl(&m_mutex, true);

      IShellFolder  * lpsf = _017GetShellFolder(lpiidlAbsolute);


      LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(lpiidlAbsolute);
      bool bGet = GetIcon(
         oswindow,
         lpsf,
         lpiidlAbsolute,
         lpiidlChild,
         lpcszExtra,
         eicon,
         phicon16,
         phicon48);

      lpsf->Release();

      _017ItemIDListFree(lpiidlChild);

      return bGet;
   }

#endif

} // namespace _shell


#ifdef WINDOWSEX

index Shell::GetCSIDL(LPITEMIDLIST lpiidl)
{
   LPMALLOC lpmalloc;
   SHGetMalloc(&lpmalloc);
   LPITEMIDLIST ppidl;

   int32_t csidla[] =
   {
      CSIDL_DESKTOP,
      CSIDL_DRIVES,
      CSIDL_PERSONAL,
      CSIDL_NETHOOD,
      CSIDL_NETWORK,
      CSIDL_BITBUCKET,
      -1,
   };

   int32_t * pcsidl = csidla;

   while(*pcsidl != -1)
   {
      if(SUCCEEDED(SHGetSpecialFolderLocation(
         NULL,
         *pcsidl,
         &ppidl)))
      {
         if(_shell::_017ItemIDListIsEqual(ppidl, lpiidl))
         {
            lpmalloc->Free(ppidl);
            break;
         }
         lpmalloc->Free(ppidl);
      }
      pcsidl++;
   }

   return *pcsidl;


}

index Shell::GetCSIDLSort(index iCsidl)
{
   switch(iCsidl)
   {
   case CSIDL_DESKTOP:
      return 100;
   case CSIDL_PERSONAL:
      return 200;
   case CSIDL_DRIVES:
      return 300;
   case CSIDL_NETHOOD:
      return 1000;
   default:
      return 2000 + iCsidl;
   }

}

void Shell::GetAscendants(
   LPITEMIDLIST lpiidl,
   array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)
{
   if(lpiidl == NULL)
      return;
   for(;;)
   {
      lpiidl = _shell::_017ItemIDListGetFolderParent(lpiidl);
      if(lpiidl == NULL)
         break;
      lpiidla.add(lpiidl);
   }
}

void Shell::Free(array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)
{
   LPMALLOC lpmalloc = NULL;

   SHGetMalloc(&lpmalloc);

   for(int32_t i = 0; i < lpiidla.get_size(); i++)
   {
      lpmalloc->Free(lpiidla[i]);
   }
   lpiidla.remove_all();

   lpmalloc->Release();
}


#endif



} // namespace filemanager
