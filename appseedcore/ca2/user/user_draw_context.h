#pragma once

namespace user
{
   
   class CLASS_DECL_ca draw_context :
      virtual public ::radix::object
   {
   public:
      rect            m_rectClient;
      bool                 m_bItemHover;
      bool                 m_bSubItemHover;
      bool                 m_bFocus;
   };

} // namespace user