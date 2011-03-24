// AudioSpectrumViewUpdateHint.h: interface for the CAudioSpectrumViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIOSPECTRUMVIEWUPDATEHINT_H__A050A7EE_9513_497F_9CE1_A252BEF2A7DE__INCLUDED_)
#define AFX_AUDIOSPECTRUMVIEWUPDATEHINT_H__A050A7EE_9513_497F_9CE1_A252BEF2A7DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLASS_DECL_CA2_CUBE CAudioSpectrumViewUpdateHint : public ::radix::object  
{
   
public:
   CAudioSpectrumViewUpdateHint();
   virtual ~CAudioSpectrumViewUpdateHint();

   LPWAVEFORMATEX   m_lpwaveformatex;
   double         m_dDeltaScore;
   double         m_dScoreAddUp;


};

#endif // !defined(AFX_AUDIOSPECTRUMVIEWUPDATEHINT_H__A050A7EE_9513_497F_9CE1_A252BEF2A7DE__INCLUDED_)
