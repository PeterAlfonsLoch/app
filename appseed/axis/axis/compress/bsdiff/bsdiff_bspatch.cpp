/*-
 * Copyright 2003-2005 Colin Percival
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted providing that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/
#include "framework.h"
#include "bsdiff_private.h"
#include "bzlib.h"
#include "bsdiff.h"

typedef uchar u_char;

//#ifdef WINDOWS
//typedef uint_ptr ssize_t;
//#endif

int32_t err(int32_t i, const char* str)
{
    
   wchar_t lastErrorTxt[1024];
    
#if defined(WINDOWS)
    
   FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(), 0, lastErrorTxt, 1024, NULL);
    
#else
    
    throw "not implemented";
    
#endif
    
   printf("%s", string(lastErrorTxt).c_str());
    
   if (str!=NULL)
   {
       
      printf("%s",str);
       
   }
    
   return (i);
    
}

int32_t errx(int32_t i, const char* str)
{
   
   printf("%s",str);
   
   return i;

}


static off_t offtin(u_char *buf)
{
   off_t y;

   y=buf[7]&0x7F;
   y=y*256;y+=buf[6];
   y=y*256;y+=buf[5];
   y=y*256;y+=buf[4];
   y=y*256;y+=buf[3];
   y=y*256;y+=buf[2];
   y=y*256;y+=buf[1];
   y=y*256;y+=buf[0];

   if(buf[7]&0x80) y=-y;

   return y;
}

int32_t bspatch(const char * oldfile, const char * newfile, const char * patchfile)
{
   _FILE * f, * cpf, * dpf, * epf;
   BZFILE * cpfbz2, * dpfbz2, * epfbz2;
   int32_t cbz2err, dbz2err, ebz2err;
   _FILE * fd;
   ssize_t oldsize,newsize;
   ssize_t bzctrllen,bzdatalen;
   u_char header[32],buf[8];
   u_char *old = NULL;
   u_char *_new = NULL;
   off_t oldpos,newpos;
   off_t ctrl[3];
   off_t lenread;
   off_t i;
   errno_t errno;

   /* fopen_dup patch file */
   if ((f = fopen_dup(patchfile, "rb")) == NULL)
      return err(1, "fopen_s(%s)", patchfile);

   /*
   File format:
      0   8   "BSDIFF40"
      8   8   X
      16   8   Y
      24   8   sizeof(newfile)
      32   X   bzip2(control block)
      32+X   Y   bzip2(diff block)
      32+X+Y   ???   bzip2(extra block)
   with control block a set of triples (x,y,z) meaning "add x bytes
   from oldfile to x bytes from the diff block; copy y bytes from the
   extra block; seek forwards in oldfile by z bytes".
   */

   /* _read header */
   if (fread_dup(header, 1, 32, f) < 32) {
      if (feof_dup(f))
      {
         fclose_dup(f);
         return errx(1, "Corrupt patch\n");
      }
      fclose_dup(f);
      return  err(1, "fread_dup(%s)", patchfile);
   }

   /* Check for appropriate magic */
   if (memcmp_dup(header, "BSDIFF40", 8) != 0)
   {
      fclose_dup(f);
      return errx(1, "Corrupt patch\n");
   }

   /* _read lengths from header */
   bzctrllen=offtin(header+8);
   bzdatalen=offtin(header+16);
   newsize=offtin(header+24);
   if((bzctrllen<0) || (bzdatalen<0) || (newsize<0))
   {
      fclose_dup(f);
      return errx(1,"Corrupt patch\n");
   }

   /* fclose_dup patch file and re-fopen_dup it via libbzip2 at the right places */
   if (fclose_dup(f))
      return err(1, "fclose_dup(%s)", patchfile);
   if ((cpf = fopen_dup( patchfile, "rb")) == 0)
      return err(1, "fopen_s(%s)", patchfile);
   if (fseek_dup(cpf, 32, SEEK_SET))
   {
      fclose_dup(cpf);
      return err(1, "fseeko(%s, %d)", patchfile, 32);
   }
   if ((cpfbz2 = BZ2_bzReadOpen(&cbz2err, cpf, 0, 0, NULL, 0)) == NULL)
   {
      fclose_dup(cpf);
      return errx(1, "BZ2_bzReadOpen, bz2err = %d", cbz2err);
   }
   if ((dpf = fopen_dup(patchfile, "rb")) == 0)
   {
      fclose_dup(cpf);
      return err(1, "fopen_s(%s)", patchfile);
   }
   if (fseek_dup(dpf, 32 + bzctrllen, SEEK_SET))
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      return err(1, "fseeko(%s, %d)", patchfile,
          (32 + bzctrllen));
   }
   if ((dpfbz2 = BZ2_bzReadOpen(&dbz2err, dpf, 0, 0, NULL, 0)) == NULL)
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      return errx(1, "BZ2_bzReadOpen, bz2err = %d", dbz2err);
   }
   if ((epf = fopen_dup(patchfile, "rb")) == 0)
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      return err(1, "fopen_s(%s)", patchfile);
   }
   if (fseek_dup(epf, 32 + bzctrllen + bzdatalen, SEEK_SET))
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      fclose_dup(epf);
      return err(1, "fseeko(%s, %d)", patchfile,
          (32 + bzctrllen + bzdatalen));
   }
   if ((epfbz2 = BZ2_bzReadOpen(&ebz2err, epf, 0, 0, NULL, 0)) == NULL)
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      fclose_dup(epf);
      return errx(1, "BZ2_bzReadOpen, bz2err = %d", ebz2err);
   }

   //org:
   //if(((fd=fopen_dup(oldfile,O_RDONLY,0))<0) ||
   //   ((oldsize=fseek_dup(fd,0,SEEK_END))==-1) ||
   //   ((old=memory_alloc(oldsize+1))==NULL) ||
   //   (fseek_dup(fd,0,SEEK_SET)!=0) ||
   //   (_read(fd,old,oldsize)!=oldsize) ||
   //   (fclose_dup(fd)==-1)) return err(1,"%s",oldfile);
   //new:
   //_read in chunks, don't rely on _read always returns full data!
   if(((fd=fopen_dup(oldfile,"rb"))==0) ||
      ((oldsize = (ssize_t) fseek_dup(fd,0,SEEK_END))==-1) ||
      ((old=(u_char*)memory_alloc(oldsize+1))==NULL) ||
      (fseek_dup(fd,0,SEEK_SET)!=0))
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      fclose_dup(epf);
      if(fd != 0)
      {
         fclose_dup(fd);
      }
      if(old != NULL)
      {
         memory_free_dbg(old, 0);
      }
      return err(1,"%s",oldfile);
   }
   
   size_t r = oldsize;
   
   while(r > 0 && (i = (off_t) fread_dup(old+oldsize-r,r, 1, fd)) > 0)
      r-=i;

   if (r>0 || fclose_dup(fd)==-1)
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      fclose_dup(epf);
      memory_free_dbg(old, 0);
      return err(1,"%s",oldfile);
   }

   if((_new=(u_char*)memory_alloc(newsize+1))==NULL)
   {
      fclose_dup(cpf);
      fclose_dup(dpf);
      fclose_dup(epf);
      fclose_dup(fd);
      memory_free_dbg(old, 0);
      return err(1,NULL);
   }

   oldpos=0;newpos=0;
   while(newpos < newsize) {
      /* _read control data */
      for(i=0;i<=2;i++) {
         lenread = BZ2_bzRead(&cbz2err, cpfbz2, buf, 8);
         if ((lenread < 8) || ((cbz2err != BZ_OK) &&
             (cbz2err != BZ_STREAM_END)))
         {
            fclose_dup(cpf);
            fclose_dup(dpf);
            fclose_dup(epf);
            fclose_dup(fd);
            memory_free_dbg(_new, 0);
            memory_free_dbg(old, 0);
            return errx(1, "Corrupt patch\n");
         }
         ctrl[i]=offtin(buf);
      };

      /* Sanity-check */
      if(newpos + ctrl[0] > newsize)
      {
         fclose_dup(cpf);
         fclose_dup(dpf);
         fclose_dup(epf);
         fclose_dup(fd);
         memory_free_dbg(_new, 0);
         memory_free_dbg(old, 0);
         return errx(1,"Corrupt patch\n");
      }

      /* _read diff string */
      lenread = BZ2_bzRead(&dbz2err, dpfbz2, _new + newpos, (int32_t)ctrl[0]);
      if ((lenread < ctrl[0]) ||
          ((dbz2err != BZ_OK) && (dbz2err != BZ_STREAM_END)))
      {
         fclose_dup(cpf);
         fclose_dup(dpf);
         fclose_dup(epf);
         fclose_dup(fd);
         memory_free_dbg(_new, 0);
         memory_free_dbg(old, 0);
         return errx(1, "Corrupt patch\n");
      }

      /* add old data to diff string */
      for(i=0;i<ctrl[0];i++)
         if((oldpos+i>=0) && (oldpos + i <oldsize))
            _new[newpos+i]+=old[oldpos+i];

      /* Adjust pointers */
      newpos+=ctrl[0];
      oldpos+=ctrl[0];

      /* Sanity-check */
      if(newpos + ctrl[1] >newsize)
      {
         fclose_dup(cpf);
         fclose_dup(dpf);
         fclose_dup(epf);
         fclose_dup(fd);
         memory_free_dbg(_new, 0);
         memory_free_dbg(old, 0);
         return errx(1,"Corrupt patch\n");
      }

      /* _read extra string */
      lenread = BZ2_bzRead(&ebz2err, epfbz2, _new + newpos, (int32_t)ctrl[1]);
      if ((lenread < ctrl[1]) ||
          ((ebz2err != BZ_OK) && (ebz2err != BZ_STREAM_END)))
      {
         fclose_dup(cpf);
         fclose_dup(dpf);
         fclose_dup(epf);
         fclose_dup(fd);
         memory_free_dbg(_new, 0);
         memory_free_dbg(old, 0);
         return errx(1, "Corrupt patch\n");
      }

      /* Adjust pointers */
         newpos+=ctrl[1];
         oldpos+=ctrl[2];
      };

   /* Clean up the bzip2 reads */
   BZ2_bzReadClose(&cbz2err, cpfbz2);
   BZ2_bzReadClose(&dbz2err, dpfbz2);
   BZ2_bzReadClose(&ebz2err, epfbz2);
   if (fclose_dup(cpf) || fclose_dup(dpf) || fclose_dup(epf))
   {
      memory_free_dbg(_new, 0);
      memory_free_dbg(old, 0);
      return err(1, "fclose_dup(%s)", patchfile);
   }

   /* _write the new file */
   //org:
   //if(((fd=fopen_dup(newfile,O_CREAT|O_TRUNC|O_WRONLY,0666))<0) ||
   //new:
   if(((fd=fopen_dup(newfile,"wb")) == 0) ||
      (fwrite_dup(_new,newsize,1, fd)!=newsize) || (fclose_dup(fd)==-1))
   {
      memory_free_dbg(_new, 0);
      memory_free_dbg(old, 0);
      return err(1,"%s",newfile);
   }

   memory_free_dbg(_new, 0);
   memory_free_dbg(old, 0);

   return 0;
}
