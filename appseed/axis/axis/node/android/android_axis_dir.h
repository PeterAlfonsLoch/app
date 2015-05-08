#pragma once


namespace android
{


	namespace axis
	{


		class CLASS_DECL_AXIS dir :
			virtual public ::android::dir,
			virtual public ::file::dir::axis::system
		{
		public:




			string      m_strca2;


			dir(::aura::application *  papp);


			//         virtual bool  ls_pattern(::aura::application *  papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
			//         virtual bool  ls(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
			//         virtual bool  rls_pattern(::aura::application *  papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL, e_extract eextract = extract_first);
			//         virtual bool  rls(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, e_extract eextract = extract_first);
			//         virtual bool  rls_dir(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
			//         virtual bool  ls_dir(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
			//         virtual bool  ls_file(::aura::application *  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);

			virtual ::file::listing & ls(::aura::application * app, ::file::listing & listing);


			virtual bool  is(const ::file::path & lpcsz, ::aura::application * papp);
			virtual bool  name_is(const ::file::path & str, ::aura::application * papp);


			virtual bool initialize();
		};


	} // namespace axis


} // namespace android


















