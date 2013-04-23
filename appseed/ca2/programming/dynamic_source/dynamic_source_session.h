#pragma once


namespace dynamic_source
{


   class CLASS_DECL_ca2 session :
      virtual public ::ca::object
   {
   public:


      mutex                      m_mutex;
      ::ca::property_set         m_set;
      ::datetime::time           m_timeAccess;


      session(::ca::application * papp);
      virtual ~session();


      virtual int64_t release();


   };


   class CLASS_DECL_ca2 session_map :
      virtual public strsp(session)
   {
   public:


   };


} // namespace dynamic_source




