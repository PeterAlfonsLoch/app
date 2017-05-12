//#include "framework.h"


namespace user
{

   
   namespace wndfrm
   {


      namespace frame
      {

         
         control_box_button::control_box_button(::aura::application * papp) :
            object(papp),
            ::user::button(papp)
         {
            
         }
         
         
         control_box_button::~control_box_button()
         {
            
         }


         void control_box_button::UpdateWndRgn()
         {

         }


         void control_box_button::_001OnClip(::draw2d::graphics * pgraphics)
         {

            //return;



            try
            {

               rect rectClip;

               ::aura::draw_context * pdrawcontext = pgraphics->::core::simple_chain < ::aura::draw_context >::get_last();

               rect rectClient;

               bool bFirst = true;

               if (pdrawcontext != NULL)
               {

                  rectClient = pdrawcontext->m_rectWindow;

                  ScreenToClient(rectClient);

                  rectClient.bottom++;
                  rectClient.right++;

                  rectClip = rectClient;

                  bFirst = false;

               }

               ::user::interaction * pui = this;

               ::rect rectFocus;

               ::rect rectIntersect;

               index i = 0;

               while (pui != NULL)
               {

                  pui->GetWindowRect(rectClient);

                  if (pui == m_pcontrolbox->m_pworkset->GetWndDraw())
                  {

                     m_pcontrolbox->m_pworkset->m_pframeschema->GetFrameRect(&rectFocus);

                  }
                  else
                  {

                     pui->GetClientRect(rectFocus);

                  }


                  rectFocus.offset(rectClient.top_left());

                  ScreenToClient(rectFocus);

                  rectFocus.bottom++;
                  rectFocus.right++;

                  if (i == 0)
                  {

                     rectIntersect = rectFocus;

                  }
                  else
                  {

                     rectIntersect.intersect(rectFocus);

                  }

                  i++;

                  pui = pui->GetParent();

               }

               pgraphics->IntersectClipRect(rectIntersect);

            }
            catch (...)
            {

               throw simple_exception(::get_thread_app(), "no more a window");

            }

         }

      } // namespace frame


   } // namespace wndfrm


} // namespace user


















