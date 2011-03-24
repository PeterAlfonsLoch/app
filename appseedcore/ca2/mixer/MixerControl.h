#pragma once

class MixerCtrlData;
class MixerSource;

class CLASS_DECL_ca MixerControl :
   public mixer::ControlArray
{
public:
    enum Styles
    {
        StyleV001 = 1
    };
public:
   
   MixerControl(::ca::application * papp);
   MixerControl(MixerControl & control);
   virtual ~MixerControl();
   MixerSource *      m_pmixersource;
    
//    string             m_strTypeName;

   MIXERCONTROL         m_mixercontrol;
   MIXERCONTROLDETAILS  m_mixercontroldetails;

public:

#if !core_level_1
   using ::mixer::ControlArray::add;
#endif


   virtual INT_PTR add(mixer::control * pcontrol);
   DWORD GetControlType() const;
   BOOL OnCommand(WPARAM wParam, LPARAM lParam);
   MixerCtrlData * GetWindowDataByDlgCtrlID(UINT nID);
   mixer::control * GetControlByDlgCtrlID(UINT nID);
   bool OnNotify(UINT nID, LPNMHDR lpnmhdr);
   void OnVHScroll(UINT nSBCode, UINT nPos, ::user::interaction * pScrollBar); 
   MixerCtrlData * GetWindowData(int iType);
   void OnMixerControlChange();
   mixer::control * GetControl(int iType);
   mixer::control * GetControlByIndex(int iIndex);
   void Prepare();
   //void OnArrayReallocation(void *pNewPointer);
   bool CreateWindowsVolumeV001(::user::interaction * pParent, UINT nStartID, UINT * nNextID);
   
 //  bool _001CreateMuteControl(::user::interaction * pParent, CRuntimeClass * pruntimeclassMuteControl, UINT nStartID, UINT * nNextID);
   bool _001CreateMuteControl(::user::interaction * pParent, UINT nStartID, UINT * nNextID);
   
   bool CreateWindows(::user::interaction * pParent, int iStyle);

   MixerControl & operator =(const MixerControl & control);


   MIXERCONTROL & GetMixerControl();
   MIXERCONTROLDETAILS & GetMixerControlDetails();

};


class MixerControlArray :
   public array_app_alloc <MixerControl, MixerControl &>
{
public:
   MixerControlArray(::ca::application * papp);

};
