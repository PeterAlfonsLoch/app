#include "framework.h"


simple_graphics::simple_graphics()
{

}


simple_graphics::~simple_graphics()
{


}



void fastblur(DWORD * pdata, int w, int h, int radius)
{
   if(radius < 1)
   {
      return;
   }
  int wm=w-1;
  int hm=h-1;
  int wh=w*h;
  int div=radius+radius+1;
  simple_int_array iaA;
  iaA.set_size(wh);
  int * a = iaA.get_data();
  simple_int_array iaR;
  iaR.set_size(wh);
  int * r = iaR.get_data();
  simple_int_array iaG;
  iaG.set_size(wh);
  int * g = iaG.get_data();
  simple_int_array iaB;
  iaB.set_size(wh);
  int * b = iaB.get_data();
  int asum, rsum,gsum,bsum,x,y,i,yp,yi,yw;
  int p;
  int p1;
  int p2;
  simple_int_array iaVmin;
  iaVmin.set_size(max(w,h));
  int * vmin = iaVmin.get_data();
  simple_int_array iaVmax;
  iaVmax.set_size(max(w,h));
  int * vmax = iaVmax.get_data();
  int * pix=(int *) pdata;
  simple_int_array iaDv;
  iaDv.set_size(256*div);
  int * dv = iaDv.get_data();
  for (i=0;i<iaDv.get_count();i++)
  {
      dv[i]= min(255, i/div);
  }

  yw=yi=0;

   for(x=0;x<w;x++)
   {
      vmin[x]=min(x+radius+1,wm);
      vmax[x]=max(x-radius,0);
   }

   for (y=0;y<h;y++)
   {
      asum=rsum=gsum=bsum=0;
      for(i=-radius;i<=radius;i++)
      {
         p=pix[yi+min(wm,max(i,0))];
         asum+=((p & 0xff000000)>>24);
         rsum+=((p & 0xff0000)>>16);
         gsum+=((p & 0x00ff00)>>8);
         bsum+=(p & 0x0000ff);
      }
      for(x=0;x<w;x++)
      {
         a[yi]=dv[asum];
         r[yi]=dv[rsum];
         g[yi]=dv[gsum];
         b[yi]=dv[bsum];

         p1=pix[yw+vmin[x]];
         p2=pix[yw+vmax[x]];

         asum+= ((p1 >> 24) & 0xff )-((p2 >> 24) & 0xff);
         rsum+= ((p1 & 0x00ff0000)-(p2 & 0x00ff0000))>>16;
         gsum+= ((p1 & 0x0000ff00)-(p2 & 0x0000ff00))>>8;
         bsum+= ((p1 & 0x000000ff)-(p2 & 0x000000ff));
         yi++;
      }
      yw+=w;
  }
   for (y=0;y<h;y++)
   {
      vmin[y] = min(y+radius+1,hm) * w;
      vmax[y] = max(y-radius,0) * w;
   }

   for (x=0;x<w;x++)
   {
      asum=rsum=gsum=bsum=0;
      yp=-radius*w;
      for(i=-radius;i<=radius;i++)
      {
         yi=max(0,yp)+x;
         rsum+=r[yi];
         gsum+=g[yi];
         bsum+=b[yi];
         asum+=a[yi];
         yp+=w;
      }
      yi=x;
      for (y=0;y<h;y++)
      {
         pix[yi]=(dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];

         p1=x+vmin[y];
         p2=x+vmax[y];

         rsum+=r[p1]-r[p2];
         gsum+=g[p1]-g[p2];
         bsum+=b[p1]-b[p2];
         asum+=a[p1]-a[p2];

      yi+=w;

      }

   }

}

//=============================================================================
//
// draw_round_rect()
//
// Purpose:     Draws a rounded rectangle with a solid pen
//
// Parameters:  pGraphics	- [in]	pointer to the Graphics device
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the brush
//				radius		- [in]  radius of the rounded corner
//				width		- [in]  width of the border
//
// Returns:     None
//
bool simple_graphics::draw_round_rect(const RECT & rect, simple_pen & pen, int radius)
{

   simple_path path;

   path.begin_figure(true, ::ca::fill_mode_winding);

   path.add_round_rect(rect, 2 * radius);

   path.end_figure(true);

   draw_path(path, pen);

   return true;

}


