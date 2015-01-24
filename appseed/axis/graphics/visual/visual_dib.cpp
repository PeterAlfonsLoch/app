//#include "framework.h"

#ifdef WINDOWS
#include <wincodec.h>
#endif


////#include "ft2build.h"


////#include FT_FREETYPE_H

bool windows_write_dib_to_file(::file::buffer_sp,::draw2d::dib * pdib,::visual::save_image * psaveimage,::aura::application * papp);
bool windows_load_dib_from_file(::draw2d::dib * pdib,::file::buffer_sp,::aura::application * papp);

namespace visual
{


   dib_sp::dib_sp()
   {
   }

   dib_sp::dib_sp(const ::aura::allocatorsp & allocer):
      ::draw2d::dib_sp(allocer)
   {
   }

   dib_sp::~dib_sp()
   {
   }



   bool dib_sp::load_from_file(var varFile,bool bCache)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_p,varFile,bCache,m_p->m_pauraapp);

   }


   bool dib_sp::load_from_matter(const char * pszMatter)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_p,m_p->m_pauraapp->m_paxisapp->dir().matter(pszMatter),true,m_p->m_pauraapp);

   }


   bool dib_sp::read_from_file(::file::buffer_sp spfile)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().read_from_file(m_p,spfile,m_p->m_pauraapp);

   }


   bool dib_sp::save_to_file(var varFile,save_image * psaveimage)
   {
      ::file::buffer_sp spfile;
      spfile = Sess(m_p->m_pauraapp).file().get_file(varFile,::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      return write_to_file(spfile,psaveimage);
   }

   bool dib_sp::write_to_file(::file::buffer_sp pfile,save_image * psaveimage)
   {
      save_image saveimageDefault;
      if(psaveimage == NULL)
         psaveimage = &saveimageDefault;
#ifdef WINDOWSEX

      return windows_write_dib_to_file(pfile,m_p,psaveimage,m_p->get_app());

#elif METROWIN

      throw todo(m_p->m_pauraapp);

#else

      bool bOk = false;

      bool b8 = false;
      bool b24 = false;
      int iFreeImageSave = 0;
      FREE_IMAGE_FORMAT eformat = (FREE_IMAGE_FORMAT) 0;
      string strFile;
      switch(psaveimage->m_eformat)
      {
      case ::visual::image::format_png:
         eformat = FIF_PNG;
         strFile = "foo.png";
         break;
      case ::visual::image::format_bmp:
         eformat = FIF_BMP;
         strFile= "foo.bmp";
         break;
      case ::visual::image::format_gif:
         b8 = true;
         eformat = FIF_GIF;
         strFile = "foo.gif";
         break;
      case ::visual::image::format_jpeg:
         b24 = true;
         eformat = FIF_JPEG;
         strFile = "foo.jpg";
         if(psaveimage->m_iQuality > 80)
         {
            iFreeImageSave |= JPEG_QUALITYSUPERB;
         }
         else if(psaveimage->m_iQuality > 67)
         {
            iFreeImageSave |= JPEG_QUALITYGOOD;
         }
         else if(psaveimage->m_iQuality > 33)
         {
            iFreeImageSave |= JPEG_QUALITYNORMAL;
         }
         else if(psaveimage->m_iQuality > 15)
         {
            iFreeImageSave |= JPEG_QUALITYAVERAGE;
         }
         else
         {
            iFreeImageSave |= JPEG_QUALITYBAD;
         }
         break;
      default:
         return false;
      }

      eformat = FreeImage_GetFIFFromFilename(strFile);


      FIMEMORY * pfm1 = FreeImage_OpenMemory();
      FIBITMAP * pfi7 = Sys(m_p->m_pauraapp).visual().imaging().HBITMAPtoFI(m_p->get_bitmap());
      FIBITMAP * pfi8 = NULL;
      bool bConv;
      if(b8)
      {
         pfi8 = FreeImage_ConvertTo8Bits(pfi7);
         bConv = true;
      }
      else if(b24)
      {
         pfi8 = FreeImage_ConvertTo24Bits(pfi7);
         bConv = true;
      }
      else
      {
         //FreeImage_SetTransparent(pfi8,true);
         pfi8 = pfi7;
         bConv = false;
      }

      bOk = FreeImage_SaveToMemory(eformat,pfi8,pfm1,iFreeImageSave) != FALSE;

      BYTE * pbData = NULL;
      DWORD dwSize = 0;
      if(bOk)
         bOk = FreeImage_AcquireMemory(pfm1,&pbData,&dwSize) != FALSE;
      if(bOk)
      {
         try
         {
            pfile->write(pbData,dwSize);
         }
         catch(...)
         {
            bOk = false;
         }
      }

      FreeImage_CloseMemory(pfm1);
      if(bConv)
      {
         FreeImage_Unload(pfi8);
      }
      FreeImage_Unload(pfi7);



      return bOk != FALSE;

#endif

   }




   save_image::save_image()
   {
      m_eformat = ::visual::image::format_png;
      m_iQuality = 100;
   }


#ifndef  WINDOWSEX

   bool dib_sp::from(class draw2d::graphics * pgraphics,struct FIBITMAP * pfi,bool bUnload)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().from(m_p,pgraphics,pfi,bUnload);

   }

