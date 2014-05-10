#include "framework.h"



BaseMenuCentral::BaseMenuCentral(sp(::base::application) papp) :
   element(papp),
   m_fontMenu(allocer())
{

   m_pil             = new image_list(papp);
   m_pilHue          = new image_list(papp);
   m_pilBlend        = new image_list(papp);
   m_pilHueLight     = new image_list(papp);


   VERIFY(m_fontMenu->create_point_font("Arial Unicode", 11));

#ifdef WINDOWSEX
   if(!MenuV033GetImageList()->create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 10))
   {
      throw simple_exception(papp, "resource exception BaseMenuCentral constructor");
   }
#else
   if(!MenuV033GetImageList()->create(16, 16, 0, 0, 10))
   {
      throw simple_exception(papp, "resource exception BaseMenuCentral constructor");
   }
#endif

}

BaseMenuCentral::~BaseMenuCentral()
{
}

BaseMenuCentral * BaseMenuCentral::GetMenuCentral(sp(::base::application) papp)
{
   return App(papp).userex()->get_menucentral();
}

/*bool BaseMenuCentral::MenuV033CreateImageMap(UINT uiaMenuV003Map [][2])
{
   UINT user = 0;
   int32_t i;
   while(true)
   {
      if(uiaMenuV003Map[user][0] == 0xffffffff &&
         uiaMenuV003Map[user][1] == 0xffffffff)
         break;
      i = MenuV033GetImageList()->add(System.LoadIcon(uiaMenuV003Map[user][1]));
      m_mapCommandToImage.set_at(uiaMenuV003Map[user][0], i);
      m_mapImageToCommand.set_at(i, uiaMenuV003Map[user][0]);
      user++;
   }

   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);

   System.visual().imaging().CreateHueImageList(
      &spgraphics,
      MenuV033GetImageListHueLight(),
      MenuV033GetImageList(),
      RGB(220, 220, 215),
      0.50);




   return ;
}

*/

bool BaseMenuCentral::MenuV033AddImageMap(sp(::xml::node) lpnode)
{

/*   if(!MenuV033GetImageList()->create(
      16, 16,
      ILC_COLOR24 | ILC_MASK,
      0, 10))
   {
      return FALSE;
   }*/
   int32_t iIndex;
   id id;
   for(int32_t i = 0; i < lpnode->children().get_count(); i++)
   {
      sp(::xml::node) lpchild = lpnode->child_at(i);
      string strId;
      lpchild->get_attr("id", strId);
      string strImage;
      lpchild->get_attr("img", strImage);
      iIndex = MenuV033GetImageList()->add_matter(strImage);
      id = strId;
      m_mapCommandToImage.set_at(id, iIndex);
      m_mapImageToCommand.set_at(iIndex, id);
   }


   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);

   class imaging & imaging = System.visual().imaging();

   imaging.CreateHueImageList(
      spgraphics,
      m_pilHue,
      MenuV033GetImageList(),
      RGB(192, 192, 180),
      0.50);

   imaging.Createcolor_blend_ImageList(
      m_pilBlend,
      MenuV033GetImageList(),
      RGB(255, 255, 240),
      64);

   imaging.CreateHueImageList(
      spgraphics,
      m_pilHueLight,
      m_pil,
      RGB(220, 220, 215),
      0.5);

   return true;

}




::draw2d::font * BaseMenuCentral::MenuV033GetFont()
{
   return GetMenuFont();
}

::draw2d::font * BaseMenuCentral::GetMenuFont()
{
   return m_fontMenu;
}



/*bool BaseMenuCentral::MenuV033CreateImageMap()
{
    UINT uiaMenuV003Map [][2] =
    {
        {ID_FILE_NEW, 0},
        {ID_FILE_OPEN, 1},
        {ID_FILE_SAVE, 2},
        {ID_VIEW_FULL_SCREEN, 7},
        {ID_TOOLS_ALBUM, 8},
        {ID_VIEW_PLAYLIST, 9},
        {ID_VIEW_LYRICS, 10},
        {ID_TOOLS_MIXER, 11},
        {ID_PLAY, 12},
        {ID_STOP, 13},
        {ID_PAUSE, 14},
        {ID_NEXTSONG, 15},
        {ID_ALBUM_NAVIGATOR, 20},
        {ID_ALBUM_FULLLIST, 21},
        {ID_ALBUM_TREELIST, 22},
        {ID_ALBUM_SEARCHLIST, 23},
        {ID_ALBUM_RESERVESONG, 24},
        {ID_CHECK, 25},
        {ID_ALBUM_DUPLICATESLIST, 27},
    };

    UINT uiSize = sizeof(uiaMenuV003Map) / (sizeof(UINT) * 2);
    for(UINT user = 0; user < uiSize; user++)
    {
        theDll.m_relMenuV033ImageMap.add(uiaMenuV003Map[user][0], uiaMenuV003Map[user][1]);
    }
    return ;
}*/

UINT BaseMenuCentral::CommandToImage(id id)
{
   UINT uiImage;
   if(m_mapCommandToImage.Lookup(id, uiImage))
   {
      return uiImage;
   }
   else
   {
      return 0xffffffff;
   }
}

id BaseMenuCentral::ImageToCommand(UINT uiImage)
{
   id id;
   if(m_mapImageToCommand.Lookup(uiImage, id))
   {
      return id;
   }
   else
   {
      return ::id();
   }
}

sp(image_list) BaseMenuCentral::MenuV033GetImageList()
{
    return m_pil;
}

sp(image_list) BaseMenuCentral::MenuV033GetImageListHue()
{
    return m_pilHue;
}

sp(image_list) BaseMenuCentral::MenuV033GetImageListBlend()
{
    return m_pilBlend;
}

sp(image_list) BaseMenuCentral::MenuV033GetImageListHueLight()
{
    return m_pilHueLight;
}


BaseMenuCentralContainer::BaseMenuCentralContainer()
{
   m_pmenucentral = NULL;
}

BaseMenuCentralContainer::~BaseMenuCentralContainer()
{
}

BaseMenuCentral * BaseMenuCentralContainer::get_menucentral()
{
   return m_pmenucentral;
}

bool BaseMenuCentralContainer::initialize_central_container(sp(::base::application) papp)
{
   m_pmenucentral = new BaseMenuCentral(papp);
   if(!m_pmenucentral)
      throw memory_exception(papp);
   return true;
}


bool BaseMenuCentralContainer::finalize_central_container()
{
   if(m_pmenucentral != NULL)
   {
      delete m_pmenucentral;
      m_pmenucentral = NULL;
   }
   return true;
}
