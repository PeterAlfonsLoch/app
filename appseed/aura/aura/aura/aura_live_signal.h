#pragma once


namespace aura
{


   class CLASS_DECL_AURA live_signal :
      virtual public ::aura::live_object,
      virtual protected ::comparable_array < live_object * >
   {
   public:

      live_signal();
      live_signal(const live_signal & signal);

      void keep(live_object * pliveobject);
      void unkeep(live_object * pliveobject);

      virtual void on_keep_alive();
      virtual bool is_alive();

      live_signal & operator = (const live_signal & signal);

   };


} // namespace aura










