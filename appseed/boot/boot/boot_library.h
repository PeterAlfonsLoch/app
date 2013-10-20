#pragma once


namespace boot
{


   class CLASS_DECL_BOOT library
   {
   public:


      void *                        m_plibrary;
      bool                          m_bAutoClose;


      library();
      library(const char * pszOpen);
      virtual ~library();

      virtual bool open(const char * pszPath);
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

   class CLASS_DECL_BOOT ca2_library :
      virtual public library
   {
   public:

      ca2_library();
      ca2_library(const char * pszOpen);
      virtual ~ca2_library();

      virtual bool open(const char * pszPath);

   };


} // namespace caa



namespace core
{


   CLASS_DECL_BOOT void * open_ca2_library(const char * psz);


} // namespace core


