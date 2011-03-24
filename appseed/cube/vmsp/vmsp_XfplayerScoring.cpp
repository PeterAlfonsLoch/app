#include "StdAfx.h"
#include "XfplayerScoring.h"
#include <math.h>

double fsimpleround(double value)
{
   double dInteger, dFraction;
   dFraction = modf(value, &dInteger);
   if(dFraction >= 0.0)
      if(dFraction >= 0.5)
         return ceil(value);
      else
         return floor(value);
   else
      if(dFraction <= -0.5)
         return floor(value);
      else
         return ceil(value);
   
   

}

XfplayerScoring::XfplayerScoring(::ca::application * papp)
: thread(papp)
{
   m_dScore = 1.0;
   m_bEnabled = false;
   m_pWaveBuffer = NULL;
}

XfplayerScoring::~XfplayerScoring()
{

}

bool XfplayerScoring::initialize_instance()
{
#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
   HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
   CoInitialize(NULL);
#endif
   return true;
}

int XfplayerScoring::exit_instance()
{
   return thread::exit_instance();
}

 // BEGIN_MESSAGE_MAP(XfplayerScoring, thread)
   //{{AFX_MSG_MAP(XfplayerScoring)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
//   ON_THREAD_MESSAGE(MessageWaveInData, OnWaveInData)
 // END_MESSAGE_MAP()

void XfplayerScoring::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(MessageWaveInData, pinterface, this, &XfplayerScoring::OnWaveInData);
}

void XfplayerScoring::CalcFrequenciesRange(
   BYTE bNote)
{
   double dFrequencySample;
   
   dFrequencySample = ::mus::midi::GetNoteFrequency(m_dLa4Frequency, bNote);
//   TRACE("Reference Frequency : %f  ", dFrequencySample);
   while(dFrequencySample > m_dMinimumFrequency
      && dFrequencySample != 0.0)
   {
      dFrequencySample /= 2;
   }
   if(dFrequencySample < m_dMinimumFrequency)
   {
      dFrequencySample *= 2;
   }
   m_frequenciesRange.remove_all();
   DOUBLESIMPLERANGE dsr;
   while(dFrequencySample <= m_dMaximumFrequency)
   {
//      m_frequenciesRange.set_size(m_frequenciesRange.get_size() + 1);
//       = m_frequenciesRange.get_at(m_frequenciesRange.get_size() - 1);
      dsr.dA = dFrequencySample / m_dMaximumDeviation;
      dsr.dB = dFrequencySample * m_dMaximumDeviation;
      m_frequenciesRange.add(dsr);
      dFrequencySample *= 2;
   }

}

void XfplayerScoring::Initialize(
   double dA4Frequency,
   double dSamplingFrequency,
   audWaveBuffer * pWaveBuffer)
{
   m_dLa4Frequency = dA4Frequency;
   m_dMinimumFrequency = ::mus::midi::GetNoteFrequency(dA4Frequency, 0);
   m_dMaximumFrequency = ::mus::midi::GetNoteFrequency(dA4Frequency, 96);
   m_dMaximumDeviation = pow(2.0, 1.0 / 48.0);
   m_dSamplingFrequency = dSamplingFrequency;
   m_dSampleHarmonicFrequency = dSamplingFrequency / pWaveBuffer->m_uiAnalysisSize;
   m_dInterestSamplesCount = pWaveBuffer->m_uiInterestSize;
   m_pWaveBuffer = pWaveBuffer;
}

void XfplayerScoring::CalcHarmonicsRange()
{
   int i;
   m_harmonicsRange.set_size(m_frequenciesRange.get_size());
   DOUBLESIMPLERANGE dsrH;
   for(i = 0; i < m_frequenciesRange.get_size(); i++)
   {
      DOUBLESIMPLERANGE &dsrF = m_frequenciesRange.get_at(i);   
      dsrH.dA = fsimpleround(dsrF.dA / m_dSampleHarmonicFrequency);
      dsrH.dB = fsimpleround(dsrF.dB / m_dSampleHarmonicFrequency);
      m_harmonicsRange.set_at(i, dsrH)   ;
   }
   for(i = 0; i < m_frequenciesRange.get_size(); i++)
   {
      DOUBLESIMPLERANGE &dsrH = m_harmonicsRange.get_at(i);   
      if(dsrH.dA > m_dInterestSamplesCount ||
         dsrH.dB > m_dInterestSamplesCount)
      {
         m_harmonicsRange.set_size(i);
         break;
      }
   }

}
// esse é que está sendo usado


