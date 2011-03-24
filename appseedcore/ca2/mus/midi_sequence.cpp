/*****************************************************************************
*
*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
*  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
*  A PARTICULAR PURPOSE.
*
*  Copyright (C) 1993 - 1997 ca2. 
*
******************************************************************************
*
* Sequence.C
*
* Sequencer engine for MIDI player cast
*
*****************************************************************************/
#include "StdAfx.h"

namespace mus
{

   namespace midi
   {
      //PRIVATE void FAR PASCAL seqMIDICallback(HMIDISTRM hms, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
      //MMRESULT TranslateSMFResult(e_file_result smfrc);

      sequence::sequence(::ca::application * papp) :
         ca(papp),
         ikar::karaoke(papp),
         m_evMmsgDone(FALSE, TRUE), 
         m_memfile(papp)
      {
         m_pthread = NULL;
         m_iaLevel.set_size(16);
         SetLevelMeter(0);

         //   m_cBuffer = 0;
         //   m_cbBuffer = 0;
         //m_pstrFile =  NULL;
         m_uiDeviceID = 0;
         //   m_uMCIDeviceID = 0;
         //   m_uMCITimeFormat = 0;
         //   m_uMCITimeDiv = 0;
         //   m_hWnd = NULL;

         m_uiPreviousState = StatusNoFile;
         m_uiState = StatusNoFile;
         m_tkLength = 0;
         m_mmrcLastErr = 0;

         m_hMidiStream = NULL;
         m_dwTimeDivision = 0;

         m_lpbAlloc = 0;
         m_tkBase = 0;
         m_tkEnd = 0;

         m_cbPreroll = 8 * 1024;
         m_cbPrerollNominalMax = 8 * 256;

         m_pfile = new file(get_app());

         m_buffera.Initialize(16, m_cbPreroll, (DWORD) (void *) &m_midicallbackdata);


      };

      sequence::~sequence()
      {

         CloseFile();
         if(m_pfile != NULL)
         {
            delete m_pfile;
            m_pfile = NULL;
         }
      }


      /***************************************************************************
      *  
      * seqAllocBuffers
      *
      * allocate buffers for this instance.
      *
      * pSeq                      - The sequencer instance to allocate buffers for.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation was successful.
      *
      *   MCIERR_OUT_OF_MEMORY  If there is insufficient primitive::memory for
      *     the requested number and size of buffers.
      *
      * seqAllocBuffers allocates playback buffers based on the
      * cbBuffer and cBuffer fields of pSeq. cbBuffer specifies the
      * number of bytes in each buffer, and cBuffer specifies the
      * number of buffers to allocate.
      *
      * seqAllocBuffers must be called before any other sequencer call
      * on a newly allocted SEQUENCE structure. It must be paired with
      * a call to seqFreeBuffers, which should be the last call made
      * before the SEQUENCE structure is discarded.
      *
      ***************************************************************************/
      MMRESULT sequence::AllocBuffers()
      {
         ASSERT(FALSE);
         /*
         DWORD                   dwEachBufferSize;
         DWORD                   dwAlloc;
         UINT                    i;
         LPBYTE                  lpbWork;

         //    assert(pSeq != NULL);

         SetState(StatusNoFile);
         m_lpmhFree  = NULL;
         m_lpbAlloc  = NULL;
         //    m_hSmf      = (HSMF)NULL;

         // First make sure we can allocate the buffers they asked for
         //
         dwEachBufferSize = sizeof(MIDIHDR) + (DWORD)(m_cbBuffer);
         dwAlloc          = dwEachBufferSize * (DWORD)(m_cBuffer);

         //m_lpbAlloc = (unsigned char *) GlobalAllocPtr(GMEM_MOVEABLE|GMEM_SHARE, dwAlloc);
         m_lpbAlloc = (unsigned char *) HeapAlloc(GetProcessHeap(), 0, dwAlloc);
         if (NULL == m_lpbAlloc)
         return MCIERR_OUT_OF_MEMORY;

         // Initialize all MIDIHDR's and throw them into a free list
         //
         m_lpmhFree = NULL;

         lpbWork = m_lpbAlloc;
         for (i=0; i < m_cBuffer; i++)
         {
         ((LPMIDIHDR)lpbWork)->lpNext            = m_lpmhFree;

         ((LPMIDIHDR)lpbWork)->lpData            = (char *) (lpbWork + sizeof(MIDIHDR));
         ((LPMIDIHDR)lpbWork)->dwBufferLength    = m_cbBuffer;
         ((LPMIDIHDR)lpbWork)->dwBytesRecorded   = 0;
         ((LPMIDIHDR)lpbWork)->dwUser            = (DWORD)(UINT)this;
         ((LPMIDIHDR)lpbWork)->dwFlags           = 0;

         m_lpmhFree = (LPMIDIHDR)lpbWork;

         lpbWork += dwEachBufferSize;
         }

         return MMSYSERR_NOERROR;*/
         return MMSYSERR_NOERROR;
      }

      /***************************************************************************
      *  
      * seqFreeBuffers
      *
      * Free buffers for this instance.
      *
      * pSeq                      - The sequencer instance to free buffers for.
      *   
      * seqFreeBuffers frees all allocated primitive::memory belonging to the
      * given sequencer instance pSeq. It must be the last call
      * performed on the instance before it is destroyed.
      *       
      ****************************************************************************/
      VOID sequence::FreeBuffers()
      {
         ASSERT(FALSE);
         /*
         LPMIDIHDR               lpmh;

         //    assert(pSeq != NULL);

         if (NULL != m_lpbAlloc)
         {
         lpmh = (LPMIDIHDR)m_lpbAlloc;
         ASSERT(!(lpmh->dwFlags & MHDR_PREPARED));

         //GlobalFreePtr(m_lpbAlloc);
         HeapFree(GetProcessHeap(), 0, m_lpbAlloc);
         }*/
      }

      /***************************************************************************
      *  
      * seqOpenFile
      *
      * Associates a MIDI file with the given sequencer instance.
      *
      * pSeq                      - The sequencer instance.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If there is already a file open
      *     on this instance.
      *     
      *   MCIERR_OUT_OF_MEMORY If there was insufficient primitive::memory to
      *     allocate internal buffers on the file.
      *
      *   MCIERR_INVALID_FILE If initial attempts to parse the file
      *     failed (such as the file is not a MIDI or RMI file).
      *
      * seqOpenFile may only be called if there is no currently open file
      * on the instance. It must be paired with a call to seqCloseFile
      * when operations on this file are complete.
      *
      * The pstrFile field of pSeq contains the name of the file
      * to open. This name will be passed directly to mmioOpen; it may
      * contain a specifcation for a custom MMIO file handler. The task
      * context used for all I/O will be the task which calls seqOpenFile.
      *
      ***************************************************************************/

      MMRESULT sequence::OpenFile(
         sequence &sequence,
         int openMode)
      {
         MMRESULT                rc      = MMSYSERR_NOERROR;
         SMFFILEINFO             sfi;
         e_file_result               smfrc;
         DWORD                   cbBuffer;

         if (GetState() != StatusNoFile)
         {
            return MCIERR_UNSUPPORTED_FUNCTION;
         }

         m_iOpenMode = openMode;

         smfrc = m_pfile->OpenFile(sequence.GetFile(), openMode);

         if (mus::midi::Success != smfrc)
         {
            rc = TranslateSMFResult(smfrc);
            goto Seq_Open_File_Cleanup;
         }

         m_pfile->GetFileInfo(&sfi);

         m_dwTimeDivision = sfi.dwTimeDivision;
         m_tkLength       = sfi.tkLength;
         if(m_iOpenMode == OpenForPlaying)
         {
            m_msLength      = TicksToMillisecs(m_tkLength);
         }
         /* Track buffers must be big enough to hold the state data returned
         ** by smfSeek()
         */
         cbBuffer = min(m_cbBuffer, GetStateMaxSize());


   Seq_Open_File_Cleanup:    
         if (MMSYSERR_NOERROR != rc)
            CloseFile();
         else
            SetState(StatusOpened);

         return rc;
      }

      MMRESULT sequence::OpenFile(
         const char * lpFileName,
         int openMode)
      {
         ex1::filesp file(
            get_app());
         file->open(lpFileName,
            ::ex1::file::mode_read |
            ::ex1::file::shareDenyWrite |
            ::ex1::file::type_binary);
         return OpenFile(file, openMode);
      }
      MMRESULT sequence::OpenFile(
         primitive::memory * pmemorystorage,
         int openMode,
         mus::EStorage estorage)   
      {                            
         MMRESULT                rc = MMSYSERR_NOERROR;
         SMFFILEINFO             sfi;
         e_file_result    smfrc;
         DWORD                   cbBuffer;

         if (GetState() != StatusNoFile)
         {
            CloseFile();
            //return MCIERR_UNSUPPORTED_FUNCTION;
         }

         m_iOpenMode = openMode;

         smfrc = m_pfile->OpenFile(pmemorystorage, openMode, estorage);

         if (mus::midi::Success != smfrc)
         {
            rc = TranslateSMFResult(smfrc);
         }
         else
         {
            m_pfile->GetFileInfo(&sfi);

            m_dwTimeDivision = sfi.dwTimeDivision;
            m_tkLength       = sfi.tkLength;
            if(m_iOpenMode == OpenForPlaying)
            {
               m_msLength      = TicksToMillisecs(m_tkLength);
            }
            /* Track buffers must be big enough to hold the state data returned
            ** by smfSeek()
            */
            cbBuffer = min(m_cbBuffer, GetStateMaxSize());
         }

         if(MMSYSERR_NOERROR != rc)
            CloseFile();
         else
            SetState(StatusOpened);

         return rc;
      }

