// Configuration.h: interface for the CConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURATION_H__1F23E5C7_BC81_427B_83CA_C3BDD317D25B__INCLUDED_)
#define AFX_CONFIGURATION_H__1F23E5C7_BC81_427B_83CA_C3BDD317D25B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace _vmplight
{

   enum
   {
	   WPARAM_LANGUAGE_KARAOKEENCODING_UPDATE = 2,
   };
	
	enum EDataKey
	{
		DataKeyKaraokeEncoding,
		DataKeyForceKarRegistration,
		DataKeyForceMidRegistration,
      DataKeyForceSt3Registration,
		DataKeyKarOldRegistration,
		DataKeyMidOldRegistration,
      DataKeySt3OldRegistration,
		DataKeyMidiOutDevice,
      DataKeyMidiOutDevices,
		DataKeyWaveInDevice,
      DataKeyWaveInDevices,
      DataKeyGlobalLyricsDelay,
      DataKeyImageDirectorySetInitialUpdate,
      DataKeyImageDirectorySet,
      DataKeyImageFileSet,
      DataKeySongDirectorySet,
      DataKeyNextBackgroundImagePath,
      DataKeyBackgroundImageChangeSecondsHint,
      DataKeyMRUCount,
      DataKeyMRUEnable,
      DataKeyMRUFiles,
      DataKeyWindowData,
	};

   enum EWindowData
   {
      WindowDataMainFrame,
   };

}

#endif // !defined(AFX_CONFIGURATION_H__1F23E5C7_BC81_427B_83CA_C3BDD317D25B__INCLUDED_)
