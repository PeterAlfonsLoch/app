#pragma once


namespace i2com
{


	namespace rtp
	{




		class transmitter :
			virtual public ::radix::object
		{
		public:
	   
			int						   m_iPort;
			int						   m_iReceiverPort;
			string					   m_strReceiverHost;
         ::rtp::file *           m_prtpfile;
         gen::memory_file        m_memfileMp3;
         room *                  m_proom;
         ::ex2::transfer_file    m_transferfile;
         mutex                   m_mutexMp3;


			transmitter(::ca::application * papp);

	      void start_transmitting(room * proom);
	      static UINT thread_proc_transmit(LPVOID lpparam);
	      void transmit();


         void write(void * p, count c);


		};

   

	} // namespace rtp


} // namespace i2com


