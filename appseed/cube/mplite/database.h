#pragma once

class db_file_set;

namespace mplite
{
   class database :
      virtual public ::radix::object
   {
   public:
      database(::ca::application * papp);
      virtual ~database();

      bool                    m_bInitialized;
      
      void Finalize();
      bool Initialize();

   };


} // namespace mplite