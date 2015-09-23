

void std_out_buffer::write(const void * lpBuf,memory_size_t nCount)
{

#ifdef WINDOWSEX

   DWORD dw= 0;

   ::WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),lpBuf,nCount,&dw,NULL);

#else

   string str((const char * ) lpBuf,MIN(strnlen((const char *) lpBuf, nCount), nCount));

   printf("%s",str.c_str());

#endif

}



namespace console
{


   void window::redirect_io()
   {

   }


} // namespace console


