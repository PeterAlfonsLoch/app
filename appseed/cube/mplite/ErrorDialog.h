#pragma once

class midi_exception;

class CErrorDialog : public dialog
{
public:
   CErrorDialog(::ca::application * papp);

public:
   void Initialize(midi_exception * pMidiException);

   midi_exception *   m_pMidiException;
   ::ca::bitmap            m_bmpImage;

   virtual BOOL OnInitDialog();
};
