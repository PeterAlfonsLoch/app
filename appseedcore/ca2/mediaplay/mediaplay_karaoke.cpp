#include "StdAfx.h"

namespace mediaplay
{

   karaoke::karaoke(::ca::application * papp) :
      ca(papp),
      ikar::karaoke(papp),
      ::audio::WavePlayerInterface(papp)
   {
   }

   karaoke::~karaoke()
   {

   }

   imedia::position karaoke::TimeToPosition(imedia::time time)
   {
      return imedia::position((int) time);
   }
   imedia::time karaoke::PositionToTime(imedia::position position)
   {
      return imedia::time((int) position);
   }

   void karaoke::get_position(imedia::position & position)
   {
      if(GetWavePlayer() != NULL)
      {
         position = (int64_t) GetWavePlayer()->GetWaveOut()->GetPositionMillisForSynch();
      }
   }

   void karaoke::get_time(imedia::time & time)
   {
      if(GetWavePlayer() != NULL)
      {
         time = GetWavePlayer()->GetWaveOut()->GetPositionMillisForSynch();
      }
   }

   void karaoke::GetTimeLength(imedia::time & time)
   {
      UNREFERENCED_PARAMETER(time);
   }

   void karaoke::GetPositionLength(imedia::position & position)
   {
      UNREFERENCED_PARAMETER(position);
   }

   bool karaoke::IsOpened()
   {
      return true;
   }
   void karaoke::Prepare(ikar::data & data)
   {
      imedia::position_2darray tk2a;
      tk2a.add(m_positionaToken);
      string2a & str2a = data.GetStaticData().m_str2aRawTokens;
      imedia::position_2darray position2a;
      stringa * pstra = str2a.add_new();
      string str;
      string strLyrics;
      for(int i = 0; i < m_straToken.get_size(); i++)
      {
         str = m_straToken[i];
         strLyrics += m_straToken[i];
         pstra->add(str);
      }
      Prepare(str2a, tk2a, data);
      data.GetStaticData().m_strLyrics = strLyrics;
   }

   void karaoke::Prepare(int iTrack, ikar::data & data)
   {
      UNREFERENCED_PARAMETER(iTrack);
      UNREFERENCED_PARAMETER(data);
   }

