#pragma once


namespace core
{


   class timer_callback;


   class CLASS_DECL_CORE timer:
      virtual public ::user::interaction
   {
   public:

      enum eID
      {
         ID_HOVER = 147
      };


      timer_callback *     m_pcallback;
      bool                 m_bEnable;


      timer();
      virtual ~timer();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual bool DestroyWindow();

      bool IsEnabled();
      bool EnableTimer(bool bEnable = true);
      bool create(timer_callback * pCallback);

      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnUser);

   };


} // namespace core





