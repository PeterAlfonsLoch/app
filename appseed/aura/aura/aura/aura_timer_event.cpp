



timer_event::timer_event(::aura::application * papp,int iTimer):
object(papp),
timer(papp,iTimer),
manual_reset_event(papp)
{

}

timer_event::~timer_event()
{


}

bool timer_event::wait(int millis)
{

   start(millis,false);

   manual_reset_event::wait();

   return true;
}


bool timer_event::on_timer()
{

   SetEvent();

   return true;

}



