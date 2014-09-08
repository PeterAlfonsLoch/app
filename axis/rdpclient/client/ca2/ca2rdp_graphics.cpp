/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * DirectFB Graphical Objects
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ca2rdp_graphics.h"

#include <winpr/crt.h>


/* Pointer Class */

void ca2rdp_Pointer_New(rdpContext* context, rdpPointer* pointer)
{
	ca2rdpInfo* ca2rdpi;
	int result;
	ca2rdpPointer* ca2rdp_pointer;
	//DFBSurfaceDescription dsc;

	ca2rdpi = ((ca2rdpContext*) context)->ca2rdpi;
	ca2rdp_pointer = (ca2rdpPointer*) pointer;


	int pitch;

	ca2rdp_pointer->xhot = pointer->xPos;
	ca2rdp_pointer->yhot = pointer->yPos;
   ca2rdp_pointer->m_pcursor = new ::visual::cursor(((ca2rdpContext*)context)->m_papp);
   
   //.m_dib.alloc(((ca2rdpContext*)context)->m_papp->allocer());
   ca2rdp_pointer->m_pcursor->m_dib->create(ca2rdp_pointer->pointer.width,ca2rdp_pointer->pointer.height);

	if ((pointer->andMaskData != 0) && (pointer->xorMaskData != 0))
	{
      freerdp_alpha_cursor_convert((BYTE *) ca2rdp_pointer->m_pcursor->m_dib->get_data(),pointer->xorMaskData,pointer->andMaskData,
				pointer->width, pointer->height, pointer->xorBpp, ca2rdpi->clrconv);
	}

	if (pointer->xorBpp > 24)
	{
      freerdp_image_swap_color_order((BYTE *)ca2rdp_pointer->m_pcursor->m_dib->get_data(),pointer->width,pointer->height);
	}

}

void ca2rdp_Pointer_Free(rdpContext* context, rdpPointer* pointer)
{
	ca2rdpPointer* ca2rdp_pointer = (ca2rdpPointer*) pointer;
///	ca2rdp_pointer->surface->Release(ca2rdp_pointer->surface);
}

void ca2rdp_Pointer_Set(rdpContext* context, rdpPointer* pointer)
{
/*	ca2rdpInfo* ca2rdpi;
	DFBResult result;
	ca2rdpPointer* ca2rdp_pointer;

	ca2rdpi = ((ca2rdpContext*) context)->ca2rdpi;
	ca2rdp_pointer = (ca2rdpPointer*) pointer;

	ca2rdpi->layer->SetCooperativeLevel(ca2rdpi->layer, DLSCL_ADMINISTRATIVE);

	ca2rdpi->layer->SetCursorOpacity(ca2rdpi->layer, ca2rdp_pointer ? 255: 0);

	if(ca2rdp_pointer != NULL)
	{
		result = ca2rdpi->layer->SetCursorShape(ca2rdpi->layer,
			ca2rdp_pointer->surface, ca2rdp_pointer->xhot, ca2rdp_pointer->yhot);

		if (result != DFB_OK)
		{
			DirectFBErrorFatal("SetCursorShape Error", result);
			return;
		}
	}

	ca2rdpi->layer->SetCooperativeLevel(ca2rdpi->layer, DLSCL_SHARED);*/
}

void ca2rdp_Pointer_SetNull(rdpContext* context)
{
	ca2rdp_Pointer_Set(context, NULL);
}

void ca2rdp_Pointer_SetDefault(rdpContext* context)
{

}

/* Graphics Module */

void ca2rdp_register_graphics(rdpGraphics* graphics)
{
	rdpPointer* pointer;

	pointer = (rdpPointer*) malloc(sizeof(rdpPointer));
	ZeroMemory(pointer, sizeof(rdpPointer));
	pointer->size = sizeof(ca2rdpPointer);

	pointer->New = ca2rdp_Pointer_New;
	pointer->Free = ca2rdp_Pointer_Free;
	pointer->Set = ca2rdp_Pointer_Set;
	pointer->SetNull = ca2rdp_Pointer_SetNull;
	pointer->SetDefault = ca2rdp_Pointer_SetDefault;

	graphics_register_pointer(graphics, pointer);
	free(pointer);
}