//=============================================================================
//
// draw_round_rect()
//
// Purpose:     Draws a rounded rectangle with a solid pen
//
// Parameters:  pGraphics	- [in]	pointer to the Graphics device
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the brush
//				radius		- [in]  radius of the rounded corner
//				width		- [in]  width of the border
//
// Returns:     None
//
bool simple_graphics::draw_round_rect(const RECT & rect, COLORREF cr, int radius, int width)
{

   RECT r = rect;

   int dia	= 2 * radius;

   simple_solid_pen pen(*this, cr);

   draw_round_rect(r, pen, radius);


   for(int i=1; i<width; i++)
   {
      dia++;

      // left stroke
      deflate_rect(r, 1, 0);

      draw_round_rect(r, pen, dia / 2);

      // up stroke
      deflate_rect(r, 0, 1);

      draw_round_rect(r, pen, dia / 2);

   }

   return true;

}


bool simple_graphics::draw_round_top_left(const RECT & rect, simple_pen & pen, int radius)
{

   simple_path path;

   path.begin_figure(false, ::ca::fill_mode_winding);

   path.add_round_top_left(rect, 2 * radius);

   path.end_figure(false);

   draw_path(path, pen);

   return true;

}


bool simple_graphics::draw_round_top_left(const RECT & rect, COLORREF cr, int radius, int width)
{

   RECT r = rect;

   int dia	= 2 * radius;

   simple_solid_pen pen(*this, cr);

   draw_round_top_left(r, pen, radius);


   for(int i=1; i<width; i++)
   {
      dia++;

      // left stroke
      deflate_rect(r, 1, 0);

      draw_round_top_left(r, pen, dia / 2);

      // up stroke
      deflate_rect(r, 0, 1);

      draw_round_top_left(r, pen, dia / 2);

   }

   return true;

}


bool simple_graphics::draw_round_bottom_right(const RECT & rect, simple_pen & pen, int radius)
{

   simple_path path;

   path.begin_figure(false, ::ca::fill_mode_winding);

   path.add_round_bottom_right(rect, 2 * radius);

   path.end_figure(false);

   draw_path(path, pen);

   return true;

}


bool simple_graphics::draw_round_bottom_right(const RECT & rect, COLORREF cr, int radius, int width)
{

   RECT r = rect;

   int dia	= 2 * radius;

   simple_solid_pen pen(*this, cr);

   draw_round_bottom_right(r, pen, radius);


   for(int i=1; i<width; i++)
   {

      dia++;

      // left stroke
      deflate_rect(r, 1, 0);

      draw_round_bottom_right(r, pen, dia / 2);

      // up stroke
      deflate_rect(r, 0, 1);

      draw_round_bottom_right(r, pen, dia / 2);

   }

   return true;

}

//=============================================================================
//
// fill_round_rect()
//
// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
//				first then fills in the rectangle.
//
// Parameters:  pGraphics	- [in]	pointer to the Graphics device
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the brush
//				radius		- [in]  radius of the rounded corner
//
// Returns:     None
//
bool simple_graphics::fill_round_rect(const RECT & r, COLORREF cr, int radius)
{

   simple_solid_brush br(*this, cr);

   return fill_round_rect(r, br, radius);

}

//=============================================================================
//
// fill_round_rect()
//
// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
//				first then fills in the rectangle.
//
// Parameters:  pGraphics	- [in]	pointer to the Graphics device
//				pBrush		- [in]  pointer to a Brush
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the border (needed in case the
//									brush is a type other than solid)
//				radius		- [in]  radius of the rounded corner
//
// Returns:     None
//
bool simple_graphics::fill_round_rect(const RECT & rect, simple_brush & br, int radius)
{

   simple_path path;

   path.begin_figure(true, ::ca::fill_mode_winding);

   path.add_round_rect(rect, 2 * radius);

   path.end_figure(true);

   fill_path(path, br);

   return true;

}

bool simple_graphics::round_rect(const RECT & r, int radius)
{

   bool bOk1 = fill_round_rect(r, m_brush, radius);

   bool bOk2 = draw_round_rect(r, m_pen, radius);

   return bOk1 && bOk2;

}





bool simple_graphics::fill_solid_rect(const RECT & rect, COLORREF clr)
{
   
   fill_solid_rect(&rect, clr);

   return true;
   
}
