#include "StdAfx.h"
#include "mixeruserbase_label.h"


namespace mixeruserbase
{


   label::label(::ca::application * papp) :
      ca(papp)
   {

   }

   label::~label()
   {
   }





   void label::SetText(const char * lpcsz)
   {
      SetWindowText(lpcsz);
   }

   ::user::interaction * label::GetWnd()
   {
      return this;
   }

   bool label::Initialize(::user::interaction * pwndParent, UINT uiId)
   {
      rect rect(0, 0, 0, 0);
      if(!CreateEx(
         WS_EX_TRANSPARENT,
         NULL,
         NULL,
         WS_CHILD | WS_VISIBLE ,
         rect,
         pwndParent,
         uiId))
      {
         return false;
      }
      return true;
   }
   int label::_GetDlgCtrlID()
   {
      return ::user::interaction::GetDlgCtrlId();
   }


} // namespace mixeruserbase