bool is_pow(double dValue, double dBase)
{
   return fmod(log(dValue) / log(dBase), 1.0) == 0.0;
}

void XfplayerScoring::MatchV1(double dPositionRate, double *pdDeltaScore)
{
   if(m_pWaveBuffer == NULL)
      return;
   double * pdSamples = m_pWaveBuffer->FFTGetResult();
   int i, j;
   bool bFound = false;
   double dDeltaScore = 0.0;
    double dMaxLevel = m_pWaveBuffer->GetMaxLevel();
    int iFound = 0;
    int iOutFound = 0;
   for(i = 0; i < m_harmonicsRange.get_size(); i++)
   {
      DOUBLESIMPLERANGE &dsrH = m_harmonicsRange.get_at(i);   
      //if(i > 0 && (((i + 1) % 2) != 0))
      bool bIsPow = is_pow(i + 1.0, 2.0);
      if(i > 0 && !bIsPow)
      {
         DOUBLESIMPLERANGE &dsrH1 = m_harmonicsRange.get_at(i - 1);   
         DOUBLESIMPLERANGE &dsrH2 = m_harmonicsRange.get_at(i);   
         for(j = (int) ((dsrH1.dA + dsrH2.dA) / 2.0); j <= ((dsrH1.dB + dsrH2.dB) / 2.0); j++)
         {
         if(pdSamples[j] > dMaxLevel * 0.50)
            {
               iOutFound++;
   //            TRACE("Matching Frequency: %f\n", j * m_dSampleHarmonicFrequency);
   //            if(m_dScore == 0.0)
   //               m_dScore = 30.0 / 100.0;
   //            else if(m_dScore < 1.2)
   //               m_dScore += (1.2 - m_dScore) / 5.0;
   //         if(m_dScore > 0)
   //            m_dScore += (2.0 * (1.0 - dPositionRate) / 100);
   //            break;
   //         if(m_dScore > 0)
   //            break;
            }
         }
      }
      for(j = (int) dsrH.dA; j <= dsrH.dB; j++)
      {
      if(pdSamples[j] > dMaxLevel * 0.50)
         {
            iFound++;
//            TRACE("Matching Frequency: %f\n", j * m_dSampleHarmonicFrequency);
//            if(m_dScore == 0.0)
//               m_dScore = 30.0 / 100.0;
//            else if(m_dScore < 1.2)
//               m_dScore += (1.2 - m_dScore) / 5.0;
//         if(m_dScore > 0)
//            m_dScore += (2.0 * (1.0 - dPositionRate) / 100);
//            break;
//         if(m_dScore > 0)
//            break;
         }
      }
   }
   if(iOutFound == 0)
   {
      m_bFoundMatch = true;
      if(m_dScore < 1.2)
      {
         m_dScore += m_dScoreAddUp * iFound;
         dDeltaScore += m_dScoreAddUp;;
      }
   }
//   if(!bFound)
//   {
//      TRACE("UNMATCH!!!: \n");
//      if(m_dScore > 0)
//         m_dScore -= (1.0 * (1.0 - dPositionRate) / 100);
//      if(m_dScore > 0)
//      {
//         m_dScore -= m_dScoreAddUp;
//      }
//      dDeltaScore -= m_dScoreAddUp;
//
//   }
   (*pdDeltaScore) += dDeltaScore;
}

