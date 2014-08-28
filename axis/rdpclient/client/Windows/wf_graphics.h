/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Windows Graphical Objects
 *
 * Copyright 2010-2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
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

#ifndef __WF_GRAPHICS_H
#define __WF_GRAPHICS_H

#include "../../freerdp_rdpclient_setup.h"

#include "wf_interface.h"

#ifdef __cplusplus
extern "C" {
#endif


CLASS_DECL_RDPCLIENT HBITMAP wf_create_dib(wfContext* wfc,int width,int height,int bpp,BYTE* data,BYTE** pdata);
CLASS_DECL_RDPCLIENT wfBitmap* wf_image_new(wfContext* wfc,int width,int height,int bpp,BYTE* data);
CLASS_DECL_RDPCLIENT void wf_image_free(wfBitmap* image);

CLASS_DECL_RDPCLIENT void wf_register_graphics(rdpGraphics* graphics);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* WF_GRAPHICS */
