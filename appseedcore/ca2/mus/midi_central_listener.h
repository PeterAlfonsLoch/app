///////////////////////////////////////////////////////////////////////////////
//
// File Name: MidiCentralListener.h
// Long Name: Midi Central Listener
//
// Author: Camilo Sasuke Tsumanuma
//
// Creation Date: 1999-2000
//
// Purpose: Center global Midi Attributes and functions.
//
///////////////////////////////////////////////////////////////////////////////
// MidiCentralListener.h: interface for the CMidiCentralListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDICENTRALLISTENER_H__0506B76B_4AAE_4D31_A695_5782FF696BE4__INCLUDED_)
#define AFX_MIDICENTRALLISTENER_H__0506B76B_4AAE_4D31_A695_5782FF696BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class midi_central;

class CLASS_DECL_ca CMidiCentralListener  
{
   friend class midi_central;
protected:
   midi_central *       m_pmidicentral;
public:
   void SetMidiCentral(midi_central * pcentral);
   CMidiCentralListener();
   CMidiCentralListener(midi_central * pcentral);
   virtual ~CMidiCentralListener();

protected:
   virtual void OnAttributeChange(int iAttribute);
   virtual void OnAttributeChange(mus::EMidiCentralAttribute eattribute);


};

class CLASS_DECL_ca CMidiCentralListenerPtrArray :
   public DispatchPtrArray < CMidiCentralListener, CMidiCentralListener *>
{
public:
//   CMidiCentralListenerPtrArray();
//   virtual ~CMidiCentralListenerPtrArray();

};


#endif // !defined(AFX_MIDICENTRALLISTENER_H__0506B76B_4AAE_4D31_A695_5782FF696BE4__INCLUDED_)