      MMRESULT sequence::OpenFile(
         ex1::file & ar,
         int openMode)
      {                            
         MMRESULT                rc      = MMSYSERR_NOERROR;
         //    SMFOPENFILESTRUCT       sofs;
         SMFFILEINFO             sfi;
         e_file_result               smfrc;
         DWORD                   cbBuffer;
         //    assert(pSeq != NULL);

         if (GetState() != StatusNoFile)
         {
            return MCIERR_UNSUPPORTED_FUNCTION;
         }



         //   m_pstrFile = _tcsdup(lpFileName);
         //   m_strFile = lpFileName;

         //    ASSERT(m_pstrFile != NULL);

         m_iOpenMode = openMode;

         //    sofs.pstrName     = m_pstrFile;

         //PSMF pSmf = new SMF();

         //smfrc = m_pfile->OpenFile(&sofs);
         smfrc = m_pfile->OpenFile(ar, openMode);

         //smfrc = smfOpenFile(&sofs);
         if (mus::midi::Success != smfrc)
         {
            //      delete pSmf;
            rc = TranslateSMFResult(smfrc);
         }
         else
         {
            //    m_hSmf = sofs.hSmf;
            //    ((PSMF) m_hSmf)->GetFileInfo(&sfi);
            m_pfile->GetFileInfo(&sfi);

            m_dwTimeDivision = sfi.dwTimeDivision;
            m_tkLength       = sfi.tkLength;
            if(m_iOpenMode == OpenForPlaying)
            {
               m_msLength      = TicksToMillisecs(m_tkLength);
            }
            /* Track buffers must be big enough to hold the state data returned
            ** by smfSeek()
            */
            cbBuffer = min(m_cbBuffer, GetStateMaxSize());
         }

         if (MMSYSERR_NOERROR != rc)
            CloseFile();
         else
            SetState(StatusOpened);

         return rc;
      }
      /***************************************************************************
      *  
      * seqCloseFile
      *
      * Deassociates a MIDI file with the given sequencer instance.
      *
      * pSeq                      -  The sequencer instance.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     stopped.
      *     
      * A call to seqCloseFile must be paired with a prior call to
      * seqOpenFile. All buffers associated with the file will be
      * freed and the file will be closed. The sequencer must be
      * stopped before this call will be accepted.
      *
      ***************************************************************************/
      MMRESULT sequence::CloseFile()
      {
         CSingleLock sl(&m_mutex, true);

         //if (StatusNoFile == GetState())
         //   return MCIERR_UNSUPPORTED_FUNCTION;

         m_pfile->CloseFile();

         /* If we were prerolled, need to clean up -- have an open MIDI handle
         ** and buffers in the ready queue
         */

         //    CSingleLock slStream(&m_csStream, false);

         //    for (lpmh = m_lpmhFree; lpmh; lpmh = lpmh->lpNext)
         //    for (lpmh = m_buffera[0]; lpmh != NULL; lpmh = lpmh->lpNext)


         /*   m_lpmhFree = NULL;

         if (m_lpmhPreroll != NULL)
         {
         slStream.Lock();
         if(m_hMidiStream != NULL)
         {
         midiOutUnprepareHeader((HMIDIOUT) m_hMidiStream, m_lpmhPreroll, sizeof(*m_lpmhPreroll));
         }
         slStream.Unlock();
         }
         m_lpmhPreroll = NULL;*/
         //    slStream.Lock();
         if (m_hMidiStream != NULL)
         {
            m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hMidiStream);
            midiStreamClose( m_hMidiStream);
            m_hMidiStream = NULL;
         }
         //  slStream.Unlock();

         SetState(StatusNoFile);

         return MMSYSERR_NOERROR;
      }

      /***************************************************************************
      *  
      * seqPreroll
      *
      * Prepares the file for playback at the given position.
      *
      * pSeq                      - The sequencer instance.
      *
      * lpPreroll                 - Specifies the starting and ending tick
      *                             positions to play between.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     opened or prerolled.
      *
      * open the device so we can initialize channels.
      *
      * Loop through the tracks. For each track, seek to the given position and
      * send the init data SMF gives us to the handle.
      *
      * Wait for all init buffers to finish.
      *
      * Unprepare the buffers (they're only ever sent here; the sequencer
      * engine merges them into a single stream during normal playback) and
      * refill them with the first chunk of data from the track. 
      *
      *     
      ****************************************************************************/
      MMRESULT sequence::Preroll(
         ::radix::thread *         pthread,
         LPPREROLL            lpPreroll,
         bool                  bThrow)
      {
         UNREFERENCED_PARAMETER(pthread);
         CSingleLock sl(&m_mutex, TRUE);
         int i;
         //   midi_callback_data *      lpData = &m_midicallbackdata;
         e_file_result     smfrc;
         MMRESULT                mmrc        = MMSYSERR_NOERROR;
         MIDIPROPTIMEDIV         mptd;
         LPMIDIHDR               lpmh = NULL;
         //   LPMIDIHDR               lpmhPreroll = NULL;
         UINT                    uDeviceID;


         ASSERT(m_iOpenMode == OpenForPlaying
            || IsInSpecialModeV001());

         m_flags.unsignalize(FlagEOF);

         m_mmrcLastErr = MMSYSERR_NOERROR;

         if(GetState() != StatusOpened &&
            GetState() != StatusPreRolled &&
            !IsInSpecialModeV001())
            return MCIERR_UNSUPPORTED_FUNCTION;

         m_tkBase = lpPreroll->tkBase;
         m_tkEnd = lpPreroll->tkEnd;
         if(m_hMidiStream != NULL)
         {
            // Recollect buffers from MMSYSTEM back into free queue
            //
            SetState(StatusReset);
            midiOutReset((HMIDIOUT) m_hMidiStream);
            while (m_uBuffersInMMSYSTEM)
               Sleep(0);
         }
         else
         {
         }

         m_uBuffersInMMSYSTEM = 0;
         SetState(StatusPreRolling);

         //
         // We've successfully opened the file and all of the tracks; now
         // open the MIDI device and set the time division.
         //
         // NOTE: seqPreroll is equivalent to seek; device might already be open
         //

         if (m_hMidiStream == NULL)
         {
            uDeviceID = m_uiDeviceID;
            mmrc = midiStreamOpen(&m_hMidiStream,
               &uDeviceID,
               1,
               (DWORD) MidiOutProc,
               0,
               CALLBACK_FUNCTION);
            if(mmrc != MMSYSERR_NOERROR)
            {
               m_hMidiStream = NULL;
               if(bThrow)
               {
                  SetState(StatusOpened);
                  throw new midi_exception(mmrc, MIDIPLAYERPRERROLLSTREAMOPENEXCEPTION);
               }
               TRACE("midiStreamOpenError %d\n", mmrc);
               //goto seq_Preroll_Cleanup;
               if(mmrc == MMSYSERR_BADDEVICEID)
                  goto seq_Preroll_Cleanup;
               else if(mmrc == MMSYSERR_INVALPARAM)
                  goto seq_Preroll_Cleanup;
               else if(mmrc == MMSYSERR_NOMEM)
                  goto seq_Preroll_Cleanup;
               else
                  goto seq_Preroll_Cleanup;
            }

            mptd.cbStruct  = sizeof(mptd);
            mptd.dwTimeDiv = m_dwTimeDivision;
            mmrc = midiStreamProperty(
               m_hMidiStream,
               (LPBYTE)&mptd,
               MIDIPROP_SET
               | MIDIPROP_TIMEDIV);
            if (mmrc != MMSYSERR_NOERROR)
            {
               TRACE( "midiStreamProperty() -> %04X", (WORD)mmrc);
               midiStreamClose(m_hMidiStream);
               m_hMidiStream = NULL;
               mmrc = MCIERR_DEVICE_NOT_READY;
               if(bThrow)
               {
                  SetState(StatusOpened);
                  throw new midi_exception(mmrc, MIDIPLAYERPRERROLLSTREAMPROPERTYEXCEPTION);
               }
               goto seq_Preroll_Cleanup;
            }
         }

         mmrc = MMSYSERR_NOERROR;



         m_buffera.Reset();
         lpmh = m_buffera[0].GetMidiHdr();

         if(IsInSpecialModeV001())
         {
            if(m_uiSpecialModeV001Operation == SPMV001GMReset)
            {
               const unsigned char gmModeOn[] = {
                  //        0x00, 0x00, 0x00, 0x00,
                  //        0x00, 0x00, 0x00, 0x00,
                  //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
                  0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00,
                  0x06, 0x00, 0x00, MEVT_LONGMSG,
                  0xf0, 0x7e, 0x7f, 0x09,
                  0x01, 0xf7, 0x00, 0x00};
                  char * lpch = lpmh->lpData + lpmh->dwBytesRecorded;
                  lpmh->dwBytesRecorded += sizeof(gmModeOn);
                  memcpy(lpch, gmModeOn, sizeof(gmModeOn));
                  SetSpecialModeV001Flag(false);
            }
         }

         smfrc = m_pfile->WorkSeek(m_tkBase, lpmh);

         m_tkPrerollBase = GetFile().GetPosition();




         m_flags.unsignalize(FlagEOF);
         m_pfile->GetFlags().unsignalize(EndOfFile);
         for(i = 1; i < m_buffera.get_size(); i++)
         {
            lpmh = m_buffera[i].GetMidiHdr();

            smfrc = m_pfile->WorkStreamRender(lpmh, m_tkEnd, m_cbPrerollNominalMax);
            if(mus::midi::Success != smfrc && mus::midi::SEndOfFile != smfrc)
            {
               TRACE( "SFP: smfReadEvents() -> %u", (UINT)smfrc);
               mmrc = TranslateSMFResult(smfrc);
               /*if(bThrow)
               {
               SetState(StatusOpened);
               throw new midi_exception(mmrc, MIDIPLAYERPRERROLLREADEVENTSEXCEPTION);
               }*/
               goto seq_Preroll_Cleanup;
            }



            if (SEndOfFile == smfrc)
            {
               m_flags.signalize(FlagEOF);
               break;
            }
         } 

         mmrc = m_buffera.midiOutPrepareHeader((HMIDIOUT) m_hMidiStream);
         if (mmrc != MMSYSERR_NOERROR)
         {
            TRACE( "midiOutPrepare(preroll) -> %lu!", (DWORD)mmrc);
            mmrc = MCIERR_DEVICE_NOT_READY;
            if(bThrow)
            {
               SetState(StatusOpened);
               throw new midi_exception(mmrc, MIDIPLAYERPRERROLLPREPAREHEADEREXCEPTION);
            }
            else
            {
               goto seq_Preroll_Cleanup;
            }
         }


         mmrc = m_buffera.midiStreamOut(m_hMidiStream);
         if (mmrc != MMSYSERR_NOERROR)
         {
            TRACE( "midiOutPrepare(preroll) -> %lu!", (DWORD)mmrc);
            mmrc = MCIERR_DEVICE_NOT_READY;
            if(bThrow)
            {
               SetState(StatusOpened);
               throw new midi_exception(mmrc, MIDIPLAYERPRERROLLPREPAREHEADEREXCEPTION);
            }
            else
            {
               goto seq_Preroll_Cleanup;
            }
         }
         m_uBuffersInMMSYSTEM += m_buffera.get_size(); 

   seq_Preroll_Cleanup:

         if (mmrc != MMSYSERR_NOERROR)
         {
            SetState(StatusOpened);
            m_flags.unsignalize(sequence::FlagWaiting);
         }
         else
         {
            SetState(StatusPreRolled);
         }

         return mmrc;
      }