#endif


} // namespace visual


#if 0


CLASS_DECL_AXIS void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int xParam,int yParam)
{

   FT_Bitmap * bitmap = (FT_Bitmap *) pftbitmap;
   FT_Int x = (FT_Int) xParam;
   FT_Int y = (FT_Int) yParam;

   FT_Int  i,j,p,q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for(i = x,p = 0; i < x_max; i++,p++)
   {
      for(j = y,q = 0; j < y_max; j++,q++)
      {
         if(i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a,0,0,0);

      }
   }

}


CLASS_DECL_AXIS void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int xParam,int yParam,byte aParam,byte r,byte g,byte b)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i,j,p,q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for(i = x,p = 0; i < x_max; i++,p++)
   {
      for(j = y,q = 0; j < y_max; j++,q++)
      {
         if(i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         if(a > 0)
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a * aParam / 255,r,g,b);

         }
         else
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;

         }

      }
   }

}

#endif



#ifdef WINDOWS

bool windows_load_dib_from_file(::draw2d::dib * pdib,::file::buffer_sp pfile,::aura::application * papp)
{
   int iSize = pfile->get_length();

   primitive::memory mem(papp);

   mem.allocate(iSize);

   pfile->read(mem.get_data(),iSize);
   try
   {

      comptr<IStream> pstream = mem.CreateIStream();
      comptr < IWICImagingFactory > piFactory = NULL;

      comptr< IWICBitmapDecoder > decoder;
      HRESULT hr = CoCreateInstance(
         CLSID_WICImagingFactory,
         NULL,
         CLSCTX_INPROC_SERVER,
         IID_IWICImagingFactory,
         (LPVOID*)&piFactory);

      if(SUCCEEDED(hr))
      {

         hr = piFactory->CreateDecoderFromStream(pstream,NULL,WICDecodeMetadataCacheOnDemand,&decoder.get());
      }

      //if(SUCCEEDED(hr))
      //{

      //   hr = decoder->Initialize(pstream,WICDecodeMetadataCacheOnDemand);

      //}

      comptr< IWICBitmapFrameDecode> pframe;

      if(SUCCEEDED(hr))
      {

         hr = decoder->GetFrame(0,&pframe.get());

      }

  //    int color_type,palette_entries = 0;
      //int palette_entries = 0;
//      int bit_depth,pixel_depth;		// pixel_depth = bit_depth * channels

      WICPixelFormatGUID px;
      ZERO(px);
      if(pframe == NULL)
      {
         throw simple_exception(papp,"CreateDecoderFromStream failure");
      }
                  {
                     hr =   pframe->GetPixelFormat(&px);

                  }
                  //if(SUCCEEDED(hr))
                  //{

                  //   if(!wic_info(&px,&color_type,&pixel_depth,&bit_depth))
                  //   {
                  //      color_type = PNG_COLOR_TYPE_RGB_ALPHA;
                  //      pixel_depth = 32;
                  //      bit_depth = 8;
                  //   }

                  //}
                  //else
                  //{
                  //   color_type = PNG_COLOR_TYPE_RGB_ALPHA;
                  //   pixel_depth = 32;
                  //   bit_depth = 8;
                  //}

                  if(px == GUID_WICPixelFormat32bppBGRA)
                  {
                     UINT width=0;
                     UINT height=0;

                     pframe->GetSize(&width,&height);
                     pdib->create(width,height);
                     hr = pframe->CopyPixels(NULL,pdib->m_iScan,pdib->m_iScan * height,(BYTE *)pdib->m_pcolorref);

                  }
                  else
                  {

                     comptr<IWICFormatConverter> pbitmap;

                     if(SUCCEEDED(hr))
                     {

                        hr = piFactory->CreateFormatConverter(&pbitmap.get());

                     }



                     px  = GUID_WICPixelFormat32bppBGRA;

                     if(SUCCEEDED(hr))
                     {

                        hr = pbitmap->Initialize(pframe,px,WICBitmapDitherTypeNone,NULL,0.f,WICBitmapPaletteTypeCustom);
                     }

                     //Step 4: Create render target and D2D bitmap from IWICBitmapSource
                     UINT width=0;
                     UINT height=0;
                     if(SUCCEEDED(hr))
                     {
                        hr = pbitmap->GetSize(&width,&height);
                     }

                     pdib->create(width,height);

                     hr = pbitmap->CopyPixels(NULL,pdib->m_iScan,pdib->m_iScan * height,(BYTE *)pdib->m_pcolorref);

                     //for(int k = 0; k < height; k++)
                     //{
                     //   memcpy(&pb[k * iStride],&mem.get_data()[(height - 1 - k) * iStride],iStride);
                     //}

                  }


//               end:;


                  //synch_lock sl(&m_parea->m_mutex);
                  //m_parea->m_iArea++;

   }
   catch(...)
   {
      return false;
   }
   //DWORD dw2 =::get_tick_count();
   //TRACE("InPath %d ms\n",dw2 - dw1);
   //dwLast = dw2;

   //memfile.Truncate(0);

   //}
   return true;

}


