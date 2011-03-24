/* $Id: id3.h,v 1.21 2002/09/21 17:23:32 t1mpy Exp $
 *
 * id3lib: a software library for creating and manipulating id3v1/v2 tags
 * Copyright 1999, 2000  Scott Thomas Haug
 * Copyright 2002 Thijmen Klok (thijmen@id3lib.org)
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.

 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 * The id3lib authors encourage improvements and optimisations to be sent to
 * the id3lib coordinator.  Please see the README file for details on where to
 * send such submissions.  See the AUTHORS file for a list of people who have
 * contributed to id3lib.  See the ChangeLog file for a list of changes to
 * id3lib.  These files are distributed with id3lib at
 * http://download.sourceforge.net/id3lib/
 */

#ifndef _ID3LIB_ID3_H_
#define _ID3LIB_ID3_H_

#include "id3lib/globals.h" //has <stdlib.h> "id3/sized_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct { char _dummy; } ID3Tag;
  typedef struct { char _dummy; } ID3TagIterator;
  typedef struct { char _dummy; } ID3TagConstIterator;
  typedef struct { char _dummy; } ID3Frame;
  typedef struct { char _dummy; } ID3Field;
  typedef struct { char _dummy; } ID3FrameInfo;


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ID3LIB_ID3_H_ */
