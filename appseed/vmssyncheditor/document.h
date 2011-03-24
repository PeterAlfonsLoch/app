#pragma once




namespace vmssyncheditor
{

class document :
   public BaseDocument,
   public mediaplay::MediaDocInterface,
   public data_server,
   public MidiTrackSelectControlInterface
{
public:
   document(::ca::application * papp);

   enum EConfigId
   {
      ConfigIdStartPosition,
      ConfigIdEndPosition,
      ConfigIdToken,
   };

   int m_iCurrentToken;
   int m_iLyricTrack;
   bool  m_bMuteAll;

	virtual bool data_server_save(data_id idSection, data_id idKey, data_id idIndex, gen::variable & var, data_update_hint * puh);
   virtual bool data_server_load(data_id idSection, data_id idKey, data_id idIndex, gen::variable & var, data_update_hint * puh);

	virtual BOOL OnNewDocument();
//	virtual void Serialize(CArchive& ar);

	void OnTrackSelectApply();
	virtual void OnSelectTrack(int iTrack);
   void GetPosition(imedia::Position & position);
	virtual ~document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	DECL_GEN_SIGNAL(_001OnExecutePlay)
	DECL_GEN_SIGNAL(_001OnUpdateExecutePlay)
	DECL_GEN_SIGNAL(_001OnExecuteStop)
	DECL_GEN_SIGNAL(_001OnUpdateExecuteStop)
	DECL_GEN_SIGNAL(_001OnFileExport)
};

} // namespace vmssyncheditor
