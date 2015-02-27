#pragma once

class SimpleMenu;
class image_list;

class CLASS_DECL_CORE BaseMenuCentral :
   virtual public ::object
{
public:
   static BaseMenuCentral * GetMenuCentral(::aura::application * papp);
   BaseMenuCentral(::aura::application * papp);
   virtual ~BaseMenuCentral();
   sp(image_list) MenuV033GetImageList();
   sp(image_list) MenuV033GetImageListHue();
   sp(image_list) MenuV033GetImageListBlend();
   sp(image_list) MenuV033GetImageListHueLight();
   //bool MenuV033CreateImageMap(UINT uiaMenuV003Map [][2]);
   bool MenuV033AddImageMap(::xml::node node);

   int CommandToImage(id id);
   id ImageToCommand(int iImage);


   id_map < int > m_mapCommandToImage;
   int_map < id > m_mapImageToCommand;

   sp(image_list)    m_pil;
   sp(image_list)    m_pilHue;
   sp(image_list)    m_pilBlend;
   sp(image_list)    m_pilHueLight;
   ::draw2d::font_sp          m_fontMenu;

   ::draw2d::font * MenuV033GetFont();
   ::draw2d::font * GetMenuFont();

};


