#pragma once


namespace i2com
{


	namespace rtp
	{


		class room :
			virtual public ::radix::object
		{
		public:

			gen::memory_file							m_memfileRaw;
			gen::memory_file							m_memfileCompressed;

			string										m_strAddress;
			array_release_ptr < receiver >		m_receivera;
			array_release_ptr < transmitter >	m_transmittera;
         mixer                               m_mixer;
         compressor                          m_compressor;

         server *                            m_pserver;

			room(::ca::application * papp);

			int get_mp3_rtptx_port(i2com::rtp::server * pserver, const char  * pszSecureUserId);
			int get_mp3_rtprx_port(i2com::rtp::server * pserver, const char  * pszSecureUserId);

		};

   

	} // namespace rtp


} // namespace i2com


