#pragma once


namespace user
{


   class CLASS_DECL_ca2 data_exchange :
      virtual public ::ca2::object
   {
   public:


      bool m_bSaveAndValidate;


      data_exchange();
      virtual ~data_exchange();


      virtual void Fail();

      sp(::user::interaction) prepare_control(id id);

   };



} // namespace user


