#pragma once




namespace ca
{

   class CLASS_DECL_ca live_signal :
      virtual public ::ca::live_object,
      virtual public ::comparable_array < live_object * >
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

} // namespace ca


