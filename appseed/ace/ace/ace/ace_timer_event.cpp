



timer_event::timer_event(::ace::application * papp,int iTimer):
object(papp),
timer(papp,iTimer),
m_ev(papp)
{

}

timer_event::~timer_event()
{


}

bool timer_event::wait(int millis)
{

   start(millis,false);

   m_ev.wait();

   return true;
}


bool timer_event::on_timer()
{

   m_ev.SetEvent();

   return true;

}



