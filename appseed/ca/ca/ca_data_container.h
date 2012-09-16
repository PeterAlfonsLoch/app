#pragma once


namespace ca
{


   class CLASS_DECL_ca data_container :
      virtual public ::radix::object
   {
   public:

      
      sp(data)       m_spdata;

      
      data_container(::ca::application * papp);
      virtual ~data_container();


      virtual bool set_data(::ca::data * pdata);
      data * get_data() const;

      virtual bool is_data_in_use() const;

      virtual void on_update_data(int iHint);

   };

   class CLASS_DECL_ca data_container_base :
      virtual public ::radix::object
   {
   public:

      
      spa(data)       m_spadata;

      
      data_container_base(::ca::application * papp);
      virtual ~data_container_base();


      bool add_data(::ca::data * pdata);
      bool remove_data(::ca::data * pdata);
      data * get_data(index i) const;
      count get_count() const;


      template < class TYPE >
      bool replace_data(TYPE * pdata)
      {
         
         TYPE * pderived = NULL;

         for(index i = 0; i < m_spadata.get_count(); i++)
         {

            try
            {

               pderived = dynamic_cast < TYPE * > (m_spadata[i].m_p);

            }
            catch(...)
            {

            }

            if(pderived != NULL)
            {

               retry_single_lock rsl1(&pderived->m_mutex, millis(1), millis(1));

               retry_single_lock rsl2(&pdata->m_mutex, millis(1), millis(1));

               m_spadata[i] = pdata;

               return true;

            }

         }

         m_spadata.add(pdata);

         return true;

      }

      sync_object_ptra get_sync();

   };


} // namespace ca


