#pragma once

namespace ca
{

   class data;

   class CLASS_DECL_ca data_listener :
      virtual public ::ca::object
   {
   public:

      comparable_array < data * > m_dataptra;

      data_listener(sp(::ca::application) papp);
      virtual ~data_listener();

      bool listen(data * pdata, bool bListen = true);

      virtual void on_update_data(data * pdata, int32_t iHint);
   };

} // namespace ca