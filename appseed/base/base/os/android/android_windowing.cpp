#include "framework.h"
#include "axis/user/user.h"


CLASS_DECL_AURA int32_t oswindow_find_message_only_window(::user::interaction * puibaseMessageWindow);
//CLASS_DECL_AURA int32_t oswindow_find(Display * pdisplay,Window window);
//CLASS_DECL_AURA int32_t oswindow_find(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_get_message_only_window(::user::interaction * puibaseMessageWindow);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Display * pdisplay,Window window,Visual * pvisual = NULL,int iDepth = -1,int iScreen = -1,Colormap colormap = None);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Window window);
//CLASS_DECL_AURA oswindow oswindow_defer_get(Window w);
//CLASS_DECL_AURA bool oswindow_remove(Display * pdisplay,Window window);
CLASS_DECL_AURA bool oswindow_remove_message_only_window(::user::interaction * puibaseMessageOnlyWindow);


namespace user
{


	class interaction_base;
	class interaction;


} // namespace user



oswindow_data::oswindow_data()
{

	m_plongmap = new int_map < LONG >();

	m_hthread = NULL;

	m_pui = NULL;

	m_bMessageOnlyWindow = false;

	m_bDestroying = false;

}

oswindow_data::~oswindow_data()
{

	delete m_plongmap;

}



#define CA2_CCVOTAGUS_WINDOW_LONG "ca2_ccvotagus_fontopu_window_long"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE "ca2_ccvotagus_fontopu_window_long_style"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_fontopu_window_long_style_ex"

//oswindow_dataptra * oswindow_data::s_pdataptra = new oswindow_dataptra;
//mutex * oswindow_data::s_pmutex = new mutex;


int32_t oswindow_find_message_only_window(::user::interaction * pui)
{

	if (pui == NULL)
		return -1;

	synch_lock slOsWindow(oswindow_data::s_pmutex);

	for (int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
	{
		if (::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
			&& ::oswindow_data::s_pdataptra->element_at(i)->m_pui == pui)
		{
			return i;
		}
	}

	return -1;

}



int32_t oswindow_find(::user::interaction * pui)
{

	synch_lock slOsWindow(::oswindow_data::s_pmutex);

	for (int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
	{
		if (!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
			&&  ::oswindow_data::s_pdataptra->element_at(i)->m_pui == pui)
		{
			return i;
		}
	}

	return -1;

}

oswindow_data * oswindow_get_message_only_window(::user::interaction * pui)
{

	if (pui == NULL)
		return NULL;

	synch_lock slOsWindow(::oswindow_data::s_pmutex);

	int_ptr iFind = oswindow_find_message_only_window(pui);

	if (iFind >= 0)
		return ::oswindow_data::s_pdataptra->element_at(iFind);

	::oswindow_data * pdata = new oswindow_data;

	pdata->m_bMessageOnlyWindow = true;
	pdata->m_pui = pui;

	::oswindow_data::s_pdataptra->add(pdata);

	return pdata;

}


oswindow_data * oswindow_get(::user::interaction * pui)
{

	synch_lock slOsWindow(::oswindow_data::s_pmutex);

	int_ptr iFind = oswindow_find(pui);

	if (iFind >= 0)
		return ::oswindow_data::s_pdataptra->element_at(iFind);

	::oswindow_data * pdata = new ::oswindow_data;

	pdata->m_bMessageOnlyWindow = false;
	pdata->m_pui = pui;

	::oswindow_data::s_pdataptra->add(pdata);

	return pdata;

}



/*
oswindow::oswindow()
{

m_pdata = NULL;

}

oswindow::oswindow(::user::interaction * pui)
{

synch_lock slOsWindow(s_pmutex);

m_pdata = get_message_only_window(pui);



}

oswindow::oswindow(Display * pdisplay, Window interaction_impl, Visual * pvisual)
{

synch_lock slOsWindow(s_pmutex);

m_pdata = get(pdisplay, interaction_impl);

if(pvisual != NULL)
{

m_pdata->m_pvisual = pvisual;

}


}

oswindow::oswindow(const oswindow & oswindow)
{

m_pdata = oswindow.m_pdata;

}

oswindow::oswindow(const void * p)
{

m_pdata = (data *) p;

}

oswindow::oswindow(const LPARAM & lparam)
{

m_pdata = (data *) lparam;

}

oswindow::oswindow(const WPARAM & wparam)
{

m_pdata = (data *) wparam;

}






oswindow & oswindow::operator = (const oswindow & oswindow)
{

m_pdata = oswindow.m_pdata;

return *this;

}



*/


oswindow oswindow_defer_get(::user::interaction * pui)
{

	return oswindow_get(pui);

}



//int_bool oswindow_remove(::user::interaction * pui)
//{
//
//   synch_lock slOsWindow(::oswindow_data::s_pmutex);
//
//   int_ptr iFind = oswindow_find(pui);
//
//   if(iFind < 0)
//      return false;
//
//   ::oswindow_data::s_pdataptra->remove_at(iFind);
//
//   return true;
//
//}


bool oswindow_remove_message_only_window(::user::interaction * pui)
{

	synch_lock slOsWindow(::oswindow_data::s_pmutex);

	int_ptr iFind = oswindow_find_message_only_window(pui);

	if (iFind < 0)
		return false;

	::oswindow_data::s_pdataptra->remove_at(iFind);

	return true;

}


int32_t oswindow_data::store_name(const char * psz)
{

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);

	/*

	xdisplay d(display());

	return XStoreName(display(), interaction_impl(), psz);

	*/

	return 0;

}


int32_t oswindow_data::select_input(int32_t iInput)
{


	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);

	/*

	xdisplay d(display());

	return XSelectInput(display(), interaction_impl(), iInput);

	*/

	return 0;

}


