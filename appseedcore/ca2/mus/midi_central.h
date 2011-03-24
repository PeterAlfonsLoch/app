#pragma once

namespace mus
{
   class midi_central_container;
} // namespace mus


class CLASS_DECL_ca midi_central :
   virtual public ::radix::object
{
public:


   mus::midi_central_container *             m_pcontainer;
   CMidiCentralListenerPtrArray              m_listenerptra;
   UINT                                      m_uiMidiOutDevice;


   midi_central(::ca::application * papp);
   virtual ~midi_central();


   void RemoveListener(CMidiCentralListener * plistener);
   void AddListener(CMidiCentralListener * plistener);
   UINT GetMidiOutDevice();
   void SetMidiOutDevice(UINT uiDevice);
   bool Initialize(mus::midi_central_container * pcontainer);


   bool IsSoftKaraokeFile(const char * lpszPathName);
   bool IsXFFile(const char * lpcszPathName);

};
