#pragma once


namespace aura
{


   class CLASS_DECL_AURA message_queue_listener:
      virtual public ::object
   {
   public:

      virtual void message_queue_message_handler(signal_details * pobj) { UNREFERENCED_PARAMETER(pobj); };

   };


} // namespace aura