void XfplayerScoring::MatchV2(double dPositionRate)
{
   double dAmplitude;
   double dHarmonic = m_pWaveBuffer->PeakValueFrequency(&dAmplitude);
   bool bFound = false;
   int i;
   if(dAmplitude > m_pWaveBuffer->GetMaxLevel() * 0.40)
   {
      for(i = 0; i < m_harmonicsRange.get_size(); i++)
      {
         DOUBLESIMPLERANGE &dsrH = m_harmonicsRange.get_at(i);   
         if(dHarmonic >= dsrH.dA &&
            dHarmonic <= dsrH.dB)
         {
            TRACE("Matching Frequency: %f\n", dHarmonic * m_dSampleHarmonicFrequency);
//            TRACE("1.0 - PositionRate: %f\n", 1.0 - dPositionRate);
            bFound = true;
//            m_dScoreDown = 0.0;
            if(m_dScore < 1.2)
               m_dScore += (1.2 - m_dScore) * (1.0 - dPositionRate) / 20.0 ;
            break;
         }
         if(bFound)
            break;
      }
   }
   if(!bFound)
   {
      TRACE("UnMatching Frequency: %f\n", dHarmonic * m_dSampleHarmonicFrequency);
//      TRACE("1.0 - PositionRate: %f\n", 1.0 - dPositionRate);
      if(m_dScore > 0)
         m_dScore -= (1.0 * (1.0 - dPositionRate) / 100);
      //m_dScoreDown += (.25 * (1.0 - dPositionRate) / 100);
   }

}

void XfplayerScoring::MatchV3(double dPositionRate, double *pdDeltaScore)
{
   if(m_pWaveBuffer == NULL)
      return;
   double * pdSamples = m_pWaveBuffer->FFTGetResult();
   double_array daFreq;
   double_array daAmp;

   m_pWaveBuffer->PeakValueFrequencies(daFreq, daAmp, 16);

   int i, j;
   bool bFound = false;
   double dDeltaScore = 0.0;
    double dMaxLevel = m_pWaveBuffer->GetMaxLevel();
    int iFound = 0;
    int iOutFound = 0;
   for(i = 0; i < m_harmonicsRange.get_size(); i++)
   {
      DOUBLESIMPLERANGE &dsrH = m_harmonicsRange.get_at(i);   
      for(j = (int) dsrH.dA; j <= dsrH.dB; j++)
      {
         if(daFreq.contains(j))
         {
            iFound++;
//            TRACE("Matching Frequency: %f\n", j * m_dSampleHarmonicFrequency);
//            if(m_dScore == 0.0)
//               m_dScore = 30.0 / 100.0;
//            else if(m_dScore < 1.2)
//               m_dScore += (1.2 - m_dScore) / 5.0;
//         if(m_dScore > 0)
//            m_dScore += (2.0 * (1.0 - dPositionRate) / 100);
//            break;
//         if(m_dScore > 0)
//            break;
         }
      }
   }
   if(iOutFound == 0)
   {
      m_bFoundMatch = true;
      if(m_dScore < 1.2)
      {
         m_dScore += m_dScoreAddUp * iFound;
         dDeltaScore += m_dScoreAddUp;;
      }
   }
//   if(!bFound)
//   {
//      TRACE("UNMATCH!!!: \n");
//      if(m_dScore > 0)
//         m_dScore -= (1.0 * (1.0 - dPositionRate) / 100);
//      if(m_dScore > 0)
//      {
//         m_dScore -= m_dScoreAddUp;
//      }
//      dDeltaScore -= m_dScoreAddUp;
//
//   }
   (*pdDeltaScore) += dDeltaScore;
}


void XfplayerScoring::Start(DWORD msMelodyDuration)
{
   m_dScore = 0.0;
   m_msMelodyDuration = msMelodyDuration;
   if(m_msMelodyDuration != 0)
   {
      m_dScoreAddUp = 
         4000 *
         m_pWaveBuffer->m_uiAnalysisSize /
         (m_dSamplingFrequency *
         msMelodyDuration);
   }
   else
   {
      m_dScoreAddUp = 0.0;
   }
    Enable(true);

}

void XfplayerScoring::Process(BYTE bNote, double dPositionRate, double * pdDeltaScore)
{
   CalcFrequenciesRange(bNote);
   CalcHarmonicsRange();
   //MatchV1(dPositionRate, pdDeltaScore);
   MatchV3(dPositionRate, pdDeltaScore);
}

