

BEGIN_EXTERN_C


void * os_impl_alloc(size_t size)
{

	cslock csl(g_pmutexSystemHeap);

	return ::HeapAlloc(g_system_heap(), 0, size);

	return  malloc(size);

}


void * os_impl_realloc(void * p, size_t size)
{

	cslock lock(g_pmutexSystemHeap);

	return ::HeapReAlloc(g_system_heap(), 0, p, size);

}


void os_impl_free(void * p)
{

	cslock lock(g_pmutexSystemHeap);

	if (!::HeapFree(g_system_heap(), 0, p))
	{

		uint32_t dw = ::GetLastError();

		::OutputDebugString("system_heap_free : Failed to free memory");

	}

}


END_EXTERN_C


