#pragma once

namespace calculator
{

      class CLASS_DECL_ca2 element :
         virtual public ::ca2::ca2
      {
      public:

         element();
         ~element();

         token *     m_ptoken;
         element *   m_pparent;
         element *   m_pelement1;
         element *   m_pelement2;
         element *   m_pelement3;


         value get_value();
         string get_expression();
         



        
      };



} // namespace calculator