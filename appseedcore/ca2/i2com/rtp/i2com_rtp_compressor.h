#pragma once


namespace i2com
{


	namespace rtp
	{



		class compressor :
			virtual public ::radix::object
		{
		public:

			room * m_proom;

			compressor(::ca::application * papp);

			void start_compressing(room * proom);

			static UINT thread_proc_compress(LPVOID lpparam);

			void compress();

		};
   

	} // namespace rtp


} // namespace i2com


