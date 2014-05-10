#pragma once


class CLASS_DECL_BASE base_library :
   virtual public ::element
{
public:


   void *                        m_plibrary;
   bool                          m_bAutoClose;


   base_library(sp(::base::application) papp);
   base_library(sp(::base::application) papp, const char * pszOpen);
   virtual ~base_library();

   virtual bool open(const char * pszPath, bool bAutoClose = true);
   virtual bool close();


   virtual bool is_opened();
   virtual bool is_closed();

   template < typename TARGET >
   TARGET get(const char * pszElement)
   {
      return reinterpret_cast < TARGET >(raw_get(pszElement));
   }

   void * raw_get(const char * pszElement);

};

class CLASS_DECL_BASE ca2_library :
   virtual public base_library
{
public:

   ca2_library(sp(::base::application) papp);
   ca2_library(sp(::base::application) papp, const char * pszOpen);
   virtual ~ca2_library();

   virtual bool open(const char * pszPath, bool bAutoClose = true);
   
};


namespace core
{


   CLASS_DECL_BASE void * open_ca2_library(const char * psz);


} // namespace core


