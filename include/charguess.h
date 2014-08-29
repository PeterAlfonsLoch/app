/*
	libcharguess	-	Guess the encoding/charset of a string
    Copyright (C) 2003  Stephane Corbe <noubi@users.sourceforge.net>
	Based on Mozilla sources

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "aura/aura/aura.h"

#if defined(_AURA_CHARGUESS)
#define CHARGUESS_API  CLASS_DECL_EXPORT
#else
#define CHARGUESS_API  CLASS_DECL_IMPORT
#endif

typedef void * charguess_det;

BEGIN_EXTERN_C

CHARGUESS_API charguess_det CharGuessInit(void);
CHARGUESS_API const char * GuessChardet(charguess_det p,const char *str);
CHARGUESS_API void CharGuessDestroy(charguess_det p);


END_EXTERN_C



#ifdef cplusplus

CHARGUESS_API const char * GuessChardet(charguess_det * p,const string & str);


class CHARGUESS_API charguess
{
public:

   charguess_det     m_pdet;
   string            m_strDet;

   charguess()
   {
      m_pdet = CharGuessInit();
   }
   charguess(const string & str)
   {
      m_pdet = CharGuessInit();
      det(str);
   }
   ~charguess()
   {
      CharGuessDestroy(m_pdet);
   }


   string det(const string & str)
   {
      return m_strDet = GuessChardet(m_pdet,str);
   }

   string operator () (void) { return m_strDet; }


};

#ifdef _DEBUG
inline void _debug_charguess()
{
   string strCharGuest = charguess("\"Carlos é brasileiro\" está escrito em um código de página latino?")();
}

#endif



#endif // cplusplus





























