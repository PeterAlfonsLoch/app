#pragma once


namespace user
{

   class ::user::interaction_base;

} // namespace user


namespace windows
{


   class CLASS_DECL_AXIS window_draw:
      virtual public ::user::window_draw,
      virtual public message_queue
   {
   public:


      enum EOptimize
      {
         OptimizeNone,
         OptimizeThis,
         OptimizeAllNext,
      };

      mutex                                  m_mutexRendering;
      mutex                                  m_mutexRgnUpdate;
      semaphore                              m_semaphoreBuffer;
      bool                                   m_bRender;
      DWORD                                  m_dwLastRedrawRequest;
      mutex                                  m_mutexRender;
      critical_section                       m_csWndInterfaceMap;
      DWORD                                  m_dwLastUpdate;
      DWORD                                  m_dwLastDelay;


      window_draw(sp(::base::application) papp);
      virtual ~window_draw();


      virtual void do_events();


      bool UpdateBuffer(const RECT & rect);

      virtual bool UpdateBuffer();

      virtual bool pre_run();
      virtual int32_t run();

      virtual UINT RedrawProc();

      virtual void asynch_redraw();
      virtual void _asynch_redraw();
      virtual void synch_redraw();
      virtual void _synch_redraw();

   };


} // namespace windows


