#include "framework.h"
#include "user_shell_windows.h"


namespace user
{


   namespace shell
   {


      windows::windows(::aura::application * papp) :
         ::object(papp),
         //::thread(papp),
         ::user::shell::shell(papp)
      {

         defer_create_mutex();
         //begin();

         SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);
         SHGetDesktopFolder(&m_pfolderDesktop);
         SHGetMalloc(&m_pmalloc);


      }

      windows::~windows()
      {

      }


      ::windows::comptr < IShellFolder > windows::_017GetShellFolder(const string & strParam, LPITEMIDLIST lpiidlFolder)
      {

         if (lpiidlFolder == NULL)
         {

            return NULL;

         }

         string str(strParam);

         str.make_lower();

         {

            synch_lock sl(m_pmutex);

            if (m_mapFolder[str].m_lpsf.is_set())
            {

               return m_mapFolder[str].m_lpsf;

            }

         }

         HRESULT hr = S_OK;

         if (SUCCEEDED(hr))
         {

            ::windows::comptr < IShellFolder > pfolder;

            hr = m_pfolderDesktop->BindToObject(
               lpiidlFolder,
               NULL,
               IID_IShellFolder,
               pfolder);

            if (SUCCEEDED(hr))
            {

               m_mapFolder[str].m_lpsf = pfolder;

               m_mapFolder[str].m_iRef = 1;

               return pfolder;

            }

         }
         else
         {
            ASSERT(FALSE);
         }

         return NULL;

      }


      ::windows::comptr < IShellFolder> windows::_017GetShellParentFolder(LPITEMIDLIST lpiidlChild)
      {

         LPITEMIDLIST lpiidlParent = _017ItemIDListGetFolderParent(lpiidlChild);

         WCHAR szPath[_MAX_PATH * 10];

         SHGetPathFromIDListW(lpiidlParent, szPath);

         string strPath(szPath);

         ::windows::comptr < IShellFolder> pfolderRet = _017GetShellFolder(strPath, lpiidlParent);

         _017ItemIDListFree(lpiidlParent);

         return pfolderRet;

      }


      LPITEMIDLIST windows::_017ItemIDListDup(LPITEMIDLIST lpiidl)
      {
         
         if (lpiidl == NULL)
            return NULL;

         int32_t iLen = _017ItemIDListGetLen(lpiidl);

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            m_pmalloc->Alloc(iLen + 2);

         memcpy(lpiidlRet, lpiidl, iLen);
         ((LPBYTE)lpiidlRet)[iLen] = 0;
         ((LPBYTE)lpiidlRet)[iLen + 1] = 0;

         return lpiidlRet;

      }


      int32_t _017ItemIDListIHash(LPITEMIDLIST lpiidl)
      {
         if (lpiidl == NULL)
            return 0;

         int32_t iLen = _017ItemIDListGetLen(lpiidl);


         int32_t iHash = 0;
         int32_t iRemain = iLen;
         uint32_t * lpdw = (uint32_t *)lpiidl;
         while (iRemain >= 4)
         {
            iHash += *lpdw;
            lpdw++;
            iRemain -= 4;
         }
         LPBYTE lpb = (LPBYTE)lpdw;
         while (iRemain > 0)
         {
            iHash += *lpb;
            lpb++;
            iRemain--;
         }
         return iHash;
      }


