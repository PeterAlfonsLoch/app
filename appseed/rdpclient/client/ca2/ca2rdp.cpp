/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * DirectFB Client
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

#include "ca2rdp_event.h"
#include "ca2rdp_graphics.h"

#include "ca2rdp.h"

#include <errno.h>
#include <locale.h>

#include <freerdp/freerdp.h>
#include <freerdp/constants.h>
//#include <freerdp/utils/event.h>
#include <freerdp/client/file.h>
#include <freerdp/client/cmdline.h>
#include <freerdp/client/channels.h>
#include <freerdp/client/cliprdr.h>

#include <winpr/crt.h>
#include <winpr/synch.h>

#if defined(ANDROID) || defined(__APPLE__)
#include <sys/select.h>
#endif

#define TAG CLIENT_TAG("axisrdpclient")

//FREERDP_LOCAL rdpChannels* freerdp_channels_new(freerdp* instance);
//FREERDP_LOCAL UINT freerdp_channels_disconnect(rdpChannels* channels,
//   freerdp* instance);
//FREERDP_LOCAL void freerdp_channels_close(rdpChannels* channels,
//   freerdp* instance);
//FREERDP_LOCAL void freerdp_channels_free(rdpChannels* channels);
//FREERDP_LOCAL UINT freerdp_channels_pre_connect(rdpChannels* channels,
//   freerdp* instance);
//FREERDP_LOCAL UINT freerdp_channels_post_connect(rdpChannels* channels,
//   freerdp* instance);
BOOL ca2rdp_begin_paint(rdpContext* context)
{
	rdpGdi* gdi = context->gdi;
#ifdef WINDOWSEX
	gdi->primary->hdc->hwnd->invalid->null = 1;
#endif
	return 1;
}


BOOL ca2rdp_end_paint(rdpContext* context)
{

	rdpGdi* gdi;
	ca2rdpInfo* ca2rdpi;

#ifdef _WIN32
	gdi = context->gdi;
	ca2rdpi = ((ca2rdpContext*) context)->ca2rdpi;

	if (gdi->primary->hdc->hwnd->invalid->null)
		return 1;

	ca2rdpi->x = 0;
	ca2rdpi->y = 0;
	ca2rdpi->w = gdi->width;
	ca2rdpi->h = gdi->height;
   ::draw2d::dib_copy(ca2rdpi->surface,ca2rdpi->primary);
#endif


	return 1;

}


BOOL ca2rdp_get_fds(freerdp* instance, void** rfds, int* rcount, void** wfds, int* wcount)
{
	ca2rdpInfo* ca2rdpi;

	ca2rdpi = ((ca2rdpContext*) instance->context)->ca2rdpi;

	rfds[*rcount] = (void*)(size_t)(ca2rdpi->read_fds);
	(*rcount)++;

	return TRUE;
}

BOOL ca2rdp_check_fds(freerdp* instance, fd_set* set)
{
	ca2rdpInfo* ca2rdpi;

	ca2rdpi = ((ca2rdpContext*) instance->context)->ca2rdpi;

	if (!FD_ISSET(ca2rdpi->read_fds, set))
		return TRUE;

	return TRUE;

}


BOOL ca2rdp_pre_connect(freerdp* instance)
{
	ca2rdpInfo* ca2rdpi;
	BOOL bitmap_cache;
	ca2rdpContext* context;
	rdpSettings* settings;

	ca2rdpi = (ca2rdpInfo*) malloc(sizeof(ca2rdpInfo));
	ZeroMemory(ca2rdpi, sizeof(ca2rdpInfo));

	context = ((ca2rdpContext*) instance->context);
	context->ca2rdpi = ca2rdpi;

	settings = instance->settings;
	bitmap_cache = settings->BitmapCacheEnabled;

	settings->OrderSupport[NEG_DSTBLT_INDEX] = TRUE;
	settings->OrderSupport[NEG_PATBLT_INDEX] = TRUE;
	settings->OrderSupport[NEG_SCRBLT_INDEX] = TRUE;
	settings->OrderSupport[NEG_OPAQUE_RECT_INDEX] = TRUE;
	settings->OrderSupport[NEG_DRAWNINEGRID_INDEX] = FALSE;
	settings->OrderSupport[NEG_MULTIDSTBLT_INDEX] = FALSE;
	settings->OrderSupport[NEG_MULTIPATBLT_INDEX] = FALSE;
	settings->OrderSupport[NEG_MULTISCRBLT_INDEX] = FALSE;
	settings->OrderSupport[NEG_MULTIOPAQUERECT_INDEX] = TRUE;
	settings->OrderSupport[NEG_MULTI_DRAWNINEGRID_INDEX] = FALSE;
	settings->OrderSupport[NEG_LINETO_INDEX] = TRUE;
	settings->OrderSupport[NEG_POLYLINE_INDEX] = TRUE;
	settings->OrderSupport[NEG_MEMBLT_INDEX] = bitmap_cache;
	settings->OrderSupport[NEG_MEM3BLT_INDEX] = FALSE;
	settings->OrderSupport[NEG_MEMBLT_V2_INDEX] = bitmap_cache;
	settings->OrderSupport[NEG_MEM3BLT_V2_INDEX] = FALSE;
	settings->OrderSupport[NEG_SAVEBITMAP_INDEX] = FALSE;
	settings->OrderSupport[NEG_GLYPH_INDEX_INDEX] = FALSE;
	settings->OrderSupport[NEG_FAST_INDEX_INDEX] = FALSE;
	settings->OrderSupport[NEG_FAST_GLYPH_INDEX] = FALSE;
	settings->OrderSupport[NEG_POLYGON_SC_INDEX] = FALSE;
	settings->OrderSupport[NEG_POLYGON_CB_INDEX] = FALSE;
	settings->OrderSupport[NEG_ELLIPSE_SC_INDEX] = FALSE;
	settings->OrderSupport[NEG_ELLIPSE_CB_INDEX] = FALSE;

	//ca2rdpi->clrconv = (CLRCONV*) malloc(sizeof(CLRCONV));
	//ZeroMemory(ca2rdpi->clrconv, sizeof(CLRCONV));

	//ca2rdpi->clrconv->alpha = 1;
	//ca2rdpi->clrconv->invert = 0;
	//ca2rdpi->clrconv->rgb555 = 0;

	//ca2rdpi->clrconv->palette = (rdpPalette*) malloc(sizeof(rdpPalette));
	//ZeroMemory(ca2rdpi->clrconv->palette, sizeof(rdpPalette));

	//freerdp_channels_pre_connect(instance->context->channels, instance);

	instance->context->cache = cache_new(instance->settings);

	return TRUE;
}

