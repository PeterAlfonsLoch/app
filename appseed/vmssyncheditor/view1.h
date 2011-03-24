#pragma once

namespace vmssyncheditor
{

class document;
class CMidiTrackSelectDoc;

class view1 :
   public BaseSplitView
{
protected:
   view1(::ca::application * papp); 
	document* get_document();
	MultipleDocumentTemplate* m_pdoctemplateMidiTrackSelect;
   CMidiTrackSelectDoc * m_pdocMidiTrackSelect;


// Operations
public:
	void PrepareMidiLyrics();
   KaraokeUtil         m_karaokeutil;
   mus::microke1      m_microke1;
   CXFInfoHeaders		m_xfInfoHeaders;
	MidiSequence & GetMidiSequence();
	bool OpenDocument(LPCTSTR lpcsz);

	virtual ~view1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnFileInsert)
};

#ifndef _DEBUG  // debug version in view.cpp
inline document* view1::get_document()
   { return (document*)m_pDocument; }
#endif

} // namespace vmssyncheditor