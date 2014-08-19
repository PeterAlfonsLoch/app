#include "framework.h"


namespace file
{


   void seekable::seek_to_begin()
   {

      seek(0, seek_begin);

   }


   file_position seekable::seek_to_end()
   {

      return seek(0, seek_end);

   }


   file_position seekable::seek_from_begin(file_position position)
   {

      return seek((file_offset) position, seek_begin);

   }

   file_position seekable::seek(file_offset offset, e_seek seekOrigin)
   {
      UNREFERENCED_PARAMETER(offset);
      UNREFERENCED_PARAMETER(seekOrigin);
      throw interface_only_exception(get_app());
   }

   file_position seekable::get_position() const
   {
      return const_cast < seekable * > (this)->seek(0, seek_current);
   }


} // namespace file




