// Scoring.h: interface for the Scoring class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCORING_H__E0B7A8E5_85D4_44FE_A72E_8A3FACA9ABE5__INCLUDED_)
#define AFX_SCORING_H__E0B7A8E5_85D4_44FE_A72E_8A3FACA9ABE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLASS_DECL_ca Scoring  
{
public:

   class UpdateMessage
   {
   public:
      double m_dDeltaScore;
      double m_dScoreAddUp;
   };

   Scoring();
   virtual ~Scoring();

};

#endif // !defined(AFX_SCORING_H__E0B7A8E5_85D4_44FE_A72E_8A3FACA9ABE5__INCLUDED_)
