#pragma once

namespace base
{


   class CLASS_DECL_BASE library:
      virtual public ::element
   {
   public:


      void *                        m_plibrary;
      bool                          m_bAutoClose;


      library(sp(::base::application) papp);
      library(sp(::base::application) papp,const char * pszOpen);
      virtual ~library();

      virtual bool open(const char * pszPath,bool bAutoClose = true);
      virtual bool close();


      virtual bool is_opened();
      virtual bool is_closed();

      template < typename TARGET >
      TARGET get(const char * pszElement)
      {
         return reinterpret_cast <TARGET>(raw_get(pszElement));
      }

      void * raw_get(const char * pszElement);

   };



   CLASS_DECL_BASE void * open_ca2_library(const char * psz);


} // namespace base




class CLASS_DECL_BASE ca2_library:
   virtual public ::base::library
{
public:

   ca2_library(sp(::base::application) papp);
   ca2_library(sp(::base::application) papp,const char * pszOpen);
   virtual ~ca2_library();

   virtual bool open(const char * pszPath,bool bAutoClose = true);

};

