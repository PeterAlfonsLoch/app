#pragma once
class MixerDevice;

namespace mixer
{
   class MixerCallback;
}

class MixerCtrlData
{
public:
    enum
    {
        TypeDefault = 1,
        TypeStereoBalance = 2,
        TypeStereoVolume = 3,
        TypeStereoBalanceLabel = 4,
        TypeStereoVolumeLabel = 5,
        TypeUniformMute = 6
    };
    enum
    {
        DataTypeBase = 0,
        DataTypeVolume = 1,
        DataTypeMute = 2
    };
    int             m_iType;
    UINT            m_uiMixerID;
    UINT            m_uiLineID;
    UINT            m_uiControlID;
    int              m_iIndex;
    inline virtual int GetObjectType()
    {
        return DataTypeBase;
    };
    inline virtual int get_type()
    {
        return m_iType;
    }
};

class MixerCtrlDataVolume :
    public MixerCtrlData
{
public:
    int                             nRange;
    int                             nPageInc;
    inline virtual int GetObjectType()
    {
        return DataTypeVolume;
    };
};

class MixerCtrlDataSwitch :
   public MixerCtrlData
{
    inline virtual int GetObjectType()
    {
        return DataTypeMute;
    };
};



class CLASS_DECL_ca Mixer :
   virtual public ::radix::object
{
public:
   Mixer(::ca::application * papp);
   virtual ~Mixer();

// Atributes
public:
   MixerDevice  *    m_pdevice;

   mixer::MixerCallback * GetCallback();
   void SetCallback(mixer::MixerCallback * pcallback);
protected:
   MixerWnd      m_mixerwnd;
   mixer::MixerCallback * m_pcallback;

// Operations
public:
   bool OnCommand(WPARAM wparam, LPARAM lparam);
   void OnMixerControlChange(HMIXER hMixer, DWORD dwControlID);
   void OnMixerLineChange(HMIXER hMixer, DWORD dwLineID);
   MMRESULT SetNewDevice(UINT uiMixerId);
    static BOOL GetComponentName(
        LPMIXERLINE             pmxl,
        string &               strComponent);
    static BOOL GetControlTypeName(
        LPMIXERCONTROL          pmxctrl,
        string    &            strTypeName);



};
