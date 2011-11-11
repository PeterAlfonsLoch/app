#pragma once


namespace mixer
{

   class CLASS_DECL_ca label :
      public control
   {
   public:


      label(void);
      virtual ~label(void);


      virtual void SetText(const char * lpcszText) = 0;
      MixerCtrlData & get_data();


   };

} // namespace mixer