//#include "framework.h"


root::root()
{

   m_countReference  = 1;
   m_bHeap           = false;
   m_pauraapp        = NULL;

}


root::root(::aura::application * papp)
{

   m_countReference  = 1;
   m_bHeap           = false;
   m_pauraapp        = papp;

}


root::~root()
{
}




void root::delete_this()
{

   // quite verisimple default implementation
   delete this;

}


