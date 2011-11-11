// Archive/Common/ItemNameUtils.cpp
// from 7-zip on 2010-12-25, Christmas evening
#include "StdAfx.h"

//#include "../../../../C/Types.h"
/*
#include "ItemNameUtils.h"*/

namespace archive
{

   namespace item_name
   {

   static const wchar_t kOSDirDelimiter = CHAR_PATH_SEPARATOR;
   static const wchar_t kDirDelimiter = '/';

   string MakeLegalName(const string &name)
   {
     string zipName = name;
     zipName.replace(kOSDirDelimiter, kDirDelimiter);
     return zipName;
   }

   string GetOSName(const string &name)
   {
     string newName = name;
     newName.replace(kDirDelimiter, kOSDirDelimiter);
     return newName;
   }

   string GetOSName2(const string &name)
   {
     if (name.is_empty())
       return string();
     string newName = GetOSName(name);
     if (newName[newName.get_length() - 1] == kOSDirDelimiter)
       newName.Delete(newName.get_length() - 1);
     return newName;
   }

   bool HasTailSlash(const string & name, UINT codePage)
   {
     if (name.is_empty())
       return false;
     LPCSTR prev =
     #if defined(_WIN32) && !defined(UNDER_CE)
       CharPrevExA((WORD)codePage, name, &LPCSTR(name)[name.get_length()], 0);
     #else
       (LPCSTR)(name) + (name.Length() - 1);
     #endif
     return (*prev == '/');
   }

   #ifdef _WIN32
   string WinNameToOSName(const string &name)
   {
     return name;
   }
   #else
   string WinNameToOSName(const string &name)
   {
     string newName = name;
     newName.Replace(L'\\', kOSDirDelimiter);
     return newName;
   }
   #endif

   } // namespace item_name

} // namespace archive
