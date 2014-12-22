#pragma once

/*
uint32_t ___ReadProc    (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
uint32_t ___WriteProc   (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
int32_t      ___SeekProc    (fi_handle handle, long offset, int32_t origin);
long     ___TellProc    (fi_handle handle);


uint32_t __ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
uint32_t __WriteProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
uint32_t __ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
uint32_t __WriteProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
*/


uint32_t DLL_CALLCONV __ReadProc2(void *buffer, uint32_t size, uint32_t count, fi_handle handle);
uint32_t DLL_CALLCONV __WriteProc2(void *buffer, uint32_t size, uint32_t count, fi_handle handle);
int32_t      DLL_CALLCONV __SeekProc2(fi_handle handle, long offset, int32_t origin);
long     DLL_CALLCONV __TellProc2(fi_handle handle);


uint32_t _stdcall ___Ex1File__ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
uint32_t _stdcall ___Ex1File__WriteProc(void *buffer, uint32_t size, uint32_t count, fi_handle handle);
int32_t      _stdcall ___Ex1File__SeekProc (fi_handle handle, long offset, int32_t origin);
long     _stdcall ___Ex1File__TellProc (fi_handle handle);
