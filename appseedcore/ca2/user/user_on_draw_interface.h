#pragma once


namespace user
{
   class buffer;
}


class CLASS_DECL_ca on_draw_interface : 
   virtual public window_draw_interface,
   virtual public gen::signalizable
{
protected:
   user::buffer *   m_pbuffer;
   ::user::win::message::dispatch * m_pwindowinterface;
public:
   bool                 m_bOnPaint;
   bool                 m_bAutoClip;
   void InstallBuffering(::user::win::message::dispatch * pinterface);
   void UninstallBuffering();

   on_draw_interface();
   virtual ~on_draw_interface();

   virtual void OnDrawInterfaceDraw(::ca::graphics * pdc);
   virtual ::user::interaction * get_guie();
   virtual void _001InstallOnDrawInterface(::user::win::message::dispatch * pinterface);

   DECL_GEN_VSIGNAL(OnDrawInterfacePaint)
   DECL_GEN_VSIGNAL(OnDrawInterfaceNcPaint)

};

