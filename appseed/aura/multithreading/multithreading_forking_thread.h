#pragma once


template < typename PRED >
class forking_thread:
   virtual public thread
{
public:

   PRED m_pred;

   forking_thread(::aura::application * papp,PRED pred) :
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
void fork(::aura::application * papp,PRED pred)
{

   new forking_thread < PRED >(papp,pred);

}

template < typename PRED >
inline void object::fork(PRED pred)
{

   ::fork(get_app(),pred);

}
