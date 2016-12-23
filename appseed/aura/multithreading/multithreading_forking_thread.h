#pragma once


#undef new

#define new AURA_NEW

template < typename PRED >
class forking_thread:
   virtual public thread
{
public:

   PRED m_pred;

   sp(object) m_pholdref;

   forking_thread(::aura::application * papp, sp(object) pholdref, PRED pred) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred)
   {

   }

   forking_thread(::aura::application * papp,PRED pred) :
      object(papp),
      thread(papp),
      m_pred(pred)
   {

   }


   virtual ~forking_thread()
   {

   }

   int32_t run()
   {

      m_pred();

      return 0;

   }

};


template < typename PRED >
::thread * fork(::aura::application * papp, sp(object) pholdref, PRED pred)
{

   auto pforkingthread = new forking_thread < PRED >(papp, pholdref, pred);

   ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

   pthread->begin();

   return pthread;

}


template < typename PRED >
::thread * fork(::aura::application * papp, PRED pred)
{

   auto pforkingthread = new forking_thread < PRED >(papp, pred);

   ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

   pthread->begin();

   return pthread;

}


template < typename PRED >
inline ::thread * object::fork(PRED pred)
{

   return ::fork(get_app(),pred);

}


template < typename T >
inline void fork_release(::aura::application * papp, sp(T) & t)
{

   try
   {

      T * pt;

      pt = t.m_p;

      pt->add_ref();

      t.release();

      ::fork(papp, [&]()
      {

         ::release(pt);

      });

   }
   catch (...)
   {


   }

}



