#pragma once


/*
* Whirlpool-specific definitions.
*/

#define NESSIE_DIGESTBYTES 64
#define NESSIE_DIGESTBITS  (8*NESSIE_DIGESTBYTES) /* 512 */

#define NESSIE_WBLOCKBYTES 64
#define NESSIE_WBLOCKBITS  (8*NESSIE_WBLOCKBYTES) /* 512 */

#define NESSIE_LENGTHBYTES 32
#define NESSIE_LENGTHBITS  (8*NESSIE_LENGTHBYTES) /* 256 */

typedef struct NESSIEstruct {
   uint8_t  bitLength[NESSIE_LENGTHBYTES]; /* global number of hashed bits (256-bit counter) */
   uint8_t  buffer[NESSIE_WBLOCKBYTES];   /* buffer of data to hash */
   int32_t bufferBits;              /* current number of bits on the buffer */
   int32_t bufferPos;              /* current (possibly incomplete) byte slot on the buffer */
   uint64_t hash[NESSIE_DIGESTBYTES / 8];    /* the hashing state */
} NESSIEstruct;


CLASS_DECL_BASE void NESSIEinit(struct NESSIEstruct * const structpointer);
CLASS_DECL_BASE void NESSIEadd(const uchar * const source, uint_ptr sourceBits, struct NESSIEstruct * const structpointer);
CLASS_DECL_BASE void NESSIEfinalize(struct NESSIEstruct * const structpointer, uchar * const result);

string crypt_nessie(const char * psz);