void XfplayerScoring::Process(dword_array * pdwaNotes, double dPositionRate, double * pdDeltaScore)
{
   int i;
   for(i = 0; i < pdwaNotes->get_size(); i++)
   {
      m_bFoundMatch = false;
      CalcFrequenciesRange((BYTE) pdwaNotes->get_at(i));
      CalcHarmonicsRange();
      MatchV3(dPositionRate, pdDeltaScore);

   }
   if(!m_bFoundMatch && (pdwaNotes->get_size() > 0))
   {
      if(m_dScore > 0)
      {
         m_dScore -= m_dScoreAddUp;
      }
      (*pdDeltaScore) -= m_dScoreAddUp;
   }
}

bool XfplayerScoring::IsEnabled()
{
    return m_bEnabled;
}

VMSRESULT XfplayerScoring::Enable(bool bEnable)
{
   audWaveCentral & wavecentral = Application.GetAudioWaveCentral();
   audWaveIn * pwavein = wavecentral.GetWaveIn();
   if(bEnable)
   {
      m_bEnabled = true;
      pwavein->AddListener(this);
   }
   else
   {
      m_bEnabled = false;
      pwavein->RemoveListener(this);
   }

   return VMSR_SUCCESS;
}

void XfplayerScoring::WaveInDataProc(audWaveIn *pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr)
{
   CSingleLock slWaveInData(&m_csWaveInData, true);
   m_waveindataa.add(CWaveInData(pwavein, dwSampleTime, lpwavehdr));
   slWaveInData.Unlock();
   PostThreadMessage(MessageWaveInData, 0, 0);
}

void XfplayerScoring::OnWaveInData(gen::signal_object * pobj)
{
   CSingleLock slWaveInData(&m_csWaveInData, true);
   if(m_waveindataa.get_size() <= 0)
      return;
   CWaveInData waveindata = m_waveindataa.get_at(0);
   slWaveInData.Unlock();
   WaveInDataProc(waveindata);
}

void XfplayerScoring::WaveInDataProc(CWaveInData & waveindata)
{
   if(!IsEnabled())
      return;
   audWaveIn * pwavein = waveindata.m_pwavein;
   imedia::time dwSampleTime = waveindata.m_dwSampleTime;
   LPWAVEHDR lpwavehdr = waveindata.m_lpwavehdr;
   ASSERT(lpwavehdr != NULL);
   
   critical_section & csHandle = pwavein->GetHandleCriticalSection();
     

   ikar::data & data = GetKaraokeData();
   ikar::karaoke * pinterface = data.GetInterface();
   if(!pinterface->IsOpened())
      return;

   ikar::static_data & staticdata = data.GetStaticData();

   

   int msPosition;
   imedia::time dwPositionTime;
   imedia::position tkPosition;
   pinterface->GetPosition(tkPosition);
   dwPositionTime = timeGetTime();
   msPosition = pinterface->PositionToTime(tkPosition);
   //msPosition = msPosition - (dwPositionTime - dwSampleTime);

   // Valor de Correção
   //msPosition = msP100;
   
   audWaveBuffer & buffer = pwavein->GetBuffer();
   double dDeltaScore = -100.0;
   EventsTracksV1 * peventsa = &staticdata.m_eventsTracksForScoring;
   LyricEventsV2 * pevents;
   if(staticdata.m_str2aRawTokens.get_size() <= 0)
      pevents = NULL;
   else if(peventsa->get_size() < staticdata.m_str2aRawTokens.get_size())
      pevents = NULL;
   else
   {
      //pEvents = (LyricEventsV2 *) pEventsArray->operator [](pDoc->m_p2DTokens->get_size());
      pevents = (LyricEventsV2 *) peventsa->operator [](0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
      
   if(pevents != NULL)
   {
      int i;
      int_array iaNotes;
      //m_iaNotes.remove_all();
      pevents->GetMillisIntervalNotes(
         iaNotes,
         msPosition  - pwavein->GetAnalysisMillis() - 100,
         msPosition);
      dDeltaScore = 0;
      dword_array dwaNotes;
      for(i = 0; i < iaNotes.get_size(); i++)
      {
         dwaNotes.add(pevents->GetNotePitch(iaNotes.element_at(i)));
      }
      imedia::time timeLength;
      pinterface->GetTimeLength(timeLength);
      Process(&dwaNotes, (double) msPosition / timeLength, &dDeltaScore );
   }


}

