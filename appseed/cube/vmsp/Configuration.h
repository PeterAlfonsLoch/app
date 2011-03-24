// Configuration.h: interface for the Configuration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSP_CONFIGURATION_H__1F23E5C7_BC81_427B_83CA_C3BDD317D25B__INCLUDED_)
#define AFX_VMSP_CONFIGURATION_H__1F23E5C7_BC81_427B_83CA_C3BDD317D25B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "_vmsguiConfiguration.h"

namespace vmsp
{

class Configuration  
{
public:
   static const UINT WPARAM_LANGUAGE_KARAOKEENCODING_UPDATE;
};
   
   enum EDataKey
   {
      DataKeyKaraokeEncoding,
      DataKeyForceKarRegistration,
      DataKeyForceMidRegistration,
      DataKeyMidiOutDevice,
      DataKeyWaveInDevice,
   };

}

#endif // !defined(AFX_VMSP_CONFIGURATION_H__1F23E5C7_BC81_427B_83CA_C3BDD317D25B__INCLUDED_)
