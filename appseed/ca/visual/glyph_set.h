// glyph_set.h: interface for the glyph_set class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLYPHSET_H__672A0FFB_D085_4E96_BD33_2D6D20BFF65C__INCLUDED_)
#define AFX_GLYPHSET_H__672A0FFB_D085_4E96_BD33_2D6D20BFF65C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace visual
{

class glyph_set : public base_array<glyph , glyph &>
{
public:
   virtual INT_PTR add(glyph & glyph);
   glyph_set();
   virtual ~glyph_set();

   void QuickSort();
   int find_first(UINT user);
   glyph * GetGlyph(UINT user);


};

} // namespace visual

#endif // !defined(AFX_GLYPHSET_H__672A0FFB_D085_4E96_BD33_2D6D20BFF65C__INCLUDED_)
