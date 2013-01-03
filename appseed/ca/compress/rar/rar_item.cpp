// RarItem.cpp
// from 7-zip
#include "framework.h"

//#include "RarItem.h"

namespace rar
{

   bool CItem::IgnoreItem() const
   {
      switch(HostOS)
      {
      case header::file::kHostMSDOS:
      case header::file::kHostOS2:
      case header::file::kHostWin32:
         return ((Attrib & header::file::kLabelFileAttribute) != 0);
      }
      return false;
   }

   bool CItem::IsDir() const
   {
      if (GetDictSize() == header::file::kDictDirectoryValue)
         return true;
      switch(HostOS)
      {
      case header::file::kHostMSDOS:
      case header::file::kHostOS2:
      case header::file::kHostWin32:
         if ((Attrib & FILE_ATTRIBUTE_DIRECTORY) != 0)
            return true;
      }
      return false;
   }

   uint32_t CItem::GetWinAttributes() const
   {
      uint32_t winAttributes;
      switch(HostOS)
      {
      case header::file::kHostMSDOS:
      case header::file::kHostOS2:
      case header::file::kHostWin32:
         winAttributes = Attrib;
         break;
      default:
         winAttributes = 0; // must be converted from unix value;
      }
      if (IsDir())
         winAttributes |= header::file::kWinFileDirectoryAttributeMask;
      return winAttributes;
   }

} // namespace rar
