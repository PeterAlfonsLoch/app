#pragma once


namespace user
{


   class CLASS_DECL_CORE margin_base:
      virtual public ::user::interaction
   {
   public:


      rect        m_rectMargin;


      margin_base();
      virtual ~margin_base();


      virtual void get_margin_rect(LPRECT lprectMargin) override;


   };


   template < class BASE >
   class margin:
      virtual public margin_base,
      virtual public BASE
   {
   public:

      margin()
      {
      }

      margin(::aura::application * papp):
         object(papp)
      {
      }

      virtual ~margin()
      {
      }

      virtual void install_message_handling(::message::dispatch * pinterface)
      {

         ::user::margin_base::install_message_handling(pinterface);
         BASE::install_message_handling(pinterface);

      }

//      void ScreenToClient(LPRECT lprect)
  //    {

    //     BASE::ScreenToClient(lprect);

         /*lprect->left   -= m_rectMargin.left;
         lprect->right  -= m_rectMargin.left;
         lprect->top    -= m_rectMargin.top;
         lprect->bottom -= m_rectMargin.top;*/

     // }

      virtual point get_viewport_offset() override
      {
         
         point ptOffset = BASE::get_viewport_offset();

         ptOffset.x += m_rectMargin.left;
         
         ptOffset.y += m_rectMargin.top;

         return ptOffset;

      }


      void set_viewport_offset(int x,int y)
      {

         BASE::set_viewport_offset(x - m_rectMargin.left, y - m_rectMargin.top);

      }


      virtual size get_total_size() override
      {

         size s = BASE::get_total_size();

         return size(s.cx + m_rectMargin.left + m_rectMargin.right,s.cy + m_rectMargin.top + m_rectMargin.bottom);

      }

   };

} // namespace user



