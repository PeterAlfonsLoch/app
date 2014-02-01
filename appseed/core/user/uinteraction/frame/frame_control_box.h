#pragma once



namespace uinteraction
{


   namespace frame
   {


      class  CLASS_DECL_CORE control_box :
         virtual public ::user::interaction
      {
      public:

         WorkSet *      m_pworkset;
         DWORD          m_dwShowTime;
         bool           m_bShowAttempt;
         bool           m_bDrag;
         point          m_ptDrag;

         control_box(sp(base_application) papp);
         virtual ~control_box();


         virtual void install_message_handling(::message::dispatch *pinterface);


         void drag(point pt);


         DECL_GEN_SIGNAL(_001OnShowWindow)
         DECL_GEN_SIGNAL(_001OnLButtonDown)
         DECL_GEN_SIGNAL(_001OnLButtonUp)
         DECL_GEN_SIGNAL(_001OnMouseMove)
         DECL_GEN_SIGNAL(_001OnTimer)
         DECL_GEN_SIGNAL(_001OnCreate)

      };


   } // namespace frame


} // namespace uinteraction




