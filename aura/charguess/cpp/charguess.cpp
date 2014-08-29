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

#include "charguess.h"
#include "universal.h"
#include "string.h"




extern "C" charguess CharGuessInit()
{
   nsUniversalDetector* det = new nsUniversalDetector;
	if (det != NULL)
      return (charguess) det;
	else
		return NULL;
}

extern "C" const char* GuessChardet(charguess * p, const char *str)
{
   
   nsUniversalDetector* det = (nsUniversalDetector*) p;

	det->Reset();
	det->HandleData(str, strlen(str));
	det->DataEnd();
	
   return det->GetCharset();

}


extern "C" void CharGuessDestroy(charguess * p)
{
   
   nsUniversalDetector* det = (nsUniversalDetector*)p;

   if (det != NULL)
		delete det;

}
