#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA tileset :
      virtual public object
   {
   public:

      
      image_list        m_il;

      string_to_int     m_map;


      tileset(::aura::application * papp);
      virtual ~tileset();

      bool load_tilemap(string strMatter);
      bool load_imagelist(::draw2d::dib * pdib, const stringa & stra);

      bool draw(::draw2d::graphics * pgraphics, const char * psz, int x, int y);

   };



} // namespace estamira