#pragma once

class MixerCtrlData;

namespace mixer
{


class CLASS_DECL_ca control
{
public:
   control(MixerCtrlData * pdata);

   virtual ::user::interaction * GetWnd() = 0;
   virtual bool Initialize(::user::interaction * pwndParent, UINT uiId) = 0;
   virtual int _GetDlgCtrlID() = 0;

   MixerCtrlData *   m_pdata;
public:
   virtual ~control(void);
};

class CLASS_DECL_ca ControlArray :
   public base_array < control *, control *>
{
};

} // namespace mixer