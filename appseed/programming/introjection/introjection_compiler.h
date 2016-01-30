#pragma once


namespace introjection
{


class CLASS_DECL_PROGRAMMING library:
   virtual public ::object
{
public:


   ::aura::library                           m_library;
   ::file::path                              m_pathScript;
   file::plain_text_stream_memory_buffer     m_memfileError;
   string                                    m_strError;
   file_time                                 m_filetime;


   library(::aura::application * papp);
   virtual ~library();


};



class CLASS_DECL_PROGRAMMING compiler:
   virtual public ::object
{
public:

   string                                    m_strDynamicSourceConfiguration;
   ::file::path                              m_strDynamicSourceStage;
   ::file::path                              m_strDynamicSourceStageFolder;


   string      m_strLibPlatform;


   stringa                                   m_straSync;
   //      map_string_to_ptr                         m_mapLib;
   string                                    m_strLibsLibs;
   string                                    m_strEnv;
   string                                    m_strSdk1;
   string                                    m_strPlatform;
   string                                    m_strStagePlatform;

   string                                    m_strPlat1;
   string                                    m_strPlat2;
   ::file::path                              m_strTime;


   mutex                                     m_mutex;

   mutex                                     m_mutexLibrary;

   string_map < sp(library) >                m_lib;


   compiler(::aura::application * papp);
   virtual ~compiler();

   void initialize();
   void prepare1(const char * lpcszSource,const char * lpcszDest);
   void prepare_compile_and_link_environment();

   ::aura::library & compile(string str,bool & bNew);


};



} // namespace dynamic_source

class xyz
{
public:
   xyz(string strName)
   {
      m_strName = strName;
   }

   string m_strName;


   virtual ::object *  create_object(::aura::application * papp,object * p) = 0;


};


template < class T >
class xy:
   virtual public xyz
{
public:
   xy(string strName):
      xyz(strName)
   {
   }
   virtual ::object *  create_object(::aura::application * papp,object * p)
   {
      return new T(papp,p);
   }

};



#define BEGIN_LIBRARY  class library : virtual public ::aura::library { public: \
ptr_array < xyz > m_xyzptra; library(::aura::application * papp) : object(papp), ::aura::library(papp) { initialize_factory(); }

#define BEGIN_CREATE_OBJECT \
      virtual sp(::object) create_object(::aura::application * papp, const char * pszClass, object * p) override { xyz * pxyz = find_xyz(pszClass); if(pxyz == NULL) return NULL; return pxyz->create_object(papp, p); } \
      virtual bool has_object_class(const char * pszClass) override { return find_xyz(pszClass) != NULL; } \
	  xyz * find_xyz(const char * pszClass) { index iFind = m_xyzptra.pred_find_first([&](auto pxy){return pxy->m_strName == pszClass; }); if(iFind < 0) return NULL; return m_xyzptra[iFind]; } \
	  void initialize_factory() {
#define CREATE_OBJECT_ENTRY(name, cl) m_xyzptra.add(new xy < cl>(name));

#define END_CREATE_OBJECT }

#define END_LIBRARY  };

#define BEG_ONLY_FACT BEGIN_LIBRARY \
 BEGIN_CREATE_OBJECT

#define END_ONLY_FACT END_CREATE_OBJECT \
 END_LIBRARY \
BEGIN_EXTERN_C \
::aura::library * get_new_library(::aura::application * papp) \
{ \
\
   return new library(papp); \
 \
} \
 \
 \
END_EXTERN_C