BOOL ca2rdp_post_connect(freerdp* instance)
{
	rdpGdi* gdi;
	ca2rdpInfo* ca2rdpi;
	ca2rdpContext* context;

	context = ((ca2rdpContext*) instance->context);
	ca2rdpi = context->ca2rdpi;

   ::draw2d::dib_alloc(context->m_pappRdp, ca2rdpi->primary);
   ::draw2d::dib_create(ca2rdpi->primary, instance->settings->DesktopWidth,instance->settings->DesktopHeight);

   ::draw2d::dib_alloc(context->m_pappRdp, ca2rdpi->surface);
   ::draw2d::dib_create(ca2rdpi->surface, instance->settings->DesktopWidth,instance->settings->DesktopHeight);

//   gdi_init(instance,CLRCONV_ALPHA |  CLRBUF_32BPP,(BYTE*) ::draw2d::dib_get_data(ca2rdpi->primary));
   if (!gdi_init(instance, PIXEL_FORMAT_BGRX32))
   {

      return FALSE;

   }

	gdi = instance->context->gdi;

	instance->update->BeginPaint = ca2rdp_begin_paint;
	instance->update->EndPaint = ca2rdp_end_paint;

	pointer_cache_register_callbacks(instance->update);
	ca2rdp_register_graphics(instance->context->graphics);

	return TRUE;

}


BOOL ca2rdp_verify_certificate(freerdp* instance, char* subject, char* issuer, char* fingerprint)
{
	char answer;

	printf("Certificate details:\n");
	printf("\tSubject: %s\n", subject);
	printf("\tIssuer: %s\n", issuer);
	printf("\tThumbprint: %s\n", fingerprint);
	printf("The above X.509 certificate could not be verified, possibly because you do not have "
		"the CA certificate in your certificate store, or the certificate has expired. "
		"Please look at the documentation on how to create local certificate store for a private CA.\n");

	while (1)
	{
		printf("Do you trust the above certificate? (Y/N) ");
		answer = fgetc(stdin);

		if (answer == 'y' || answer == 'Y')
		{
			return TRUE;
		}
		else if (answer == 'n' || answer == 'N')
		{
			break;
		}
	}

	return FALSE;
}

static int ca2rdp_receive_channel_data(freerdp* instance, int channelId, BYTE* data, int size, int flags, int total_size)
{
	return freerdp_channels_data(instance, channelId, data, size, flags, total_size);
}

//static void ca2rdp_process_cb_monitor_ready_event(rdpChannels* channels, freerdp* instance)
//{
//	wMessage* event;
//	RDP_CB_FORMAT_LIST_EVENT* format_list_event;
//
//	event = freerdp_event_new(CliprdrChannel_Class, CliprdrChannel_FormatList, NULL, NULL);
//
//	format_list_event = (RDP_CB_FORMAT_LIST_EVENT*) event;
//	format_list_event->num_formats = 0;
//
//	freerdp_channels_send_event(channels, event);
//}
//
//static void ca2rdp_process_channel_event(rdpChannels* channels, freerdp* instance)
//{
//	wMessage* event;
//
//	event = freerdp_channels_pop_event(channels);
//
//	if (event)
//	{
//		switch (GetMessageType(event->id))
//		{
//			case CliprdrChannel_MonitorReady:
//				ca2rdp_process_cb_monitor_ready_event(channels, instance);
//				break;
//
//			default:
//				WLog_ERR(TAG, "ca2rdp_process_channel_event: unknown event type %d\n", GetMessageType(event->id));
//				break;
//		}
//
//		freerdp_event_free(event);
//	}
//}

