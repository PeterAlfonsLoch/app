#pragma once

namespace database
{

   class id;

   class CLASS_DECL_ca server :
      public client_array
   {
   public:
      virtual bool data_server_load       (class id idSection, class id id, class id idIndex, var & var, update_hint * phint = NULL);
      virtual bool data_server_load       (class id idSection, class id id, class id idIndex, ex1::serializable & obj, update_hint * phint = NULL);
      virtual bool data_server_save       (class id idSection, class id id, class id idIndex, var & var, update_hint * phint = NULL);
      virtual bool data_server_save       (class id idSection, class id id, class id idIndex, ex1::serializable & obj, update_hint * phint = NULL);
      virtual bool data_pulse_change      (class id idSection, class id id, class id idIndex, update_hint * puh = NULL);
      virtual bool on_before_data_change  (class id idSection, class id id, class id idIndex, var & varNew, update_hint * puh = NULL);
      virtual bool on_after_data_change   (class id idSection, class id id, class id idIndex, update_hint * puh = NULL);

      virtual var data_load               (class id idSection, class  id id, class id idIndex, update_hint * phint = NULL);
      virtual bool data_save              (class id idSection, class id id, class id idIndex, var var, update_hint * phint = NULL);
   };

} // namespace database