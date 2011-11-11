#pragma once


namespace i2com
{


	namespace rtp
	{


		class mixer :
			virtual public ::radix::object
		{
		public:

			UINT_PTR										m_uiPosition;
	   

			room * m_proom;


			mixer(::ca::application * papp);

			void start_mixing(room * proom);

			static UINT thread_proc_mix(LPVOID lpparam);

			void mix();


		};

   

	} // namespace rtp


} // namespace i2com


