#pragma once


class CLASS_DECL_AXIS rgb_quad_array : 
   public array < RGBQUAD, RGBQUAD >
{
public:
   rgb_quad_array();
   virtual ~rgb_quad_array();

   void create_web_palette();
};