int32_t oswindow_data::select_all_input()
{

	/*

	xdisplay d(display());

	return select_input(ExposureMask | ButtonPressMask);

	*/

	return 0;

}


int32_t oswindow_data::map_window()
{

	/*

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);

	xdisplay d(display());

	return XMapWindow(display(), interaction_impl());

	*/

	return 0;

}


void oswindow_data::post_nc_destroy()
{

	synch_lock slOsWindow(s_pmutex);

	oswindow_remove(m_pui);

}


void oswindow_data::set_user_interaction(::user::interaction * pui)
{

	synch_lock slOsWindow(s_pmutex);

	if (this == NULL)
		throw "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction";

	m_pui = pui;

	m_hthread = pui->m_pauraapp->get_os_handle();

}


::user::interaction * oswindow_data::get_user_interaction()
{

	synch_lock slOsWindow(s_pmutex);

	if (this == NULL)
		return NULL;

	if (m_pui == NULL)
		return NULL;

	return m_pui;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

	synch_lock slOsWindow(s_pmutex);

	if (this == NULL)
		return NULL;

	if (m_pui == NULL)
		return NULL;

	return m_pui;

}


bool oswindow_data::is_child(::oswindow oswindow)
{

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);

	oswindow = oswindow->GetParent();

	while (!oswindow->is_null())
	{
		if (oswindow == this)
			return true;
	}

	return false;

}

oswindow oswindow_data::GetParent()
{

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);

	if (this == NULL)
		return NULL;

	return NULL;

	/*

	Window root = 0;
	Window parent = 0;
	Window * pchildren = NULL;
	uint32_t ncount = 0;

	XQueryTree(display(), interaction_impl(), &root, &parent, &pchildren, &ncount);

	if(pchildren != NULL)
	XFree(pchildren);

	return oswindow_get(display(), parent);

	*/

	return NULL;

}

