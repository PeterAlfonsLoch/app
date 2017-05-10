
//http://borland.public.cppbuilder.nativeapi.narkive.com/7OPcjHO5/loading-x48-icons-with-extracticonex


BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);
CLASS_DECL_BASE HICON ExtractResourceIcon(string strPath, int cx, int cy, int iIcon);


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
} ICONDIRENTRY, *LPICONDIRENTRY;

typedef struct
{
   WORD           idReserved;   // Reserved (must be 0)
   WORD           idType;       // Resource Type (1 for icons)
   WORD           idCount;      // How many images?
   ICONDIRENTRY   idEntries[1]; // An entry for each image (idCount of 'em)
} ICONDIR, *LPICONDIR;

typedef struct
{
   BITMAPINFOHEADER   icHeader;      // DIB header
   RGBQUAD         icColors[1];   // Color table
   BYTE            icXOR[1];      // DIB bits for XOR mask
   BYTE            icAND[1];      // DIB bits for AND mask
} ICONIMAGE, *LPICONIMAGE;

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
} GRPICONDIRENTRY, *LPGRPICONDIRENTRY;
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
} GRPICONDIR, *LPGRPICONDIR;
#pragma pack( pop )









BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);

CLASS_DECL_BASE HICON ExtractResourceIcon(string strPath, int cx, int cy, int iIcon)
{

   HMODULE hLib = NULL;

   try
   {

      hLib = LoadLibraryExW(wstring(strPath), NULL, LOAD_LIBRARY_AS_DATAFILE);

   }
   catch (...)
   {

      return NULL;

   }

   if (hLib == NULL)
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

      EnumResourceNamesW(hLib, MAKEINTRESOURCEW((ULONG_PTR)(RT_ICON)+11), (ENUMRESNAMEPROCW)ExtractResourceIcon_EnumNamesFunc, (LONG_PTR)& i);

   }
   catch (...)
   {


   }

   try
   {

      FreeLibrary(hLib);

   }
   catch (...)
   {


   }

   return i.hicon;
}

BOOL ExtractResourceIcon_EnumNamesFunc(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
   extract_resource_icon * pi = (extract_resource_icon *)lParam;

   if (pi->iIcon > 0)
   {

      pi->iIcon--;



      return TRUE;

   }



   HRSRC hRsrc = FindResourceW(hModule, lpName, lpType);

   HGLOBAL hGroup = LoadResource(hModule, hRsrc);

   GRPICONDIR * lpGrpIconDir = (LPGRPICONDIR)LockResource(hGroup);
   //   if(pi->iIcon >= lpGrpIconDir->idCount)
   //    return FALSE;

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 32)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 32)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }


   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 24)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }
   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 24)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 16)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 16)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth == pi->cx && e->bHeight == pi->cy && e->wBitCount == 8)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth > pi->cx && e->bHeight > pi->cy && e->wBitCount == 8)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth == pi->cx && e->bHeight == pi->cy)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   for (int i = 0; i < lpGrpIconDir->idCount; ++i)
   {

      GRPICONDIRENTRY * e = &lpGrpIconDir->idEntries[i];


      if (e->bWidth > pi->cx && e->bHeight > pi->cy)
      {

         hRsrc = FindResource(hModule, MAKEINTRESOURCE(e->nID), RT_ICON);

         HGLOBAL hGlobal = LoadResource(hModule, hRsrc);

         ICONIMAGE *lpIconImage = (LPICONIMAGE)LockResource(hGlobal);

         pi->hicon = CreateIconFromResourceEx(
            (PBYTE)lpIconImage,
            e->dwBytesInRes,
            TRUE,
            0x00030000,//DWORD dwVersion,
            e->bWidth,
            e->bHeight,
            0);

         if (pi->hicon != NULL)
            return FALSE;

      }

   }

   return FALSE;

}
