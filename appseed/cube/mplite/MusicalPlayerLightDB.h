#pragma once

class MusicalPlayerLightDB  :
   public ::database::server
{
public:
   MusicalPlayerLightDB(::ca::application * papp);
   virtual ~MusicalPlayerLightDB();
   
   virtual bool data_server_save(
      ::database::id idSection,
      ::database::id id, 
      ::database::id idIndex,
      var & var, ::database::update_hint * puh);

   virtual bool data_server_load(
      ::database::id idSection,
      ::database::id id, 
      ::database::id idIndex, 
      var & var, ::database::update_hint * puh);

};
