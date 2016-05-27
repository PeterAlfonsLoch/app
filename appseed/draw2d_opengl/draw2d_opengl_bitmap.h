#pragma once


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#ifdef LINUX
#include <GL/glx.h>
#endif

//-----------------------------------------------------------------------------
// Copyright (c) 2006-2010 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
//
// This demo builds on the previous layered window demo.
// (http://www.dhpoware.com/downloads/LayeredWindow.zip).
//
// In the previous demo, we used a TGA image with an embedded alpha mask as the
// source of our layered window.
//
// In this demo we use OpenGL to draw a rotating cube to a pbuffer. Once the
// scene is drawn to the pbuffer we then make a local system memory copy of
// the pbuffer's pixel data and use that as the source of our layered window.
//
// You can move the cube around the screen by holding down the left mouse
// button and dragging. To exit the demo press the ESC key.
//
// This demo requires Windows 2000, XP, or higher to run. The minimum supported
// operating system for the layered windows API is Windows 2000.
//
// This demo also requires the following OpenGL extensions:
//  WGL_ARB_pbuffer
//  WGL_ARB_pixel_format
//
//-----------------------------------------------------------------------------

// Force the layered windows APIs to be visible.
//#define _WIN32_WINNT 0x0500

// Disable warning C4244: conversion from 'float' to 'BYTE', possible loss of
// data. Used in the ImagePreMultAlpha() function.
#pragma warning (disable : 4244)

//#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

//-----------------------------------------------------------------------------
// WGL_ARB_pbuffer.
//-----------------------------------------------------------------------------

#define WGL_DRAW_TO_PBUFFER_ARB                   0x202D
#define WGL_MAX_PBUFFER_HEIGHT_ARB                0x2030
#define WGL_MAX_PBUFFER_PIXELS_ARB                0x202E
#define WGL_MAX_PBUFFER_WIDTH_ARB                 0x202F
#define WGL_PBUFFER_HEIGHT_ARB                    0x2035
#define WGL_PBUFFER_LARGEST_ARB                   0x2033
#define WGL_PBUFFER_LOST_ARB                      0x2036
#define WGL_PBUFFER_WIDTH_ARB                     0x2034

DECLARE_HANDLE(HPBUFFERARB);


//-----------------------------------------------------------------------------
// WGL_ARB_pixel_format.
//-----------------------------------------------------------------------------

#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_ACCUM_ALPHA_BITS_ARB                  0x2021
#define WGL_ACCUM_BITS_ARB                        0x201D
#define WGL_ACCUM_BLUE_BITS_ARB                   0x2020
#define WGL_ACCUM_GREEN_BITS_ARB                  0x201F
#define WGL_ACCUM_RED_BITS_ARB                    0x201E
#define WGL_ALPHA_BITS_ARB                        0x201B
#define WGL_ALPHA_SHIFT_ARB                       0x201C
#define WGL_AUX_BUFFERS_ARB                       0x2024
#define WGL_BLUE_BITS_ARB                         0x2019
#define WGL_BLUE_SHIFT_ARB                        0x201A
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_DRAW_TO_BITMAP_ARB                    0x2002
#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_FULL_ACCELERATION_ARB                 0x2027
#define WGL_GENERIC_ACCELERATION_ARB              0x2026
#define WGL_GREEN_BITS_ARB                        0x2017
#define WGL_GREEN_SHIFT_ARB                       0x2018
#define WGL_NEED_PALETTE_ARB                      0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB               0x2005
#define WGL_NO_ACCELERATION_ARB                   0x2025
#define WGL_NUMBER_OVERLAYS_ARB                   0x2008
#define WGL_NUMBER_PIXEL_FORMATS_ARB              0x2000
#define WGL_NUMBER_UNDERLAYS_ARB                  0x2009
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_RED_BITS_ARB                          0x2015
#define WGL_RED_SHIFT_ARB                         0x2016
#define WGL_SHARE_ACCUM_ARB                       0x200E
#define WGL_SHARE_DEPTH_ARB                       0x200C
#define WGL_SHARE_STENCIL_ARB                     0x200D
#define WGL_STENCIL_BITS_ARB                      0x2023
#define WGL_STEREO_ARB                            0x2012
#define WGL_SUPPORT_GDI_ARB                       0x200F
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_SWAP_COPY_ARB                         0x2029
#define WGL_SWAP_EXCHANGE_ARB                     0x2028
#define WGL_SWAP_LAYER_BUFFERS_ARB                0x2006
#define WGL_SWAP_METHOD_ARB                       0x2007
#define WGL_SWAP_UNDEFINED_ARB                    0x202A
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB           0x203A
#define WGL_TRANSPARENT_ARB                       0x200A
#define WGL_TRANSPARENT_BLUE_VALUE_ARB            0x2039
#define WGL_TRANSPARENT_GREEN_VALUE_ARB           0x2038
#define WGL_TRANSPARENT_INDEX_VALUE_ARB           0x203B
#define WGL_TRANSPARENT_RED_VALUE_ARB             0x2037
#define WGL_TYPE_COLORINDEX_ARB                   0x202C
#define WGL_TYPE_RGBA_ARB                         0x202B


