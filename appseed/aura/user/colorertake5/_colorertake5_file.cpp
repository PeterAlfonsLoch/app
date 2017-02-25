#include "framework.h"


#include "colorertake5.h"
#include "aura/filestream.h"




namespace colorertake5
{


   void HRCParserImpl::loadFileType(file_type *filetype)
   {
      if (filetype == NULL) return;

      file_type_impl *thisType = (file_type_impl*)filetype;

      if (thisType->typeLoaded || thisType->inputSourceLoading || thisType->loadBroken) {
         return;
      }
      thisType->inputSourceLoading = true;

      thisType->m_strSource = Application.file().as_string(thisType->m_strSourceLocation);

      try
      {
         loadSource(thisType->m_strSourceLocation, thisType->m_strSource);
      }
      catch (::file::exception &e)
      {
         if (errorHandler != NULL)
         {
            errorHandler->fatalError("Can't open source stream: " + e.get_message());
         }
         thisType->loadBroken = true;
      }
      catch (HRCParserException &e) {
         if (errorHandler != NULL) {
            errorHandler->fatalError(string(e.getMessage()) + " [" + thisType->m_strSourceLocation + "]");
         }
         thisType->loadBroken = true;
      }
      catch (exception &e) {
         if (errorHandler != NULL) {
            errorHandler->fatalError(string(e.getMessage()) + " [" + thisType->m_strSourceLocation + "]");
         }
         thisType->loadBroken = true;
      }
      catch (...) {
         if (errorHandler != NULL) {
            errorHandler->fatalError(string("Unknown exception while loading ") + thisType->m_strSourceLocation);
         }
         thisType->loadBroken = true;
      }
   }



   string ParserFactory::searchPath()
   {

      return Application.dir().matter("colorer.zip:catalog.xml");

   }

   HRCParser* ParserFactory::getHRCParser()
   {
      if (hrcParser != NULL)
         return hrcParser;
      hrcParser = new HRCParserImpl(get_app());
      hrcParser->setErrorHandler(fileErrorHandler);
      for (int32_t idx = 0; idx < hrcLocations.get_size(); idx++)
      {
         string relPath = hrcLocations.element_at(idx);
         string path;
         if (file_path_is_relative_dup(relPath))
         {
            path = catalogPath.sibling(relPath);
            string path2del = path;
            ::str::begins_eat(path, "file://");
            ::str::begins_eat(path, "file:/");
            ::str::begins_eat(path, "file:");
         }
         else
         {
            path = relPath;
         }
         if (Application.dir().is(path))
         {
            //if(path == "v:\\ca2os\\basis\\app\\appmatter\\main\\_std\\_std\\colorer\\hrc\\auto")
            {
               // debug_break();
            }
            ::file::listing patha(get_app());
            patha.rls(path);
            ::file::file_sp spfile(allocer());
            for (int32_t i = 0; i < patha.get_count(); i++)
            {
               if (!Application.dir().is(patha[i]))
               {
                  string str = Application.file().as_string(patha[i]);
                  try
                  {
                     hrcParser->loadSource(patha[i], str);
                  }
                  catch (::exception::base &e)
                  {
                     string str;
                     e.get_error_message(str);
                     TRACE("exception %s", str.c_str());
                  }
               }
            }
         }
         else
         {
            string strSource = Application.file().as_string(path);
            if (strSource.has_char())
            {
               try
               {
                  hrcParser->loadSource(path, strSource);
               }
               catch (::exception::base & e)
               {
                  string str;
                  e.get_error_message(str);
                  TRACE("exception %s", str.c_str());
               }
            }
         }
      }
      return hrcParser;
   }



   StyledHRDMapper *ParserFactory::createStyledMapper(string classID, string nameID)
   {
      string_map<stringa> * hrdClass = NULL;
      if (classID.is_empty())
         hrdClass = hrdLocations.pget(("rgb"));
      else
         hrdClass = hrdLocations.pget(classID);

      if (hrdClass == NULL)
         throw ParserFactoryException(get_app(), string("can't find hrdClass '") + classID + "'");

      stringa *hrdLocV = NULL;
      if (nameID.is_empty())
      {
         char * hrd = NULL;
#ifndef METROWIN
         hrd = getenv("COLORER5HRD");
#endif
         hrdLocV = (hrd) ? hrdClass->pget((hrd)) : hrdClass->pget(("default"));
         if (hrdLocV == NULL)
         {
            hrdLocV = hrdClass->pget(("default"));
         }
      }
      else
         hrdLocV = hrdClass->pget(nameID);
      if (hrdLocV == NULL)
         throw ParserFactoryException(get_app(), string("can't find hrdName '") + nameID + "'");

      StyledHRDMapper *mapper = new StyledHRDMapper(get_app());

      ::file::path strDir = this->catalogPath.folder();

      for (int32_t idx = 0; idx < hrdLocV->get_size(); idx++)
      {
         if (hrdLocV->element_at(idx).has_char())
         {

            try
            {

               string strPath;

               strPath = strDir / hrdLocV->element_at(idx);

               ::file::byte_istream spfile(Application.file().get_file(strPath, ::file::mode_read | ::file::type_binary));

               if (spfile.is_reader_set())
               {

                  mapper->loadRegionMappings(spfile);

               }

            }
            catch (::exception::base &)
            {
            }

         }

      }

      return mapper;

   }

   TextHRDMapper *ParserFactory::createTextMapper(string nameID) {
      // fixed class 'text'
      string_map<stringa> *hrdClass = hrdLocations.pget(("text"));
      if (hrdClass == NULL) throw ParserFactoryException(get_app(), string("can't find hrdClass 'text'"));

      stringa *hrdLocV = NULL;
      if (nameID.is_empty())
         hrdLocV = hrdClass->pget(("default"));
      else
         hrdLocV = hrdClass->pget(nameID);
      if (hrdLocV == NULL)
         throw ParserFactoryException(get_app(), string("can't find hrdName '") + nameID + "'");

      TextHRDMapper *mapper = new TextHRDMapper(get_app());
      for (int32_t idx = 0; idx < hrdLocV->get_size(); idx++)
      {
         if (hrdLocV->element_at(idx).has_char())
         {
            try
            {
               ::file::byte_istream stream(Application.file().get_file(hrdLocV->element_at(idx), ::file::mode_read | ::file::type_binary));
               if (stream.is_reader_set())
               {
                  mapper->loadRegionMappings(stream);
               }
            }
            catch (::exception::base &)
            {
            }
         }
      }
      return mapper;
   }




} // namespace colorertake5



