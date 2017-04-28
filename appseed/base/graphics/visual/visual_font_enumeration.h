#pragma once


namespace visual
{


   class CLASS_DECL_AXIS font_enumeration :
      virtual public object
   {
   public:

      
      stringa              m_stra;
      stringa              m_straPath;
      ::draw2d::font::csa  m_csa;


      font_enumeration(::aura::application * papp);

      virtual ~font_enumeration();

      template < typename PRED >
      void start_update(PRED predRunAfterEnumeration = []() {})
      {

         ::fork(get_app(), [&]()
         {

            update();

            predRunAfterEnumeration();

         });

      }


      void update();

   };



} // namespace visual



