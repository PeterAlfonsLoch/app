#pragma once

namespace ca
{
   class graphics;

   class CLASS_DECL_ca2 draw_item
   {
   public:
       UINT          CtlType;
       UINT          CtlID;
       UINT          itemID;
       UINT          itemAction;
       UINT          itemState;
       oswindow          oswindowItem;
       graphics *    m_pgraphics;
       RECT          rcItem;
       uint_ptr     itemData;
   };

} // namespace ca