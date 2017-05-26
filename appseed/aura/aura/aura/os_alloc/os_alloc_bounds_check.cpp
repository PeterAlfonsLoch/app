

BEGIN_EXTERN_C


void os_alloc_check_bounds(byte * p)
{

	uint_ptr * pui = (uint_ptr *)p;

	byte a[256];

	ZERO(a);

	if (memcmp(&p[sizeof(uint_ptr)], a, sizeof(a)) != 0)
	{

		output_debug_string("memory corruption before allocation");

	}
	if (memcmp(&p[sizeof(uint_ptr) + 256 + *pui], a, sizeof(a)) != 0)
	{

		output_debug_string("memory corruption after allocation");

	}

}


void * os_alloc(size_t size)
{

	cslock sl(g_pmutexSystemHeap);

	byte * p = (byte *)os_impl_alloc(size + 512 + sizeof(uint_ptr));

	memset(&p[sizeof(uint_ptr)], 0, 256);

	memset(&p[sizeof(uint_ptr) + 256 + size], 0, 256);

	uint_ptr * pui = (uint_ptr *)p;

	*pui = size;

	return &p[sizeof(uint_ptr) + 256];

}


void * os_realloc(void * pParam, size_t size)
{

	cslock sl(g_pmutexSystemHeap);

	byte * p = &((byte *)pParam)[-(int_ptr)((sizeof(uint_ptr) + 256))];

	os_alloc_check_bounds(p);

	p = (byte *)os_impl_realloc(p, size + 512 + sizeof(uint_ptr));

	memset(&p[sizeof(uint_ptr)], 0, 256);

	memset(&p[sizeof(uint_ptr) + 256 + size], 0, 256);

	uint_ptr * pui = (uint_ptr *)p;

	*pui = size;

	return &p[sizeof(uint_ptr) + 256];

}


void os_free(void * pParam)
{

	cslock sl(g_pmutexSystemHeap);

	byte * p = &((byte *)pParam)[-(int_ptr)((sizeof(uint_ptr) + 256))];

	os_alloc_check_bounds(p);

	os_impl_free(p);

}


END_EXTERN_C


