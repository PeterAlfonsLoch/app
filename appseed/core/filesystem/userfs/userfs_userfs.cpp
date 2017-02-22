//#include "framework.h"


namespace userfs
{


   userfs::userfs(::aura::application * papp) :
      object(papp),
      ::aura::department(papp)
   {

   }

   userfs::~userfs()
   {

   }

   bool userfs::initialize()
   {

      if(Application.is_system())
      {
         System.factory().creatable_small < ::userfs::main_view > ();
         System.factory().creatable_small < ::userfs::tree > ();
         System.factory().creatable_small < ::userfs::list > ();
         System.factory().creatable_small < ::userfs::list_item > ();
      }


      if(!::aura::department::initialize())
         return false;


      return true;


   }



} // namespace core





namespace core
{

   ::userfs::userfs * application::create_userfs()
   {

      ::userfs::userfs * puserfs = canew(::userfs::userfs(this));

      if (puserfs == NULL)
      {

         return NULL;

      }

      return puserfs;

   }


   bool application::process_initialize_userfs()
   {

      thisstart;

      m_puserfs = create_userfs();

      if (m_puserfs == NULL)
      {

         thiserr << "end failure (1)";

         return false;

      }

      m_spobjectUserFs = m_puserfs;

      m_puserfs->construct(this);

      thisinfo << "end";

      return true;

   }


   bool application::initialize1_userfs()
   {

      thisstart;

      if (!m_puserfs->initialize())
      {

         thiserr << "err failure (1)";

         return false;

      }

      thisend;


      return true;

   }








} // namespace userfs







