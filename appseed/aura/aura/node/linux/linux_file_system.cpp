


struct PROCESS_INFO_t
{
    string csProcess;
    uint32_t dwImageListIndex;
};


namespace linux
{


   file_system::file_system(::aura::application *  papp) :
      ::object(papp),
      ::file::system(papp)
   {
   }


   file_system::~file_system()
   {
   }




} // namespace linux






