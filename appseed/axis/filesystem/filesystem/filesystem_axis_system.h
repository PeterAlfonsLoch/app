#pragma once


namespace file
{

   
   namespace axis
   {


      class CLASS_DECL_AXIS system:
         virtual public ::file::system
      {
      public:


         system(::aura::application * papp);
         virtual ~system();



         using ::file::system::exists;

         virtual bool exists(const path & path,var * pvarQuery,::aura::application * papp);

         virtual var length(const path & path,::aura::application * papp);

         virtual var length(const path & path,var * pvarQuery,::aura::application * papp);

         using ::file::system::time_square;
         
         template < class T >
         string time_square(::aura::application * papp,T * p,bool (T::*lpfnOutput)(ostream &,const path &),const path & lpszSource)
         {
            string strTime = this->time_square(papp);
            if(strTime.has_char())
               if(!output(strTime,p,lpfnOutput,lpszSource))
                  return "";
            return strTime;
         }


         virtual ::file::file_sp get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp);


      };


   } // namespace axis


} // namespace file