   void karaoke::Prepare(
      string2a & str2a,
      imedia::position_2darray & tka2DTokensTicks,
      ikar::data & data)
   {


      ikar::static_data & staticdata = data.GetStaticData();

      if(staticdata.m_LyricsDisplayOffset < 480)
      {
         staticdata.m_LyricsDisplayOffset = 480;
      }
      if(staticdata.m_LyricsDisplayOffset > 720)
      {
         staticdata.m_LyricsDisplayOffset = 720;
      }
      staticdata.m_LyricsDisplay = 30;

      imedia::position_2darray tk2DBegPositions;
      imedia::position_2darray tk2DEndPositions;
      imedia::time_2darray ms2DTokensMillis;
      imedia::time_2darray ms2DNoteOnMillis;
      imedia::time_2darray ms2DNoteOffMillis;
      imedia::time_2darray ms2DBegMillis;
      imedia::time_2darray ms2DEndMillis;




      PositionToTime(
         ms2DTokensMillis,
         tka2DTokensTicks,
         0);

      ms2DNoteOnMillis = ms2DTokensMillis;
      ms2DBegMillis = ms2DTokensMillis;
      imedia::time_array a;
      int i;
      for(int i = 0; i < ms2DTokensMillis.get_size(); i++)
      {
         int iSize = ms2DTokensMillis[i].get_size();
         a.set_size(iSize);
         iSize--;
         int j;
         for(j = 0; j < iSize; j++)
         {
            a[j] = (ms2DTokensMillis[i][j + 1] * 6 + ms2DTokensMillis[i][j] * 4) / 10;
         }
         if(iSize >= 0)
         {
            a[j] = ms2DTokensMillis[i][j];
         }
         ms2DNoteOffMillis.add(a);
         ms2DEndMillis.add(a);
      }

      EventsTracksV1 lyricEventsForPositionCB;
      EventsTracksV1 lyricEventsForBouncingBall;
      EventsTracksV1 lyricEventsForScoring;
      EventsTracksV1 lyricEvents;



      LyricEventsV2 *pLyricEventsV2;
      LyricEventsV2 *pLyricEventsV2_;
      LyricEventsV2 *pLyricEventsV2B;
      LyricEventsV2 *pLyricEventsV2C;
      tk2DBegPositions.set_size(tka2DTokensTicks.get_size());
      tk2DEndPositions.set_size(tka2DTokensTicks.get_size());
      for(i = 0; i < tka2DTokensTicks.get_size(); i++)
      {
         pLyricEventsV2 = new LyricEventsV2();
         pLyricEventsV2B = new LyricEventsV2();
         pLyricEventsV2C = new LyricEventsV2();
         pLyricEventsV2_ = new LyricEventsV2();
         lyricEvents.add(pLyricEventsV2_);
         lyricEventsForScoring.add(pLyricEventsV2);
         lyricEventsForPositionCB.add(pLyricEventsV2B);
         lyricEventsForBouncingBall.add(pLyricEventsV2C);
         pLyricEventsV2->m_iType = 0;
         pLyricEventsV2->m_iOrder = i;
         pLyricEventsV2->m_iType = 2;
         pLyricEventsV2->m_iOrder = i;
         pLyricEventsV2B->m_iType = ikar::EventRunningElement;
         pLyricEventsV2B->m_iOrder = i;
         pLyricEventsV2C->m_iType = 4;
         pLyricEventsV2C->m_iOrder = i;
         pLyricEventsV2->m_iTrack = -1;
         pLyricEventsV2B->m_iTrack = pLyricEventsV2->m_iTrack;
         pLyricEventsV2C->m_iTrack = pLyricEventsV2->m_iTrack;
         pLyricEventsV2_->m_iTrack = pLyricEventsV2->m_iTrack;
         staticdata.SetGuessMelodyTrack(pLyricEventsV2->m_iTrack);
         pLyricEventsV2->m_dwaNotesData.set_size(str2a[i].get_size());
         pLyricEventsV2B->m_dwaNotesData.set_size(str2a[i].get_size());
         pLyricEventsV2C->m_dwaNotesData.set_size(str2a[i].get_size());
         pLyricEventsV2_->m_dwaNotesData.set_size(str2a[i].get_size());



      }




      LyricEventsV1 *pLyricEventsV1;


      for(i = 0; i < tka2DTokensTicks.get_size(); i++)
      {
         pLyricEventsV2 = (LyricEventsV2 *) lyricEvents.get_at(i);
         TimeToPosition(
            pLyricEventsV2->m_tkaTokensPosition,
            ms2DTokensMillis[i],
            0);
         TimeToPosition(
            pLyricEventsV2->m_tkaNotesPosition,
            ms2DNoteOnMillis[i],
            0);

         imedia::time time1(0);
         imedia::time time2(0);

         pLyricEventsV2->m_msaTokensPosition.CopySorted(
            ms2DTokensMillis[i],
            time1,
            time2);

         pLyricEventsV2->m_msaNotesDuration.Diff(
            ms2DNoteOffMillis[i],
            ms2DNoteOnMillis[i]);

         imedia::time time3(0);
         imedia::time time4(0);

         pLyricEventsV2->m_msaNotesPosition.CopySorted(
            ms2DNoteOnMillis[i],
            time3,
            time4);

         imedia::time time5(0x7fffffff);

         pLyricEventsV2->m_msaTokensDuration.ElementDiff(
            ms2DTokensMillis[i],
            time5);

      }


      for(i = 0; i < tka2DTokensTicks.get_size(); i++)
      {
         pLyricEventsV1 = new LyricEventsV1();
         pLyricEventsV1->m_iType = ikar::EventAdvanceShow;
         pLyricEventsV1->m_iOrder = i;
         //staticdata.m_eventsTracksForPositionCB.add(pLyricEventsV1);
         TimeToPosition(
            pLyricEventsV1->m_tkaTokensPosition,
            ms2DTokensMillis[i],
            -1000);
      }


      for(i = 0; i < tka2DTokensTicks.get_size(); i++)
      {
         pLyricEventsV2 = (LyricEventsV2 *) lyricEventsForScoring.get_at(i);
         staticdata.m_eventsTracksForScoring.add(pLyricEventsV2);
         TimeToPosition(
            pLyricEventsV2->m_tkaTokensPosition,
            ms2DTokensMillis[i],
            0);
         TimeToPosition(
            pLyricEventsV2->m_tkaNotesPosition,
            ms2DNoteOnMillis[i],
            0);

         imedia::time time1(-100);
         imedia::time time2(0);

         pLyricEventsV2->m_msaTokensPosition.CopySorted(
            ms2DTokensMillis[i],
            time1,
            time2);

         pLyricEventsV2->m_msaNotesDuration.Diff(
            ms2DNoteOffMillis[i],
            ms2DNoteOnMillis[i]);

         imedia::time time3(-100);
         imedia::time time4(0);

         pLyricEventsV2->m_msaNotesPosition.CopySorted(
            ms2DNoteOnMillis[i],
            time3,
            time4);

         imedia::time time5(0x7fffffff);

         pLyricEventsV2->m_msaTokensDuration.ElementDiff(
            ms2DTokensMillis[i],
            time5);

         pLyricEventsV2->PrepareForScoring(this);
      }







      for(i = 0; i < tka2DTokensTicks.get_size(); i++)
      {
         pLyricEventsV2 = (LyricEventsV2 *) lyricEventsForPositionCB.get_at(i);
         staticdata.m_eventsTracksForPositionCB.add(pLyricEventsV2);

         staticdata.m_eventstracksV002.add(pLyricEventsV2);

         TimeToPosition(
            pLyricEventsV2->m_tkaTokensPosition,
            ms2DTokensMillis[i],
            -100);

         TimeToPosition(
            pLyricEventsV2->m_tkaNotesPosition,
            ms2DBegMillis[i],
            -100);

         imedia::time time1(-100);
         imedia::time time2(0);

         pLyricEventsV2->m_msaTokensPosition.CopySorted(
            ms2DTokensMillis[i],
            time1,
            time2);

         pLyricEventsV2->m_msaNotesDuration.Diff(
            ms2DEndMillis[i],
            ms2DBegMillis[i]);

         imedia::time time3(-100);
         imedia::time time4(0);

         pLyricEventsV2->m_msaNotesPosition.CopySorted(
            ms2DBegMillis[i],
            time3,
            time4);

         imedia::time time5(0x7fffffff);

         pLyricEventsV2->m_msaTokensDuration.ElementDiff(
            ms2DTokensMillis[i],
            time5);

         pLyricEventsV2->PrepareForLyricsDisplay(this);
      }










      for(i = 0; i < tka2DTokensTicks.get_size(); i++)
      {
         pLyricEventsV2 = (LyricEventsV2 *) lyricEventsForBouncingBall.get_at(i);
         staticdata.m_eventsTracksForBouncingBall.add(pLyricEventsV2);

         TimeToPosition(
            pLyricEventsV2->m_tkaTokensPosition,
            ms2DTokensMillis[i],
            -100);

         TimeToPosition(
            pLyricEventsV2->m_tkaNotesPosition,
            ms2DBegMillis[i],
            -100);

         imedia::time time1(-100);
         imedia::time time2(0);

         pLyricEventsV2->m_msaTokensPosition.CopySorted(
            ms2DTokensMillis[i],
            time1,
            time2);

         pLyricEventsV2->m_msaNotesDuration.Diff(
            ms2DEndMillis[i],
            ms2DBegMillis[i]);

         imedia::time time3(-100);
         imedia::time time4(0);

         pLyricEventsV2->m_msaNotesPosition.CopySorted(
            ms2DEndMillis[i],
            time3,
            time4);

         imedia::time time5(0x7fffffff);

         pLyricEventsV2->m_msaTokensDuration.ElementDiff(
            ms2DTokensMillis[i],
            time5);

         pLyricEventsV2->PrepareForBouncingBall(this);
      }

   }