      /***************************************************************************
      *  
      * seqStart
      *
      * Starts playback at the current position.
      *
      * pSeq                      - The sequencer instance.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     stopped.
      *
      *   MCIERR_DEVICE_NOT_READY If the underlying MIDI device could
      *     not be opened or fails any call.
      * 
      * The sequencer must be prerolled before seqStart may be called.
      *
      * Just feed everything in the ready queue to the device.
      *       
      ***************************************************************************/
      MMRESULT sequence::Start()
      {
         CSingleLock sl(&m_mutex, TRUE);
         if (StatusPreRolled != GetState())
         {
            TRACE( "seqStart(): State is wrong! [%u]", GetState());
            return MCIERR_UNSUPPORTED_FUNCTION;
         }

         SetState(StatusPlaying);

         m_evMmsgDone.ResetEvent();

         MMRESULT mmrc = 0;
         if(m_hMidiStream != NULL)
         {
            mmrc = midiStreamRestart(m_hMidiStream);
         }
         sl.Unlock();
         if(mmrc == MMSYSERR_NOERROR)
         {
            m_pthread->PostMidiSequenceEvent(
               this,
               sequence::EventMidiPlaybackStart,
               NULL);

         }
         return mmrc;
      }

      /***************************************************************************
      *  
      * seqPause
      *
      * Pauses playback of the instance.
      *
      * pSeq                      - The sequencer instance.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     playing.
      *
      * The sequencer must be playing before seqPause may be called.
      * Pausing the sequencer will cause all currently on notes to be turned
      * off. This may cause playback to be slightly inaccurate on restart
      * due to missing notes.
      *       
      ***************************************************************************/
      MMRESULT sequence::Pause()

      {
         CSingleLock sl(&m_mutex, TRUE);

         //    assert(NULL != pSeq);

         if (StatusPlaying != GetState())
            return MCIERR_UNSUPPORTED_FUNCTION;

         SetState(StatusPaused);

         MMRESULT mmrc = 0;
         //    CSingleLock slStream(&m_csStream, false);
         //  slStream.Lock();
         if(m_hMidiStream != NULL)
         {
            mmrc = midiStreamPause(m_hMidiStream);;
         }
         //slStream.Unlock();

         SetLevelMeter(0);

         return MMSYSERR_NOERROR;
      }

      /***************************************************************************
      *  
      * seqRestart
      *
      * Restarts playback of an instance after a pause.
      *
      * pSeq                      - The sequencer instance.
      *
      * Returns
      *    MMSYSERR_NOERROR If the operation is successful.
      *    
      *    MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     paused.
      *
      * The sequencer must be paused before seqRestart may be called.
      *
      ***************************************************************************/
      MMRESULT sequence::Restart()
      {
         //    assert(NULL != pSeq);

         CSingleLock sl(&m_mutex, TRUE);

         if (StatusPaused != GetState())
            return MCIERR_UNSUPPORTED_FUNCTION;

         SetState(StatusPlaying);
         m_evMmsgDone.ResetEvent();

         //    MMRESULT mmrc = 0;
         //    CSingleLock slStream(&m_csStream, false);
         //  slStream.Lock();
         if(m_hMidiStream != NULL)
         {
            midiStreamRestart(m_hMidiStream);
         }
         //slStream.Unlock();
         return MMSYSERR_NOERROR;
      }

      /***************************************************************************
      *  
      * seqStop
      *
      * Totally stops playback of an instance.
      *
      * pSeq                      - The sequencer instance.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     paused or playing.
      *
      * The sequencer must be paused or playing before seqStop may be called.
      *
      ***************************************************************************/
      MMRESULT sequence::Stop()
      {
         CSingleLock sl(&m_mutex, TRUE);

         // Automatic success if we're already stopped
         if (GetState() != StatusPlaying
            && GetState() != StatusPaused)
         {
            m_flags.unsignalize(sequence::FlagWaiting);
            GetPlayerLink().OnFinishCommand(MidiPlayerCommandStop);
            return MMSYSERR_NOERROR;
         }

         SetState(StatusStopping);
         m_flags.signalize(sequence::FlagWaiting);

         m_eventMidiPlaybackEnd.ResetEvent();

         if(m_hMidiStream != NULL)
         {
            m_mmrcLastErr = midiStreamStop(m_hMidiStream);
            if(MMSYSERR_NOERROR != m_mmrcLastErr)
            {
               TRACE( "sequence::Stop() -> midiOutStop() returned %lu in seqStop()!\n", (DWORD)m_mmrcLastErr);
               m_flags.unsignalize(FlagWaiting);
               return MCIERR_DEVICE_NOT_READY;
            }
         }

         //m_eventMidiPlaybackEnd.Lock();

         SetLevelMeter(0);

         return MMSYSERR_NOERROR;
      }

      /***************************************************************************
      *  
      * seqTime
      *
      * Determine the current position in playback of an instance.
      *
      * pSeq                      - The sequencer instance.
      *
      * pTicks                    - A pointer to a DWORD where the current position
      *                             in ticks will be returned.
      *
      * Returns
      *   MMSYSERR_NOERROR If the operation is successful.
      *
      *   MCIERR_DEVICE_NOT_READY If the underlying device fails to report
      *     the position.
      *    
      *   MCIERR_UNSUPPORTED_FUNCTION If the sequencer instance is not
      *     paused or playing.
      *
      * The sequencer must be paused, playing or prerolled before seqTime
      * may be called.
      *
      ***************************************************************************/
      MMRESULT sequence::get_time(
         imedia::position &                  pTicks)
      {
         CSingleLock sl(&m_mutex);
         if(!sl.Lock(184))
            return MCIERR_INTERNAL;

         MMRESULT                mmr;
         MMTIME                  mmt;

         if (StatusPlaying != GetState() &&
            StatusPaused != GetState() &&
            StatusPreRolling != GetState() &&
            StatusPreRolled != GetState() &&
            StatusOpened != GetState() &&
            StatusStopping != GetState())
         {
            TRACE( "seqTime(): State wrong! [is %u]", GetState());
            return MCIERR_UNSUPPORTED_FUNCTION;
         }

         pTicks = 0;
         if (StatusOpened != GetState())
         {
            pTicks = m_tkBase;
            if (StatusPreRolled != GetState())
            {
               mmt.wType = TIME_TICKS;
               //            CSingleLock slStream(&m_csStream, false);
               //          slStream.Lock();
               if(m_hMidiStream == NULL)
               {
                  TRACE("m_hmidi == NULL!!!!");
                  return MCIERR_DEVICE_NOT_READY;
               }
               else
               {
                  try
                  {

                     mmr = midiStreamPosition(m_hMidiStream, &mmt, sizeof(mmt));
                     if (MMSYSERR_NOERROR != mmr)
                     {
                        TRACE( "midiStreamPosition() returned %lu", (DWORD)mmr);
                        return MCIERR_DEVICE_NOT_READY;
                     }
                  }
                  catch(...)
                  {
                     return MCIERR_DEVICE_NOT_READY;
                  }
                  pTicks += mmt.u.ticks;
               }
               //        slStream.Unlock();
            }
         }

         return MMSYSERR_NOERROR;
      }

