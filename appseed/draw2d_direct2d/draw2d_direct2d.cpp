#include "framework.h"

#undef new
#ifdef METROWIN
#include <wrl/module.h>
#endif

#ifdef METROWIN
[Platform::MTAThread]
#endif
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::OutputDebugStringW(L"::core:: draw2d_direct2d.dll :: initializing!\n");
      


   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      ::OutputDebugStringW(L"::core:: draw2d_direct2d.dll :: terminating!\n");

   }

   return 1;   // ok

}




#ifdef METROWIN


//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#pragma warning( disable: 4073 )  // initializers put in library initialization area
#pragma init_seg( lib )

extern int __abi___threading_model;
__abi_Module* __abi_module = nullptr;

namespace Platform {
	namespace Details {

		class InProcModule :
			public Microsoft::WRL::Module<Microsoft::WRL::InProcDisableCaching, InProcModule>,
			public __abi_Module
		{
		public:
			InProcModule()
			{
				__abi_module = this;
			}

			virtual ~InProcModule()
			{
				__abi_module = nullptr;
			}

			virtual unsigned long __stdcall __abi_IncrementObjectCount()
			{
				return Module::IncrementObjectCount();
			}

			virtual unsigned long __stdcall __abi_DecrementObjectCount()
			{
				return Module::DecrementObjectCount();
			}
		};

		auto &module_ = InProcModule::Create();


		// Forward declarations from vccorlib DLL
		HRESULT InitializeData(int __threading_model);
		void UninitializeData(int __threading_model);

		//Initializaton forwarders
		void __cdecl Cleanup();

		// Initialize MoCOM data and clean up handlers
		int __cdecl Initialize()
		{
			//Global initialization
/*			HRESULT hr = InitializeData(__abi___threading_model);
			if (FAILED(hr))
			{
				Cleanup();
				return hr;
			}*/

			// Register cleaning handler
			atexit(Cleanup);
			return 0;
		}

		// Global clean up
		void __cdecl Cleanup()
		{
			UninitializeData(__abi___threading_model);
		}

	} } // namespace Platform::Details

//Put initialization data into the departament that we can return failure
#pragma section(".CRT$XIY",long,read)
extern "C" __declspec(allocate(".CRT$XIY")) void* __abi__initialize = Platform::Details::Initialize;

// All required libraries must be pulled in in init.cpp file because it always referenced
// The librairies should not be pulled in vccorlib.h unless it's vccorlib*.lib
#pragma comment(lib, "runtimeobject.lib")
#ifndef _CORESYS
#pragma comment(lib, "ole32.lib")
#endif


#endif






static mutex * s_pmutex = NULL;

mutex & draw2d_direct2_mutex()
{

   return *s_pmutex;

}


void init_draw2d_direct2_mutex(sp(::axis::application) papp)
{

   s_pmutex = new mutex(papp);

}




/************************************************************************
*
* File: CustomTextRenderer.cpp
*
* Description:
*
*
*  This file is part of the Microsoft Windows SDK Code Samples.
*
*  Copyright (C) Microsoft Corporation.  All rights reserved.
*
* This source code is intended only as a supplement to Microsoft
* Development Tools and/or on-line documentation.  See these other
* materials for detailed information regarding Microsoft code samples.
*
* THIS CODE AND INFORMATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
************************************************************************/

//#include "DWriteHelloWorld.h"

/******************************************************************
*                                                                 *
*  CustomTextRenderer::CustomTextRenderer                         *
*                                                                 *
*  The constructor stores the Direct2D factory, the render        *
*  target, and the outline and fill brushes used for drawing the  *
*  glyphs, underlines, and strikethroughs.                        *
*                                                                 *
******************************************************************/

