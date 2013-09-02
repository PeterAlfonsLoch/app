#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 data_container :
      virtual public object
   {
   public:

      
      sp(data)       m_spdata;

      
      data_container();
      virtual ~data_container();


      virtual bool set_data(::ca2::data * pdata);
      data * get_data();

      virtual bool is_data_in_use() const;

      virtual void on_update_data(int32_t iHint);

   };

   class CLASS_DECL_ca2 data_container_base :
      virtual public object
   {
   public:

      
      spa(data)       m_spadata;

      
      data_container_base(sp(::application) papp);
      virtual ~data_container_base();


      bool add_data(::ca2::data * pdata);
      bool remove_data(::ca2::data * pdata);
      data * get_data(index i);
      ::count get_count() const;


      template < class TYPE >
      bool replace_data(TYPE * pdata)
      {
         
         TYPE * pderived = NULL;

         for(index i = 0; i < m_spadata.get_count(); i++)
         {

            try
            {

               pderived = m_spadata.typed_ptr_at < TYPE > (i);

            }
            catch(...)
            {

            }

            if(pderived != NULL)
            {

               retry_single_lock rsl1(pderived->data_mutex(), millis(1), millis(1));

               retry_single_lock rsl2(pdata->data_mutex(), millis(1), millis(1));

               m_spadata(i) = pdata;

               return true;

            }

         }

         m_spadata.add(pdata);

         return true;

      }


      template < class TYPE >
      bool replace_data(smart_pointer < TYPE > & data)
      {
         
         return replace_data(data.m_p);

      }

      sync_object_ptra get_sync();

   };


} // namespace ca2


