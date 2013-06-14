#pragma once

class SimpleMenu;
class image_list;

class CLASS_DECL_ca2 BaseMenuCentral :
   virtual public ::ca2::object
{
public:
   static BaseMenuCentral * GetMenuCentral(sp(::ca2::application) papp);
   BaseMenuCentral(sp(::ca2::application) papp);
   virtual ~BaseMenuCentral();
   sp(image_list) MenuV033GetImageList();
   sp(image_list) MenuV033GetImageListHue();
   sp(image_list) MenuV033GetImageListBlend();
   sp(image_list) MenuV033GetImageListHueLight();
   //bool MenuV033CreateImageMap(UINT uiaMenuV003Map [][2]);
   bool MenuV033AddImageMap(sp(::xml::node) lpnode);

   UINT CommandToImage(id id);
   id ImageToCommand(UINT uiImage);


   map < id, id, UINT, UINT > m_mapCommandToImage;
   map < UINT, UINT, id, id > m_mapImageToCommand;

   sp(image_list)    m_pil;
   sp(image_list)    m_pilHue;
   sp(image_list)    m_pilBlend;
   sp(image_list)    m_pilHueLight;
   ::ca2::font_sp          m_fontMenu;

   ::ca2::font * MenuV033GetFont();
   ::ca2::font * GetMenuFont();

};


class CLASS_DECL_ca2 BaseMenuCentralContainer
{
public:
   BaseMenuCentralContainer();
   virtual ~BaseMenuCentralContainer();
   virtual BaseMenuCentral * get_menucentral();
   virtual bool initialize_central_container(sp(::ca2::application) papp);
   virtual bool finalize_central_container();
protected:
   BaseMenuCentral * m_pmenucentral;
};