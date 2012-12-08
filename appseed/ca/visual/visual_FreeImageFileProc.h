#pragma once

/*
unsigned ___ReadProc    (void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned ___WriteProc   (void *buffer, unsigned size, unsigned count, fi_handle handle);
int      ___SeekProc    (fi_handle handle, long offset, int origin);
long     ___TellProc    (fi_handle handle);


unsigned __ReadProc (void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned __WriteProc (void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned __ReadProc (void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned __WriteProc (void *buffer, unsigned size, unsigned count, fi_handle handle);
*/


unsigned _stdcall __ReadProc2 (void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned _stdcall __WriteProc2(void *buffer, unsigned size, unsigned count, fi_handle handle);
int      _stdcall __SeekProc2 (fi_handle handle, long offset, int origin);
long     _stdcall __TellProc2 (fi_handle handle);


unsigned _stdcall ___Ex1File__ReadProc (void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned _stdcall ___Ex1File__WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle);
int      _stdcall ___Ex1File__SeekProc (fi_handle handle, long offset, int origin);
long     _stdcall ___Ex1File__TellProc (fi_handle handle);
