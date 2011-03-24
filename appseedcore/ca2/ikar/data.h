#pragma once

namespace ikar
{
   class karaoke;
   class static_data;
   class dynamic_data;

   class CLASS_DECL_ca data :
      virtual public ::ca::data
   {
   public:

      
      mutex                      m_mutex;
      ikar::static_data *        m_pstaticdata;
      ikar::dynamic_data *       m_pdynamicdata;
      ikar::karaoke *            m_pinterface;

      
      data(::ca::application * papp);
      virtual ~data();


      bool IsNull();
      void delete_contents();
      void Prepare();
      virtual void Initialize(ikar::karaoke * pinterface);
      void SetInterface(ikar::karaoke * pinterface);

      ikar::static_data & GetStaticData();
      ikar::dynamic_data & GetDynamicData();
      ikar::karaoke * GetInterface();

   };

} // namespace ikar