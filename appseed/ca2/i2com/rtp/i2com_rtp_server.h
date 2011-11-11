#pragma once


namespace i2com
{


	namespace rtp
	{


		class room;
			
		class server :
			virtual public ::radix::object
		{
		public:

			::collection::map < int, int, room *, room * >	m_mapRtpPort;
			::collection::string_map < room * >					m_mapRtpAddress;


			server(::ca::application * papp);


         int get_mp3_rtptx_port(const char * pszSecureUserId, const char * pszAddress);
         int get_mp3_rtprx_port(const char * pszSecureUserId, const char * pszAddress);


         virtual int get_free_rtp_port();


		};



	} // namespace rtp


} // namespace i2com