static void ca2rdp_free(ca2rdpInfo* ca2rdpi)
{
//	ca2rdpi->ca2rdpb->Release(ca2rdpi->ca2rdpb);
	free(ca2rdpi);
}

int ca2rdpreerdp_run(freerdp* instance)
{
	int i;
	int fds;
	int max_fds;
	int rcount;
	int wcount;
	void* rfds[32];
	void* wfds[32];
	fd_set rfds_set;
	fd_set wfds_set;
	ca2rdpInfo* ca2rdpi;
	ca2rdpContext* context;
	rdpChannels* channels;

	ZeroMemory(rfds, sizeof(rfds));
	ZeroMemory(wfds, sizeof(wfds));

	if (!freerdp_connect(instance))
		return 0;

	context = (ca2rdpContext*) instance->context;

	ca2rdpi = context->ca2rdpi;
	channels = instance->context->channels;

	while (1)
	{
		rcount = 0;
		wcount = 0;

		if (freerdp_get_fds(instance, rfds, &rcount, wfds, &wcount) != TRUE)
		{
			WLog_ERR(TAG, "Failed to get FreeRDP file descriptor\n");
			break;
		}
		if (freerdp_channels_get_fds(channels, instance, rfds, &rcount, wfds, &wcount) != TRUE)
		{
			WLog_ERR(TAG, "Failed to get channel manager file descriptor\n");
			break;
		}
		if (ca2rdp_get_fds(instance, rfds, &rcount, wfds, &wcount) != TRUE)
		{
			WLog_ERR(TAG, "Failed to get ca2rdpreerdp file descriptor\n");
			break;
		}

		max_fds = 0;
		FD_ZERO(&rfds_set);
		FD_ZERO(&wfds_set);

		for (i = 0; i < rcount; i++)
		{
			fds = (int)(size_t)(rfds[i]);

			if (fds > max_fds)
				max_fds = fds;

			FD_SET(fds, &rfds_set);
		}

		if (max_fds == 0)
			break;

		if (select(max_fds + 1, &rfds_set, &wfds_set, NULL, NULL) == -1)
		{
			/* these are not really errors */
			if (!((errno == EAGAIN) ||
				(errno == EWOULDBLOCK) ||
				(errno == EINPROGRESS) ||
				(errno == EINTR))) /* signal occurred */
			{
				WLog_ERR(TAG, "ca2rdpreerdp_run: select failed\n");
				break;
			}
		}

		if (freerdp_check_fds(instance) != TRUE)
		{
			WLog_ERR(TAG, "Failed to check FreeRDP file descriptor\n");
			break;
		}
		if (ca2rdp_check_fds(instance, &rfds_set) != TRUE)
		{
			WLog_ERR(TAG, "Failed to check ca2rdpreerdp file descriptor\n");
			break;
		}
		if (freerdp_channels_check_fds(channels, instance) != TRUE)
		{
			WLog_ERR(TAG, "Failed to check channel manager file descriptor\n");
			break;
		}
//		ca2rdp_process_channel_event(channels, instance);
	}

	//freerdp_channels_close(channels, instance);
	//freerdp_channels_free(channels);
	ca2rdp_free(ca2rdpi);
	gdi_free(instance);
	freerdp_disconnect(instance);
	freerdp_free(instance);

	return 0;
}


::draw2d::graphics * ca2rdp_ctx_get_graphics(ca2rdp_context * pcontext)
{
   if(pcontext->ca2rdpi == NULL)
      return NULL;
   return ::draw2d::dib_get_graphics(pcontext->ca2rdpi->surface);

}

COLORREF * ca2rdp_ctx_get_primary(ca2rdp_context * pcontext)
{
//#ifdef _WIN32
//   if(pcontext->primary == NULL)
//      return NULL;
//   return (COLORREF *) pcontext->primary->pdata;
//#else
   if(pcontext->gdi == NULL)
      return NULL;
/*   if(pcontext->gdi->drawing == NULL)
      return NULL;
   if(pcontext->gdi->drawing->bitmap == NULL)
      return NULL;
   return (COLORREF *)pcontext->gdi->drawing->bitmap->p*/
   return (COLORREF *)pcontext->gdi->primary_buffer;
;
//#endif
}

int ca2rdp_ctx_get_bitmap_size(ca2rdp_context * pcontext)
{
   if(pcontext->gdi == NULL)
      return 0;
   /*   if(pcontext->gdi->drawing == NULL)
   return NULL;
   if(pcontext->gdi->drawing->bitmap == NULL)
   return NULL;
   return (COLORREF *)pcontext->gdi->drawing->bitmap->p*/
   return pcontext->gdi->bitmap_size;
   ;
}