oswindow oswindow_data::SetParent(oswindow oswindow)
{

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);

	if (this == NULL)
		return NULL;

	/*

	xdisplay d(display());

	::oswindow oswindowOldParent = get_parent();

	XReparentWindow(display(), interaction_impl(), oswindow->interaction_impl(), 0, 0);

	return oswindowOldParent;

	*/

	return NULL;

}

bool oswindow_data::ShowWindow(int32_t nCmdShow)
{

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	synch_lock slOsWindow(s_pmutex);


	if(nCmdShow == SW_HIDE)
	{

      m_pui->m_bVisible = false;
      m_bVisible = false;

	}
	else
	{

      m_pui->m_bVisible = true;
      m_bVisible = true;

	}

	return false;

}



LONG oswindow_data::get_window_long(int32_t nIndex)
{

	return m_plongmap->operator[](nIndex);

	/*   Atom type = 0;
	int32_t format = 0;
	unsigned long itemcount = 0;
	unsigned long remaining = 0;
	LONG * pl = NULL;
	LONG l;

	if(XGetWindowProperty(display(), interaction_impl(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), 0, 1, False, m_pdata->m_osdisplay.atom_long_type(), &type, &format, &itemcount, &remaining, (unsigned char **) &pl) == Success)
	{

	if(pl != NULL)
	{

	l = *pl;

	XFree(pl);

	}
	else
	{

	l = 0;

	}

	}
	else
	{

	l = 0;

	}


	return l;*/

}


LONG oswindow_data::set_window_long(int32_t nIndex, LONG l)
{

	LONG lOld = m_plongmap->operator[](nIndex);

	m_plongmap->operator[](nIndex) = l;
	/*   LONG lOld = get_window_long(nIndex);

	XChangeProperty(display(), interaction_impl(), m_osdisplay.get_window_long_atom(nIndex), m_osdisplay.atom_long_type(), 32, PropModeReplace, (unsigned char *) &l, 1);*/

	return lOld;

}


bool oswindow_data::ClientToScreen(POINT * pp)
{

	return true;

}


bool oswindow_data::ScreenToClient(POINT * pp)
{

	return true;

}


/*

Atom get_window_long_atom(int32_t nIndex);

*/


long oswindow_data::get_state()
{


	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	/*

	xdisplay d(display());

	static const long WM_STATE_ELEMENTS = 2L;

	unsigned long nitems = 0;
	unsigned long leftover = 0;
	Atom xa_WM_STATE = 0;
	Atom actual_type = 0;
	int32_t actual_format = 0;
	int32_t status = 0;
	unsigned char* p = NULL;

	xa_WM_STATE = XInternAtom(display(), "WM_STATE", false);

	status = XGetWindowProperty(display(), interaction_impl(), xa_WM_STATE, 0L, WM_STATE_ELEMENTS, False, xa_WM_STATE, &actual_type, &actual_format, &nitems, &leftover, &p);


	if(status == 0)
	{
	long lStatus = -1;
	if(p!= NULL)
	lStatus = (long)*p;
	XFree(p);
	return lStatus;
	}

	*/

	return -1;

}




bool oswindow_data::is_iconic()
{

	return m_bIconic;
}


bool oswindow_data::is_window_visible()
{

	synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

	return m_bVisible;

}






/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Cairo)?oldid=10388
*/


