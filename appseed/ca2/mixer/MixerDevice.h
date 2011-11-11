#pragma once


class CLASS_DECL_ca MixerDevice :
   virtual public ::radix::object
{
public:
   MixerDevice(Mixer * pmixer);
   virtual ~MixerDevice();
protected:
   Mixer *         m_pmixer;

public:
   UINT            m_uiMixerID;
   HMIXER          m_hMixer;

   ::collection::map <DWORD  , DWORD  , MixerControl  *, MixerControl  *>   m_mapIDToControl;
   ::collection::map <UINT   , UINT   , MixerControl  *, MixerControl  *>   m_mapDlgItemIDToControl;
   ::collection::map <DWORD  , DWORD  , MixerSource   *, MixerSource   *>   m_mapIDToLine;
   //::collection::map <UINT   , UINT   , MixerCtrlData *, MixerCtrlData *>   m_mapCtrlIDToData;

   MixerDestinationArray   m_mixerdestinationa;
   MIXERCAPS               m_mixercaps;

public:
   Mixer * GetMixer();
   const char * GetSZPName();
   bool OnCommand(WPARAM wparam, LPARAM lparam);
   MMRESULT close();
   void MapDlgCtrlIDToLineControls(MixerSource * pSource);
   void MapDlgCtrlIDToControls();
   void MapLineControls(MixerSource * pSource);
   void OnMixerControlChange(DWORD dwControlID);
   void OnMixerLineChange(DWORD dwLineID);
   void MapLines();
    void MapControls();
   MMRESULT GetDestination(DWORD dwComponentType, MixerDestination ** ppDestination);
   MMRESULT GetDestinations();
   MMRESULT GetCaps();
   MMRESULT open(UINT uiMixerId, DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen);
};
