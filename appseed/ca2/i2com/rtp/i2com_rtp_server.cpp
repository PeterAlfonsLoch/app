#include "stdafx.h"



namespace i2com
{


	namespace rtp
	{


		server::server(::ca::application * papp) :
			ca(papp)
		{
		}

      int server::get_free_rtp_port()
      {
         int iLoPort = 10000;
         int iHiPort = 20000;
         room * proom;
         for(int iPort = iLoPort; iPort <= iHiPort; iPort++)
         {
            if(!m_mapRtpPort.Lookup(iPort, proom))
            {
               return iPort;
            }
         }
         return -1;
      }


      int server::get_mp3_rtptx_port(const char * pszSecureUserId, const char * pszAddress)
      {
         room * proom;
         if(!m_mapRtpAddress.Lookup(pszAddress, proom))
         {
            proom = new room(get_app());
            proom->m_strAddress = pszAddress;
            m_mapRtpAddress.set_at(pszAddress, proom);
         }
         return proom->get_mp3_rtptx_port(this, pszSecureUserId);
      }

      int server::get_mp3_rtprx_port(const char * pszSecureUserId, const char * pszAddress)
      {
         room * proom;
         if(!m_mapRtpAddress.Lookup(pszAddress, proom))
         {
            proom = new room(get_app());
            proom->m_strAddress = pszAddress;
            m_mapRtpAddress.set_at(pszAddress, proom);
         }
         return proom->get_mp3_rtprx_port(this, pszSecureUserId);
      }


	} // 	namespace rtp

	
} // namespace i2com

