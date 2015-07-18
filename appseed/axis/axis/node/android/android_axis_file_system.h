#pragma once


namespace android
{


	namespace axis
	{


		class CLASS_DECL_AXIS file_system :
			virtual public ::android::file_system,
			virtual public ::file::axis::system
		{
		public:


			file_system(::aura::application *  papp);

         virtual ::file::buffer_sp get_file(var varFile, UINT nOpenFlags, cres * pfesp, ::aura::application * papp);

		};


	} // namespace axis


} // namespace android





