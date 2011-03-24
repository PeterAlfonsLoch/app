#pragma once

namespace ikar
{

   class data;

   class CLASS_DECL_ca data_container :
      virtual public ::radix::object
   {
   public:
      data *      m_pdata;

      data_container();
      virtual ~data_container();

      void SetKaraokeData(data * pdata);
      data & GetKaraokeData();

   };

} // namespace ikar
