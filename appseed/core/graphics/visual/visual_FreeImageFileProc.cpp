#include "framework.h"
#define _WINDOWS_
#include "freeimage/freeimage.h"
#include "visual_FreeImageFileProc.h"

/*uint32_t ___ReadProc    (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
uint32_t ___WriteProc   (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
int32_t      ___SeekProc    (fi_handle handle, long offset, int32_t origin)
{
   if(origin == SEEK_SET)
      origin = FILE_BEGIN;
   else if(origin == SEEK_CUR)
      origin = FILE_CURRENT;
   else if(origin == SEEK_END)
      origin = FILE_END;
   if(SetFilePointer(handle, offset, NULL, origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long     ___TellProc    (fi_handle handle)
{
   return SetFilePointer(handle, 0, NULL, SEEK_CUR);
}

uint32_t __ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
uint32_t __WriteProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
int32_t __SeekProc (fi_handle handle, long offset, int32_t origin)
{
   if(origin == SEEK_SET)
      origin = FILE_BEGIN;
   else if(origin == SEEK_CUR)
      origin = FILE_CURRENT;
   else if(origin == SEEK_END)
      origin = FILE_END;
   if(SetFilePointer(handle, offset, NULL, origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long __TellProc (fi_handle handle)
{
   return SetFilePointer(handle, 0, NULL, SEEK_CUR);
}*/

uint32_t DLL_CALLCONV  __ReadProc2 (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   primitive::memory_size dwRead;
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   if((dwRead = pfile->read(buffer, count * size)) > 0)
   {
      return count;
   }
   else
   {
      return --count;
   }

}
uint32_t DLL_CALLCONV __WriteProc2(void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   try
   {
      pfile->write(buffer, count * size);
   }
   catch(...)
   {
      return --count;
   }
   return count;
}
int32_t DLL_CALLCONV __SeekProc2(fi_handle handle, long offset, int32_t origin)
{
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   if(origin == SEEK_SET)
      origin = ::file::seek_begin;
   else if(origin == SEEK_CUR)
      origin = ::file::seek_current;
   else if(origin == SEEK_END)
      origin = ::file::seek_end;
   try
   {
      pfile->seek(offset, (::file::e_seek) origin);
   }
   catch(...)
   {
      return -1;
   }
   return 0;
}
long DLL_CALLCONV __TellProc2(fi_handle handle)
{
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   return (long) pfile->get_position();
}

   //static uint32_t _stdcall  __ReadProc3 (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
   //static uint32_t _stdcall __WriteProc3 (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
   //static int32_t _stdcall __SeekProc3 (fi_handle handle, long offset, int32_t origin);
   //static long _stdcall __TellProc3 (fi_handle handle);

uint32_t _stdcall  ___Ex1File__ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   primitive::memory_size dwRead;
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   if((dwRead = pfile->read(buffer, count * size)))
   {
      return count;
   }
   else
   {
      return --count;
   }

}

uint32_t _stdcall ___Ex1File__WriteProc(void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   try
   {
      pfile->write(buffer, count * size);
   }
   catch(...)
   {
      return --count;
   }
   return count;
}

int32_t _stdcall ___Ex1File__SeekProc(fi_handle handle, long offset, int32_t origin)
{
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   if(origin == SEEK_SET)
      origin = ::file::seek_begin;
   else if(origin == SEEK_CUR)
      origin = ::file::seek_current;
   else if(origin == SEEK_END)
      origin = ::file::seek_end;
   if(pfile->seek(offset, (::file::e_seek) origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}

long _stdcall ___Ex1File__TellProc(fi_handle handle)
{
   ::file::buffer_sp  pfile = (::file::stream_buffer * ) handle;
   return (long) pfile->get_position();
}

