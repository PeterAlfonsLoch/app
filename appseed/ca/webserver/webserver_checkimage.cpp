#include "StdAfx.h"


namespace webserver
{

void checkimage::generate_new_image()
{
   string strCode = generate_code();
   register_code(strCode);
   output_image(strCode);
}

void checkimage::output_image(const char * pszCode)
{
   string strText = pszCode;
   outheader("Cache-control") = "max-age=1, no-store, no-cache, must-revalidate";
   outheader("Content-type") = "image/png";
   int w = 84 + 77;
   int h = 84;
   ::ca::dib_sp spdib(get_app());
   spdib->create(w, h);
//   int maxy = h - 1;
//   int maxx = w - 1;

   
   array_app_alloc < ::ca::font_sp, ::ca::font_sp & > fonta(get_app());
   fonta.set_size(5);
   LOGFONT lf;
   memset(&lf, 0, sizeof(lf));

   int iMul = 5;
   int iDiv = 3;

   strcpy(lf.lfFaceName, "Times New Roman");
   lf.lfHeight = 17 * iMul / iDiv;
   fonta[0]->CreateFontIndirect(&lf);

   lf.lfHeight = 23 * iMul / iDiv;
   fonta[1]->CreateFontIndirect(&lf);
   
   strcpy(lf.lfFaceName, "Arial");
   lf.lfHeight = 11 * iMul / iDiv;
   fonta[2]->CreateFontIndirect(&lf);

   lf.lfHeight = 25 * iMul / iDiv;
   fonta[3]->CreateFontIndirect(&lf);

   strcpy(lf.lfFaceName, "Impact");
   lf.lfHeight = 33 * iMul / iDiv;
   fonta[4]->CreateFontIndirect(&lf);
   
   int x;
   spdib->get_graphics()->FillSolidRect(0, 0, w, h, RGB(0x22, 0x22, 0x22));
   /*for(x = 0; x < w; x+=)
   {
      spgraphics->SelectObject(fonta[System.math().RandRange(0, 4)]);
      int y = System.math().RandRange(5, 23);
      spgraphics->SetTextColor(RGB(System.math().RandRange(110, 255),
         System.math().RandRange(110, 255),
         System.math().RandRange(110, 255)) |(((DWORD)(BYTE)(0))<<24));
       spgraphics->TextOut(System.math().RandRange(-20, w), System.math().RandRange(-20, h), &pszCode[i], 1);
       size = spgraphics->GetTextExtent(&pszCode[i], 1);
       x += size.cx;
//         imagecolordeallocate($im, $back_color);
   }*/
   x = 5;
   size size;
   spdib->get_graphics()->SetBkMode(TRANSPARENT);
   for(int i = 0; natural(i) < strlen(pszCode); i++)
   {
      spdib->get_graphics()->SelectObject(fonta[System.math().RandRange(0, 4)]);
      int y = System.math().RandRange(5, 23);
      spdib->get_graphics()->SetTextColor(RGB(System.math().RandRange(110, 255),
      System.math().RandRange(110, 255),
      System.math().RandRange(110, 255)) |(((DWORD)(BYTE)(0))<<24));
      spdib->get_graphics()->TextOut(x, y, &pszCode[i], 1);
      size = spdib->get_graphics()->GetTextExtent(&pszCode[i], 1);
      x += size.cx;
   }
   spdib->fill_channel(255, visual::rgba::channel_alpha);
   image_png(spdib->get_bitmap());
}

string checkimage::generate_code()
{
   string str;
   str.Format("%d", System.math().RandRange(10000, 99999));
   ASSERT(is_valid_code(str));
   return str;
}
   
   
string checkimage::register_code(const char * pszCode)
{
   set_session_value("ci_verifycode", pszCode);
   return pszCode;
}

bool checkimage::verify_code(const char * pszCode)
{
   bool bOk =   get_session_value("ci_verifycode") == pszCode && is_valid_code(get_session_value("ci_verifycode"));
   set_session_value("ci_verifycode", gen::g_nullconst);
   return bOk;
}



bool checkimage::is_valid_code(const char * pszCode)
{
   return strlen(pszCode) >= 5;
}

} // namespace webserver