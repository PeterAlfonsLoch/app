#pragma once

class midi_exception;

class CErrorDialog : public dialog
{
public:
   CErrorDialog(::ca::application * papp);

   void Initialize(midi_exception * pMidiException);

   midi_exception *   m_pMidiException;
   ::ca::bitmap            m_bmpImage;

//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   virtual BOOL OnInitDialog();
};

