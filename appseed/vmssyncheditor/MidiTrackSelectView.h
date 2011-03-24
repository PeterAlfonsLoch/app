#pragma once


class CMidiTrackSelectView :
	public BaseView,
	public PointerInterface<CMidiTrackSelectView>,
	public data_client
{
public:
   CMidiTrackSelectView(::ca::application * papp);

	MidiSequence * m_pmidisequence;
	BaseIntArray	m_iaRealLevel;
	BaseIntArray	m_iaTimer;
	BaseIntArray	m_iaDisplayLevel;
	BaseIntArray	m_iaLastLevel;
	array_app_alloc<SimplePushButton, SimplePushButton> m_buttonaTrackNoteOn;
	XfplayerViewLines	m_lineaInstrument;
	BaseIntArray	m_iaInstrument;
	CPen				m_penInstrument;
	base_rect_array	m_recta;
	array<base_rect_array, base_rect_array & > m_rect2a;
	bool				m_bEnabled;
	CDC				m_dcBack;
	CBitmap			m_bmpBack;
	base_rect				m_rectLevelMeter;
	virtual void PostNcDestroy();
	virtual void OnUpdate(view* pSender, LPARAM lHint, base_object* pHint);
	virtual void _001OnDraw(CDC* pDC);

   void RenderLevelMeter(CDC * pdc);
	void UpdatePushButtonMute(int iIndex);
	bool IsEnabled();
	bool Enable(bool bEnable = true);
	int GetLowerLevel(int iChannel);
	void Layout();
	void Update(bool bRedraw);
	void OnTimerProc(UINT nIDEvent);
	afx_msg LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);
	void TimerProc(UINT uiIDEvent);
	double GetRateComplement(int iChannel);
	double GetRate(int iChannel);
	void TwiOnDraw(CDC * pdc);
	void GetLowerRect(LPRECT lprect, int iChannel);
	void GetUpperRect(LPRECT lprect, int iChannel);
	bool Initialize(MidiSequence * pmidisequence, bool bEnable);
	virtual ~CMidiTrackSelectView();

	afx_msg void OnPushButtonTrackNoteOn(UINT nID);

	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnContextMenu)
};

