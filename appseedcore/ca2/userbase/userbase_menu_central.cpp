#include "StdAfx.h"


HHOOK BaseMenuCentral::m_hCBTHook = NULL;

static class CBaseMenuCentralInit
{
public:
   CBaseMenuCentralInit()
   {
      BaseMenuCentral::HookCBTHook();
   }

   ~CBaseMenuCentralInit()
   {
      BaseMenuCentral::UnhookCBTHook();
   }
} __basemenucentralInit;

BaseMenuCentral::BaseMenuCentral(::ca::application * papp) :
   ca(papp),
   m_fontMenu(papp)
{
   m_pil             = new image_list(papp);
   m_pilHue          = new image_list(papp);
   m_pilBlend        = new image_list(papp);
   m_pilHueLight     = new image_list(papp);
   NONCLIENTMETRICS ncm;
   ncm.cbSize = sizeof(NONCLIENTMETRICS);
   ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
   VERIFY(m_fontMenu->CreateFontIndirect(&ncm.lfMenuFont));
   if(!MenuV033GetImageList()->create(
      16, 16,
      ILC_COLOR24 | ILC_MASK, 
      0, 10))
   {
      return;
   }
}

BaseMenuCentral::~BaseMenuCentral()
{
   if(m_pil != NULL)
   {
      delete m_pil;
      m_pil = NULL;
   }
   if(m_pilHue != NULL)
   {
      delete m_pilHue;
      m_pilHue = NULL;
   }
   if(m_pilBlend != NULL)
   {
      delete m_pilBlend;
      m_pilBlend = NULL;
   }
   if(m_pilHueLight != NULL)
   {
      delete m_pilHueLight;
      m_pilHueLight = NULL;
   }
}

BaseMenuCentral * BaseMenuCentral::GetMenuCentral(::ca::application * papp)
{
   return dynamic_cast < BaseMenuCentralContainer * > (papp)->get_menucentral();
}

/*bool BaseMenuCentral::MenuV033CreateImageMap(UINT uiaMenuV003Map [][2])
{
   UINT user = 0;
   int i;
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

   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);

   System.imaging().CreateHueImageList(
      &spgraphics,
      MenuV033GetImageListHueLight(),
      MenuV033GetImageList(),
      RGB(220, 220, 215),
      0.50);
   



   return VMSR_SUCCESS;
}

*/

bool BaseMenuCentral::MenuV033AddImageMap(xml::node * lpnode)
{

/*   if(!MenuV033GetImageList()->create(
      16, 16,
      ILC_COLOR24 | ILC_MASK, 
      0, 10))
   {
      return FALSE;
   }*/
   int iIndex;
   id id;
   for(int i = 0; i < lpnode->children().get_count(); i++)
   {
      xml::node * lpchild = lpnode->child_at(i);
      string strId;
      lpchild->get_attr("id", strId);
      string strImage;
      lpchild->get_attr("img", strImage);
      iIndex = MenuV033GetImageList()->add_matter(strImage);
      id = strId;
      m_mapCommandToImage.set_at(id, iIndex);
      m_mapImageToCommand.set_at(iIndex, id);
   }


   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);

   class imaging & imaging = System.imaging();

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

   return VMSR_SUCCESS;
}




::ca::font * BaseMenuCentral::MenuV033GetFont()
{
   return GetMenuFont();
}

::ca::font * BaseMenuCentral::GetMenuFont()
{
   return m_fontMenu;
}



/*VMSRESULT BaseMenuCentral::MenuV033CreateImageMap()
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
    return VMSR_SUCCESS;
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
      return class id();
   }
}

image_list * BaseMenuCentral::MenuV033GetImageList()
{
    return m_pil;
}

image_list * BaseMenuCentral::MenuV033GetImageListHue()
{
    return m_pilHue;
}

image_list * BaseMenuCentral::MenuV033GetImageListBlend()
{
    return m_pilBlend;
}

image_list * BaseMenuCentral::MenuV033GetImageListHueLight()
{
    return m_pilHueLight;
}

LRESULT CALLBACK BaseMenuCentral::CBTHook(int nCode, WPARAM wParam, LPARAM lParam)
{
   static int cbt_counter = 0;

   LRESULT lRes;

   ++cbt_counter;

   if (cbt_counter == 1)
   {
      if (nCode == HCBT_CREATEWND)
      {
//         HWND hWnd = (HWND)wParam;
         lRes = CallNextHookEx(m_hCBTHook, nCode, wParam, lParam);
         goto out;
      }

      if (nCode == HCBT_DESTROYWND)
      {
//         HWND hWnd = (HWND)wParam;
         lRes = CallNextHookEx(m_hCBTHook, nCode, wParam, lParam);
         goto out;
      }
   }

   lRes = CallNextHookEx(m_hCBTHook, nCode, wParam, lParam);

out:
   --cbt_counter;
   return lRes;
}

void BaseMenuCentral::HookCBTHook()
{
   if (!m_hCBTHook)
   {
      m_hCBTHook = SetWindowsHookEx(WH_CBT, CBTHook, 
         NULL, GetCurrentThreadId());
   }
}

void BaseMenuCentral::UnhookCBTHook()
{
   if (m_hCBTHook)
   {
      UnhookWindowsHookEx(m_hCBTHook);    
      m_hCBTHook = NULL;
   }
}

/* trans
void BaseMenuCentral::RemoveBorder(HWND hWnd)
{
   const int SWP_STYLE = SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | 
      SWP_NOZORDER | SWP_NOACTIVATE;

   DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
   DWORD dwStyleEx = ::GetWindowLong(hWnd, GWL_EXSTYLE);
   ::user::interaction::ModifyStyle(hWnd, WS_POPUP | WS_DLGFRAME | WS_THICKFRAME | WS_BORDER, 0, SWP_STYLE);
   ::user::interaction::ModifyStyleEx(hWnd, WS_EX_STATICEDGE|WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME, 0, SWP_STYLE);
}
*/

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

bool BaseMenuCentralContainer::initialize_central_container(::ca::application * papp)
{
   m_pmenucentral = new BaseMenuCentral(papp);
   if(!m_pmenucentral)
      AfxThrowMemoryException();
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
