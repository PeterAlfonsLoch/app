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

} // namespace ca