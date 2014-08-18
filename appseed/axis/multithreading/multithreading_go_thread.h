#pragma once


class CLASS_DECL_AXIS go_thread :
   virtual public simple_thread
{
public:


   bool m_bRelease;
   bool m_bStartRelease;


   go_thread(sp(::base::application) papp, bool bRelease = true);
   virtual ~go_thread();

   virtual void start();

   virtual int32_t run();
   virtual void go() = 0;

};
