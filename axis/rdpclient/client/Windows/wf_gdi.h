/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Windows GDI
 *
 * Copyright 2009-2011 Jay Sorg
 * Copyright 2010-2011 Vic Lee
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

#ifndef __WF_GDI_H
#define __WF_GDI_H


#include "../../freerdp_rdpclient_setup.h"

#include "wf_interface.h"



BEGIN_EXTERN_C

CLASS_DECL_RDPCLIENT void wf_invalidate_region(wfContext* wfc, int x, int y, int width, int height);
CLASS_DECL_RDPCLIENT wfBitmap* wf_image_new(wfContext* wfc,int width,int height,int bpp,BYTE* data);
CLASS_DECL_RDPCLIENT void wf_image_free(wfBitmap* image);
CLASS_DECL_RDPCLIENT void wf_update_offset(wfContext* wfc);
CLASS_DECL_RDPCLIENT void wf_resize_window(wfContext* wfc);
CLASS_DECL_RDPCLIENT void wf_toggle_fullscreen(wfContext* wfc);

CLASS_DECL_RDPCLIENT void wf_gdi_register_update_callbacks(rdpUpdate* update);

CLASS_DECL_RDPCLIENT void wf_update_canvas_diff(wfContext* wfc);

END_EXTERN_C

#endif /* __WF_GDI_H */
