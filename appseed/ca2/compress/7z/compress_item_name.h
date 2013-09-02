#pragma once

namespace archive
{

   namespace item_name
   {

     string MakeLegalName(const string &name);
     string GetOSName(const string &name);
     string GetOSName2(const string &name);
     bool HasTailSlash(const string &name, UINT codePage);
     string WinNameToOSName(const string &name);
     string WinNameToOSName(const string &name);

   } // namespace item_name

} // namespace libcompress
