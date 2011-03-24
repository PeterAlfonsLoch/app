#ifndef vmgetnempl
#define vmgetnempl

template<class TYPE> void freePointer(TYPE * * pointer);

/*template<class TYPE> void freePointer(TYPE * * pointer)
{
   free((void *) *pointer);
   *pointer = NULL;
}*/

#endif// vmgetnempl