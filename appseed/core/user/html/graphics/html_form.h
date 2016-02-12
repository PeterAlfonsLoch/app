#pragma once


namespace html
{


   class CLASS_DECL_CORE form:
      virtual public object
   {
   public:

      ::html::elemental *              m_pelementalLButtonDown;
      ::html::elemental *              m_pelementalHover;
      spa(::html::elemental)           m_elementalptraMouseMove;
      sp(::html::data)                 m_sphtmldata;

      form();
      virtual ~form();

   };


} // namespace html

