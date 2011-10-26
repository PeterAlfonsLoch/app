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
// MidiCentralListener.h: interface for the midi_central_listener class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class midi_central;

class CLASS_DECL_ca midi_central_listener  
{
   friend class midi_central;
protected:
   midi_central *       m_pmidicentral;
public:
   void SetMidiCentral(midi_central * pcentral);
   midi_central_listener();
   midi_central_listener(midi_central * pcentral);
   virtual ~midi_central_listener();

protected:
   virtual void OnAttributeChange(int iAttribute);
   virtual void OnAttributeChange(mus::e_midi_central_attribute eattribute);


};

class CLASS_DECL_ca midi_central_listener_ptr_array :
   public DispatchPtrArray < midi_central_listener, midi_central_listener *>
{
public:

};

