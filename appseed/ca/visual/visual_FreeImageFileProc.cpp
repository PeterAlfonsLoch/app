#include "framework.h"
#define _WINDOWS_
#include "include/freeimage.h"

unsigned ___ReadProc    (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   DWORD dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
unsigned ___WriteProc   (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   DWORD dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
int      ___SeekProc    (fi_handle handle, long offset, int origin)
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

unsigned __ReadProc (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   DWORD dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
unsigned __WriteProc (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   DWORD dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
int __SeekProc (fi_handle handle, long offset, int origin)
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
}

unsigned _stdcall  __ReadProc2 (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   primitive::memory_size dwRead;
   ex1::file * pfile = (ex1::file *) handle;
   if(dwRead = pfile->read(buffer, count * size))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
unsigned _stdcall __WriteProc2 (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   ex1::file * pfile = (ex1::file *) handle;
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
int _stdcall __SeekProc2 (fi_handle handle, long offset, int origin)
{
   ex1::file * pfile = (ex1::file *) handle;
   if(origin == SEEK_SET)
      origin = ::ex1::seek_begin;
   else if(origin == SEEK_CUR)
      origin = ::ex1::seek_current;
   else if(origin == SEEK_END)
      origin = ::ex1::seek_end;
   if(pfile->seek(offset, (::ex1::e_seek) origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long _stdcall __TellProc2 (fi_handle handle)
{
   ex1::file * pfile = (ex1::file *) handle;
   return (long) pfile->get_position();
}

   //static unsigned _stdcall  __ReadProc3 (void *buffer, unsigned size, unsigned count, fi_handle handle);
   //static unsigned _stdcall __WriteProc3 (void *buffer, unsigned size, unsigned count, fi_handle handle);
   //static int _stdcall __SeekProc3 (fi_handle handle, long offset, int origin);
   //static long _stdcall __TellProc3 (fi_handle handle);

unsigned _stdcall  ___Ex1File__ReadProc (void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   primitive::memory_size dwRead;
   ex1::file * pfile = (ex1::file *) handle;
   if(dwRead = pfile->read(buffer, count * size))
   {
      return count;
   }
   else
   {
      return --count;
   }

}

unsigned _stdcall ___Ex1File__WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
{
   ex1::file * pfile = (ex1::file *) handle;
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

int _stdcall ___Ex1File__SeekProc(fi_handle handle, long offset, int origin)
{
   ex1::file * pfile = (ex1::file *) handle;
   if(origin == SEEK_SET)
      origin = ::ex1::seek_begin;
   else if(origin == SEEK_CUR)
      origin = ::ex1::seek_current;
   else if(origin == SEEK_END)
      origin = ::ex1::seek_end;
   if(pfile->seek(offset, (::ex1::e_seek) origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}

long _stdcall ___Ex1File__TellProc(fi_handle handle)
{
   ex1::file * pfile = (ex1::file *) handle;
   return (long) pfile->get_position();
}

