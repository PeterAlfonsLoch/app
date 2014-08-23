#pragma once


namespace aura
{


   class CLASS_DECL_AURA live_object :
      virtual public element
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


} // namespace aura