   void karaoke::ParseSSAFile(ex1::file * pfile)
   {
      delete_contents();

      gen::memory_file file(get_app());
      file.FullLoad(*pfile);
      string str;

      file.to_string(str);
      stringa straLine;
      stringa straSeparator;
      straSeparator.add("\n");
      straSeparator.add("\r");
      straSeparator.add("\r\n");
      straSeparator.add("\n\r");
      straLine.add_smallest_tokens(str, straSeparator, FALSE);

      string strLine;

      bool bOk = false;
      int i = 0;
      while(i < straLine.get_count())
      {
         if(straLine[i] == "[Events]")
         {
            bOk = true;
            break;
         }
         i++;
      }

      if(!bOk)
         return;

      int iFind;
      int iStart;

      string strToken;

      imedia::position position;
      imedia::position duration;
      //imedia::position positionStart;

      int iLineToken;
      int iLine = 0;;

      while(i < straLine.get_count())
      {
         strLine = straLine[i];
         i++;
         if(strLine.Left(10) == "Dialogue: ")
         {
            iStart = 10;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            strToken = strLine.Mid(iStart, iFind - iStart);
            position = TimeToPosition(strToken);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            iFind = strLine.find(",", iStart);
            iStart = iFind + 1;

            if((iFind = strLine.find("{\\k"), iStart) >= 0)
            {
               iLineToken = 0;
               while(true)
               {
                  iStart = iFind + 3;
                  iFind = strLine.find("}", iStart);
                  if(iFind < 0)
                  {
                     break;
                  }
                  strToken = strLine.Mid(iStart, iFind - iStart);
                  duration = atoi(strToken) * 10;
                  m_positionaToken.add(position);
                  position = position + duration;
                  iStart = iFind + 1;
                  iFind = strLine.find("{\\k", iStart);

                  if(iFind < 0)
                  {
                     strToken = strLine.Mid(iStart);
                     str =  strToken;
                     if(iLine % 4 == 0 && iLineToken == 0)
                     {
                        str = "<" + str;
                     }
                     str += "/";
                     m_straToken.add(str);
                     break;
                  }
                  else
                  {
                     strToken = strLine.Mid(iStart, iFind - iStart);
                     str = strToken;
                     if(iLine % 4 == 0 && iLineToken == 0)
                     {
                        str = "<" + str;
                     }
                     m_straToken.add(str);
                  }
                  iLineToken++;
               }
            }
            iLine++;
         }
      }


   }


