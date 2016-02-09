#pragma once


namespace user
{

   class interaction_base;

} // namespace user


namespace windows
{


   class CLASS_DECL_BASE window_draw:
      virtual public ::user::window_draw,
      virtual public ::user::message_queue
   {
   public:


      bool                                   m_bRender;
      DWORD                                  m_dwLastRedrawRequest;
      //mutex                                  m_mutexRender;
      DWORD                                  m_dwLastUpdate;
      DWORD                                  m_dwLastDelay;


      window_draw(::aura::application * papp);
      virtual ~window_draw();


      virtual void do_events();


      bool UpdateBuffer(const RECT & rect);

      virtual bool UpdateBuffer();

      virtual bool pre_run();
      virtual int32_t run();
      virtual bool finalize();

      virtual UINT RedrawProc();

      virtual void asynch_redraw();
      virtual void _asynch_redraw();
      virtual void synch_redraw();
      virtual void _synch_redraw();


      virtual void message_handler(signal_details * pobj);

   };


} // namespace windows


