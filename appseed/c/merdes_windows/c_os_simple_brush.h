#pragma once


class CLASS_DECL_c simple_brush
{
public:

   enum e_type
   {
      type_none,
      type_brush,
      type_solid,
      type_null,
   };


   e_type                        m_etype;

   union
   {
      
      ID2D1Brush *               m_pbrush;

      ID2D1SolidColorBrush *     m_psolidbrush;

   };



   simple_brush();
   ~simple_brush();


   virtual bool create_solid(COLORREF cr, simple_graphics & g);
   virtual bool from_stock(int iId);

   virtual bool destroy();


   ID2D1Brush * get_os_data();


};