   void karaoke::ParseKOKFile(ex1::file * pfile)
   {
      delete_contents();

      gen::memory_file file(get_app());
      file.FullLoad(*pfile);
      string str;

      file.to_string(str);
      stringa straLine;
      stringa straSeparator;
      straSeparator.add("\n");
      straSeparator.add("\r");
      straSeparator.add("\r\n");
      straSeparator.add("\n\r");
      straLine.add_smallest_tokens(str, straSeparator, FALSE);

      string strLine;

      int i = 0;

//      bool bOk = false;


      int iFind;
      int iStart;

      string strToken;

      imedia::position position;
      imedia::position duration;
      //imedia::position positionStart;

      int iLineToken;
      int iLine = 0;;

      while(i < straLine.get_count())
      {
         strLine = straLine[i];
         i++;
         iStart = 0;
         iLineToken = 0;
         while(true)
         {
            iFind = strLine.find(";", iStart);
            if(iFind < 0 && iLineToken > 0)
            {
               if(iLine % 4 == 0 && iLineToken == 1)
               {
                  str = "<" + str;
               }
               str += "/";
               m_straToken.add(str);
               break;
            }
            else
            {
               if(iLineToken > 0)
               {
                  m_straToken.add(str);
               }
               strToken = strLine.Mid(iStart, iFind - iStart);
   //            gen::international::ACPToUnicode(str, strToken);
               str = strToken;
               if(iLine % 4 == 0 && iLineToken == 0)
               {
                  str = "<" + str;
               }
            }

            iStart = iFind + 1;
            iFind = strLine.find(";", iStart);
            strToken = strLine.Mid(iStart, iFind - iStart);
            strToken.replace(",",".");
            position = (int) (_tcstod(strToken, NULL) * 1000.0);
            m_positionaToken.add(position);
            //position = position + duration;





            iStart = iFind + 1;
            iLineToken++;
         }
         iLine++;
      }

   }


   imedia::position karaoke::TimeToPosition(const char * lpcsz)
   {
      imedia::position position;

        string_tokenizer strTokenizer(lpcsz);
      string strToken;
      strTokenizer.GetNextToken(strToken, ":", FALSE);
      position = atoi(strToken) * 60 * 60 * 1000;
      strTokenizer.GetNextToken(strToken, ":", FALSE);
      position = position + atoi(strToken) * 60 * 1000;
      strTokenizer.GetNextToken(strToken, ".", FALSE);
      position = position + atoi(strToken) * 1000;
      strTokenizer.GetNextToken(strToken, " ", FALSE);
      position = position + atoi(strToken) * 10;

      return position;
   }

   void karaoke::delete_contents()
   {
      m_positionaToken.remove_all();
      m_straToken.remove_all();
   }

   imedia::position karaoke::GetQuarterNote()
   {
      return 500;
   }

   int karaoke::GetDefaultCodePage()
   {
      return 1252;
   }

} // namespace mediaplay
