#pragma once


namespace user
{


   class CLASS_DECL_ca data_exchange :
      virtual public ::radix::object
   {
   public:


      bool m_bSaveAndValidate;


      data_exchange();
      virtual ~data_exchange();


   };



} // namespace user