bool windows_write_dib_to_file(::file::buffer_sp pfile,::draw2d::dib * pdib,::visual::save_image * psaveimage,::aura::application * papp)
{

   comptr < IStream > pstream = SHCreateMemStream(NULL,NULL);

   //m_spmemfile->Truncate(0);

   //m_spmemfile->seek_to_begin();

   comptr < IWICImagingFactory > piFactory = NULL;
   comptr < IWICBitmapEncoder > piEncoder = NULL;
   comptr < IWICBitmapFrameEncode > piBitmapFrame = NULL;
   comptr < IPropertyBag2 > pPropertybag = NULL;

   comptr < IWICStream > piStream = NULL;
   UINT uiWidth = pdib->m_size.cx;
   UINT uiHeight = pdib->m_size.cy;

   HRESULT hr = CoCreateInstance(
      CLSID_WICImagingFactory,
      NULL,
      CLSCTX_INPROC_SERVER,
      IID_IWICImagingFactory,
      (LPVOID*)&piFactory);

   if(SUCCEEDED(hr))
   {
      hr = piFactory->CreateStream(&piStream.get());
   }

   if(SUCCEEDED(hr))
   {
      hr = piStream->InitializeFromIStream(pstream);
   }

   if(SUCCEEDED(hr))
   {
      switch(psaveimage->m_eformat)
      {
      case ::visual::image::format_bmp:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatBmp,NULL,&piEncoder.get());
         break;
      case ::visual::image::format_gif:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatGif,NULL,&piEncoder.get());
         break;
      case ::visual::image::format_jpeg:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatJpeg,NULL,&piEncoder.get());
         break;
      case ::visual::image::format_png:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatPng,NULL,&piEncoder.get());
         break;
      default:
         break;
      }
   }

   if(SUCCEEDED(hr))
   {
      hr = piEncoder->Initialize(piStream,WICBitmapEncoderNoCache);
   }

   if(SUCCEEDED(hr))
   {
      hr = piEncoder->CreateNewFrame(&piBitmapFrame.get(),&pPropertybag.get());
   }

   if(SUCCEEDED(hr))
   {
      //if(m_bJxr)
      //{
      //   //PROPBAG2 option ={0};
      //   //option.pstrName = L"ImageQuality";
      //   //VARIANT varValue;
      //   //VariantInit(&varValue);
      //   //varValue.vt = VT_R4;
      //   //varValue.fltVal = 0.49f;
      //   PROPBAG2 option ={0};
      //   option.pstrName = L"UseCodecOptions";
      //   VARIANT varValue;
      //   VariantInit(&varValue);
      //   varValue.vt = VT_BOOL;
      //   varValue.boolVal = -1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Quality";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 184;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Subsampling";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Overlap";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 2;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"StreamOnly";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_BOOL;
      //   varValue.boolVal = -1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //}
      if(psaveimage->m_eformat == ::visual::image::format_jpeg)
      {
         PROPBAG2 option ={0};
         option.pstrName = L"ImageQuality";
         VARIANT varValue;
         VariantInit(&varValue);
         varValue.vt = VT_R4;
         varValue.fltVal = MAX(0.f,MIN(1.f,psaveimage->m_iQuality / 100.0f));
         if(SUCCEEDED(hr))
         {
            hr = pPropertybag->Write(1,&option,&varValue);
         }
      }
      if(SUCCEEDED(hr))
      {
         hr = piBitmapFrame->Initialize(pPropertybag);
      }
   }

   if(SUCCEEDED(hr))
   {
      hr = piBitmapFrame->SetSize(uiWidth,uiHeight);
   }

   WICPixelFormatGUID formatGUID = GUID_WICPixelFormat32bppBGRA;
   if(SUCCEEDED(hr))
   {
      hr = piBitmapFrame->SetPixelFormat(&formatGUID);
   }

   if(SUCCEEDED(hr))
   {
      if(IsEqualGUID(formatGUID,GUID_WICPixelFormat32bppBGRA))
      {
         if(SUCCEEDED(hr))
         {
            hr = piBitmapFrame->WritePixels(uiHeight,uiWidth * sizeof(COLORREF),uiHeight*uiWidth * sizeof(COLORREF),(BYTE *)pdib->m_pcolorref);
         }
      }
      else
      {

         comptr <IWICBitmap> pbitmap;

         if(SUCCEEDED(hr))
         {
            hr=piFactory->CreateBitmapFromMemory(
               pdib->m_size.cx,
               pdib->m_size.cy,
               GUID_WICPixelFormat32bppBGRA,
               pdib->m_iScan,
               pdib->m_iScan * pdib->m_size.cy,
               (BYTE *)pdib->m_pcolorref,
               &pbitmap.get()
               );
         }

         comptr<IWICFormatConverter> pconverter;

         if(SUCCEEDED(hr))
         {

            hr = piFactory->CreateFormatConverter(&pconverter.get());

         }



         if(SUCCEEDED(hr))
         {

            hr = pconverter->Initialize(pbitmap,formatGUID,WICBitmapDitherTypeNone,NULL,0.f,WICBitmapPaletteTypeCustom);
         }

         //Step 4: Create render target and D2D bitmap from IWICBitmapSource
         //UINT width=0;
         //UINT height=0;
         //if(SUCCEEDED(hr))
         //{
         //   hr = pbitmap->GetSize(&width,&height);
         //}

         //pdib->create(width,height);

         if(SUCCEEDED(hr))
         {
            hr = piBitmapFrame->WriteSource(pconverter,NULL);
         }


         //for(int k = 0; k < height; k++)
         //{
         //   memcpy(&pb[k * iStride],&mem.get_data()[(height - 1 - k) * iStride],iStride);
         //}

      }
   }



   if(SUCCEEDED(hr))
   {
      hr = piBitmapFrame->Commit();
   }

   if(SUCCEEDED(hr))
   {
      hr = piEncoder->Commit();
   }

   //if(piFactory)
   //   piFactory->Release();

   //if(piBitmapFrame)
   //   piBitmapFrame->Release();

   //if(piEncoder)
   //   piEncoder->Release();

   //if(piStream)
   //   piStream->Release();



   STATSTG stg;
   ZERO(stg);
   pstream->Stat(&stg,STATFLAG_NONAME);
   LARGE_INTEGER l;
   l.QuadPart = 0;
   pstream->Seek(l,STREAM_SEEK_SET,NULL);


   primitive::memory mem(papp);

   mem.allocate(1024 * 1024);

   ULONG ulPos = 0;
   ULONG ulRead;
   ULONG ul;
   do
   {

      ulRead = 0;

      ul = stg.cbSize.QuadPart - ulPos;

      pstream->Read(mem.get_data(),MIN(ul,mem.get_size()),&ulRead);

      if(ulRead > 0)
      {

         pfile->write(mem.get_data(),ulRead);

         ulPos+=ulRead;

      }

   } while(ulRead > 0 && stg.cbSize.QuadPart - ulPos > 0);

   //pstream->Release();

   return true;

}

#endif