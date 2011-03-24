#pragma once

namespace mixeruserbase
{

   // label
   // linux CStatic
   class CLASS_DECL_ca label : 
      public ::user::interaction,
      public mixer::label
   {
   public:
      label(::ca::application * papp);
      virtual ~label();

      virtual ::user::interaction * GetWnd();
      virtual bool Initialize(::user::interaction * pwndParent, UINT uiId);
      virtual int _GetDlgCtrlID();
      virtual void SetText(const char * lpcsz);
   };

} // namespace mixeruserbase
