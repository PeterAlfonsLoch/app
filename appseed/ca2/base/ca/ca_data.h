#pragma once


namespace ca
{


   class data_listener;
   class base_edit;
   class data;

   typedef CLASS_DECL_ca2 spa(data_listener) data_listener_ptra;
   typedef CLASS_DECL_ca2 comparable_array < data * > data_ptra;
   typedef CLASS_DECL_ca2 comparable_array < sp(::ca::ca) > ca_ptra;


   class CLASS_DECL_ca2 data :
      virtual public ::ca::object
   {
   public:


      class CLASS_DECL_ca2 writing :
         public interlocked_long_pulse
      {
      public:


         sp(data)    m_spdata;


         writing(data * pdata);
         virtual ~writing();

      };

      class CLASS_DECL_ca2 saving :
         public interlocked_long_pulse
      {
      public:


         sp(data) m_spdata;


         saving(data * pdata);
         virtual ~saving();


      };

      spa(data_listener)                     m_listenerptra;
      sp(data)                               m_spdataParentLock;

      // writing to this data
      interlocked_long  m_lockedlongWriting;

      // reading data - for saving for example;
      interlocked_long  m_lockedlongSaving;


      mutex  *           m_pmutex;

      data(sp(::ca::application) papp);
      virtual ~data();


      virtual bool is_in_use() const;


      virtual void on_update_data(int32_t iHint);


      virtual void edit(::ca::base_edit * pbaseedit);
      template < class EDIT >
      EDIT * validate_edit(::ca::base_edit * pedit);

      inline mutex * data_mutex() { if(m_pmutex != NULL) return m_pmutex; m_pmutex = new ::mutex(get_app()); return m_pmutex; }

   };


} // namespace ca

