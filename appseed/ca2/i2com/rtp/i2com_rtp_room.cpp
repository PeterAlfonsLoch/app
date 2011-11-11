#include "stdafx.h"



namespace i2com
{


	namespace rtp
	{


		room::room(::ca::application * papp) :
			ca(papp),
         m_memfileRaw(papp),
         m_memfileCompressed(papp),
         m_mixer(papp),
         m_compressor(papp)
		{
         m_mixer.start_mixing(this);
         m_compressor.start_compressing(this);
		}

		int room::get_mp3_rtptx_port(i2com::rtp::server * pserver, const char  * pszSecureUserId)
		{
         UNREFERENCED_PARAMETER(pserver);
         UNREFERENCED_PARAMETER(pszSecureUserId);
         transmitter * ptransmitter = new transmitter(get_app());
         m_transmittera.add(ptransmitter);
         ptransmitter->start_transmitting(this);
         return ptransmitter->m_iPort;
		}

		int room::get_mp3_rtprx_port(i2com::rtp::server * pserver, const char  * pszSecureUserId)
		{
         UNREFERENCED_PARAMETER(pserver);
         UNREFERENCED_PARAMETER(pszSecureUserId);
         receiver * preceiver = new receiver(get_app());
         m_receivera.add(preceiver);
         preceiver->start_receiving(this);
         return preceiver->m_iPort;
		}


	} // 	namespace rtp

	
} // namespace i2com

