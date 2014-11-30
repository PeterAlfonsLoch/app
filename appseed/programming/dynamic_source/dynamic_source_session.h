#pragma once


namespace dynamic_source
{


   class CLASS_DECL_CORE session :
      virtual public ::object
   {
   public:


      string                              m_strId;
      mutex                               m_mutex;
      property_set                  m_set;
      ::datetime::time                    m_timeExpiry;
      ::dynamic_source::script_manager *  m_pmanager;


      session(const string & strId, ::dynamic_source::script_manager * pmanager);
      virtual ~session_parent;

      virtual int64_t add_ref();
      virtual int64_t release();


   };


   class CLASS_DECL_CORE session_map :
      virtual public strsp(session)
   {
   public:


   };


} // namespace dynamic_source




