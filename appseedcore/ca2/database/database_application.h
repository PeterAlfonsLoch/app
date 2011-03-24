#pragma once

class DBCentralInterface;
class CResourceCentral;
class VmsDataServerInterface;

namespace database
{

   class CLASS_DECL_ca application :
      virtual public ca4::application,
      virtual public ::database::client
   {
   public:
      application();
      virtual ~application();

      virtual bool initialize();

      virtual ::database::server * get_data_server();


      virtual int exit_instance();

   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace database