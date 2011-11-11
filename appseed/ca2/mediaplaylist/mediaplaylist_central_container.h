#pragma once


namespace mediaplaylist
{

   class central;
   class callback_interface;

   class CLASS_DECL_ca central_container : 
      virtual public gen::signalizable
   {
   public:
      central_container();
      virtual ~central_container();

   protected:
      central *   m_pplaylistcentral;
   public:
      virtual callback_interface * GetNewPlaylistCallback();

      static central_container & AppGetPlaylistAppInterface(::ca::application * papp);

      static central & AppGetPlaylistCentral(::ca::application * papp);

      inline central & GetPlaylistCentral();

      bool initialize(::ca::application * papp);

   };



} // namespace mediaplaylist


