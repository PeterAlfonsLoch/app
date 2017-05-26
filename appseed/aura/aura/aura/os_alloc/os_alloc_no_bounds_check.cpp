

BEGIN_EXTERN_C


void * os_alloc(size_t size)
{

	return os_impl_alloc(size);


}


void * os_realloc(void * p, size_t size)
{

	return os_impl_realloc(p, size);

}


void os_free(void * p)
{

	return os_impl_free(p);

}


END_EXTERN_C