//-----------------------------------------------------------------------------
// Globals.
//-----------------------------------------------------------------------------

#define TEXTURE_WIDTH   64
#define TEXTURE_HEIGHT  64

namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL bitmap : 
      virtual public ::draw2d::bitmap
   {
   public:


      bool                 m_bTexture;
      GLuint               m_texture;
      memory               m_memIn;
      memory               m_memOut;

      bool                 m_bFlashed;
      bool                 m_bPBuffer;
#ifdef WINDOWS

      HWND  g_hWnd;
      HDC   g_hDC;
      HGLRC g_hRC;
      HDC   g_hPBufferDC;
      HGLRC g_hPBufferRC;
      HPBUFFERARB g_hPBuffer;

#else
      Display *dpy;
      Window win;
      GLXContext PBufferCtx;
      GLXContext WinCtx;
      GLXPbuffer PBuffer;
      GLXFBConfig* fbc;
      XVisualInfo* vi = NULL;
      Colormap cmap;
      XSetWindowAttributes swa;
      XEvent event;
      Bool bRedraw = False;
      int dummy;
      int nElements;
      int nval;
      int nCounter;

#endif


      ::size               m_sizeOut;
      ::size               m_sizeIn;


      bitmap(::aura::application * papp);
      virtual ~bitmap();

      void destroy_bitmap();

      // Resample Quality
      // 0 - low
      // 1 - good
      // 2 - excelent
      void create_texture(int iResampleQuality);
      bool flash();
      void defer_reveal();

      bool Init();
      bool InitGL();
      bool InitGLExtensions();
      bool InitPBuffer();
      void Cleanup();

      

      void * get_os_data() const;


      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
   //#ifndef ___NO_AFXCMN_SUPPORT
   //   bool LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = NULL, int32_t nMapSize = 0);
   //#endif
      bool CreateBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits, int32_t stride);
      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      bool CreateDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, int * stride, HANDLE hSection, uint32_t offset);
      bool CreateDIBitmap(::draw2d::graphics * pgraphics, const BITMAPINFOHEADER *pbmih, uint32_t flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);


      int32_t GetBitmap(BITMAP* pBitMap);


      uint32_t SetBitmapBits(uint32_t dwCount, const void * lpBits);
      uint32_t GetBitmapBits(uint32_t dwCount, LPVOID lpBits) const;
      class size SetBitmapDimension(int32_t nWidth, int32_t nHeight);
      class size GetBitmapDimension() const;

      virtual void dump(dump_context & dumpcontext) const;


      virtual bool attach(void * posdata);
      virtual void * detach();

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_opengl