CustomTextRenderer::CustomTextRenderer(
   ID2D1Factory* pD2DFactory,
   ID2D1RenderTarget* pRT,
   ID2D1Brush* pOutlineBrush,
   ID2D1Brush* pFillBrush
   )
   :
   cRefCount_(0),
   pD2DFactory_(pD2DFactory),
   pRT_(pRT),
   pOutlineBrush_(pOutlineBrush),
   pFillBrush_(pFillBrush)
{
   pD2DFactory_->AddRef();
//   pRT_->AddRef();
   if(pOutlineBrush_ != NULL)
   {
      pOutlineBrush_->AddRef();
   }
   if(pFillBrush_ != NULL)
   {
      pFillBrush_->AddRef();
   }
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::~CustomTextRenderer                        *
*                                                                 *
*  The destructor releases the member variables                   *
*                                                                 *
******************************************************************/

CustomTextRenderer::~CustomTextRenderer()
{
   if(pOutlineBrush_ != NULL)
   {
      pOutlineBrush_->Release();
   }
   if(pFillBrush_ != NULL)
   {
      pFillBrush_->Release();
   }
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawGlyphRun                               *
*                                                                 *
*  Gets GlyphRun outlines via IDWriteFontFace::GetGlyphRunOutline *
*  and then draws and fills them using Direct2D path geometries   *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawGlyphRun(
   __maybenull void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   DWRITE_MEASURING_MODE measuringMode,
   __in DWRITE_GLYPH_RUN const* glyphRun,
   __in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
   IUnknown* clientDrawingEffect
   )
{
   HRESULT hr = S_OK;


   Microsoft::WRL::ComPtr<ID2D1PathGeometry>        pPathGeometry;
   Microsoft::WRL::ComPtr<ID2D1GeometrySink>        pSink;


   // Create the path geometry.
   hr = GetD2D1Factory1()->CreatePathGeometry(
      &pPathGeometry
      );

   // Write to the path geometry using the geometry sink.
   if(SUCCEEDED(hr))
   {
      hr = pPathGeometry->Open(
         &pSink
         );
   }

   // Get the glyph run outline geometries back from DirectWrite and place them within the
   // geometry sink.
   if(SUCCEEDED(hr))
   {
      hr = glyphRun->fontFace->GetGlyphRunOutline(
         glyphRun->fontEmSize,
         glyphRun->glyphIndices,
         glyphRun->glyphAdvances,
         glyphRun->glyphOffsets,
         glyphRun->glyphCount,
         glyphRun->isSideways,
         glyphRun->bidiLevel % 2,
         pSink.Get()
         );
   }

   // Close the geometry sink
   if(SUCCEEDED(hr))
   {
      hr = pSink->Close();
   }

   // Initialize a matrix to translate the origin of the glyph run.
   D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
      1.0f,0.0f,
      0.0f,1.0f,
      baselineOriginX,baselineOriginY
      );

   // Create the transformed geometry
   ID2D1TransformedGeometry* pTransformedGeometry = NULL;
   if(SUCCEEDED(hr))
   {
      hr = pD2DFactory_->CreateTransformedGeometry(
         pPathGeometry.Get(),
         &matrix,
         &pTransformedGeometry
         );
   }

   // Draw the outline of the glyph run
   if(pOutlineBrush_ != NULL)
   {
      pRT_->DrawGeometry(
         pTransformedGeometry,
         pOutlineBrush_
         );
   }

   if(pFillBrush_ != NULL)
   {
      // Fill in the glyph run
      pRT_->FillGeometry(
         pTransformedGeometry,
         pFillBrush_
         );
   }
   pTransformedGeometry->Release();

   return hr;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawUnderline                              *
*                                                                 *
*  Draws underlines below the text using a Direct2D recatangle    *
*  geometry                                                       *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawUnderline(
   __maybenull void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   __in DWRITE_UNDERLINE const* underline,
   IUnknown* clientDrawingEffect
   )
{
   /*HRESULT hr;

   D2D1_RECT_F rect = D2D1::RectF(
      0,
      underline->offset,
      underline->width,
      underline->offset + underline->thickness
      );

   ID2D1RectangleGeometry* pRectangleGeometry = NULL;
   hr = pD2DFactory_->CreateRectangleGeometry(
      &rect,
      &pRectangleGeometry
      );

   // Initialize a matrix to translate the origin of the underline
   D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
      1.0f,0.0f,
      0.0f,1.0f,
      baselineOriginX,baselineOriginY
      );

   ID2D1TransformedGeometry* pTransformedGeometry = NULL;
   if(SUCCEEDED(hr))
   {
      hr = pD2DFactory_->CreateTransformedGeometry(
         pRectangleGeometry,
         &matrix,
         &pTransformedGeometry
         );
   }

   // Draw the outline of the rectangle
   pRT_->DrawGeometry(
      pTransformedGeometry,
      pOutlineBrush_
      );

   // Fill in the rectangle
   pRT_->FillGeometry(
      pTransformedGeometry,
      pFillBrush_
      );

      */
   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawStrikethrough                          *
*                                                                 *
*  Draws strikethroughs below the text using a Direct2D           *
*  recatangle geometry                                            *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawStrikethrough(
   __maybenull void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   __in DWRITE_STRIKETHROUGH const* strikethrough,
   IUnknown* clientDrawingEffect
   )
{
   /*HRESULT hr;

   D2D1_RECT_F rect = D2D1::RectF(
      0,
      strikethrough->offset,
      strikethrough->width,
      strikethrough->offset + strikethrough->thickness
      );

   ID2D1RectangleGeometry* pRectangleGeometry = NULL;
   hr = pD2DFactory_->CreateRectangleGeometry(
      &rect,
      &pRectangleGeometry
      );

   // Initialize a matrix to translate the origin of the strikethrough
   D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
      1.0f,0.0f,
      0.0f,1.0f,
      baselineOriginX,baselineOriginY
      );

   ID2D1TransformedGeometry* pTransformedGeometry = NULL;
   if(SUCCEEDED(hr))
   {
      hr = pD2DFactory_->CreateTransformedGeometry(
         pRectangleGeometry,
         &matrix,
         &pTransformedGeometry
         );
   }

   // Draw the outline of the rectangle
   pRT_->DrawGeometry(
      pTransformedGeometry,
      pOutlineBrush_
      );

   // Fill in the rectangle
   pRT_->FillGeometry(
      pTransformedGeometry,
      pFillBrush_
      );

   SafeRelease(&pRectangleGeometry);
   SafeRelease(&pTransformedGeometry);*/

   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawInlineObject                           *
*                                                                 *
*  This function is not implemented for the purposes of this      *
*  sample.                                                        *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawInlineObject(
   __maybenull void* clientDrawingContext,
   FLOAT originX,
   FLOAT originY,
   IDWriteInlineObject* inlineObject,
   BOOL isSideways,
   BOOL isRightToLeft,
   IUnknown* clientDrawingEffect
   )
{
   // Not implemented
   return E_NOTIMPL;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::AddRef                                     *
*                                                                 *
*  Increments the ref count                                       *
*                                                                 *
******************************************************************/

IFACEMETHODIMP_(unsigned long) CustomTextRenderer::AddRef()
{
   return InterlockedIncrement(&cRefCount_);
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::Release                                    *
*                                                                 *
*  Decrements the ref count and deletes the instance if the ref   *
*  count becomes 0                                                *
*                                                                 *
******************************************************************/

IFACEMETHODIMP_(unsigned long) CustomTextRenderer::Release()
{
   unsigned long newCount = InterlockedDecrement(&cRefCount_);
   if(newCount == 0)
   {
      delete this;
      return 0;
   }

   return newCount;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::IsPixelSnappingDisabled                    *
*                                                                 *
*  Determines whether pixel snapping is disabled. The recommended *
*  default is FALSE, unless doing animation that requires         *
*  subpixel vertical placement.                                   *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::IsPixelSnappingDisabled(
   __maybenull void* clientDrawingContext,
   __out BOOL* isDisabled
   )
{
   *isDisabled = FALSE;
   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::GetCurrentTransform                        *
*                                                                 *
*  Returns the current transform applied to the render target..   *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::GetCurrentTransform(
   __maybenull void* clientDrawingContext,
   __out DWRITE_MATRIX* transform
   )
{
   //forward the render target's transform
   pRT_->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(transform));
   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::GetPixelsPerDip                            *
*                                                                 *
*  This returns the number of pixels per DIP.                     *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::GetPixelsPerDip(
   __maybenull void* clientDrawingContext,
   __out FLOAT* pixelsPerDip
   )
{
   float x,yUnused;

   pRT_->GetDpi(&x,&yUnused);
   *pixelsPerDip = x / 96;

   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::QueryInterface                             *
*                                                                 *
*  Query interface implementation                                 *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::QueryInterface(
   IID const& riid,
   void** ppvObject
   )
{
   if(__uuidof(IDWriteTextRenderer) == riid)
   {
      *ppvObject = this;
   }
   else if(__uuidof(IDWritePixelSnapping) == riid)
   {
      *ppvObject = this;
   }
   else if(__uuidof(IUnknown) == riid)
   {
      *ppvObject = this;
   }
   else
   {
      *ppvObject = NULL;
      return E_FAIL;
   }

   this->AddRef();

   return S_OK;
}