      void sequence::get_time(imedia::time & time)
      {
         DWORD dw;
         GetMillis(dw);
         time = dw;
      }

      MMRESULT sequence::GetMillis(
         DWORD &                  pTicks)
      {
         CSingleLock sl(&m_mutex);
         if(!sl.Lock(184))
            return MCIERR_INTERNAL;

         MMRESULT                mmr;
         MMTIME                  mmt;

         if (StatusPlaying != GetState() &&
            StatusPaused != GetState() &&
            StatusPreRolling != GetState() &&
            StatusPreRolled != GetState() &&
            StatusOpened != GetState() &&
            StatusStopping != GetState())
         {
            TRACE( "seqTime(): State wrong! [is %u]", GetState());
            return MCIERR_UNSUPPORTED_FUNCTION;
         }

         pTicks = 0;
         if (StatusOpened != GetState())
         {
            pTicks = m_tkBase;
            if (StatusPreRolled != GetState())
            {
               mmt.wType = TIME_MS;
               //            CSingleLock slStream(&m_csStream, false);
               //          slStream.Lock();
               if(m_hMidiStream == NULL)
               {
                  TRACE("m_hmidi == NULL!!!!");
                  return MCIERR_DEVICE_NOT_READY;
               }
               else
               {
                  try
                  {

                     mmr = midiStreamPosition(m_hMidiStream, &mmt, sizeof(mmt));
                     if (MMSYSERR_NOERROR != mmr)
                     {
                        TRACE( "midiStreamPosition() returned %lu", (DWORD)mmr);
                        return MCIERR_DEVICE_NOT_READY;
                     }
                  }
                  catch(...)
                  {
                     return MCIERR_DEVICE_NOT_READY;
                  }
                  pTicks += mmt.u.ms;
               }
               //        slStream.Unlock();
            }
         }

         return MMSYSERR_NOERROR;
      }

      /***************************************************************************
      *  
      * seqMillisecsToTicks
      *
      * Given a millisecond offset in the output stream, returns the associated
      * tick position.
      *
      * pSeq                      - The sequencer instance.
      *
      * msOffset                  - The millisecond offset into the stream.
      *
      * Returns the number of ticks into the stream.
      *
      ***************************************************************************/
      imedia::position sequence::MillisecsToTicks(
         DWORD                   msOffset)
      {
         return m_pfile->MillisecsToTicks(msOffset);
      }

      /***************************************************************************
      *  
      * seqTicksToMillisecs
      *
      * Given a tick offset in the output stream, returns the associated
      * millisecond position.
      *
      * pSeq                      - The sequencer instance.
      *
      * tkOffset                  - The tick offset into the stream.
      *
      * Returns the number of milliseconds into the stream.
      *
      ***************************************************************************/
      DWORD sequence::TicksToMillisecs(
         imedia::position                   tkOffset)
      {
         return m_pfile->TicksToMillisecs(tkOffset);
      }

