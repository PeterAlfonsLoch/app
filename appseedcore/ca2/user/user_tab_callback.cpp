#include "StdAfx.h"

namespace user
{

   tab_callback::tab_callback()
   {

   }

   tab_callback::~tab_callback()
   {

   }

   bool tab_callback::_001IsAddTab(int iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
      return false;
   }

   void tab_callback::_001OnTabClick(int iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
   }

   ::user::interaction * tab_callback::_001GetTabWnd(int iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
      return NULL;
   }

   void tab_callback::on_show_view(tab * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

   void tab_callback::_001OnDropTab(int iTab, e_position eposition)
   {
      UNREFERENCED_PARAMETER(iTab);
      UNREFERENCED_PARAMETER(eposition);
   }

   void tab_callback::_001DropTargetWindowInitialize(tab * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

   void tab_callback::_001DropTargetWindowRelay(tab * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

   void tab_callback::_001DropTargetWindowFinalize(tab * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

} // namespace ex1