      LPITEMIDLIST windows::_017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl)
      {

         int32_t iLenParent = _017ItemIDListGetLen(lpiidlParent);
         int32_t iLen = _017ItemIDListGetLen(lpiidl);

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            m_pmalloc->Alloc(iLenParent + iLen + 2);

         memcpy(lpiidlRet, lpiidlParent, iLenParent);
         memcpy(&(((LPBYTE)lpiidlRet)[iLenParent]), lpiidl, iLen);
         ((LPBYTE)lpiidlRet)[iLenParent + iLen] = 0;
         ((LPBYTE)lpiidlRet)[iLenParent + iLen + 1] = 0;

         return lpiidlRet;

      }

      LPITEMIDLIST windows::_017ItemIDListGetLast(LPITEMIDLIST lpiidl)
      {

         if (lpiidl == NULL)
            return NULL;


         LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
         LPSHITEMID  lpshiidLast = lpshiid;
         USHORT cb;

         while (true)
         {
            cb = *((USHORT *)lpshiid);
            if (cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);
         }
         int32_t iCount = *((USHORT *)lpshiidLast);

         if (iCount == 0)
            return NULL;

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            m_pmalloc->Alloc(iCount + 2);

         memcpy(lpiidlRet, lpshiidLast, iCount);

         *((USHORT *)&(((LPBYTE)lpiidlRet)[iCount])) = 0;

         return lpiidlRet;

      }

      LPITEMIDLIST windows::_017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl)
      {
         if (lpiidl == NULL)
            return NULL;

         HRESULT hr;

         LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
         LPSHITEMID  lpshiidLast = lpshiid;
         USHORT cb;

         while (true)
         {
            cb = *((USHORT *)lpshiid);
            if (cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);
         }
         ::count iCount = ((LPBYTE)lpshiidLast) - ((LPBYTE)lpiidl);

         if (iCount == 0)
            return NULL;

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            m_pmalloc->Alloc(iCount + 2);

         memcpy(lpiidlRet, lpiidl, iCount);

         *((USHORT *)&(((LPBYTE)lpiidlRet)[iCount])) = 0;

         return lpiidlRet;
      }

      bool windows::_017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2)
      {
         if (lpiidl1 == NULL && lpiidl2 == NULL)
         {
            return true;
         }
         if (lpiidl1 == NULL || lpiidl2 == NULL)
         {
            return false;
         }


         LPSHITEMID  lpshiid1 = (LPSHITEMID)lpiidl1;
         LPSHITEMID  lpshiid2 = (LPSHITEMID)lpiidl2;
         USHORT cb1;
         USHORT cb2;

         while (true)
         {
            cb1 = *((USHORT *)lpshiid1);
            cb2 = *((USHORT *)lpshiid2);
            if (cb1 == 0 && cb2 == 0)
            {
               return true;
            }
            if (cb1 == 0 || cb2 == 0)
            {
               return false;
            }
            if (cb1 != cb2)
               return false;
            if (memcmp(lpshiid1, lpshiid2, cb1) != 0)
               return false;
            lpshiid1 = (LPSHITEMID)(((LPBYTE)lpshiid1) + cb1);
            lpshiid2 = (LPSHITEMID)(((LPBYTE)lpshiid2) + cb2);
         }
      }

      void windows::_017ItemIDListParsePath(oswindow window, LPITEMIDLIST * lpiidl, const char * lpcsz)
      {
         HRESULT hr;

         try
         {
            hr = m_pfolderDesktop->ParseDisplayName(
               window,
               NULL,
               ::str::international::utf8_to_unicode(lpcsz),
               //&ulEaten,
               NULL,
               lpiidl,
               //&dwAttrib);
               NULL);
         }
         catch (...)
         {
         }

      }

      void windows::_017ItemIDListFree(LPITEMIDLIST lpiidl)
      {

         m_pmalloc->Free(lpiidl);


      }

      bool windows::_017HasSubFolder(::aura::application * papp, LPITEMIDLIST lpiidl, const char * lpcszExtra)
      {

         WCHAR szPath[_MAX_PATH * 10];

         SHGetPathFromIDListW(lpiidl, szPath);

         e_folder efolder = get_folder_type(papp, szPath);

         if (efolder == folder_none)
         {

            return false;

         }
         else if (efolder == folder_zip)
         {

            string wstrPath;

            ::str::international::unicode_to_utf8(wstrPath, szPath);

            string wstrExtra(lpcszExtra);

            if (wstrExtra.get_length() > 0)
            {
               wstrPath += ":" + wstrExtra;
            }

            return zip::Util().HasSubFolder(papp, wstrPath);

         }
         else
         {

            ::file::listing listing(papp);

            listing.ls(::str::international::unicode_to_utf8(szPath));

            for (int32_t i = 0; i < listing.get_size(); i++)
            {

               efolder = get_folder_type(papp, listing[i]);

               if (efolder != folder_none)
                  return true;

            }

            return false;

         }

      }


      int32_t windows::get_image_by_extension(oswindow oswindow, image_key & key, COLORREF crBk)
      {

#ifdef WINDOWSEX

         return get_foo_image(oswindow, key, crBk);

#else

         return 0x80000000;

#endif // WINDOWSEX

      }


      int32_t windows::get_image( oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, COLORREF crBk)
      {

         ::windows::comptr < IShellFolder> lpsf;

         lpsf = _017GetShellParentFolder(lpiidlAbsolute);

         if (lpsf.is_null())
         {

            return 0x80000000;

         }

         int32_t iType;
         switch (imagekey.m_eicon)
         {
         case icon_normal:
            iType = 0;
            break;
         case icon_open:
            iType = GIL_OPENICON;
            break;
         default:
            // unexpected icon type
            ASSERT(FALSE);
            return 0x80000000;
         }


         //WCHAR szFilePath[_MAX_PATH * 10];
         //wcscpy(szFilePath, wstrParentPath);
         string strFilePath(imagekey.m_pszPath);

         //   WCHAR wszFilePath[_MAX_PATH * 10];
         //SHGetPathFromIDListW(
         //   lpiidlAbsolute,
         //   szFilePath);

         CHAR szPath[_MAX_PATH * 6];
         WCHAR wszPath[_MAX_PATH * 6];
         string strPath;
         int32_t iImage = 0x80000000;

         const char * pszPathParam = imagekey.m_pszPath;

         HICON hicon16 = NULL;
         HICON hicon48 = NULL;
         HRESULT hrIconLocation;
         HRESULT hrExtract;
         //         image_key imagekey;
         string strExpandEnv;

         //imagekey.m_pszShellThemePrefix = (char *) m_strShellThemePrefix.c_str();
         //imagekey.m_pszPath = strPath;
         //imagekey.m_pszExtension = &strPath[];

         string strPathEx(strFilePath);
         string strExtra;

         ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

         if (strExtra.get_length() > 0)
         {
            strPathEx += ":" + strExtra;
         }

         wstring wstrPath;
         int32_t iIcon = 0x80000000;
         //UINT uiFlags = 0;

         SHFILEINFOW shfi16;
         SHFILEINFOW shfi48;

         ::windows::comptr < IExtractIconW > lpiextracticon;
         ::windows::comptr < IShellIconOverlayIdentifier > lpioverlay;
         ::windows::comptr < IExtractImage > lpiextractimage;

         /*e_folder efolder = get_folder_type(wszFilePath);
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
         
         UINT uiExtractIconLocationFlags = 0;

         if (SUCCEEDED(lpsf->GetUIObjectOf(
            oswindow,
            1,
            (LPCITEMIDLIST *)&lpiidlChild,
            IID_IExtractIconW,
            NULL,
            lpiextracticon)))
         {
            if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
               iType,
               wszPath,
               sizeof(wszPath) / sizeof(wszPath[0]),
               &iIcon,
               &uiExtractIconLocationFlags)))
            {
               if (wcscmp(wszPath, L"*") == 0)
               {
                  strsize iFind = strFilePath.reverse_find('.');

                  imagekey.m_iIcon = 0x80000000;
                  imagekey.m_pszExtension = (char*)&strFilePath[iFind];
                  imagekey.m_pszPath = "";
               }
               else
               {

                  strFilePath = wszPath;

                  strFilePath = expand_env(strFilePath);

                  imagekey.set_path(strFilePath);

                  if (::str::ends_ci(strFilePath, ".lnk"))
                  {

                     string strTarget;

                     string strFolder;

                     string strParams;

                     //if(System.file().resolve_link(strTarget, strFilePath, System.ui_from_handle))
                     if (System.file().resolve_link(strTarget, strFolder, strParams, strFilePath, NULL))
                     {

                        if (m_straThemeableIconName.get_count() > 0)
                        {

                           index i = m_straThemeableIconName.pred_find_first(
                              [=](auto & str)
                           {
                              return ::str::ends_ci(imagekey.m_pszPath, str);
                           }
                           );

                           if (i >= 0)
                           {

                              string str = m_straThemeableIconName[i];

                              if (::str::ends_ci(imagekey.m_pszPath, str))
                              {

                                 strExpandEnv = imagekey.m_pszPath;
                                 strExpandEnv.replace_ci(str, m_strShellThemePrefix + str);
                                 imagekey.m_pszPath = (char*)strExpandEnv.c_str();

                              }

                           }

                        }

                     }

                  }

                  imagekey.m_iIcon = iIcon;

                  imagekey.m_pszExtension = "";

               }
            }
         }
         else if (SUCCEEDED(lpsf->GetUIObjectOf(
            oswindow,
            1,
            (LPCITEMIDLIST *)&lpiidlChild,
            IID_IShellIconOverlayIdentifier,
            NULL,
            lpioverlay)))
         {
            int iIndex = 0;
            DWORD dwFlags = 0;
            if (SUCCEEDED(hrIconLocation = lpioverlay->GetOverlayInfo(
               wszPath,
               sizeof(wszPath),
               &iIndex,
               &dwFlags)))
            {
               if (*wszPath == L'*' && wszPath[1] == '\0')
               {
                  strsize iFind = strFilePath.reverse_find('.');

                  imagekey.m_iIcon = 0x80000000;
                  imagekey.m_pszExtension = (char *)&strFilePath.Mid(iFind);
                  imagekey.m_pszPath = "";
               }
               else
               {
                  strFilePath = expand_env(szPath);
                  imagekey.m_pszPath = (char *)strFilePath.c_str();
                  imagekey.m_iIcon = iIcon;
                  imagekey.m_pszExtension = "";
               }
            }
         }
         else if (SUCCEEDED(lpsf->GetUIObjectOf(
            oswindow,
            1,
            (LPCITEMIDLIST *)&lpiidlChild,
            IID_IExtractImage,
            NULL,
            lpiextractimage)))
         {
            SIZE s;
            s.cx = 48;
            s.cy = 48;
            DWORD dwDepth = 32;
            DWORD dwFlags = 0;
            if (SUCCEEDED(hrIconLocation = lpiextractimage->GetLocation(
               wszPath,
               sizeof(wszPath),
               NULL,
               &s,
               dwDepth,
               &dwFlags)))
            {
               string strP = wszPath;
               if (strcmp(strP, "*") == 0)
               {
                  strsize iFind = strFilePath.reverse_find('.');

                  imagekey.m_iIcon = 0x80000000;
                  imagekey.m_pszExtension = (char *)&strFilePath.Mid(iFind);
                  imagekey.m_pszPath = "";
               }
               else
               {
                  //imagekey.m_strPath = expand_env(strP);
                  strFilePath = expand_env(strP);
                  imagekey.m_pszPath = (char *)strFilePath.c_str();
                  imagekey.m_iIcon = iIcon;
                  imagekey.m_pszExtension = "";
               }
            }
         }
         else
         {

            imagekey.m_pszPath = (char *) strFilePath.c_str();
            imagekey.m_iIcon = iIcon;
            imagekey.m_pszExtension = "";

         }
         if (imagekey.m_iIcon == 0x80000000)
         {

            string strTarget;

            string strFolder;

            string strParams;

            //if(System.file().resolve_link(strTarget, strFilePath, System.ui_from_handle))
            if (System.file().resolve_link(strTarget, strFolder, strParams, strFilePath, NULL))
            {

               wstring wstr = ::str::international::utf8_to_unicode(strTarget);

               imagekey.set_path(strTarget);

               return get_image(oswindow, imagekey, NULL, crBk);

               //LPITEMIDLIST lpiidl2 = NULL;

               //uint32_t dwAttrib = 0;

               ////            unsigned long ulEaten;

               //HRESULT hr;

               //try
               //{
               //   hr = SHParseDisplayName(
               //      wstr,
               //      NULL,
               //      &lpiidl2,
               //      0,
               //      NULL);
               //}
               //catch (...)
               //{
               //}

               //LPITEMIDLIST lpiidlChild2 = _017ItemIDListGetLast(lpiidl2);

               //LPITEMIDLIST lpiidlParent2 = _017ItemIDListGetFolderParent(lpiidl2);

               //int32_t iImage = get_image(
               //   oswindow,
               //   imagekey,
               //   lpiidl2,
               //   lpiidlChild2,
               //   NULL,
               //   crBk);

               //_017ItemIDListFree(lpiidlParent2);

               //_017ItemIDListFree(lpiidlChild2);

               //return iImage;

            }
         }
         if (!m_imagemap.Lookup(imagekey, iImage))
         {

            if (imagekey.m_iIcon == 0x80000000)
            {

               if (wcslen(wszPath) > 0 && wcscmp(wszPath, L"*") != 0)
               {

                  ::file::path p = wszPath;

                  string strExtension = p.extension();

                  if (m_strShellThemePrefix.has_char())
                  {

                     image_key imagekey;

                     string strFooPath = m_strShellThemePrefix + "foo." + strExtension;

                     imagekey.m_pszPath = (char *)(const char *)strFooPath;
                     imagekey.m_iIcon = 0;
                     imagekey.m_pszExtension = "";

                     if (m_imagemap.Lookup(imagekey, iImage))
                        return iImage;

                     ::file::path p = ::file::path(strFooPath);

                     string strIcon;

                     //if (p.title().CompareNoCase("dark") == 0)
                     //{

                     strIcon = ::dir::system() / "config/windows/app_theme" / m_strShellThemePrefix + strExtension + ".ico";

                     //}
                     //else if (p.title().CompareNoCase("blue") == 0)
                     //{
                     // strIcon = Application.dir().matter("visual_studio/blue_solution.ico");
                     //}
                     //else
                     //{
                     // strIcon = Application.dir().matter("visual_studio/lite_solution.ico");
                     //}
                     int iImage = m_pil16->add_icon_os_data((HICON)LoadImage(NULL, strIcon, IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
                     m_pil48->add_icon_os_data((HICON)LoadImage(NULL, strIcon, IMAGE_ICON, 48, 48, LR_LOADFROMFILE));
                     m_pil48Hover->add_icon_os_data((HICON)LoadImage(NULL, strIcon, IMAGE_ICON, 48, 48, LR_LOADFROMFILE));
                     m_imagemap.set_at(imagekey, iImage);
                     return iImage;
                  }

                  try
                  {

                     hicon16 = NULL;

                     strPath.Truncate(0);

                     strPath.free_extra();

                     strPath = imagekey.m_pszPath;

                     HICON hicon32 = NULL;

                     SHGetFileInfoW(
                        wszPath,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi16,
                        sizeof(shfi16),
                        SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_OVERLAYINDEX
                        | SHGFI_SMALLICON);
                     hicon16 = shfi16.hIcon;
                     SHGetFileInfoW(
                        wszPath,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi48,
                        sizeof(shfi48),
                        SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_OVERLAYINDEX
                        | SHGFI_LARGEICON);

                     hicon48 = shfi48.hIcon;

                     if (hicon16 != NULL && hicon48 != NULL)
                     {

                        iImage = m_pil16->add_icon_os_data(hicon16);

                        synch_lock sl1(m_pil48Hover->m_pmutex);

                        synch_lock sl2(m_pil48->m_pmutex);

                        if (crBk == 0)
                        {

                           System.visual().imaging().Createcolor_blend_ImageList(
                              m_pil48,
                              m_pil48Hover,
                              RGB(255, 255, 240),
                              64);

                        }
                        else
                        {

                           *m_pil48 = *m_pil48Hover;

                        }

                        m_pil48Hover->add_icon_os_data(hicon48);

                        if (crBk == 0)
                        {

                           System.visual().imaging().Createcolor_blend_ImageList(
                              m_pil48,
                              m_pil48Hover,
                              RGB(255, 255, 240),
                              64);

                        }
                        else
                        {
                           *m_pil48 = *m_pil48Hover;
                        }

                        m_pil48->add_icon_os_data(hicon48);

                        m_imagemap.set_at(imagekey, iImage);

                     }

                  }
                  catch (...)
                  {

                  }

               }

               if (iImage < 0)
               {

                  iImage = get_foo_image(oswindow, imagekey, crBk);

               }

            }
            else
            {
               try
               {
                  hicon16 = NULL;
                  //strPath.Truncate(0);
                  //strPath.free_extra();
                  //strPath = imagekey.m_pszPath;
                  //iIcon = imagekey.m_iIcon;
                  bool bExtract = false;
                  //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
                  //LPTSTR lpsz = (LPTSTR) ::GlobalLock(hglobal);
                  //strcpy(lpsz, strPath);
                  try
                  {
                     if ((hrIconLocation == S_OK && !(uiExtractIconLocationFlags & GIL_NOTFILENAME))
                        && lpiextracticon.is_set()
                        && (NOERROR == (hrExtract = lpiextracticon->Extract(
                           wszPath,
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
                        synch_lock sl1(m_pil48Hover->m_pmutex);
                        synch_lock sl2(m_pil48->m_pmutex);

                        {
                           m_pil48Hover->add_icon_os_data(hicon48);
                        }

                        if (crBk == 0)
                        {


                           System.visual().imaging().Createcolor_blend_ImageList(
                              m_pil48,
                              m_pil48Hover,
                              RGB(255, 255, 240),
                              64);

                        }
                        else
                        {
                           *m_pil48 = *m_pil48Hover;

                        }
                        m_imagemap.set_at(imagekey, iImage);
                     }
                  }
                  catch (...)
                  {
                  }
                  //::GlobalUnlock(hglobal);
                  //::GlobalFree(hglobal);
                  if (!bExtract)
                  {
                     HICON hicon32 = NULL;
                     if (strlen(pszPathParam) > 0)
                     {
                        SHGetFileInfoW(
                           wstring(pszPathParam),
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi16,
                           sizeof(shfi16),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_SMALLICON);
                        hicon16 = shfi16.hIcon;
                        SHGetFileInfoW(
                           wstring(pszPathParam),
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi48,
                           sizeof(shfi48),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_LARGEICON);
                        hicon48 = shfi48.hIcon;
                        iImage = m_pil16->add_icon_os_data(hicon16);

                        synch_lock sl1(m_pil48Hover->m_pmutex);
                        synch_lock sl2(m_pil48->m_pmutex);

                        if (m_pilExtraLarge.is_set())
                        {

                           HICON hicon48;

                           m_pilExtraLarge->GetIcon(shfi48.iIcon, ILD_TRANSPARENT, &hicon48);

                           if (hicon48 == NULL)
                           {

                              m_pil48Hover->add_icon_os_data(shfi48.hIcon);

                           }
                           else
                           {
                              m_pil48Hover->add_icon_os_data(hicon48);
                           }

                        }
                        else
                        {
                           m_pil48Hover->add_icon_os_data(shfi48.hIcon);
                        }
                        if (crBk == 0)
                        {
                           System.visual().imaging().Createcolor_blend_ImageList(
                              m_pil48,
                              m_pil48Hover,
                              RGB(255, 255, 240),
                              64);

                        }
                        else
                        {
                           *m_pil48 = *m_pil48Hover;
                        }

                     }
                     else
                     {
                        ExtractIconEx(
                           imagekey.m_pszPath,
                           imagekey.m_iIcon,
                           &hicon32,
                           &hicon16,
                           1);


                     }

                     if (hicon48 == NULL && ::str::ends_ci(imagekey.m_pszPath, ".ico"))
                     {

                        hicon48 = (HICON)LoadImage(NULL, imagekey.m_pszPath, IMAGE_ICON, 48, 48, LR_LOADFROMFILE);

                     }
                     if (hicon48 == NULL)
                     {

                        hicon48 = ExtractResourceIcon(imagekey.m_pszPath, 48, 48, imagekey.m_iIcon);

                     }

                     if (hicon48 == NULL)
                     {

                        if (hicon32 != NULL)
                        {

                           hicon48 = hicon32;
                        }
                        else
                        {

                           hicon48 = hicon16;

                        }

                     }

                     if (hicon16 == NULL)
                     {
                        SHGetFileInfoW(
                           L"foo",
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi16,
                           sizeof(shfi16),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_SMALLICON);
                        hicon16 = shfi16.hIcon;
                     }
                     if (hicon48 == NULL)
                     {
                        SHGetFileInfoW(
                           L"foo",
                           FILE_ATTRIBUTE_NORMAL,
                           &shfi48,
                           sizeof(shfi48),
                           SHGFI_USEFILEATTRIBUTES
                           | SHGFI_ICON
                           | SHGFI_LARGEICON);
                        hicon48 = shfi48.hIcon;
                     }
                     if (hicon48 == NULL)
                     {

                        if (m_pilExtraLarge.is_set())
                        {

                           m_pilExtraLarge->GetIcon(shfi48.iIcon, ILD_TRANSPARENT, &hicon48);

                        }

                     }
                     iImage = m_pil16->add_icon_os_data(hicon16);

                     m_pil48Hover->add_icon_os_data(hicon48);

                     if (crBk == 0)
                     {

                        System.visual().imaging().Createcolor_blend_ImageList(
                           m_pil48,
                           m_pil48Hover,
                           RGB(255, 255, 240),
                           64);

                     }
                     else
                     {
                        *m_pil48 = *m_pil48Hover;
                     }
                     m_imagemap.set_at(imagekey, iImage);
                  }
               }
               catch (...)
               {
               }
            }
         }

         return iImage;

      }


      int32_t windows::get_foo_image(oswindow oswindow, image_key imagekey, COLORREF crBk)
      {

         int32_t iImage;

         SHFILEINFO shfi16;

         SHFILEINFO shfi48;

         //image_key imagekey;

         //imagekey.m_iIcon           = 0;

         //imagekey.set_path(m_pszPath         = "foo";

         //if(strExtension.has_char())
         //{
         //   imagekey.m_pszExtension = (char *)strExtension.c_str();
         //   
         //}
         //else
         //{
         //   imagekey.m_pszExtension = "";
         //}

         //if (bFolder)
         //{

         //   imagekey.m_eattribute = FileAttributeDirectory;

         //}
         //else
         //{

         //   imagekey.m_eattribute = FileAttributeNormal;

         //}

         string strFilePath;

         //imagekey.m_iIcon = 0;
         //imagekey.m_pszPath= "foo";

         imagekey.m_pszShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

         if (m_imagemap.Lookup(imagekey, iImage))
            return iImage;

         if (imagekey.m_eattribute.is_signalized(file_attribute_directory))
         {
            //imagekey.m_eattribute = FileAttributeDirectory;
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
            //imagekey.m_eattribute = FileAttributeNormal;
            strFilePath = "foo." + string(imagekey.m_pszExtension);
            SHGetFileInfo(
               strFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi16,
               sizeof(shfi16),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_SMALLICON);
            SHGetFileInfo(
               strFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi48,
               sizeof(shfi48),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_LARGEICON);
         }

         iImage = m_pil16->add_icon_os_data(shfi16.hIcon);

         if (m_pilExtraLarge.is_set())
         {

            HICON hicon48;

            m_pilExtraLarge->GetIcon(shfi48.iIcon, ILD_TRANSPARENT, &hicon48);

            if (hicon48 == NULL)
            {

               m_pil48Hover->add_icon_os_data(shfi48.hIcon);

            }
            else
            {

               m_pil48Hover->add_icon_os_data(hicon48);

            }

         }
         else
         {

            m_pil48Hover->add_icon_os_data(shfi48.hIcon);

         }

         synch_lock sl1(m_pil48Hover->m_pmutex);
         synch_lock sl2(m_pil48->m_pmutex);

         if (crBk == 0)
         {
            System.visual().imaging().Createcolor_blend_ImageList(
               m_pil48,
               m_pil48Hover,
               RGB(255, 255, 240),
               64);

         }
         else
         {
            *m_pil48 = *m_pil48Hover;
         }

         m_imagemap.set_at(imagekey, iImage);

         return iImage;

      }





      bool windows::get_icon(
         oswindow oswindow,
         IShellFolder * lpsf,
         LPITEMIDLIST lpiidlAbsolute,
         LPITEMIDLIST lpiidlChild,
         const unichar * lpcszExtra,
         e_icon eicon,
         HICON * phicon16,
         HICON * phicon48)
      {

         single_lock sl(m_pmutex, true);

         if (lpsf == NULL)
            return false;
         int32_t iType;
         switch (eicon)
         {
         case icon_normal:
            iType = 0;
            break;
         case icon_open:
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
         image_key imagekey;


         string strPathEx(strFilePath);
         string strExtra;

         ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

         if (strExtra.get_length() > 0)
         {
            strPathEx += ":" + strExtra;
         }



         int32_t iIcon = 0x80000000;
         UINT uiFlags = 0;

         SHFILEINFO shfi16;
         SHFILEINFO shfi48;

         ::windows::comptr< IExtractIcon > lpiextracticon;

         if (SUCCEEDED(lpsf->GetUIObjectOf(
            oswindow,
            1,
            (LPCITEMIDLIST *)&lpiidlChild,
            IID_IExtractIcon,
            NULL,
            lpiextracticon)))
         {
            if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
               iType,
               szPath,
               sizeof(szPath),
               &iIcon,
               &uiFlags)))
            {
               strPath = szPath;
               if (strPath == "*")
               {
                  strsize iFind = strFilePath.reverse_find('.');

                  imagekey.m_iIcon = 0x80000000;
                  imagekey.m_pszExtension = (char*)&strFilePath[iFind];
                  imagekey.m_pszPath = "";
               }
               else
               {
                  imagekey.m_pszPath = (char *)strPath.c_str();
                  imagekey.m_iIcon = iIcon;
                  imagekey.m_pszExtension = NULL;
               }
            }
         }
         if (Application.dir().is(::str::international::unicode_to_utf8(szFilePath)))
         {
            if (imagekey.m_iIcon == 0x80000000)
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
               strPath = "foo" + string(imagekey.m_pszExtension);
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
               strPath = imagekey.m_pszPath;
               iIcon = imagekey.m_iIcon;
               bool bExtract = false;
               //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
               //LPTSTR lpsz = (LPTSTR) ::GlobalLock(hglobal);
               //strcpy(lpsz, strPath);
               try
               {
                  if ((hrIconLocation == S_OK && !(uiFlags & GIL_NOTFILENAME))
                     && lpiextracticon.is_null()
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
               catch (...)
               {
               }
               //::GlobalUnlock(hglobal);
               //::GlobalFree(hglobal);
               if (!bExtract)
               {
                  if (strlen(imagekey.m_pszPath) <= 0)
                  {
                     SHGetFileInfo(
                        (const char *)lpiidlAbsolute,
                        FILE_ATTRIBUTE_NORMAL,
                        &shfi16,
                        sizeof(shfi16),
                        SHGFI_PIDL
                        | SHGFI_USEFILEATTRIBUTES
                        | SHGFI_ICON
                        | SHGFI_SMALLICON);
                     hicon16 = shfi16.hIcon;
                     SHGetFileInfo(
                        (const char *)lpiidlAbsolute,
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
                        imagekey.m_pszPath,
                        imagekey.m_iIcon,
                        &hicon48,
                        &hicon16,
                        1);
                  }
                  if (hicon16 == NULL)
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
                  if (hicon48 == NULL)
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
            catch (...)
            {
            }
         }

         return true;

      }



      int32_t windows::get_image(oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, COLORREF crBk)
      {


         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(lpiidlAbsolute);
         int32_t iImage = get_image(oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra,
            crBk);


         _017ItemIDListFree(lpiidlChild);

         return iImage;
      }





      bool windows::get_icon(oswindow oswindow, const char * psz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
      {

         single_lock sl(m_pmutex, true);


         LPITEMIDLIST lpiidlAbsolute;
         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, psz);
         bool bGet = get_icon(oswindow, lpiidlAbsolute, lpcszExtra, eicon, phicon16, phicon48);
         _017ItemIDListFree(lpiidlAbsolute);
         return bGet;

      }

      bool windows::get_icon(oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
      {

         single_lock sl(m_pmutex, true);

         wstring wstr;

         ::windows::comptr < IShellFolder > lpsf = _017GetShellFolder(wstr, lpiidlAbsolute);


         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(lpiidlAbsolute);
         bool bGet = get_icon(
            oswindow,
            lpsf,
            lpiidlAbsolute,
            lpiidlChild,
            lpcszExtra,
            eicon,
            phicon16,
            phicon48);

         _017ItemIDListFree(lpiidlChild);

         return bGet;
      }



      index windows::GetCSIDL(LPITEMIDLIST lpiidl)
      {
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

         while (*pcsidl != -1)
         {
            if (SUCCEEDED(SHGetSpecialFolderLocation(
               NULL,
               *pcsidl,
               &ppidl)))
            {
               if (_017ItemIDListIsEqual(ppidl, lpiidl))
               {
                  m_pmalloc->Free(ppidl);
                  break;
               }
               m_pmalloc->Free(ppidl);
            }
            pcsidl++;
         }

         return *pcsidl;


      }


      index windows::GetCSIDLSort(index iCsidl)
      {
         switch (iCsidl)
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


      void windows::GetAscendants(LPITEMIDLIST lpiidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)
      {

         if (lpiidl == NULL)
            return;

         for (;;)
         {
            lpiidl = _017ItemIDListGetFolderParent(lpiidl);
            if (lpiidl == NULL)
               break;
            lpiidla.add(lpiidl);
         }

      }


      void windows::Free(array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)
      {

         for (int32_t i = 0; i < lpiidla.get_size(); i++)
         {

            m_pmalloc->Free(lpiidla[i]);

         }

         lpiidla.remove_all();

      }


      e_folder windows::get_folder_type(::aura::application * papp, const char * lpcsz)
      {

         return get_folder_type(papp, ::str::international::utf8_to_unicode(lpcsz));

      }


      e_folder windows::get_folder_type(::aura::application * papp, const unichar * lpcszPath)
      {

         string strPath;

         ::str::international::unicode_to_utf8(strPath, lpcszPath);

         if (dir::is(strPath))
         {
            return folder_file_system;
         }
         else if (zip::Util().IsUnzipable(papp, strPath))
         {
            return folder_zip;
         }
         else
         {
            return folder_none;
         }

      }

      //int windows::run()
      //{

      //   // These images are the Shell standard extra-large icon size. This is typically 48x48, but the size can be customized by the user.

      //   return 0;

      //   while (this->get_thread_run())
      //   {

      //      if (!do_call())
      //      {

      //         Sleep(100);

      //      }

      //      try
      //      {

      //         {

      //         restart:

      //            {

      //               synch_lock sl(m_pmutex);

      //               for (auto & folder : m_mapFolder)
      //               {

      //                  if (get_tick_count() - folder.m_element2.m_dwStart > 30000)
      //                  {

      //                     m_mapFolder.remove_key(folder.m_element1);

      //                     goto restart;

      //                  }

      //               }

      //            }

      //         }

      //         //int i = 20;

      //         //while (get_run_thread() && i >= 0)
      //         //{

      //         //   Sleep(500);

      //         //   i--;

      //         //}


      //      }
      //      catch (...)
      //      {


      //      }


      //   }


      //   return 0;

      //}

      //bool windows::do_call()
      //{

      //   if (m_callCurrent.m_bCall)
      //   {

      //      m_callCurrent.m_iImage = get_image(
      //         m_callCurrent.m_oswindow,
      //         m_callCurrent.m_imagekey,
      //         m_callCurrent.m_lpcszExtra,
      //         m_callCurrent.m_crBk);
      //      m_callCurrent.m_bCall = false;
      //      m_eventReady.SetEvent();

      //      return true;

      //   }

      //   return false;

      //}

      int32_t windows::get_image(oswindow oswindow, image_key imagekey, const unichar * lpcszExtra, COLORREF crBk)
      {

         single_lock sl(m_pmutex, true);

         int32_t iImage = 0x80000000;

         if (::str::ends_ci(imagekey.m_pszPath, ".core"))
         {
            string str = Application.file().as_string(imagekey.m_pszPath);
            if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
            {
               str.trim();
               HICON hicon16 = (HICON) ::LoadImage(NULL, Application.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
               HICON hicon48 = (HICON) ::LoadImage(NULL, Application.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
               synch_lock sl1(m_pil48Hover->m_pmutex);
               synch_lock sl2(m_pil48->m_pmutex);
               iImage = m_pil16->add_icon_os_data(hicon16);
               m_pil48Hover->add_icon_os_data(hicon48);

               if (crBk == 0)
               {
                  System.visual().imaging().Createcolor_blend_ImageList(
                     m_pil48,
                     m_pil48Hover,
                     RGB(255, 255, 240),
                     64);
               }
               else
               {
                  *m_pil48 = *m_pil48Hover;
               }

            }
            return iImage;
         }
         // try to find "uifs:// http:// ftp:// like addresses"
         // then should show icon by extension or if is folder
         strsize iFind = imagekey.m_pszPath == NULL ? -1: ::str::find_ci("://", imagekey.m_pszPath);
         strsize iFind2 = imagekey.m_pszPath == NULL ? -1 : ::str::find_ci(":", imagekey.m_pszPath);
         if (iFind >= 0 || iFind2 >= 2)
         {
            string strProtocol = string(imagekey.m_pszPath).Left(MAX(iFind, iFind2));
            int32_t i = 0;

            while (i < strProtocol.get_length() && isalnum_dup(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.get_length())
            {

               // heuristically valid protocol
               return get_image_by_extension(oswindow, imagekey, crBk);

            }

            if (imagekey.m_eattribute.is_signalized(file_attribute_directory))
            {

               return get_image_by_extension(oswindow, imagekey, crBk);

            }

         }

         //#ifdef WINDOWSEX

         string strExtension;

         if (::str::ends_ci(imagekey.m_pszPath, ".sln"))
         {
            output_debug_string("test");
         }
#ifdef MACOS

         ::draw2d::dib_sp dib48(allocer());

         dib48->create(48, 48);

         dib48->Fill(0);

         if (macos_get_file_image(dib48, strPath))
         {
            ::draw2d::dib_sp dib16(allocer());

            dib16->create(16, 16);

            dib16->Fill(0);

            synch_lock sl1(m_pil48Hover->m_pmutex);
            synch_lock sl2(m_pil48->m_pmutex);
            if (macos_get_file_image(dib16, strPath))
            {
               iImage = m_pil16->add_dib(dib16, 0, 0);
               m_pil48Hover->add_dib(dib48, 0, 0);


            }
            else
            {
               dib16->get_graphics()->SetStretchBltMode(HALFTONE);

               dib16->get_graphics()->StretchBlt(0, 0, 48, 48, dib48->get_graphics(), 0, 0, dib48->m_size.cx, dib48->m_size.cy);

               iImage = m_pil16->add_dib(dib16, 0, 0);
               m_pil48Hover->add_dib(dib48, 0, 0);

            }


            if (crBk == 0)
            {
               System.visual().imaging().Createcolor_blend_ImageList(
                  m_pil48,
                  m_pil48Hover,
                  RGB(255, 255, 240),
                  64);
            }
            else
            {
               *m_pil48 = *m_pil48Hover;
            }

            return iImage;

         }
#endif

#ifdef LINUX

         string strIcon48;

         string strIcon16;

         if (::str::ends_ci(string(strPath), ".desktop"))
         {

            string str = Application.file().as_string(strPath);

            stringa stra;

            stra.add_lines(str);

            stra.filter_begins_ci("icon=");

            if (stra.get_size() <= 0)
            {

               return -1;

            }

            string strIcon = stra[0];

            ::str::begins_eat_ci(strIcon, "icon=");

            strIcon48 = strIcon;

            strIcon16 = strIcon;

         }
         else
         {

            strIcon48 = linux_get_file_icon_path(strPath, 48);

            strIcon16 = linux_get_file_icon_path(strPath, 16);

         }

         if (strIcon48.has_char())
         {

            ::visual::dib_sp dib1(allocer());

            if (!dib1.load_from_file(strIcon16))
            {

               return -1;

            }

            ::visual::dib_sp dib(allocer());

            if (!dib.load_from_file(strIcon48))
            {

               return -1;

            }

            ::draw2d::dib_sp dib16(allocer());

            if (!dib16->create(16, 16))
            {

               return -1;

            }

            ::draw2d::dib_sp dib48(allocer());

            if (!dib48->create(48, 48))
            {

               return -1;

            }

            dib16->get_graphics()->SetStretchBltMode(HALFTONE);

            dib16->get_graphics()->StretchBlt(0, 0, 16, 16, dib1->get_graphics(), 0, 0, dib1->m_size.cx, dib1->m_size.cy);

            dib48->get_graphics()->SetStretchBltMode(HALFTONE);

            dib48->get_graphics()->StretchBlt(0, 0, 48, 48, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy);

            synch_lock sl1(m_pil48Hover->m_pmutex);

            synch_lock sl2(m_pil48->m_pmutex);

            iImage = m_pil16->add_dib(dib16, 0, 0);

            m_pil48Hover->add_dib(dib48, 0, 0);

            if (crBk == 0)
            {

               System.visual().imaging().Createcolor_blend_ImageList(m_pil48, m_pil48Hover, RGB(255, 255, 240), 64);

            }
            else
            {

               *m_pil48 = *m_pil48Hover;

            }

            return iImage;

         }

#endif

         string str(imagekey.m_pszPath);

#ifdef WINDOWSEX

         if (str == "foo")
         {

            return get_foo_image(oswindow, imagekey, crBk);

         }

         if (::str::begins_eat(str, "foo."))
         {

            return get_foo_image(oswindow, imagekey, crBk);

         }

         LPITEMIDLIST lpiidlAbsolute;

         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, imagekey.m_pszPath);

         iImage = get_image(oswindow, imagekey, lpiidlAbsolute, lpcszExtra, crBk);

         _017ItemIDListFree(lpiidlAbsolute);

#elif defined(LINUX)


         iImage = GetImageByExtension(oswindow, strPath, eicon, bFolder, crBk);

#elif defined(MACOS)

         iImage = -1;

#else

         iImage = GetImageByExtension(oswindow, strPath, eicon, bFolder, crBk);

#endif

         //#endif

         return iImage;

      }
      int32_t _017ItemIDListGetLen(LPITEMIDLIST lpiidl)
      {
         if (lpiidl == NULL)
            return 0;
         LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
         LPSHITEMID  lpshiidLast = NULL;
         USHORT cb;
         int32_t iLen = 0;
         while (true)
         {
            cb = lpshiid->cb;
            iLen += cb;
            if (cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);
         }
         return iLen;
      }

      
      int32_t windows::get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         synch_lock sl(m_pmutex);

         int32_t iImage = 0x80000000;

         {
         if (argb_get_a_value(crBk) != 255)
         {

            crBk = 0;

         }



         image_key imagekey;

         imagekey.set_path(strPath);

         imagekey.m_pszShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

         imagekey.m_eattribute = eattribute;

         imagekey.m_eicon = eicon;

         imagekey.m_iIcon = 0;

         if (m_imagemap.Lookup(imagekey, iImage))
         {

            return iImage;

         }

         ////synch_lock sl(&m_mutexCall);

         ////m_eventReady.ResetEvent();

         //m_callCurrent.m_oswindow = oswindow;
         //m_callCurrent.m_imagekey = imagekey;
         //m_callCurrent.m_crBk = crBk;
         //m_callCurrent.m_bCall = true;

         //m_eventReady.wait();

//         iImage = m_callCurrent.m_iImage;

         iImage = get_image(oswindow, imagekey, NULL, crBk);

         m_imagemap.set_at(imagekey, iImage);

      }

         get_image_prologue(crBk, iImage);

         //if (crBk != 0)
         //{

         //   synch_lock sl1(m_pil48Hover->m_pmutex);

         //   synch_lock sl2(m_pil48->m_pmutex);

         //   {

         //      ::draw2d::dib_sp dib(allocer());
         //      dib->create(48, 48);
         //      dib->Fill(255, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk));
         //      dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         //      m_pil48Hover->draw(dib->get_graphics(), iImage, null_point(), 0);
         //      m_pil48Hover->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
         //      m_pil48Hover->m_spdib->get_graphics()->BitBlt(iImage * 48, 0, 48, 48, dib->get_graphics());
         //      m_pil48Hover->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         //   }

         //   {
         //      ::draw2d::dib & d = *m_pil48Hover->m_spdib;
         //      size s = m_pil48->m_spdib->m_size;
         //      ::draw2d::dib_sp dib(allocer());
         //      dib->create(d.size());
         //      dib->Fill(255, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk));
         //      dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         //      dib->get_graphics()->BitBlt(null_point(), d.size(), d.get_graphics());
         //      dib->get_graphics()->FillSolidRect(0, 0, d.size().cx, d.size().cy, ARGB(123, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk)));
         //      m_pil48->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
         //      m_pil48->m_spdib->get_graphics()->BitBlt(null_point(), d.size(), dib->get_graphics());
         //      m_pil48->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         //   }

         //}

         return iImage;


      }


      void windows::get_image_prologue(COLORREF crBk, int iImage)
      {
         if (crBk != 0)
         {

            synch_lock sl1(m_pil48Hover->m_pmutex);

            synch_lock sl2(m_pil48->m_pmutex);

            {

               ::draw2d::dib_sp dib(allocer());
               dib->create(48, 48);
               dib->Fill(255, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk));
               dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

               m_pil48Hover->draw(dib->get_graphics(), iImage, null_point(), 0);
               m_pil48Hover->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               m_pil48Hover->m_spdib->get_graphics()->BitBlt(iImage * 48, 0, 48, 48, dib->get_graphics());
               m_pil48Hover->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            }

            {
               ::draw2d::dib & d = *m_pil48Hover->m_spdib;
               size s = m_pil48->m_spdib->m_size;
               ::draw2d::dib_sp dib(allocer());
               dib->create(d.size());
               dib->Fill(255, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk));
               dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
               dib->get_graphics()->BitBlt(null_point(), d.size(), d.get_graphics());
               dib->get_graphics()->FillSolidRect(0, 0, d.size().cx, d.size().cy, ARGB(123, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk)));
               m_pil48->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               m_pil48->m_spdib->get_graphics()->BitBlt(null_point(), d.size(), dib->get_graphics());
               m_pil48->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            }

         }

      }

      
      void windows::open_folder(oswindow oswindow, const string & strFolder)
      {

         string str(strFolder);

         str.make_lower();

         {

            synch_lock sl(m_pmutex);

            if (m_mapFolder[str].m_lpsf.is_set())
            {

               m_mapFolder[str].m_iRef++;

               return;

            }

         }

         LPITEMIDLIST lpiidlAbsolute;

         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, strFolder);

         {

            synch_lock sl(m_pmutex);

            m_mapFolder[str].m_lpsf = _017GetShellFolder(strFolder, lpiidlAbsolute);

            m_mapFolder[str].m_iRef = 1;

         }

         _017ItemIDListFree(lpiidlAbsolute);
         

      }


      void windows::close_folder(const string & strFolder)
      {

         string str(strFolder);

         str.make_lower();

         {

            synch_lock sl(m_pmutex);

            if (m_mapFolder[str].m_lpsf.is_set())
            {

               m_mapFolder[str].m_iRef--;

               if (m_mapFolder[str].m_iRef <= 0)
               {

                  m_mapFolder[str].m_iRef = 0;

                  m_mapFolder[str].m_lpsf.Release();

               }

            }

         }

      }


      int32_t windows::get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         synch_lock sl(m_pmutex);

         int32_t iImage = 0x80000000;

         {

            if (argb_get_a_value(crBk) != 255)
            {

               crBk = 0;

            }


            image_key imagekey;

            imagekey.m_pszPath = "foo";

            imagekey.m_pszShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

            imagekey.m_pszExtension = (char *)strExtension.c_str();

            imagekey.m_eattribute = eattribute;

            imagekey.m_eicon = eicon;

            imagekey.m_iIcon = 0;

            if (m_imagemap.Lookup(imagekey, iImage))
            {

               return iImage;

            }

            //synch_lock sl(&m_mutexCall);

            //m_eventReady.ResetEvent();

            //m_callCurrent.m_oswindow = oswindow;
            //m_callCurrent.m_imagekey = imagekey;
            //m_callCurrent.m_crBk = crBk;
            //m_callCurrent.m_bCall = true;

            //m_eventReady.wait();

            //iImage = m_callCurrent.m_iImage;
            iImage = get_image(oswindow, imagekey, NULL, crBk);


            m_imagemap.set_at(imagekey, iImage);


         }

         get_image_prologue(crBk, iImage);

         return iImage;

      }

   } // namespace shell


} // namespace user







