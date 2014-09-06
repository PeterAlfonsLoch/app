#pragma once


namespace draw2d
{


   class CLASS_DECL_AXIS item
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


} // namespace draw2d



