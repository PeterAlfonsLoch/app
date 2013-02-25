#pragma once


namespace ca
{


   class data_listener;
   class base_edit;
   class data;

   typedef CLASS_DECL_ca comparable_array < data_listener * > data_listener_ptra;
   typedef CLASS_DECL_ca comparable_array < data * > data_ptra;
   typedef CLASS_DECL_ca comparable_array < ::ca::ca * > ca_ptra;


   class CLASS_DECL_ca data :
      virtual public ::ca::object
   {
   public:


      class CLASS_DECL_ca writing :
         public interlocked_long_pulse
      {
      public:


         sp(data)    m_spdata;


         writing(data * pdata);
         virtual ~writing();

      };

      class CLASS_DECL_ca saving :
         public interlocked_long_pulse
      {
      public:


         sp(data) m_spdata;


         saving(data * pdata);
         virtual ~saving();


      };

      comparable_array < data_listener * >   m_listenerptra;
      sp(data)                               m_spdataParentLock;

      // writing to this data
      interlocked_long  m_lockedlongWriting;

      // reading data - for saving for example;
      interlocked_long  m_lockedlongSaving;


      mutex             m_mutex;

      data(::ca::application * papp);
      virtual ~data();


      virtual bool initialize_data();
      virtual bool finalize_data();

      virtual bool is_in_use() const;


      virtual void on_update_data(int32_t iHint);


      virtual void edit(::ca::base_edit * pbaseedit);
      template < class EDIT >
      EDIT * validate_edit(::ca::base_edit * pedit);



   };


} // namespace ca

