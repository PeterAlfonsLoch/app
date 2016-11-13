#pragma once


class CLASS_DECL_AURA go_thread :
   virtual public simple_thread
{
public:



   go_thread(::aura::application * papp);
   virtual ~go_thread();

   virtual void start();

   virtual int32_t run();
   virtual void go() = 0;

};