      void sequence::OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr)
      {
         UNREFERENCED_PARAMETER(hmidistream);
         e_file_result               smfrc;
         midi_callback_data *      lpData;
         ASSERT(lpmidihdr != NULL);
         lpData = (midi_callback_data *) lpmidihdr->dwUser;
         ASSERT(lpData != NULL);

         sequence * psequence = lpData->m_psequence;

         MidiSequenceThread * pthread = psequence->m_pthread;
         ASSERT(NULL != lpmidihdr);

         --m_uBuffersInMMSYSTEM;

         if(m_uBuffersInMMSYSTEM == 0)
         {
            m_evBuffersZero.SetEvent();
         }

         if (StatusReset == GetState())
         {
            // We're recollecting buffers from MMSYSTEM
            //
            //      if (lpmidihdr != m_lpmhPreroll)
            //    {
            //     lpmidihdr->lpNext    = m_lpmhFree;
            //   m_lpmhFree           = lpmidihdr;
            //      }
            return;
         }

         bool bStopping = StatusStopping == GetState();
         bool bEof = m_flags.is_signalized(FlagEOF);
         bool bSpecialModeV001End = m_flags.is_signalized(FlagSpecialModeV001End);

         if (bStopping || bEof || bSpecialModeV001End)
         {
            //
            // Reached EOF, just put the buffer back on the free
            // list 
            //
            if(bSpecialModeV001End)
            {
               m_flags.unsignalize(FlagSpecialModeV001End);
               TRACE("void CALLBACK sequence::MidiOutProc m_flags.is_signalized(FlagSpecialModeV001End\n");
               pthread->PostMidiSequenceEvent(
                  this,
                  sequence::EventSpecialModeV001End,
                  lpmidihdr);
            }
            else if(bStopping)
            {
               if(m_uBuffersInMMSYSTEM == 0)
               {
                  TRACE("void CALLBACK sequence::MidiOutProc StatusStopping == pSeq->GetState()\n");
                  pthread->PostMidiSequenceEvent(
                     this,
                     sequence::EventStopped,
                     lpmidihdr);
               }
            }
            else
            {
               if(m_flags.is_signalized(FlagEOF))
               {
                  TRACE("void CALLBACK sequence::MidiOutProc m_flags.is_signalized(FlagEOF\n");
               }
               //       if (lpmidihdr != m_lpmhPreroll)
               //     {
               //      lpmidihdr->lpNext = m_lpmhFree;
               //    m_lpmhFree        = lpmidihdr;
               //}
               if(m_uBuffersInMMSYSTEM <= 0)
               {
                  pthread->PostMidiSequenceEvent(
                     this,
                     sequence::EventMidiPlaybackEnd,
                     lpmidihdr);
               }
            }
         }
         else
         {
            if(IsInSpecialModeV001())
            {
               if(m_uiSpecialModeV001Operation == SPMV001GMReset)
               {
                  const unsigned char gmModeOn[] = {
                     //        0x00, 0x00, 0x00, 0x00,
                     //        0x00, 0x00, 0x00, 0x00,
                     //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x06, 0x00, 0x00, MEVT_LONGMSG,
                     0xf0, 0x7e, 0x7f, 0x09,
                     0x01, 0xf7, 0x00, 0x00};
                     lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);
                     memcpy(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));
               }
               else if(m_uiSpecialModeV001Operation == SPMV001TempoChange)
               {
                  MidiEventV016 event;
                  m_pfile->GetTempoEvent(event);
                  m_pfile->StreamEvent(event.GetDelta(), &event, lpmidihdr, 0x7fffffff, 256);
                  // lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);
                  // memcpy(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));
               }
               else
               {
                  ASSERT(FALSE);
               }
               //PostThreadMessage(lpData->dwThreadID, MIDIPLAYERMESSAGE_STREAMOUT, (WPARAM) pSeq, (LPARAM) lpmidihdr);
               pthread->PostMidiSequenceEvent(
                  this,
                  EventMidiStreamOut,
                  lpmidihdr);
               m_flags.signalize(FlagSpecialModeV001End);
               smfrc = ::mus::midi::Success;
               return;
            }
            //
            // Not EOF yet; attempt to fill another buffer
            //
            pthread->PostMidiSequenceEvent(
               this,
               EventMidiStreamOut,
               lpmidihdr);
         }

      }

      void sequence::OnPositionCB(LPMIDIHDR lpmidihdr)
      {
         ASSERT(lpmidihdr != NULL);
         LPBYTE lpbData = (LPBYTE) (lpmidihdr->lpData + lpmidihdr->dwOffset);
         MIDIEVENT * lpme = (MIDIEVENT *) lpbData;
         file::CMidiStreamEventHeader * pheader = (file::CMidiStreamEventHeader *) &lpme->dwParms[0];
         lpbData = (LPBYTE) pheader;
         LPDWORD lpdwParam;

         int iSize = pheader->m_dwLength;
         switch(pheader->m_dwType)
         {
         case 0:
            {
               base_array < LyricEventV1, LyricEventV1 &> * plyriceventa = NULL;
               base_array < LyricEventV1, LyricEventV1 &> lyriceventa;
               for(int i = sizeof(file::CMidiStreamEventHeader); i < iSize;)
               {
                  pheader = (file::CMidiStreamEventHeader *) &lpbData[i];
                  lpdwParam = (LPDWORD) &lpbData[i + sizeof(file::CMidiStreamEventHeader)];
                  ASSERT(*lpdwParam == pheader->m_dwType);
                  switch(pheader->m_dwType)
                  {
                  case EVENT_ID_LYRIC_V1:
                     {
                        if(plyriceventa == NULL)
                        {
                           plyriceventa = new base_array <LyricEventV1, LyricEventV1 &>;
                        }
                        gen::memory_file memFile(get_app(), (LPBYTE) &lpdwParam[1], pheader->m_dwLength - sizeof(DWORD));
                        /* x2x                  CArchive ar(&memFile, CArchive::load);
                        lyriceventa.Serialize(ar);
                        plyriceventa->append(lyriceventa); */
                     }
                     break;
                  case EVENT_ID_PAD:
                     {
                     }
                     break;
                  case EVENT_ID_NOTE_ON:
                     {
                        gen::memory_file memFile(get_app(), (LPBYTE) &lpdwParam[1], pheader->m_dwLength - sizeof(DWORD));
                        for(int i = 0; i < m_iaLevel.get_size(); i++)
                        {
                           BYTE b;
                           memFile >> b;
                           m_iaLevel.element_at(i) = b;
                        }
                     }
                     break;
                  }
                  i += pheader->m_dwLength + sizeof(file::CMidiStreamEventHeader);
               }
               /*         if(plyriceventa != NULL)
               {
               ::PostMessage(m_midicallbackdata.hWnd, WM_APP + 3388, 3388, (LPARAM) plyriceventa);
               }*/
            }
            break;
         case EVENT_ID_PAD:
            break;
         default:
            ASSERT(FALSE);
            break;
         }

      }

      void CALLBACK sequence::MidiOutProc(
         HMIDIOUT hmo,      
         UINT wMsg,         
         DWORD dwInstance,  
         DWORD dwParam1,    
         DWORD dwParam2)
      {
         UNREFERENCED_PARAMETER(hmo);
         UNREFERENCED_PARAMETER(dwInstance);
         UNREFERENCED_PARAMETER(dwParam2);

         LPMIDIHDR               lpmh         = (LPMIDIHDR) dwParam1;

         switch(wMsg)
         {
         case MOM_POSITIONCB:
            ((midi_callback_data *) lpmh->dwUser)->m_psequence->OnPositionCB(lpmh);
            break;
         case MOM_DONE:
            ((midi_callback_data *) lpmh->dwUser)->m_psequence->OnDone(NULL,lpmh);
            return;
         }
      }

      /***************************************************************************
      *  
      * seqMIDICallback
      *
      * Called by the system when a buffer is done
      *
      * dw1                       - The buffer that has completed playback.
      *
      ***************************************************************************/
      /*void sequence
      ::MidiOutCallbackDeprecated(HMIDISTRM hms, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2_, MidiPlayer * lpMidiPlayer, CXfplayerView * pview)
      {
      //TRACE("sequence::MIDICallback current thread %X\n", GetCurrentThreadId());
      LPMIDIHDR               lpmh      = (LPMIDIHDR)dw1;
      //LPMIDIHDR               lpmh2      = (LPMIDIHDR)dw2;
      sequence *         pSeq;
      //    MMRESULT                mmrc;
      e_file_result               smfrc;
      LPMIDICALLBACKDATA      lpData = (LPMIDICALLBACKDATA) dwUser;
      //EVENT      *pEvent;
      //   char *      str;
      //   LPDWORD      lpdw;
      //   DWORD      dwSize;




      if (uMsg == MM_MOM_POSITIONCB)
      {
      //CMidiEventV001 *pEvent = (CMidiEventV001 *) lpmh->lpData;
      LPDWORD lpdw = (unsigned long *) (lpmh->lpData + lpmh->dwOffset);
      TRACE("MM_MOM_POSITIONCB lpmh->dwOffset = %d\n", lpmh->dwOffset);
      lpdw++;
      lpdw++;
      lpdw++;
      if(*lpdw == EVENT_ID_LYRIC_V1)
      {
      LyricEventV1 *pLyricEvent = new LyricEventV1();
      CMemFile memFile((LPBYTE) lpdw, lpmh->dwBytesRecorded - lpmh->dwOffset);
      CArchive ar(&memFile, CArchive::load);
      pLyricEvent->Serialize(ar);
      //::ca::window * pWnd = (::ca::window *) dwUser;
      //   HWND hWnd = (HWND) dwUser;
      //pWnd->PostMessage(WM_USER, 3377, (LPARAM) pLyricEvent);
      //pview->OnUserMessage(3377, (LPARAM) pLyricEvent);
      //lpMidiPlayer->OnUserMessage(3377, (LPARAM) pLyricEvent);
      //PostThreadMessage(lpData->dwThreadID, WM_USER, 3377, (LPARAM) pLyricEvent);
      PostMessage(lpData->hWnd, WM_USER, 3377, (LPARAM) pLyricEvent);
      }
      else if(*lpdw == EVENT_ID_PAD)
      {
      //TRACE("MIDICallback pad event\n");
      }
      //   pEvent = lpmh->lpData;
      //      lpdw = (unsigned long *) (lpmh->lpData + lpmh->dwOffset);
      //      lpdw++;
      //      lpdw++;
      //      dwSize = *lpdw & 0x00FFFFFFL;
      //      lpdw++;
      //      str = (char *) malloc(dwSize  + 1);
      //      strncpy(str, (const char *) lpdw, dwSize);
      //      str[dwSize] = 0;
      //      TRACE0("Lyric:");
      //      TRACE1("%s", str);
      //      TRACE0("\n");
      //      printf("MOM_POSITIONCB");
      return;
      }

      if (uMsg != MM_MOM_DONE)
      return;

      MidiPlayer * pthread = lpData->m_pthread;
      ASSERT(NULL != lpmh);

      pSeq = (sequence *)(lpmh->dwUser);

      ASSERT(pSeq != NULL);

      --pSeq->m_uBuffersInMMSYSTEM;

      if (StatusReset == pSeq->GetState())
      {
      // We're recollecting buffers from MMSYSTEM
      //
      //      if (lpmh != pSeq->m_lpmhPreroll)
      //      {
      //          lpmh->lpNext   = pSeq->m_lpmhFree;
      //        pSeq->m_lpmhFree = lpmh;
      //  }

      return;
      }


      if ((StatusStopping == pSeq->GetState()) || (m_flags.is_signalized(FlagEOF)))
      {
      /*
      ** Reached EOF, just put the buffer back on the free
      ** list 
      */
      //      if (lpmh != pSeq->m_lpmhPreroll)
      //      {
      //         lpmh->lpNext   = pSeq->m_lpmhFree;
      //       pSeq->m_lpmhFree = lpmh;
      //}
      //      PostThreadMessage(lpData->dwThreadID, MIDIPLAYERMESSAGE_PLAYBACKEND, (WPARAM) pSeq, (LPARAM) lpmh);
      /*      pplayer->PostMidiSequenceEvent(
      pSeq,
      EventMidiPlaybackEnd,
      lpmh);

      }
      else
      {
      /*
      ** Not EOF yet; attempt to fill another buffer
      */
      /*        smfrc = pSeq->m_pfile->WorkStreamRender(lpmh, pSeq->m_tkEnd, m_cbPrerollNominalMax);

      switch(smfrc)
      {
      case Success:
      break;

      case SEndOfFile:
      pSeq->m_flags.signalize(FlagEOF);
      smfrc = Success;
      break;

      default:
      TRACE( "smfReadEvents returned %lu in callback!", (DWORD)smfrc);
      pSeq->SetState(StatusStopping);
      break;
      }

      if (Success == smfrc)
      {
      //         PostThreadMessage(lpData->dwThreadID, MIDIPLAYERMESSAGE_STREAMOUT, (WPARAM) pSeq, (LPARAM) lpmh);
      pplayer->PostMidiSequenceEvent(
      pSeq,
      EventMidiStreamOut,
      lpmh);
      }
      }
      }*/

      /***************************************************************************
      *  
      * TranslateSMFResult
      *
      * Translates an error from the SMF layer into an appropriate MCI error.
      *
      * smfrc                     - The return code from any SMF function.
      *
      * Returns
      *   A parallel error from the MCI error codes.   
      *
      ***************************************************************************/




      bool sequence::IsPlaying()
      {
         return GetState() == StatusPlaying ||
            GetState() == StatusStopping;
      }




      MMRESULT sequence::SaveFile()
      {
         return SaveFile(m_pfile->m_strName);
      }

      MMRESULT sequence::SaveFile(const char * lpFileName)
      {
         return TranslateSMFResult(m_pfile->SaveFile(lpFileName));

      }

      MMRESULT sequence::SaveFile(ex1::filesp &ar)
      {
         return m_pfile->SaveFile(ar);
      }



      UINT sequence::SetState(UINT uiState)
      {
         m_uiPreviousState = m_uiState;
         m_uiState = uiState;
         return m_uiPreviousState;
      }

      void sequence::SetSpecialModeV001Flag(bool bSet)
      {
         if(m_flags.is_signalized(FlagIsInSpecialModeV001))
            m_flags.signalize(FlagWasInSpecialModeV001);
         else
            m_flags.unsignalize(FlagWasInSpecialModeV001);

         if(bSet)
            m_flags.signalize(FlagIsInSpecialModeV001);
         else
            m_flags.unsignalize(FlagIsInSpecialModeV001);
      }

      void sequence::SetSpecialModeV001Operation(UINT uiOperation)
      {
         m_uiPreSpecialModeV001State = m_uiState;
         SetSpecialModeV001Flag();
         m_uiSpecialModeV001Operation = uiOperation;
      }

      bool sequence::IsInSpecialModeV001()
      {
         return m_flags.is_signalized(FlagIsInSpecialModeV001);
      }

      bool sequence::WasInSpecialModeV001()
      {
         return m_flags.is_signalized(FlagWasInSpecialModeV001);
      }


      void sequence::GetMidiDoneData(LPMIDIDONEDATA lpmdd)
      {
         lpmdd->m_flags = m_flags;
         lpmdd->m_uiSeqPreviousState = m_uiPreviousState;
         lpmdd->m_uiSeqState = m_uiState;
      }

      int sequence::GetKeyShift()
      {
         return m_pfile->GetKeyShift();
      }

      int sequence::SetKeyShift(int iKeyShift)
      {
         /*//    CSingleLock slStream(&m_csStream, false);
         //  slStream.Lock();
         if(m_hMidiStream)
         {
         midiStreamPause(m_hMidiStream);
         if(!m_pfile->SetKeyShift(iKeyShift))
         return false;
         midiStreamRestart(m_hMidiStream);
         }
         //slStream.Unlock();
         return true;
         void sequence::SetKeyShift(int iShift)
         {*/
         bool bPlay = IsPlaying();
         imedia::position ticks = 0;
         if(bPlay)
         {
            ticks = GetPositionTicks();
            Stop();
         }
         GetFile().SetKeyShift(iKeyShift);
         if(bPlay)
         {
            m_pthread->PrerollAndWait(ticks);
            Start();
         }
         //}
         return true;
      }

      int sequence::GetTempoShift()
      {
         return m_pfile->GetTempoShift();
      }



      int sequence::SetTempoShift(int iTempoShift)
      {

         //midiStreamPause(m_hMidiStream);
         if(VMS_FAILED(m_pfile->SetTempoShift(iTempoShift)))
            return false;
         //midiStreamRestart(m_hMidiStream);
         return true;
      }


      bool sequence::SetMidiOutDevice(UINT uiDevice)
      {
         m_uiDeviceID = uiDevice;
         return true;
      }

      MMRESULT sequence::CloseStream()
      {
         CSingleLock sl(&m_mutex, TRUE);
         if(IsPlaying())
         {
            Stop();
         }

         /* If we were prerolled, need to clean up -- have an open MIDI handle
         ** and buffers in the ready queue
         */

         m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hMidiStream);

         if (m_hMidiStream != NULL)
         {
            midiStreamClose( m_hMidiStream);
            m_hMidiStream = NULL;
         }

         SetState(StatusOpened);

         return MMSYSERR_NOERROR;
      }

      void sequence::SetLevelMeter(int iLevel)
      {
         for(int i = 0; i < m_iaLevel.get_size(); i++)
         {
            m_iaLevel.element_at(i) = iLevel;
         }
      }

      void sequence::OnMidiPlaybackEnd(sequence::Event * pevent)
      {
         UNREFERENCED_PARAMETER(pevent);
         CSingleLock sl(&m_mutex, TRUE);
         //   LPMIDIHDR lpmh = pevent->m_lpmh;
         //   midi_callback_data * lpData = &m_midicallbackdata;
         MMRESULT mmrc;


         if (0 == m_uBuffersInMMSYSTEM)
         {
            TRACE( "seqBufferDone: normal sequencer shutdown.");

            /* Totally done! Free device and notify.
            */
            if(m_hMidiStream)
            {
               if((mmrc = m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hMidiStream))
                  != MMSYSERR_NOERROR)
               {
                  TRACE( "midiOutUnprepareHeader failed in seqBufferDone! (%lu)", (DWORD)mmrc);
               }
               midiStreamClose(m_hMidiStream);
               m_hMidiStream = NULL;
            }

            m_mmrcLastErr = MMSYSERR_NOERROR;
            m_flags.unsignalize(FlagWaiting);

            m_evMmsgDone.SetEvent();
         }
      }

      void sequence::OnEvent(sequence::Event * pevent)
      {
         switch(pevent->m_eevent)
         {
         case EventSpecialModeV001End:
            {
               SetSpecialModeV001Flag(false);
               OnMidiPlaybackEnd(pevent);
               SetState(m_uiPreSpecialModeV001State);
            }
            break;
         case EventStopped:
            {
               OnMidiPlaybackEnd(pevent);
               SetState(StatusOpened);
            }
            break;
         case EventMidiPlaybackEnd:
            {
               OnMidiPlaybackEnd(pevent);
               SetState(StatusOpened);
            }
            break;
         case EventMidiStreamOut:
            {
               CSingleLock sl(&m_mutex, TRUE);

               LPMIDIHDR lpmh = pevent->m_lpmh;
               //         midi_callback_data * lpData = &m_midicallbackdata;
               MMRESULT mmrc;

               if(IsInSpecialModeV001())
               {
                  TRACE("sequence::OnEvent EventMidiStreamOut IsInSpecialModeV001");
               }
               else
               {
                  mmrc = m_pfile->WorkStreamRender(
                     lpmh, 
                     m_tkEnd, 
                     m_cbPrerollNominalMax);
               }

               switch(mmrc)
               {
               case mus::midi::Success:
                  break;
               case mus::midi::SEndOfFile:
                  m_flags.signalize(FlagEOF);
                  mmrc = mus::midi::Success;
                  break;
               default:
                  TRACE( "smfReadEvents returned %lu in callback!", (DWORD)mmrc);
                  SetState(StatusStopping);
                  break;
               }


               if(sequence::StatusStopping == GetState())
               {
                  m_pthread->PostMidiSequenceEvent(
                     this,
                     EventMidiPlaybackEnd,
                     lpmh);
                  return;
               }
               ++m_uBuffersInMMSYSTEM;

               //         CSingleLock slStream(&m_csStream, false);
               //         slStream.Lock();
               if(m_hMidiStream != NULL)
               {
                  mmrc = midiStreamOut(m_hMidiStream, lpmh, sizeof(*lpmh));
               }
               //         slStream.Unlock();

               if (MMSYSERR_NOERROR != mmrc)
               {
                  TRACE("seqBufferDone(): midiStreamOut() returned %lu!", (DWORD)mmrc);

                  --m_uBuffersInMMSYSTEM;
                  SetState(sequence::StatusStopping);
               }
            }
         default:
            break;
         }
      }

      void sequence::OnEvent(e_event eevent)
      {
         Event ev;
         ev.m_psequence = this;
         ev.m_eevent = eevent;
         ev.m_lpmh = NULL;
         OnEvent(&ev);
      }

      imedia::position sequence::GetPositionTicks()
      {
         CSingleLock sl(&m_mutex);
         if(!sl.Lock(0))
            return -1;
         MMTIME mmt;
         mmt.wType = TIME_TICKS;
         if(MMSYSERR_NOERROR ==
            midiStreamPosition(
            m_hMidiStream,
            &mmt,  
            sizeof(mmt)))
            return mmt.u.ticks + m_tkPrerollBase;
         else
            return -1;
      }


      bool sequence::IsChangingTempo()
      {
         return m_flags.is_signalized(sequence::FlagTempoChange);
      }
      void sequence::SetTempoChangeFlag(bool bSet)
      {
         if(bSet)
            m_flags.signalize(sequence::FlagTempoChange);
         else
            m_flags.unsignalize(sequence::FlagTempoChange);
      }

      void sequence::PlayerLink::SetCommand(MidiPlayerCommand *pcommand)
      {
         if(m_pcommand != NULL)
         {
            m_pcommand->Release();
         }
         m_pcommand = pcommand;
         m_pcommand->AddRef();
      }

      void sequence::PlayerLink::OnFinishCommand(EMidiPlayerCommand ecommand)
      {
         if(m_pcommand != NULL)
         {
            if(ecommand == m_pcommand->GetCommand())
            {
               m_pcommand->OnFinish();
            }
            m_pcommand->Release();
            m_pcommand = NULL;
         }

      }

      sequence::e_flag sequence::PlayerLink::GetFlag()
      {
         return m_eflag;
      }

      void sequence::PlayerLink::SetFlag(e_flag eflag)
      {
         m_eflag = eflag;
      }

      bool sequence::PlayerLink::TestFlag(e_flag eflag)
      {
         return (m_eflag & eflag) > 0;
      }

      void sequence::PlayerLink::ModifyFlag(e_flag eflagAdd, e_flag eflagRemove)
      {
         ASSERT(!(eflagAdd & eflagRemove));
         m_eflag = (e_flag) (m_eflag | eflagAdd);
         m_eflag = (e_flag) (m_eflag & ~eflagRemove);
      }

      sequence::PlayerLink & sequence::GetPlayerLink()
      {
         return m_playerlink;
      }


      sequence::PlayerLink::PlayerLink()
      {
         m_eflag = FlagNull;
         m_pcommand = NULL;
      }

      bool sequence::IsNull()
      {
         if(this == NULL)
            return true;
         return false;
      }

      imedia::position sequence::TimeToPosition(imedia::time millis)
      {
         return imedia::position(MillisecsToTicks((DWORD) millis));
      }
      imedia::time sequence::PositionToTime(imedia::position tk)
      {
         return imedia::time(TicksToMillisecs((imedia::position) (DWORD) tk));
      }
      void sequence::GetPosition(imedia::position & position)
      {
         get_time(position);
      }

      bool sequence::IsOpened()
      {
         return GetState() != StatusNoFile;
      }

      void sequence::GetTimeLength(imedia::time & time)
      {
         time = m_msLength;
      }



      void sequence::Prepare(
         string2a & str2a,
         imedia::position_2darray & tka2DTokensTicks,
         int iMelodyTrack,
         int2a & ia2TokenLine,
         ikar::data & data)
      {
         UNREFERENCED_PARAMETER(str2a);
         file & file = GetFile();
         MidiTracks & tracks = file.GetTracks();

         ASSERT(!file.IsNull());
         file.GetTracks().seek_begin();
         imedia::position               tkMax = file.m_tkLength;
         imedia::position               tkLastPosition = 0;


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

         imedia::position_2darray tk2DNoteOnPositions;
         imedia::position_2darray tk2DNoteOffPositions;
         imedia::position_2darray tk2DBegPositions;
         imedia::position_2darray tk2DEndPositions;
         imedia::time_2darray ms2DTokensMillis;
         imedia::time_2darray ms2DNoteOnMillis;
         imedia::time_2darray ms2DNoteOffMillis;
         imedia::time_2darray ms2DBegMillis;
         imedia::time_2darray ms2DEndMillis;
         MidiEventsV1 midiEvents;




         // Note on and off events
         // and maximum and minimum 
         // pitch bend peaks.
         MidiEventsV1 midiEventsLevel2;

         MidiEventsV1 noteOnEvents;
         MidiEventsV1 noteOffEvents;

         MidiEventsV1 eventsLevel2Beg;
         MidiEventsV1 eventsLevel2End;
         EventsTracksV1 lyricEventsForPositionCB;
         EventsTracksV1 lyricEventsForBouncingBall;
         EventsTracksV1 lyricEventsForScoring;
         EventsTracksV1 lyricEvents;

         //   tracks.seek_begin();
         // tracks.GetXFInfoHeaders(
         //  &m_xfInfoHeaders);



         file.PositionToTime(
            ms2DTokensMillis,
            tka2DTokensTicks,
            0);

         LyricEventsV2 *pLyricEventsV2;
         LyricEventsV2 *pLyricEventsV2_;
         LyricEventsV2 *pLyricEventsV2B;
         LyricEventsV2 *pLyricEventsV2C;
         MidiEventsV1 *pMidiEventsV1;
         tk2DNoteOnPositions.set_size(tka2DTokensTicks.get_size());
         tk2DNoteOffPositions.set_size(tka2DTokensTicks.get_size());
         tk2DBegPositions.set_size(tka2DTokensTicks.get_size());
         tk2DEndPositions.set_size(tka2DTokensTicks.get_size());
         int i;
         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
         {
            pLyricEventsV2 = new LyricEventsV2();
            pLyricEventsV2B = new LyricEventsV2();
            pLyricEventsV2C = new LyricEventsV2();
            pLyricEventsV2_ = new LyricEventsV2();
            staticdata.m_eventsv1.add(pLyricEventsV2);
            staticdata.m_eventsv1.add(pLyricEventsV2B);
            staticdata.m_eventsv1.add(pLyricEventsV2C);
            staticdata.m_eventsv1.add(pLyricEventsV2_);
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
            pMidiEventsV1 = NULL;
            if(iMelodyTrack < 0)
            {
               pLyricEventsV2->m_iTrack =
                  file.WorkCalcMelodyTrack(
                  &pMidiEventsV1,
                  tka2DTokensTicks.operator[](i),
                  ia2TokenLine[i]);
            }
            else
            {
               pLyricEventsV2->m_iTrack = iMelodyTrack;
            }
            pLyricEventsV2B->m_iTrack = pLyricEventsV2->m_iTrack;
            pLyricEventsV2C->m_iTrack = pLyricEventsV2->m_iTrack;
            pLyricEventsV2_->m_iTrack = pLyricEventsV2->m_iTrack;
            if(pLyricEventsV2->m_iTrack < 0)
            {
               pLyricEventsV2->m_iTrack = tracks.m_iMelodyTrackTipA;
               pLyricEventsV2B->m_iTrack = tracks.m_iMelodyTrackTipA;
               pLyricEventsV2C->m_iTrack = tracks.m_iMelodyTrackTipA;
               pLyricEventsV2_->m_iTrack = tracks.m_iMelodyTrackTipA;
            }
            staticdata.SetGuessMelodyTrack(pLyricEventsV2->m_iTrack);
            if(pLyricEventsV2->m_iTrack >= 0)
            {
               if(file.GetFormat() == 0)
               {
                  tracks.TrackAt(0)->WorkSeekBegin();
                  ((MidiTrack *)tracks.TrackAt(0))->WorkGetNoteOnOffEventsV1(
                     &midiEvents, 
                     pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
                  tracks.TrackAt(0)->WorkSeekBegin();
                  ((MidiTrack *)tracks.TrackAt(0))->WorkGetLevel2Events(
                     &midiEventsLevel2, 
                     pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
               }
               else
               {
                  tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
                  ((MidiTrack *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
                     &midiEvents, 
                     pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
                  tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
                  ((MidiTrack *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
                     &midiEventsLevel2, 
                     pLyricEventsV2->m_iTrack,
                     file.GetFormat() == 1);
               }
            }

            MidiUtil miditutil(get_app());

            miditutil.PrepareNoteOnOffEvents(
               &noteOnEvents,
               &noteOffEvents,
               pLyricEventsV2->m_iTrack,
               file.GetFormat(),
               &midiEvents,
               tka2DTokensTicks.operator[](i));

            miditutil.PrepareLevel2Events(
               &eventsLevel2Beg,
               &eventsLevel2End,
               pLyricEventsV2->m_iTrack,
               file.GetFormat(),
               &midiEventsLevel2,
               tka2DTokensTicks.operator[](i));


            tk2DNoteOnPositions[i]     = noteOnEvents.m_tkaEventsPosition;
            tk2DNoteOffPositions[i]    = noteOffEvents.m_tkaEventsPosition;
            tk2DBegPositions[i]        = eventsLevel2Beg.m_tkaEventsPosition;
            tk2DEndPositions[i]        = eventsLevel2End.m_tkaEventsPosition;
            pLyricEventsV2->m_dwaNotesData.copy(noteOnEvents.m_dwaEventsData);
            pLyricEventsV2B->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
            pLyricEventsV2C->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
            pLyricEventsV2_->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
            midiEvents.remove_all();
            noteOnEvents.remove_all();
            noteOffEvents.remove_all();
            midiEventsLevel2.remove_all();
            eventsLevel2Beg.remove_all();
            eventsLevel2End.remove_all();
            delete pMidiEventsV1;
         }

         file.PositionToTime(
            ms2DNoteOnMillis,
            tk2DNoteOnPositions,
            0);

         file.PositionToTime(
            ms2DNoteOffMillis,
            tk2DNoteOffPositions,
            0);

         file.PositionToTime(
            ms2DBegMillis,
            tk2DBegPositions,
            0);

         file.PositionToTime(
            ms2DEndMillis,
            tk2DEndPositions,
            0);


         LyricEventsV1 *pLyricEventsV1;


         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
         {
            pLyricEventsV2 = (LyricEventsV2 *) lyricEvents.get_at(i);
            staticdata.m_eventstracks.add(pLyricEventsV2);
            file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               0);
            file.TimeToPosition(
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
            file.TimeToPosition(
               pLyricEventsV1->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               -1000);
            //CMidiLyricTrack * pLyricTrk = file.GetTracks().CreateLyricTrack();
            //pLyricTrk->Prepare(*pLyricEventsV1);
         }


         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
         {
            pLyricEventsV2 = (LyricEventsV2 *) lyricEventsForScoring.get_at(i);
            staticdata.m_eventsTracksForScoring.add(pLyricEventsV2);
            file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               0);
            file.TimeToPosition(
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

            file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               -100);

            file.TimeToPosition(
               pLyricEventsV2->m_tkaNotesPosition,
               ms2DNoteOnMillis[i],
               -100);

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

            pLyricEventsV2->PrepareForLyricsDisplay(this);
            //CMidiLyricTrack * pLyricTrk = file.GetTracks().CreateLyricTrack();
            //pLyricTrk->Prepare(*pLyricEventsV2);
         }










         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
         {
            pLyricEventsV2 = (LyricEventsV2 *) lyricEventsForBouncingBall.get_at(i);
            staticdata.m_eventsTracksForBouncingBall.add(pLyricEventsV2);

            file.TimeToPosition(
               pLyricEventsV2->m_tkaTokensPosition,
               ms2DTokensMillis[i],
               -100);

            file.TimeToPosition(
               pLyricEventsV2->m_tkaNotesPosition,
               ms2DNoteOnMillis[i],
               -100);

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

            pLyricEventsV2->PrepareForBouncingBall(this);
         }

      }

      void sequence::Prepare(int iTrack, ikar::data & data)
      {
         file & file = GetFile();
         MidiTracks & tracks = file.GetTracks();
         string2a & str2a = data.GetStaticData().m_str2aRawTokens;
         imedia::position_2darray position2a;
         int2a ia2TokenLine;


         ia2TokenLine.add_new();

         tracks.WorkSeekBegin();
         tracks.WorkGetEmptyXFTokens(
            iTrack,
            str2a,
            position2a,
            NULL);

         Prepare(
            str2a,
            position2a,
            iTrack,
            ia2TokenLine,
            data);

      }

      void sequence::Prepare(ikar::data & data)
      {
         file & file = GetFile();
         MidiTracks & tracks = file.GetTracks();
         string2a & str2a = data.GetStaticData().m_str2aRawTokens;
         imedia::position_2darray position2a;
         int2a i2aTokenLine;

         CXFInfoHeaders xfihs;
         GetFile().GetTracks().GetXFInfoHeaders(&xfihs);

         ikar::static_data & staticdata = data.GetStaticData();
         string str;

         // add Title
         staticdata.m_straTitleFormat.add("%0");
         staticdata.m_str2aTitle.add_new();
         staticdata.m_str2aTitle[0].add(xfihs.m_strSongName);

         if(xfihs.m_xfInfoHeader.m_straComposer.get_size() > 0)
         {
            // add Performer
            staticdata.m_straTitleFormat.add("Performer: %0");
            xfihs.m_xfInfoHeader.m_straPerformer.get_format_string(str, ", ");
            staticdata.m_str2aTitle.add_new();
            staticdata.m_str2aTitle[1].add(str);

            // add Composer
            staticdata.m_straTitleFormat.add("Composer: %0");
            xfihs.m_xfInfoHeader.m_straComposer.get_format_string(str, ", ");
            staticdata.m_str2aTitle.add_new();
            staticdata.m_str2aTitle[1].add(str);


            //      staticdata.m_straPerformer = xfihs.m_xfInfoHeader.m_straPerformer;
            //    staticdata.m_straArtist = xfihs.m_xfInfoHeader.m_straPerformer;
         }

         staticdata.m_dwDefaultCodePage = 1252; // Latin (Default of All Default Code Pages)

         CXF xf;
         if(xfihs.m_xfaInfoHeaderLS.get_count())
         {
            staticdata.m_dwDefaultCodePage = xf.SymbolCharCodeToCodePage(xfihs.m_xfaInfoHeaderLS[0].m_strLanguage);
         }

         tracks.WorkSeekBegin();
         tracks.WorkGetXFTokens(staticdata.m_dwDefaultCodePage, str2a, position2a, i2aTokenLine, NULL);

         Prepare(
            str2a,
            position2a,
            -1,
            i2aTokenLine,
            data);

         tracks.WorkSeekBegin();
         tracks.WorkGetLongestXFLyrics(staticdata.m_strLyrics);

      }


      void sequence::GetPositionLength(imedia::position &position)
      {
         position = m_tkLength;
      }

      void sequence::buffer::Initialize(int iSize, DWORD dwUser)
      {
         m_storage.allocate(iSize);
         m_midihdr.lpData           = (char *) m_storage.GetAllocation();
         m_midihdr.dwBufferLength   = m_storage.GetStorageSize();
         m_midihdr.dwUser           = dwUser;
         m_bPrepared                = false;

      }

      void sequence::BufferArray::Initialize(int iCount, int iSize, DWORD dwUser)
      {
         set_size(iCount);

         int i;

         /*   for(int i = 0; i < get_size() - 1; i++)
         {
         element_at(i).SetNextMidiHdr(element_at(i + 1).GetMidiHdr());
         }

         if(get_size() > 1)
         {
         element_at(get_upper_bound()).SetNextMidiHdr(element_at(0).GetMidiHdr());
         }
         else
         {
         element_at(0).SetNextMidiHdr(NULL);
         }*/

         for(i = 0; i < get_size(); i++)
         {
            element_at(i).Initialize(iSize, dwUser);
         }
      }

      void sequence::BufferArray::Reset()
      {
         for(int i = 0; i < get_size(); i++)
         {
            element_at(i).Reset();
         }
      }

      void sequence::buffer::Reset()
      {
         m_midihdr.dwBytesRecorded  = 0;
         m_midihdr.dwFlags          = 0;
      }

      bool sequence::buffer::IsPrepared()
      {
         return m_bPrepared;
      }


      MMRESULT sequence::buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
      {
         MMRESULT mmr = 0;
         if(hmidiout == NULL)
            return mmr;
         if(m_bPrepared)
            return mmr;
         mmr = ::midiOutPrepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));
         if(mmr == MMSYSERR_NOERROR)
         {
            m_bPrepared = true;
         }
         return mmr;
      }

      MMRESULT sequence::buffer::midiOutUnprepareHeader(HMIDIOUT hmidiout)
      {
         MMRESULT mmr = 0;
         if(hmidiout == NULL)
            return mmr;
         if(!m_bPrepared)
            return mmr;
         mmr = ::midiOutUnprepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));
         if(mmr == MMSYSERR_NOERROR)
         {
            m_bPrepared = false;
         }
         return mmr;
      }

      MMRESULT sequence::BufferArray::midiOutUnprepareHeader(HMIDIOUT hmidiout)
      {
         MMRESULT mmr = MMSYSERR_NOERROR;

         for (int i = 0; i < get_size(); i++)
         {
            MMRESULT mmrBuffer = element_at(i).midiOutUnprepareHeader(hmidiout);
            if(mmrBuffer != MMSYSERR_NOERROR)
            {
               mmr = mmrBuffer;
            }
         }
         return mmr;
      }

      MMRESULT sequence::BufferArray::midiOutPrepareHeader(HMIDIOUT hmidiout)
      {
         MMRESULT mmrc = MMSYSERR_NOERROR;
         for(int i = 0; i < get_size(); i++)
         {
            mmrc = element_at(i).midiOutPrepareHeader(
               hmidiout);
            if(mmrc != MMSYSERR_NOERROR)
            {
               for(; i >= 0; i--)
               {
                  element_at(i).midiOutUnprepareHeader(hmidiout);
               }
               return mmrc;
            }
         }
         return mmrc;
      }

      LPMIDIHDR sequence::buffer::GetMidiHdr()
      {
         return &m_midihdr;
      }

      void sequence::buffer::SetNextMidiHdr(LPMIDIHDR lpNext)
      {
         m_midihdr.lpNext = lpNext;
      }


      MMRESULT sequence::buffer::midiStreamOut(HMIDISTRM hmidiout)
      {
         ASSERT(hmidiout != NULL);
         return ::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr));
      }

      MMRESULT sequence::BufferArray::midiStreamOut(HMIDISTRM hmidiout)
      {
         MMRESULT mmrc = MMSYSERR_NOERROR;
         for(int i = 0; i < get_size(); i++)
         {
            mmrc = element_at(i).midiStreamOut(
               hmidiout);
            if(mmrc != MMSYSERR_NOERROR)
            {
               //         for(; i >= 0; i--)
               //       {
               //        element_at(i).midiOutUnprepareHeader(hmidiout);
               //   }
               return mmrc;
            }
         }
         return mmrc;
      }





      void sequence::MuteAll(bool bMute, int iExcludeTrack)
      {
         bool bPlay = IsPlaying();
         imedia::position ticks = 0;
         if(bPlay)
         {
            ticks = GetPositionTicks();
            Stop();
         }
         GetFile().MuteAll(bMute, iExcludeTrack);
         if(bPlay)
         {
            m_pthread->PrerollAndWait(ticks);
            Start();
         }
      }

      void sequence::MuteTrack(int iIndex, bool bMute)
      {
         bool bPlay = IsPlaying();
         imedia::position ticks = 0;
         if(bPlay)
         {
            ticks = GetPositionTicks();
            Stop();
         }
         GetFile().MuteTrack(iIndex, bMute);
         if(bPlay)
         {
            m_pthread->PrerollAndWait(ticks);
            Start();
         }
      }

      imedia::position sequence::GetQuarterNote()
      {
         return GetFile().m_pFileHeader->GetQuarterNoteTicks();
      }


      int sequence::GetDefaultCodePage()
      {
         return 1252;
      }


      BOOL sequence::IsSettingPosition()
      {
         return m_flags.is_signalized(sequence::FlagSettingPos);
      }


      void sequence::SetSettingPositionFlag(BOOL bSet)
      {
         if(bSet)
            m_flags.signalize(sequence::FlagSettingPos);
         else
            m_flags.unsignalize(sequence::FlagSettingPos);
      }

      file & sequence::GetFile()
      {
         return * m_pfile;
      }

      UINT sequence::GetPreviousState()
      {
         return m_uiPreviousState;
      }

      UINT sequence::GetState()
      {
         return m_uiState;
      }

   } // namespace midi

} // namespace mus