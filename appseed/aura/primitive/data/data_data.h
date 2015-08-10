#pragma once


namespace data
{


   typedef CLASS_DECL_AURA ptr_array < listener > data_listener_ptra;
   typedef CLASS_DECL_AURA ptr_array < data > data_ptra;
   typedef CLASS_DECL_AURA comparable_array < sp(object) > ca_ptra;


//   class CLASS_DECL_AURA simple_lock :
//      public interlocked_long_pulse
//   {
//   public:
//
//
//      sp(simple_data)    m_spdata;
//
//
//      simple_lock(simple_data * pdata);
//      virtual ~simple_lock();
//
//   };

   


   class CLASS_DECL_AURA simple_data :
      virtual public object
   {
   public:


      // writing to or reading from this data
//      interlocked_long  m_lockedlong;
//      mutex                m_mutex;
      
      
      simple_data();
      virtual ~simple_data();


//      virtual bool is_locked() const;


      virtual void on_update_data(int32_t iHint);


   };



//   class CLASS_DECL_AURA lock :
//      public interlocked_long_pulse
//   {
//   public:
//
//
//      sp(data)    m_spdata;
//
//
//      lock(data * pdata);
//      virtual ~lock();
//
//   };




   class CLASS_DECL_AURA data :
      virtual public ::object,
      virtual public simple_data
   {
   public:


      data_listener_ptra                     m_listenerptra;
//      sp(data)                               m_spdataParentLock;


//      mutex  *                               m_pmutex;

      ::data::data_container_base *          m_pcontainerbase;


      data(::aura::application * papp);
      virtual ~data();


      virtual ::count           get_data_bound_view_count() const;
      virtual ::user::impact *  get_data_bound_view(index iView);



//      virtual bool is_locked() const;

      virtual void on_update_data(int32_t iHint);

      virtual void edit(base_edit * pbaseedit);
      template < class EDIT >
      EDIT * validate_edit(base_edit * pedit);

//      inline mutex * data_mutex() { if(m_pmutex != NULL) return m_pmutex; m_pmutex = new ::mutex(get_app()); return m_pmutex; }

      inline ::data::data_container_base * get_data_container_base() { return m_pcontainerbase; }

   };



} // namespace data



