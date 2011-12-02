#pragma once

class SimpleMenu;
class image_list;

class CLASS_DECL_ca BaseMenuCentral :
   virtual public ::radix::object
{
public:
   static BaseMenuCentral * GetMenuCentral(::ax::application * papp);
   BaseMenuCentral(::ax::application * papp);
   virtual ~BaseMenuCentral();
   image_list * MenuV033GetImageList();
   image_list * MenuV033GetImageListHue();
   image_list * MenuV033GetImageListBlend();
   image_list * MenuV033GetImageListHueLight();
   //bool MenuV033CreateImageMap(UINT uiaMenuV003Map [][2]);
   bool MenuV033AddImageMap(xml::node * lpnode);

   UINT CommandToImage(id id);
   id ImageToCommand(UINT uiImage);


   ::collection::map < id, id, UINT, UINT > m_mapCommandToImage;
   ::collection::map < UINT, UINT, id, id > m_mapImageToCommand;

   image_list *    m_pil;
   image_list *    m_pilHue;
   image_list *    m_pilBlend;
   image_list *    m_pilHueLight;
   ::ax::font_sp          m_fontMenu;

   ::ax::font * MenuV033GetFont();
   ::ax::font * GetMenuFont();

   static HHOOK m_hCBTHook;
   static LRESULT CALLBACK CBTHook(int nCode, WPARAM wParam, LPARAM lParam);
   static void UnhookCBTHook();
   static void HookCBTHook();
   // trans static void RemoveBorder(HWND hWnd);
};

class CLASS_DECL_ca BaseMenuCentralContainer
{
public:
   BaseMenuCentralContainer();
   virtual ~BaseMenuCentralContainer();
   virtual BaseMenuCentral * get_menucentral();
   virtual bool initialize_central_container(::ax::application * papp);
   virtual bool finalize_central_container();
protected:
   BaseMenuCentral * m_pmenucentral;
};