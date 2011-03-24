#pragma once


typedef struct tagDoubleSimpleRange
{
   double         dA;
   double         dB;
} DOUBLESIMPLERANGE, * LPDOUBLESIMPLERANGE;

class CLASS_DECL_CA2_CUBE XfplayerScoring :
   public ::radix::thread,
   public audWaveInListener,
   public ikar::data_container
{

public:
   enum e_message
   {
      MessageWaveInData = WM_APP,
   };
   // // DECLARE_DYNCREATE(XfplayerScoring)
   class CWaveInData
   {
   public:
      CWaveInData();
      CWaveInData(
         audWaveIn *    pwavein,
         DWORD                   dwSampleTime,
         LPWAVEHDR               lpwavehdr);
      audWaveIn *      m_pwavein;
      DWORD          m_dwSampleTime;
      LPWAVEHDR      m_lpwavehdr;
   };
    bool m_bEnabled;
public:

   XfplayerScoring(::ca::application * papp);
   virtual ~XfplayerScoring();

   VMSRESULT Enable(bool bEnable);
   bool IsEnabled();
   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
   bool m_bFoundMatch;
   void Process(BYTE bNote, double dPositionRate, double * dDeltaScore);
   void Process(dword_array *pdwaNotes, double dPositionRate, double * dDeltaScore);
   void Start(DWORD msMelodyDuration);
   void MatchV3(double dPositionRate, double *pdDeltaScore);
   void MatchV1(double dPositionRate, double * pdDeltaScore);
   void MatchV2(double dPositionRate);
   void CalcHarmonicsRange();
   void Initialize(
      double dA3Frequency,
      double dSamplingFrequency,
      audWaveBuffer * pWaveBuffer);
   void WaveInDataProc(CWaveInData & waveindata);

   virtual bool initialize_instance();
   virtual int exit_instance();


   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);


   inline double GetMinimumFrequency()
   {
      return m_dMinimumFrequency;
   }
   inline double GetLa4Frequency()
   {
      return m_dLa4Frequency;
   }
   inline double GetScore()
   {
      return m_dScore;
   }
   void CalcFrequenciesRange(
      BYTE bNote);
   base_array <DOUBLESIMPLERANGE, DOUBLESIMPLERANGE &>
                  m_frequenciesRange;
   base_array <DOUBLESIMPLERANGE, DOUBLESIMPLERANGE &>
                  m_harmonicsRange;
   double            m_dMinimumFrequency; 
   double            m_dMaximumFrequency; 
   double            m_dLa4Frequency;
   double            m_dMaximumDeviation;
   double            m_dInterestSamplesCount;
   double            m_dSamplingFrequency;
   double            m_dSampleHarmonicFrequency;
   double            m_dScore;
   DWORD            m_msMelodyDuration;
   double            m_dScoreAddUp;
   critical_section        m_csWaveInData;
   base_array < CWaveInData, CWaveInData > m_waveindataa;
      base_array <int, int >  m_iaNotes;

//   double            m_dScoreDown;
   audWaveBuffer *      m_pWaveBuffer;

   // Generated message ::collection::map functions
   //{{AFX_MSG(XfplayerScoring)
      // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG

   ()

   DECL_GEN_SIGNAL(OnWaveInData)

};

inline XfplayerScoring::CWaveInData::CWaveInData(
   audWaveIn *    pwavein,
   DWORD                   dwSampleTime,
   LPWAVEHDR               lpwavehdr)
{
   m_pwavein = pwavein;
   m_dwSampleTime = dwSampleTime;
   m_lpwavehdr = lpwavehdr;
}

inline XfplayerScoring::CWaveInData::CWaveInData()
{
   m_pwavein = NULL;
   m_dwSampleTime = 0;
   m_lpwavehdr = NULL;
}
