#pragma once


namespace ca2
{

   class CLASS_DECL_ca2 live_object :
      virtual public ::ca2::ca2
   {
   public:

      inline void keep_alive()
      {
         try
         {
            on_keep_alive();
         }
         catch(...)
         {
         }
      }
      virtual void on_keep_alive() = 0;
      virtual bool is_alive() = 0;

   };

} // namespace ca2
