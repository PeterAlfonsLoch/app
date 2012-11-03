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
       oswindow_          hwndItem;
       graphics *    m_pgraphics;
       RECT          rcItem;
       ulong_ptr     itemData;
   };

} // namespace ca