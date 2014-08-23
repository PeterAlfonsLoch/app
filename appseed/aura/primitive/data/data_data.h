#pragma once


class base_edit;


namespace data
{


   class data_listener;
   class data;
   class simple_data;


   typedef CLASS_DECL_AURA spa(data_listener) data_listener_ptra;
   typedef CLASS_DECL_AURA comparable_array < data * > data_ptra;
   typedef CLASS_DECL_AURA comparable_array < sp(element) > ca_ptra;


   class CLASS_DECL_AURA simple_lock :
      public interlocked_long_pulse
   {
   public:


      sp(simple_data)    m_spdata;


      simple_lock(simple_data * pdata);
      virtual ~simple_lock();

   };

   


   class CLASS_DECL_AURA simple_data :
      virtual public root
   {
   public:


      // writing to or reading from this data
      interlocked_long  m_lockedlong;
      
      
      simple_data();
      virtual ~simple_data();


      virtual bool is_locked() const;


      virtual void on_update_data(int32_t iHint);


   };



   class CLASS_DECL_AURA lock :
      public interlocked_long_pulse
   {
   public:


      sp(data)    m_spdata;


      lock(data * pdata);
      virtual ~lock();

   };




   class CLASS_DECL_AURA data :
      virtual public ::object,
      virtual public simple_data
   {
   public:


      spa(data_listener)                     m_listenerptra;
      sp(data)                               m_spdataParentLock;


      mutex  *                               m_pmutex;

      ::user::document *                     m_pdocument;


      data(sp(::aura::application) papp);
      virtual ~data();


      virtual bool is_locked() const;

      virtual void on_update_data(int32_t iHint);

      virtual void edit(base_edit * pbaseedit);
      template < class EDIT >
      EDIT * validate_edit(base_edit * pedit);

      inline mutex * data_mutex() { if(m_pmutex != NULL) return m_pmutex; m_pmutex = new ::mutex(get_app()); return m_pmutex; }

      inline ::user::document * get_document() { return m_pdocument; }

   };



} // namespace data



