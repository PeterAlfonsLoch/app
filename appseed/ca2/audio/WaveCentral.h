// audWaveCentral.h: interface for the audWaveCentral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVECENTRAL_H__E9979F72_4750_4A8D_8D1B_7F004AA2CC48__INCLUDED_)
#define AFX_WAVECENTRAL_H__E9979F72_4750_4A8D_8D1B_7F004AA2CC48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class audWaveIn;


class CLASS_DECL_ca audWaveCentral :
   virtual public ::radix::object
{
   // Attributes
protected:
    audWaveIn * m_pwavein;

   // Construction/Destruction
public:
   audWaveCentral();
   virtual ~audWaveCentral();

   // Attributes
public:
   audWaveIn * GetWaveIn();


   // Initialization/Finalization
public:
   void close();
   bool Initialize(::ca::application * papp);
   bool Finalize();
    

   UINT    m_uiWaveInDevice;
};


#endif // !defined(AFX_WAVECENTRAL_H__E9979F72_4750_4A8D_8D1B_7F004AA2CC48__INCLUDED_)
