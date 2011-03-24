#pragma once

namespace ca
{
   class graphics;

   class CLASS_DECL_ca draw_item
   {
   public:
       UINT          CtlType;
       UINT          CtlID;
       UINT          itemID;
       UINT          itemAction;
       UINT          itemState;
       HWND          hwndItem;
       graphics *    m_pgraphics;
       RECT          rcItem;
       ULONG_PTR     itemData;
   };

} // namespace ca