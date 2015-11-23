//#include "framework.h"

#ifdef WINDOWS
//#include <Shellapi.h>
//#include <CommonControls.h>
#endif

string expand_env(string str)
{

   hwstring hwstr( 16384);

   ExpandEnvironmentStringsW(wstring(str),  hwstr, hwstr.count());

   return hwstr;

}

struct extract_resource_icon
{

   int         iIcon;
   int         cx;
   int         cy;
   HICON       hicon;

};

typedef struct
{
   BYTE        bWidth;          // Width, in pixels, of the image
   BYTE        bHeight;         // Height, in pixels, of the image
   BYTE        bColorCount;     // Number of colors in image (0 if >=8bpp)
   BYTE        bReserved;       // Reserved ( must be 0)
   WORD        wPlanes;         // Color Planes
   WORD        wBitCount;       // Bits per pixel
   DWORD       dwBytesInRes;    // How many bytes in this resource?
   DWORD       dwImageOffset;   // Where in the file is this image?
} ICONDIRENTRY,*LPICONDIRENTRY;
typedef struct
{
   WORD           idReserved;   // Reserved (must be 0)
   WORD           idType;       // Resource Type (1 for icons)
   WORD           idCount;      // How many images?
   ICONDIRENTRY   idEntries[1]; // An entry for each image (idCount of 'em)
} ICONDIR,*LPICONDIR;

typedef struct
{
   BITMAPINFOHEADER   icHeader;      // DIB header
   RGBQUAD         icColors[1];   // Color table
   BYTE            icXOR[1];      // DIB bits for XOR mask
   BYTE            icAND[1];      // DIB bits for AND mask
} ICONIMAGE,*LPICONIMAGE;

#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
   BYTE   bWidth;               // Width, in pixels, of the image
   BYTE   bHeight;              // Height, in pixels, of the image
   BYTE   bColorCount;          // Number of colors in image (0 if >=8bpp)
   BYTE   bReserved;            // Reserved
   WORD   wPlanes;              // Color Planes
   WORD   wBitCount;            // Bits per pixel
   DWORD   dwBytesInRes;         // how many bytes in this resource?
   WORD   nID;                  // the ID
} GRPICONDIRENTRY,*LPGRPICONDIRENTRY;
#pragma pack( pop )
// #pragmas are used here to insure that the structure's
// packing in memory matches the packing of the EXE or DLL.
#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
   WORD            idReserved;   // Reserved (must be 0)
   WORD            idType;       // Resource type (1 for icons)
   WORD            idCount;      // How many images?
   GRPICONDIRENTRY   idEntries[1]; // The entries for each image
} GRPICONDIR,*LPGRPICONDIR;
#pragma pack( pop )
BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule,LPCWSTR lpType,LPWSTR lpName,LONG_PTR lParam);

HICON ExtractResourceIcon(string strPath, int cx, int cy, int iIcon)
{

   HMODULE hLib = NULL;

   try
   {

      hLib = LoadLibraryExW(wstring(strPath),NULL,LOAD_LIBRARY_AS_DATAFILE);

   }
   catch(...)
   {
      
      return NULL;

   }

   if(hLib == NULL)
   {

      return NULL;

   }

   extract_resource_icon i;

   ZERO(i);

   i.cx = cx;

   i.cy = cy;

   i.iIcon = iIcon;
   
   try
   {

      EnumResourceNamesW(hLib,MAKEINTRESOURCEW((ULONG_PTR)(RT_ICON)+ 11),(ENUMRESNAMEPROCW)ExtractResourceIcon_EnumNamesFunc,(LONG_PTR)& i);

   }
   catch(...)
   {


   }

   try
   {

      FreeLibrary(hLib);

   }
   catch(...)
   {


   }

   return i.hicon;
}

BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
   extract_resource_icon * pi = (extract_resource_icon *) lParam;

   if(pi->iIcon > 0)
   {
      
      pi->iIcon--;



      return TRUE;

   }



   HRSRC hRsrc = FindResourceW(hModule,lpName,lpType);

   HGLOBAL hGroup = LoadResource(hModule,hRsrc);

   GRPICONDIR * lpGrpIconDir = (LPGRPICONDIR)LockResource(hGroup);
//   if(pi->iIcon >= lpGrpIconDir->idCount)
  //    return FALSE;

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];

      
      if(e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 32)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 32)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }


   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 24)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }
   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 24)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 16)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 16)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 8)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 8)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth == pi->cx && e->bHeight == pi->cy)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   for(int i=0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if(e->bWidth > pi->cx && e->bHeight > pi->cy)
      {

         hRsrc = FindResource(hModule,MAKEINTRESOURCE(e->nID),RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule,hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if(pi->hicon != NULL)
            return FALSE;

      }

   }

   return FALSE;

}


