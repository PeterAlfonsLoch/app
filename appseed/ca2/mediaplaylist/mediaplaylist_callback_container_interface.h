#pragma once


namespace mediaplaylist
{


   class callback_interface;


   class CLASS_DECL_ca callback_container_interface  
   {
   public:


      callback_container_interface();
      virtual ~callback_container_interface();


      virtual callback_interface * GetPlaylistCallback() = 0;


   };


} // namespace mediaplaylist

