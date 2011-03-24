#pragma once

class CMidiTrackSelectDoc :
	public BaseDocument, 
	public PointerInterface<CMidiTrackSelectDoc>,
   public MidiTrackSelectInterface
{
public:
   CMidiTrackSelectDoc(::ca::application * papp);

//	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnNewDocument();
	virtual bool Initialize(MidiSequence * pmidisequence, bool bEnable);
	virtual ~CMidiTrackSelectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECL_GEN_SIGNAL(_001OnApply)
};
