#pragma once


namespace ca
{


   class CLASS_DECL_____ library
   {
   public:


      void *                        m_plibrary;
      bool                          m_bAutoClose;


      library();
      library(const char * pszOpen);
      virtual ~library();

      virtual bool open(const char * pszPath);
      virtual bool close();

      template < typename TARGET >
      TARGET get(const char * pszElement)
      {
         return reinterpret_cast < TARGET >(raw_get(pszElement));
      }

      void * raw_get(const char * pszElement);

   };

   class CLASS_DECL_____ ca2_library :
      virtual public library
   {
   public:

      ca2_library();
      ca2_library(const char * pszOpen);
      virtual ~ca2_library();

      virtual bool open(const char * pszPath);

   };


} // namespace ca



namespace ca2
{


   CLASS_DECL_____ void * open_ca2_library(const char * psz);


} // namespace ca2


