

void std_out_buffer::write(const void * lpBuf,memory_size_t nCount)
{

   write_memory_to_file(GetStdHandle(STD_OUTPUT_HANDLE),lpBuf,nCount,NULL);

}



namespace console
{


   void window::redirect_io()
   {

   }


} // namespace console


