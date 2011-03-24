#pragma once

class MidiSequence;

class CMidiTrackSelectViewUpdateHint : public base_object  
{
public:
   enum EType
   {
      TypeInitialize,
   };
	CMidiTrackSelectViewUpdateHint();
	virtual ~CMidiTrackSelectViewUpdateHint();

   EType             m_etype;
	EType GetType();
	void SetType(EType etype);

   MidiSequence *   m_pmidisequence;
   bool              m_bResult;

};
