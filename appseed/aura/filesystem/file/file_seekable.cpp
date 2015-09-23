//#include "framework.h"


namespace file
{


   void seekable::seek_to_begin()
   {

      seek(0, seek_begin);

   }


   file_position_t seekable::seek_to_end()
   {

      return seek(0, seek_end);

   }


   file_position_t seekable::seek_from_begin(file_position_t position)
   {

      return seek((file_offset_t) position, seek_begin);

   }

   file_position_t seekable::seek(file_offset_t offset, e_seek seekOrigin)
   {
      UNREFERENCED_PARAMETER(offset);
      UNREFERENCED_PARAMETER(seekOrigin);
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   file_position_t seekable::get_position() const
   {
      return const_cast < seekable * > (this)->seek(0, seek_current);
   }


} // namespace file




