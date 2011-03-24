#pragma once

class CMixer;
class CMixerDestination;
class MixerVisualThread;

/////////////////////////////////////////////////////////////////////////////
// MixerVisualCentral ::ca::window

class CLASS_DECL_ca MixerVisualCentral : public ::user::interaction
{
// Construction
public:
   MixerVisualCentral(::ca::application * papp);

// Attributes
public:
   ::userbase::multiple_document_template * get_document_template();

   string   m_idRecordingTab;
   string   m_idRecordingIcon;
   string   m_idPlaybackTab;
   string   m_idPlaybackIcon;
protected:
   MixerVisualThread *   m_pvisualthread;
   ::userbase::multiple_document_template *     m_pdoctemplate;

   
   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

// Operations
public:
   ::userbase::multiple_document_template * CreateDocTemplate(::ca::application * papp);
//      MMRESULT CreateNewDestination(DWORD dwComponentType);
//   MMRESULT CreateNewDevice(UINT uiMixerID);


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MixerVisualCentral)
   //}}AFX_VIRTUAL

// Implementation
public:
   void OnVisualThreadExitInstance();
   void DisplayAMixer();
   bool Initialize(::ca::application * papp);
   static void SetMIXERVISUALCENTRAL(MixerVisualCentral * pMIXERVISUALCENTRAL);
   virtual ~MixerVisualCentral();

protected:
   DECL_GEN_SIGNAL(_001OnClose)

};


