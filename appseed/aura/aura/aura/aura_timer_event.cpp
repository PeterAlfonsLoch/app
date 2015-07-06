class timer_event:
   virtual public timer,
   virtual public manual_reset_event
{
public:


   timer_event(::aura::application * papp,int iTimer):
      object(papp),
      timer(papp,iTimer),
      manual_reset_event(papp)
   {

   }

   virtual ~timer_event()
   {


   }

   bool wait(int millis)
   {

      start(millis,false);

      manual_reset_event::wait();

      return true;
   }




};


