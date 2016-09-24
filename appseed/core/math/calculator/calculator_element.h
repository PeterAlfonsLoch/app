#pragma once


namespace calculator
{


   class CLASS_DECL_CORE element:
      virtual public ::object
   {
   public:


      element *      m_pparent;

      sp(token)      m_ptoken;
      element *      m_pelement1;
      element *      m_pelement2;
      element *      m_pelement3;


      element();
      virtual ~element();


      value get_value();
      string get_expression();

   };


} // namespace calculator














