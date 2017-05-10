#pragma once


class delay_thread :
   virtual public thread
{

public:

   DWORD       m_dwSleep;

   delay_thread(::aura::application * p, DWORD dwSleep = 1000) :
      ::object(p),
      thread(p)
   {
      m_dwSleep = dwSleep;
   }


   int run()
   {

      while (true)
      {

         DWORD dwSleep = m_dwSleep;

         if (dwSleep == 0)
         {

            break;

         }

         m_dwSleep = 0;

         Sleep(dwSleep);

      }

      do_delayed();

      return 0;

   }

   virtual void do_delayed()
   {

   }

};

template < typename PRED >
class pred_delay_thread :
   virtual public delay_thread
{

public:

   PRED &      m_pred;
   pred_delay_thread(::aura::application * p, PRED pred, DWORD dwSleep = 1000) :
      m_pred(pred),
      ::object(p),
      thread(p),
      delay_thread(p, dwSleep)
   {
   }


   virtual void do_delayed() override
   {

      m_pred();

   }

};

template < typename PRED >
delay_thread * pred_delay(::aura::application * papp, DWORD dwDelay, PRED pred)
{

   delay_thread * p = canew(pred_delay_thread < PRED >(papp, pred, dwDelay));

   p->begin();

   return p;

}
