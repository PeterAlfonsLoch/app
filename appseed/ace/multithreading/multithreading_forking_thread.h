#pragma once




template < typename PRED >
class forking_thread:
   virtual public thread
{
public:

   PRED m_pred;

   sp(object) m_pholdref;

   forking_thread(::ace::application * papp, sp(object) pholdref, PRED pred) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred)
   {

      begin();

   }

   forking_thread(::ace::application * papp,PRED pred) :
      object(papp),
      thread(papp),
      m_pred(pred)
   {

      begin();

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
void fork(::ace::application * papp, sp(object) pholdref, PRED pred)
{

   new forking_thread < PRED >(papp, pholdref, pred);

}

template < typename PRED >
void fork(::ace::application * papp,PRED pred)
{

   new forking_thread < PRED >(papp,pred);

}

template < typename PRED >
inline void object::fork(PRED pred)
{

   ::fork(get_app(),pred);

}