//http://borland.public.cppbuilder.nativeapi.narkive.com/7OPcjHO5/loading-x48-icons-with-extracticonex
namespace filemanager
{

   namespace _shell
   {

      string _017FilePathGetParent(const char * lpcsz);

      int32_t _017ItemIDListGetLen(LPITEMIDLIST lpiidl)
      {
         if(lpiidl == NULL)
            return 0;
         LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
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
            lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);
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
               (void **)&lpsfParent);

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

         memcpy(lpiidlRet,lpiidl,iLen);
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
         uint32_t * lpdw = (uint32_t *)lpiidl;
         while(iRemain >= 4)
         {
            iHash += *lpdw;
            lpdw++;
            iRemain -= 4;
         }
         LPBYTE lpb = (LPBYTE)lpdw;
         while(iRemain > 0)
         {
            iHash += *lpb;
            lpb++;
            iRemain--;
         }
         return iHash;
      }

      LPITEMIDLIST _017ItemIDListGetAbsolute(LPITEMIDLIST lpiidlParent,LPITEMIDLIST lpiidl)
      {

         LPMALLOC lpmalloc = NULL;
         HRESULT hr;

         hr = SHGetMalloc(&lpmalloc);

         int32_t iLenParent = _017ItemIDListGetLen(lpiidlParent);
         int32_t iLen = _017ItemIDListGetLen(lpiidl);

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iLenParent + iLen + 2);

         memcpy(lpiidlRet,lpiidlParent,iLenParent);
         memcpy(&(((LPBYTE)lpiidlRet)[iLenParent]),lpiidl,iLen);
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

         LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
         LPSHITEMID  lpshiidLast = lpshiid;
         USHORT cb;

         while(true)
         {
            cb = *((USHORT *)lpshiid);
            if(cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);
         }
         int32_t iCount = *((USHORT *)lpshiidLast);

         if(iCount == 0)
            return NULL;

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iCount + 2);

         memcpy(lpiidlRet,lpshiidLast,iCount);

         *((USHORT *)&(((LPBYTE)lpiidlRet)[iCount])) = 0;

         lpmalloc->Release();

         return lpiidlRet;
      }

      LPITEMIDLIST _017ItemIDListGetFolderParent(LPITEMIDLIST lpiidl)
      {
         if(lpiidl == NULL)
            return NULL;

         LPMALLOC lpmalloc = NULL;
         HRESULT hr;
         hr = SHGetMalloc(&lpmalloc);

         LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
         LPSHITEMID  lpshiidLast = lpshiid;
         USHORT cb;

         while(true)
         {
            cb = *((USHORT *)lpshiid);
            if(cb == 0)
               break;
            lpshiidLast = lpshiid;
            lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);
         }
         ::count iCount = ((LPBYTE)lpshiidLast) - ((LPBYTE)lpiidl);

         if(iCount == 0)
            return NULL;

         LPITEMIDLIST lpiidlRet = (LPITEMIDLIST)
            lpmalloc->Alloc(iCount + 2);

         memcpy(lpiidlRet,lpiidl,iCount);

         *((USHORT *)&(((LPBYTE)lpiidlRet)[iCount])) = 0;

         lpmalloc->Release();

         return lpiidlRet;
      }

      bool _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1,LPITEMIDLIST lpiidl2)
      {
         if(lpiidl1 == NULL && lpiidl2 == NULL)
         {
            return true;
         }
         if(lpiidl1 == NULL || lpiidl2 == NULL)
         {
            return false;
         }


         LPSHITEMID  lpshiid1 = (LPSHITEMID)lpiidl1;
         LPSHITEMID  lpshiid2 = (LPSHITEMID)lpiidl2;
         USHORT cb1;
         USHORT cb2;

         while(true)
         {
            cb1 = *((USHORT *)lpshiid1);
            cb2 = *((USHORT *)lpshiid2);
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
            if(memcmp(lpshiid1,lpshiid2,cb1) != 0)
               return false;
            lpshiid1 = (LPSHITEMID)(((LPBYTE)lpshiid1) + cb1);
            lpshiid2 = (LPSHITEMID)(((LPBYTE)lpshiid2) + cb2);
         }
      }

      void _017ItemIDListParsePath(oswindow window,LPITEMIDLIST * lpiidl,const char * lpcsz)
      {
         HRESULT hr;
         LPMALLOC lpmalloc = NULL;
         IShellFolder * lpsfDesktop;
         hr = SHGetMalloc(&lpmalloc);


         hr = SHGetDesktopFolder(&lpsfDesktop);

         //ULONG ulEaten;
         //ULONG dwAttrib = SFGAO_FOLDER;

         hwstring w(MAX_PATH * 8);

         wstring wstr = ::str::international::utf8_to_unicode(lpcsz);

         wcscpy(w,wstr);

         try
         {
            hr = lpsfDesktop->ParseDisplayName(
               window,
               NULL,
               w,
               //&ulEaten,
               NULL,
               lpiidl,
               //&dwAttrib);
               NULL);
         }
         catch(...)
         {
         }

         lpsfDesktop->Release();
         lpmalloc->Release();

      }

      void _017ItemIDListFree(LPITEMIDLIST lpiidl)
      {
         LPMALLOC lpmalloc = NULL;

         SHGetMalloc(&lpmalloc);

         lpmalloc->Free(lpiidl);

         lpmalloc->Release();
      }

      bool _017HasSubFolder(::aura::application * papp,LPITEMIDLIST lpiidl,const char * lpcszExtra)
      {

         WCHAR szPath[_MAX_PATH * 10];

         SHGetPathFromIDListW(lpiidl,szPath);

         EFolder efolder = GetFolderType(papp,szPath);

         if(efolder == FolderNone)
         {

            return false;

         }
         else if(efolder == FolderZip)
         {

            string wstrPath;

            ::str::international::unicode_to_utf8(wstrPath,szPath);

            string wstrExtra(lpcszExtra);

            if(wstrExtra.get_length() > 0)
            {
               wstrPath += ":" + wstrExtra;
            }

            return zip::Util().HasSubFolder(papp,wstrPath);

         }
         else
         {

            ::file::listing listing(papp);

            listing.ls(::str::international::unicode_to_utf8(szPath));

            for(int32_t i = 0; i < listing.get_size(); i++)
            {

               efolder = GetFolderType(papp,listing[i]);

               if(efolder != FolderNone)
                  return true;

            }

            return false;

         }

      }




      int32_t ImageSet::GetImage(
         oswindow oswindow,
         IShellFolder * lpsf,
         LPITEMIDLIST lpiidlAbsolute,
         LPITEMIDLIST lpiidlChild,
         const unichar * lpcszExtra,
         EIcon eicon, COLORREF crBk)
      {

         single_lock sl(&m_mutex,true);

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

         ::str::international::unicode_to_utf8(strExtra,lpcszExtra);

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
            (LPCITEMIDLIST *)&lpiidlChild,
            IID_IExtractIcon,
            NULL,
            (void **)&lpiextracticon)))
         {
            if(SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
               iType,
               szPath,
               sizeof(szPath),
               &iIcon,
               &uiFlags)))
            {
               if(strcmp(szPath,"*") == 0)
               {
                  strsize iFind = strFilePath.reverse_find('.');

                  imagekey.m_iIcon         = 0x80000000;
                  imagekey.m_strExtension  = strFilePath.Mid(iFind);
                  imagekey.m_strPath.Empty();
               }
               else
               {
                  imagekey.m_strPath    = expand_env(szPath);
                  imagekey.m_iIcon      = iIcon;
                  imagekey.m_strExtension.Empty();
               }
            }
         }
         if(imagekey.m_iIcon == 0x80000000)
         {
            ::file::path strTarget;
            //if(System.file().resolve_link(strTarget, strFilePath, System.ui_from_handle))
            if(System.file().resolve_link(strTarget,strFilePath,NULL))
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
                  eicon,
                  crBk);

               _017ItemIDListFree(lpiidlParent2);

               _017ItemIDListFree(lpiidlChild2);

               return iImage;

            }
         }
         if(!m_imagemap.Lookup(imagekey,iImage))
         {

            if(imagekey.m_iIcon == 0x80000000)
            {
               iImage = GetFooImage(oswindow,eicon,imagekey.m_strPath == "folder",imagekey.m_strExtension);
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
                           RGB(255,255,240),
                           64);
                        m_imagemap.set_at(imagekey,iImage);
                     }
                  }
                  catch(...)
                  {
                  }
                  //::GlobalUnlock(hglobal);
                  //::GlobalFree(hglobal);
                  if(!bExtract)
                  {
                     HICON hicon32 = NULL;
                     if(imagekey.m_strPath.is_empty())
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
                        hicon48 = shfi48.hIcon;
                        iImage = m_pil16->add_icon_os_data(hicon16);
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
                     }
                     else
                     {
                        ExtractIconEx(
                           imagekey.m_strPath,
                           imagekey.m_iIcon,
                           &hicon32,
                           &hicon16,
                           1);


                     }

                     if(hicon48 == NULL && ::str::ends_ci(imagekey.m_strPath,".ico"))
                     {

                        hicon48 = (HICON)LoadImage(NULL,imagekey.m_strPath,IMAGE_ICON,48,48,LR_LOADFROMFILE);

                     }
                     if(hicon48 == NULL)
                     {

                        hicon48 = ExtractResourceIcon(imagekey.m_strPath,48,48,imagekey.m_iIcon);

                     }

                     if(hicon48 == NULL)
                     {

                        if(hicon32 != NULL)
                        {

                           hicon48 = hicon32;
                        }
                        else
                        {

                           hicon48 = hicon16;

                        }

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
                     if(hicon48 == NULL)
                     {

                        IImageList * pil = NULL;
                        SHGetImageList(SHIL_EXTRALARGE,IID_IImageList,(void **)&pil);
                        if(pil != NULL)
                        {
                           pil->GetIcon(shfi48.iIcon,ILD_TRANSPARENT,&hicon48);
                           pil->Release();
                        }

                     }
                     iImage = m_pil16->add_icon_os_data(hicon16);


                     m_pil48Hover->add_icon_os_data(hicon48);

                     if(crBk == 0)
                     {

                        System.visual().imaging().Createcolor_blend_ImageList(
                           m_pil48,
                           m_pil48Hover,
                           RGB(255,255,240),
                           64);

                     }
                     else
                     {
                        m_pil48->add_icon_os_data(hicon48);
                     }
                     m_imagemap.set_at(imagekey,iImage);
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

      int32_t ImageSet::GetFooImage(oswindow oswindow,EIcon eicon,bool bFolder,const string & strExtension)
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





      bool ImageSet::GetIcon(
         oswindow oswindow,
         IShellFolder * lpsf,
         LPITEMIDLIST lpiidlAbsolute,
         LPITEMIDLIST lpiidlChild,
         const unichar * lpcszExtra,
         EIcon eicon,
         HICON * phicon16,
         HICON * phicon48)
      {

         single_lock sl(&m_mutex,true);

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

         ::str::international::unicode_to_utf8(strExtra,lpcszExtra);

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
            (LPCITEMIDLIST *)&lpiidlChild,
            IID_IExtractIcon,
            NULL,
            (void **)&lpiextracticon)))
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
         const unichar * lpcszExtra,
         EIcon eicon, COLORREF crBk)
      {


         single_lock sl(&m_mutex,true);

         IShellFolder  * lpsf = _017GetShellFolder(lpiidlAbsolute);


         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(lpiidlAbsolute);
         int32_t iImage = GetImage(
            oswindow,
            lpsf,
            lpiidlAbsolute,
            lpiidlChild,
            lpcszExtra,
            eicon, crBk);

         lpsf->Release();

         _017ItemIDListFree(lpiidlChild);

         return iImage;
      }





      bool ImageSet::GetIcon(
         oswindow oswindow,
         const char * psz,
         const unichar * lpcszExtra,
         EIcon eicon,
         HICON * phicon16,
         HICON * phicon48)
      {

         single_lock sl(&m_mutex,true);


         LPITEMIDLIST lpiidlAbsolute;
         _017ItemIDListParsePath(oswindow,&lpiidlAbsolute,psz);
         bool bGet = GetIcon(oswindow,lpiidlAbsolute,lpcszExtra,eicon,phicon16,phicon48);
         _017ItemIDListFree(lpiidlAbsolute);
         return bGet;

      }

      bool ImageSet::GetIcon(
         oswindow oswindow,
         LPITEMIDLIST lpiidlAbsolute,
         const unichar * lpcszExtra,
         EIcon eicon,
         HICON * phicon16,
         HICON * phicon48)
      {

         single_lock sl(&m_mutex,true);

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



   } // namespace _shell



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
            if(_shell::_017ItemIDListIsEqual(ppidl,lpiidl))
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
      array < LPITEMIDLIST,LPITEMIDLIST > & lpiidla)
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

   void Shell::Free(array < LPITEMIDLIST,LPITEMIDLIST > & lpiidla)
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





} // namespace filemanager
