// Archive/Common/ItemNameUtils.cpp
// from 7-zip on 2010-12-25, Christmas evening
#include "framework.h"

//#include "../../../../C/Types.h"
/*
#include "ItemNameUtils.h"*/

namespace archive
{

   namespace item_name
   {

   static const char16_t kOSDirDelimiter = CHAR_PATH_SEPARATOR;
   static const char16_t kDirDelimiter = '/';

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
     return name[name.length() - 1] == '/';
   }

#ifdef WINDOWS
   string WinNameToOSName(const string &name)
   {
     return name;
   }
#else
   string WinNameToOSName(const string &name)
   {
     string newName = name;
     newName.replace('\\', kOSDirDelimiter);
     return newName;
   }
   #endif

   } // namespace item_name

} // namespace archive