void message_box_paint(::draw2d::graphics * pdc, stringa & stra, bool_array  & baTab, int_array  & ya, SIZE * psize)
{

	pdc->FillSolidRect(0, 0, psize->cx, psize->cy, RGB(84, 84, 77));

	draw2d::brush_sp pen(pdc->allocer());

	pen->create_solid(0);

	for (index i = 0; i < stra.get_count(); i++)
	{
		pdc->TextOut(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
	}



}


//class xlib_simple_message_box :
//   virtual public ::user::interaction
//{
//public:
//
//
//   spa(::simple_ui::label) m_labela;
//
//   rect m_rectDesktop;
//
//   xlib_simple_message_box(::aura::application * papp) : ::object(papp), ::user::interaction(papp)
//   {
//   }
//
//
//   void _001OnDraw(::draw2d::graphics *  pdc)
//   {
//      rect rect;
//
//      GetClientRect(rect);
//
//      pdc->FillSolidRect(rect, ARGB(255, 240, 240, 240));
//   }
//
//   int32_t show_window(const char * lpText, const char * lpCaption)
//   {
//
//      ::GetWindowRect(::GetDesktopWindow(), &m_rectDesktop);
//
//
//      rect rect(100, 100, 200, 200);
//
//      if (!create_window(rect))
//         return 0;
//
//
//      draw2d::graphics_sp g(allocer());
//
//      g->CreateCompatibleDC(NULL);
//
//      ::draw2d::font_sp font(allocer());
//
//      font->create_point_font(FONT_SANS, 12.0);
//
//      g->selectFont(font);
//
//      stringa stra;
//
//      stra.add_tokens(lpText, "\n");
//
//      bool_array baTab;
//
//      int_array ya;
//
//      size sz;
//
//      sz.cx = 0;
//      sz.cy = 0;
//
//      for (index i = 0; i < stra.get_count(); i++)
//      {
//
//         string str = stra[i];
//
//         bool bTab = str_begins_dup(str, "\t");
//
//         str.trim();
//
//         bool bEmpty = str.is_empty();
//
//         if (bEmpty)
//            str = "L";
//
//         SIZE sizeItem = g->GetTextExtent(str);
//
//         int x = bTab ? 25 : 0;
//
//         if (sizeItem.cx + x > sz.cx)
//         {
//
//            sz.cx = sizeItem.cx + x;
//
//         }
//
//         baTab.add(bTab);
//
//         ya.add(sz.cy);
//
//         sz.cy += sizeItem.cy;
//
//         if (bEmpty)
//         {
//            stra[i] = "";
//         }
//         else
//         {
//            stra[i] = str;
//         }
//
//      }
//
//      for (index i = 0; i < stra.get_count(); i++)
//      {
//
//         m_labela.add(canew(::simple_ui::label(get_app())));
//
//         ::simple_ui::label & label = *m_labela.last();
//
//         label.set_parent(this);
//
//         label.m_strText = stra[i];
//
//         label.m_bVisible = true;
//
//         label.m_rect.left = 10;
//         label.m_rect.top = 10 + (sz.cy / stra.get_count()) * i;
//         label.m_rect.right = label.m_rect.left + sz.cx - 20;
//         label.m_rect.bottom = label.m_rect.top + (sz.cy / stra.get_count());
//
//      }
//
//      sz.cx += 20;
//      sz.cy += 20;
//
//      rect.left = m_rectDesktop.left + ((m_rectDesktop.width() - sz.cx) / 2);
//      rect.top = m_rectDesktop.top + ((m_rectDesktop.height() - sz.cy) / 4);
//      rect.right = rect.left + sz.cx;
//      rect.bottom = rect.top + sz.cy;
//
//
//      if (!prepare_window(rect))
//         return 0;
//
//
//
//      SetWindowPos(m_window, NULL, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
//
//      run_loop();
//
//      return 0;
//
//   }
//
//};
//
//int32_t message_box_show_xlib(::aura::application * papp, const char * lpText, const char * lpCaption)
//{
//
//   xlib_simple_message_box box(papp);
//
//   return box.show_window(lpText, lpCaption);
//
//
//}
//
//
//
//int32_t WINAPI MessageBoxA_x11(oswindow hWnd, const char * lpText, const char * lpCaption, UINT uType)
//{
//
//   ::aura::application * papp = NULL;
//
//   if (hWnd == NULL || hWnd->get_user_interaction() == NULL || hWnd->get_user_interaction()->get_app() == NULL)
//   {
//
//      papp = get_thread_app();
//
//   }
//   else
//   {
//
//      papp = hWnd->get_user_interaction()->get_app();
//
//   }
//
//   return message_box_show_xlib(get_thread_app(), lpText, lpCaption);
//
//}
//
//
//

/*

void message_box_show_dib_data(COLORREF * pcolorref, const RECT & rect, const char * lpText, const char * lpCaption)
{

Window rootwin;
Window win;
int32_t scr;
cairo_surface_t *cs;


::draw2d::graphics_sp g(get_a)

g.create(NULL);

SIZE sz;

sz.cx = 0;
sz.cy = 0;


stringa stra;

stra.add_tokens(lpText, "\n");

array < bool > baTab;

array < int > ya;

for(index i = 0; i < stra.get_count(); i++)
{

string str = stra[i];

bool bTab = str_begins_dup(str, "\t");

str.trim();

bool bEmpty = str.is_empty();

if(bEmpty)
str = "L";

SIZE sizeItem = g.get_text_extent(str);

int x = bTab ? 25 : 0;

if(sizeItem.cx + x > sz.cx)
{

sz.cx = sizeItem.cx + x;

}

baTab.add(bTab);

ya.add( sz.cy);

sz.cy += sizeItem.cy;

if(bEmpty)
{
stra[i] = "";
}
else
{
stra[i] = str;
}

}

sz.cx += 100;
sz.cy += 100;


cs = cairo_image_surface_create_for_data((unsigned char *) pcolorref, CAIRO_FORMAT_ARGB32, sz.cx, sz.cy, sz.cx * sizeof(COLORREF));

//	while(1) {
//XNextEvent(dpy, &e);
//	if(e.type==Expose && e.xexpose.count<1) {
message_box_paint(cs, stra, baTab, ya, &sz);
//} else if(e.type==ButtonPress) break;
//}

if(cs == ::ca_cairo_keep::g_cairosurface)
{

printf("123");

}

cairo_surface_destroy(cs);

//XCloseDisplay(dpy);

}

*/


/*

int32_t WINAPI MessageBoxA(oswindow hWnd, const char * lpText, const char * lpCaption, UINT uType)
{

message_box_show_dib_data(hWnd->m_pcolorref, &hWnd->m_rect, lpText, lpCaption);

return 0;

}

*/

static oswindow g_oswindowCapture;
static oswindow g_oswindowFocus;
static oswindow g_oswindowActive;


oswindow GetCapture()
{

   return g_oswindowCapture;

}

oswindow SetCapture(oswindow interaction_impl)
{


   g_oswindowCapture = interaction_impl;


}


int_bool ReleaseCapture()
{

   g_oswindowCapture = NULL;

}


oswindow SetFocus(oswindow interaction_impl)
{

   g_oswindowFocus = interaction_impl;

   return g_oswindowFocus;

}

oswindow GetFocus()
{

   return g_oswindowFocus;

}


int_bool GetClientRect(oswindow_data * pdata, RECT * prect)
{

	*prect = pdata->m_rect;

	prect->right -= prect->left;
	prect->bottom -= prect->top;
	prect->left = 0;
	prect->top = 0;

	return TRUE;

}


int_bool GetWindowRect(oswindow_data * pdata, RECT * prect)
{

	*prect = pdata->m_rect;

	return TRUE;

}


bool ShowWindow(oswindow_data * pdata, int nCmdShow)
{

	return pdata->ShowWindow(nCmdShow);

}


int_bool SetWindowPos(oswindow_data * pdata, oswindow_data * pdataAfter, int x, int y, int cx, int cy, unsigned int uiFlags)
{

	if (uiFlags & SWP_NOMOVE)
	{
		if (uiFlags & SWP_NOSIZE)
		{
		}
		else
		{
			pdata->m_rect.right = pdata->m_rect.left + cx;
			pdata->m_rect.bottom = pdata->m_rect.top + cy;
		}
	}
	else
	{
		if (uiFlags & SWP_NOSIZE)
		{
			int offsetX = pdata->m_rect.left - x;
			int offsetY = pdata->m_rect.top - y;
			pdata->m_rect.left += offsetX;
			pdata->m_rect.top += offsetY;
			pdata->m_rect.right += offsetX;
			pdata->m_rect.bottom += offsetY;
		}
		else
		{
			pdata->m_rect.left = x;
			pdata->m_rect.top = y;
			pdata->m_rect.right = x + cx;
			pdata->m_rect.bottom = y + cy;

		}

	}

	return TRUE;

}

oswindow_data * GetParent(oswindow_data * pdata)
{

	if (pdata == NULL)
		return NULL;

	if (!IsWindow(pdata))
		return NULL;

	return pdata->GetParent();


}

int_bool IsAscendant(oswindow_data * pdata, oswindow_data * pdataAscendant)
{

	if (pdata == NULL)
		return FALSE;

	oswindow_data * pdataParent = pdata->GetParent();

	if (pdataAscendant == NULL)
	{
		if (pdataParent == NULL)
			return TRUE;
		else
			return FALSE;
	}

	while (pdataParent != NULL)
	{

		if (pdataParent == pdataAscendant)
			return TRUE;

		pdataParent = pdataParent->GetParent();
	}

	return FALSE;

}


oswindow GetActiveWindow()
{

	return GetFocus();

}


oswindow SetActiveWindow(oswindow interaction_impl)
{

	return SetFocus(interaction_impl);

}


oswindow GetWindow(oswindow windowParam, int iParentHood)
{

	synch_lock sl(windowParam == NULL ? NULL : (windowParam->m_pui == NULL ? NULL : windowParam->m_pui->m_pmutex));




	oswindow interaction_impl = windowParam;

	if (interaction_impl == NULL)
		return NULL;

	/*

	xdisplay d(interaction_impl->display());

	if(iParentHood == GW_HWNDFIRST
	|| iParentHood == GW_HWNDLAST
	|| iParentHood == GW_HWNDNEXT
	|| iParentHood == GW_HWNDPREV)
	{

	interaction_impl = ::GetParent(interaction_impl);

	if(interaction_impl == NULL)
	return NULL;

	}


	Window root = 0;
	Window parent = 0;
	Window * pchildren = NULL;
	uint32_t ncount = 0;

	XQueryTree(interaction_impl->display(), interaction_impl->interaction_impl(), &root, &parent, &pchildren, &ncount);

	switch(iParentHood)
	{
	case GW_CHILD:
	case GW_HWNDFIRST:
	{

	if(pchildren == NULL)
	return NULL;

	interaction_impl = ::oswindow_get(interaction_impl->display(), pchildren[0]);

	}
	break;
	case GW_HWNDLAST:
	{

	if(pchildren == NULL)
	return NULL;

	interaction_impl = ::oswindow_get(interaction_impl->display(), pchildren[ncount - 1]);

	}
	break;
	case GW_HWNDNEXT:
	case GW_HWNDPREV:
	{

	if(pchildren == NULL) // ????
	return NULL;

	int iFound = -1;

	for(int i = 0; i < ncount; i++)
	{
	if(pchildren[i] == windowParam->interaction_impl())
	{
	iFound = i;
	break;
	}
	}

	if(iFound < 0)
	return NULL;

	if(iParentHood == GW_HWNDNEXT)
	{

	if(iFound + 1 >= ncount)
	return NULL;

	interaction_impl = ::oswindow_get(interaction_impl->display(), pchildren[iFound - 1]);

	}
	else
	{

	if(iFound - 1 < 0)
	return NULL;

	interaction_impl = ::oswindow_get(interaction_impl->display(), pchildren[iFound - 1]);

	}

	}

	}


	if(pchildren != NULL)
	XFree(pchildren);


	return interaction_impl;
	*/

	return NULL;

}



int_bool DestroyWindow(oswindow interaction_impl)
{

   synch_lock sl(interaction_impl == NULL ? NULL : (interaction_impl->m_pui == NULL ? NULL : interaction_impl->m_pui->m_pmutex));

	if (!IsWindow(interaction_impl))
		return FALSE;

	/*
	Display * pdisplay = interaction_impl->display();

	Window win = interaction_impl->interaction_impl();

	xdisplay d(pdisplay);


	oswindow_data * pdata = (oswindow_data *) (void *) interaction_impl;

	pdata->m_bDestroying = true;

	bool bIs = IsWindow(interaction_impl);

	XDestroyWindow(pdisplay, win);

	return true;

	*/


	return FALSE;

}


bool oswindow_data::is_destroying()
{

	if (this == NULL)
		return true;

	if (m_bDestroying)
		return true;

	return false;

}


bool IsWindow(oswindow oswindow)
{
	return oswindow->get_user_interaction() != NULL && !oswindow->is_destroying();
}


oswindow g_oswindowDesktop;


bool c_xstart()
{

	/*
	Display * dpy = XOpenDisplay(NULL);

	g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));

	XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->interaction_impl(), StructureNotifyMask);


	return true;

	*/


	return false;

}



oswindow GetDesktopWindow()
{

	return g_oswindowDesktop;
}


POINT g_ptCursor;


int_bool SetCursorPos(LPPOINT lppt)
{
	g_ptCursor = *lppt;
	return TRUE;
}


int_bool GetCursorPos(LPPOINT lppt)
{
	*lppt = g_ptCursor;
	return TRUE;
}







//bool IsWindow(oswindow oswindow)
//{
//   return (oswindow->get_user_interaction() == NULL && oswindow->display() != NULL && oswindow->window() != None)
//      || (oswindow->get_user_interaction() != NULL && !oswindow->is_destroying());
//}





int32_t IsWindowVisible(oswindow window)
{

	if (!IsWindow(window))
		return false;

	return window->is_window_visible();

}



LONG GetWindowLongA(oswindow window, int nIndex)
{

	if (!IsWindow(window))
		return false;

	return window->get_window_long(nIndex);

}


LONG SetWindowLongA(oswindow window, int nIndex, LONG lValue)
{

	if (!IsWindow(window))
		return false;

	return window->set_window_long(nIndex, lValue);

}


oswindow SetParent(oswindow window, oswindow windowNewParent)
{

	if (!IsWindow(window) || !(windowNewParent == NULL || ::IsWindow(windowNewParent)))
		return NULL;

	return window->SetParent(windowNewParent);

}



int32_t IsIconic(oswindow window)
{

	if (!IsWindow(window))
		return false;

	return window->is_iconic();

}


::user::interaction * window_from_handle(oswindow oswindow)
{

	if (oswindow == NULL)
		return NULL;

	return oswindow->m_pui;

}



bool IsChild(oswindow windowParent, oswindow oswindowCandidateChildOrDescendant)
{

	if (!IsWindow(windowParent) || !IsWindow(oswindowCandidateChildOrDescendant))
		return false;


	return windowParent->is_child(oswindowCandidateChildOrDescendant);


}

void on_post_nc_destroy(oswindow window)
{

	window->post_nc_destroy();

}


bool is_message_only_window(oswindow window)
{

	return window->m_bMessageOnlyWindow;

}


int translate_android_key_message(::message::key * pkey, int keyCode, int iUni);



extern "C"
void android_mouse(unsigned int message, float x, float y)
{

   if (::aura::system::g_p == NULL)
      return;

   if (::aura::system::g_p->m_pbasesystem == NULL)
      return;

   if (::aura::system::g_p->m_pbasesystem->m_posdata == NULL)
      return;

   if (::aura::system::g_p->m_pbasesystem->m_posdata->m_pui == NULL)
      return;

   MESSAGE msg;

   msg.hwnd = ::aura::system::g_p->m_pbasesystem->m_posdata->m_pui->get_handle();

   msg.message = message;

   msg.wParam = 0;

   msg.lParam = MAKELPARAM((long)x, (long)y);

   msg.pt.x = (long)x;

   msg.pt.y = (long)y;

   ::aura::system::g_p->m_pbasesystem->m_posdata->m_pui->message_handler(&msg);


}


extern "C"
void android_l_button_down(float x, float y)
{

   android_mouse(WM_LBUTTONDOWN, x, y);

}





extern "C"
void android_mouse_move(float x, float y)
{

   android_mouse(WM_MOUSEMOVE, x, y);

}





extern "C"
void android_l_button_up(float x, float y)
{

   android_mouse(WM_LBUTTONUP, x, y);

}



extern "C"
void android_key(unsigned int message, int keyCode, int iUni)
{

   if (::aura::system::g_p == NULL)
      return;

   if (::aura::system::g_p->m_pbasesystem == NULL)
      return;

   if (::aura::system::g_p->m_pbasesystem->m_posdata == NULL)
      return;

   if (::aura::system::g_p->m_pbasesystem->m_posdata->m_pui == NULL)
      return;

   sp(::message::key) pkey = canew(::message::key(get_thread_app()));

   pkey->m_uiMessage = message;

   if (!translate_android_key_message(pkey, keyCode, iUni))
   {

      return;

   }

   ::aura::system::g_p->m_pbasesystem->m_posdata->m_pui->message_handler(pkey);


}


extern "C"
void android_key_down(int keyCode, int iUni)
{

   android_key(WM_KEYDOWN, keyCode, iUni);

}



extern "C"
void android_key_up(int keyCode, int iUni)
{

   android_key(WM_KEYUP, keyCode, iUni);

}




int translate_android_key_message(::message::key * pkey, int keyCode, int iUni)
{

   if (0x80000000 & iUni)
   {

      return 0;

   }
   bool bOk = true;
   switch (keyCode)
   {
   case 62:
      pkey->m_ekey = ::user::key_space;
      break;
   case 67:
      pkey->m_ekey = ::user::key_back;
      break;
   case 112:
      pkey->m_ekey = ::user::key_delete;
      break;
   case 59:
      pkey->m_ekey = ::user::key_lshift;
      break;
   case 60:
      pkey->m_ekey = ::user::key_rshift;
      break;
   default:
      bOk = false;
   }

   //if (keyCode >= 29 && keyCode <= 54)
   if(!bOk)
   {

      //pkey->m_ekey = (::user::e_key) ((int) ::user::key_a + keyCode - 29);
      pkey->m_ekey = ::user::key_refer_to_text_member;

      unichar32 u32sz[2];
      u32sz[0] = iUni;
      u32sz[1] = 0;

      pkey->m_strText = utf32_to_utf8(u32sz);

   }
   //else if (keyCode >= 7 && keyCode <= 16)
   //{

   //   pkey->m_ekey = (::user::e_key) ((int) ::user::key_0 + keyCode - 7);

   //   pkey->m_ekey = ::user::key_refer_to_text_member;

   //   pkey->m_strText = string((unichar)iUni);

   //}
   //else
   //{

   //}

   return 1;

}



extern "C"
void android_on_text(const wchar_t * pwch, size_t len)
{

   if(::aura::system::g_p == NULL)
      return;

   if(::aura::system::g_p->m_pbasesystem == NULL)
      return;

   if(::aura::system::g_p->m_pbasesystem->m_posdata == NULL)
      return;

   if(::aura::system::g_p->m_pbasesystem->m_posdata->m_pui == NULL)
      return;

   sp(::message::key) pkey = canew(::message::key(get_thread_app()));

   pkey->m_uiMessage = WM_KEYDOWN;

   pkey->m_ekey      = ::user::key_refer_to_text_member;

   pkey->m_strText   = string(pwch,len);

   ::aura::system::g_p->m_pbasesystem->m_posdata->m_pui->message_handler(pkey);


}
