#include "StdAfx.h"

int iMp3PacketSize = 1024;

namespace rtp
{

   file::file(::ca::application * papp) :
      ca(papp),
      m_memfile(papp)
   {
      m_uiTimeStamp        = 0;
      jittcomp             = 100;
      adapt                = TRUE;
      clockslide           = 0;
      m_dwSynchSource      = 1;
      m_dwTimeOut          = 120 * 1000;
      format               = 0;
      jitter               = 0;
      m_iRemotePort        = -1;
      m_iListenPort        = -1;
      m_psession           = NULL;
      m_pprofile           = NULL;
      m_bStreamReceived    = false;
   }

   file::~file()
   {
   }

   bool file::rx_open(const char * pszAddress, int iPort)
   {

      m_strListenAddress = pszAddress;
      m_iListenPort = iPort;
      if(m_set.has_property("--noadapt"))
         adapt=FALSE;
      if(m_set.has_property("--format"))
      {
         adapt=FALSE;
         if(m_set["--format"] == "mulaw")
         {
            //format=MULAW;
         }
         else if(m_set["--format"] == "alaw")
         {
            //format=ALAW;
         }
         else
         {
            //TRACE("Unsupported format %s\n",argv[i]);
            return false;
         }
      }
      if(m_set.has_property("--with-jitter"))
      {
         jittcomp=m_set["--with-jitter"];
         TRACE("Using a jitter buffer of %i milliseconds.\n",jittcomp);
      }
               
      ortp_init();
      ortp_scheduler_init();
      ortp_set_log_level_mask(ORTP_DEBUG|ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
      m_psession = new session(RTP_SESSION_RECVONLY);   
      m_psession->set_scheduling_mode(1);
      m_psession->set_blocking_mode(1);
      rtp_session_set_local_addr(m_psession->m_psession, m_strListenAddress, m_iListenPort);
      rtp_session_set_connected_mode(m_psession->m_psession,TRUE);
      rtp_session_set_symmetric_rtp(m_psession->m_psession,TRUE);
      rtp_session_enable_adaptive_jitter_compensation(m_psession->m_psession,adapt);
      rtp_session_set_jitter_compensation(m_psession->m_psession,jittcomp);
      rtp_session_set_payload_type(m_psession->m_psession,0);
      //rtp_session_signal_connect(m_psession->m_psession,"ssrc_changed",(RtpCallback)ssrc_cb,0);
      rtp_session_signal_connect(m_psession->m_psession,"ssrc_changed",(RtpCallback)rtp_session_reset,0);
      m_iHaveMore = 1;
      return true;   
   }

   bool file::tx_open(const char * pszAddress, int iPort)
   {
      m_strRemoteAddress = pszAddress;
      m_iRemotePort = iPort;
      if(m_set.has_property("--with-clockslide"))
      {
         clockslide=atoi(m_set["--with-clockslide"]);
         ortp_message("Using clockslide of %i milisecond every 50 packets.",clockslide);
      }
      if(m_set.has_property("--with-jitter"))
      {
         ortp_message("Jitter will be added to outgoing stream.");
         jitter=atoi(m_set["--with-jitter"]);
      }
      
      ortp_init();
      ortp_scheduler_init();
      ortp_set_log_level_mask(ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
      m_psession = new session(RTP_SESSION_SENDONLY);   
      if(m_psession->m_psession == NULL)
      {
         return false;
      }
      
      rtp_session_set_scheduling_mode(m_psession->m_psession,1);
      rtp_session_set_blocking_mode(m_psession->m_psession,1);
      rtp_session_set_connected_mode(m_psession->m_psession,TRUE);
      if(rtp_session_set_remote_addr(m_psession->m_psession,m_strRemoteAddress,m_iRemotePort) != 0)
         goto cleanup;
      rtp_session_set_payload_type(m_psession->m_psession,0);
      
      if(m_dwSynchSource != 0)
      {
         TRACE("using SSRC=%i.\n",m_dwSynchSource);
         rtp_session_set_ssrc(m_psession->m_psession,m_dwSynchSource);
      }
      return true;
cleanup:
      rtp_session_destroy(m_psession->m_psession);
      ortp_exit();
      ortp_global_stats_display();
      
      return false;
   }



   ::primitive::memory_size file::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      UINT uiRead = 0;
      DWORD dwStartTime = ::GetTickCount();
      primitive::memory mem(get_app());
      mem.allocate(nCount);
//      UINT uiStart = m_uiTimeStamp;
      while(m_memfile.get_size() <= 0)
      {
         m_iHaveMore = 1;
		   while (m_iHaveMore)
         {
            uiRead = m_iError = m_psession->recv_with_ts(mem, mem.get_size(), m_uiTimeStamp, &m_iHaveMore);
			   if(m_iError > 0) 
               m_bStreamReceived = true;
			   /* this is to avoid to write to disk some silence before the first RTP packet is returned*/	
			   if((m_bStreamReceived) && (m_iError > 0))
            {
               m_memfile.write(mem, uiRead);
               m_iError = 0;
            }
            if(GetTickCount() - dwStartTime > m_dwTimeOut)
            {
               // error = timeout
               return 0; // Eof;
            }
			}
         m_uiTimeStamp += iMp3PacketSize;
         if(GetTickCount() - dwStartTime > m_dwTimeOut)
         {
            // error = timeout
            return 0; // Eof;
         }
		}
      uiRead = min(m_memfile.get_size(), nCount);
      m_memfile.remove_begin(lpBuf, uiRead);
      return uiRead;
		
   }

   void file::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      m_psession->send_with_ts(lpBuf, nCount, m_uiTimeStamp);
      m_uiTimeStamp += nCount;
   /*   if (clockslide!=0 && user_ts%(160*50)==0){
            ortp_message("Clock sliding of %i miliseconds now",clockslide);
            rtp_session_make_time_distorsion(m_psession->m_psession,clockslide);
         }
         /*this will simulate a burst of late packets */
         /*if (jitter && (user_ts%(8000)==0)) {
            /*struct timespec pausetime, remtime;
            ortp_message("Simulating late packets now (%i milliseconds)",jitter);
            pausetime.tv_sec=jitter/1000;
            pausetime.tv_nsec=(jitter%1000)*1000000;
            while(nanosleep(&pausetime,&remtime)==-1 && errno==EINTR){
               pausetime=remtime;
            }*/
      /*      Sleep(jitter);
         }*/
   }



   void file::close()
   {
      rtp_session_destroy(m_psession->m_psession);
      ortp_exit();
               
      ortp_global_stats_display();
   }

   bool file::IsValid() const
   {
      return m_psession->m_psession != NULL;
   }

#ifdef _DEBUG
void file::assert_valid() const
{
   ex1::file::assert_valid();
}
void file::dump(dump_context & dumpcontext) const
{
   ex1::file::dump(dumpcontext);
}
#endif


void file::set_payload(const char * pszProfile, PayloadType * ptype, int iIndex)
{

   m_pprofile = new profile(pszProfile);

   m_psession->set_profile(m_pprofile);
            
   m_pprofile->set_payload(iIndex, ptype);

   m_psession->set_payload_type(iIndex);

}


} // namespace rtp