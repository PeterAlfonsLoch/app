#pragma once

class SimpleMenu;
class image_list;

class CLASS_DECL_ca2 BaseMenuCentral :
   virtual public ::ca::object
{
public:
   static BaseMenuCentral * GetMenuCentral(::ca::applicationsp papp);
   BaseMenuCentral(::ca::applicationsp papp);
   virtual ~BaseMenuCentral();
   image_list * MenuV033GetImageList();
   image_list * MenuV033GetImageListHue();
   image_list * MenuV033GetImageListBlend();
   image_list * MenuV033GetImageListHueLight();
   //bool MenuV033CreateImageMap(UINT uiaMenuV003Map [][2]);
   bool MenuV033AddImageMap(xml::node * lpnode);

   UINT CommandToImage(id id);
   id ImageToCommand(UINT uiImage);


   map < id, id, UINT, UINT > m_mapCommandToImage;
   map < UINT, UINT, id, id > m_mapImageToCommand;

   image_list *    m_pil;
   image_list *    m_pilHue;
   image_list *    m_pilBlend;
   image_list *    m_pilHueLight;
   ::ca::font_sp          m_fontMenu;

   ::ca::font * MenuV033GetFont();
   ::ca::font * GetMenuFont();

};


class CLASS_DECL_ca2 BaseMenuCentralContainer
{
public:
   BaseMenuCentralContainer();
   virtual ~BaseMenuCentralContainer();
   virtual BaseMenuCentral * get_menucentral();
   virtual bool initialize_central_container(::ca::applicationsp papp);
   virtual bool finalize_central_container();
protected:
   BaseMenuCentral * m_pmenucentral;
};