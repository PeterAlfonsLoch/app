#pragma once


namespace i2com
{


	namespace rtp
	{


		class receiver :
			virtual public ::radix::object
		{
		public:
	   
			int						m_iPort;
			int						m_iSenderPort;
			string					m_strSenderHost;
			gen::memory_file		m_memfileRawPcm;
         ::ex2::transfer_file m_transferfile;
			::rtp::file *        m_prtpfile;
         room *               m_proom;
         mutex                m_mutexRaw;
         mutex                m_mutexRtp;
         UINT_PTR             m_uiRawPosition;
         UINT_PTR             m_uiReadPosition;


			receiver(::ca::application * papp);

			void start_receiving(room * proom);

			static UINT thread_proc_receive(LPVOID lpparam);

			void receive();


         UINT read(void * p, count c);


		};
   

	} // namespace rtp


} // namespace i2com


