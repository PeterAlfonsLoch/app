/* inflate.h -- internal inflate state definition
 * Copyright (C) 1995-2004 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

/* define NO_GZIP when compiling if you want to disable gzip header and
   trailer decoding by inflate().  NO_GZIP would be used to avoid linking in
   the crc code when it is not needed.  For shared libraries, gzip decoding
   should be left enabled. */
#ifndef NO_GZIP
#  define GUNZIP
#endif

/* Possible inflate modes between inflate() calls */
typedef enum {
    HEAD,       /* i: waiting for magic header */
    FLAGS,      /* i: waiting for method and flags (gzip) */
    TIME,       /* i: waiting for modification time (gzip) */
    OS,         /* i: waiting for extra flags and operating system (gzip) */
    EXLEN,      /* i: waiting for extra length (gzip) */
    EXTRA,      /* i: waiting for extra bytes (gzip) */
    NAME,       /* i: waiting for end of file name (gzip) */
    COMMENT,    /* i: waiting for end of comment (gzip) */
    HCRC,       /* i: waiting for header crc (gzip) */
    DICTID,     /* i: waiting for dictionary check value */
    DICT,       /* waiting for inflateSetDictionary() call */
        TYPE,       /* i: waiting for type bits, including last-flag bit */
        TYPEDO,     /* i: same, but skip check to exit inflate on new block */
        STORED,     /* i: waiting for stored size (length and complement) */
        COPY,       /* i/o: waiting for input or output to copy stored block */
        TABLE,      /* i: waiting for dynamic block table lengths */
        LENLENS,    /* i: waiting for code length code lengths */
        CODELENS,   /* i: waiting for length/lit and distance code lengths */
            LEN,        /* i: waiting for length/lit code */
            LENEXT,     /* i: waiting for length extra bits */
            DIST,       /* i: waiting for distance code */
            DISTEXT,    /* i: waiting for distance extra bits */
            MATCH,      /* o: waiting for output space to copy string */
            LIT,        /* o: waiting for output space to write literal */
    CHECK,      /* i: waiting for 32-bit check value */
    LENGTH,     /* i: waiting for 32-bit length (gzip) */
    DONE,       /* finished check, done -- remain here until reset */
    BAD,        /* got a data error -- remain here until reset */
    MEM,        /* got an inflate() primitive::memory error -- remain here until reset */
    SYNC        /* looking for synchronization bytes to restart inflate() */
} inflate_mode;

/*
    State transitions between above modes -

    (most modes can go to the BAD or MEM mode -- not shown for clarity)

    Process header:
        HEAD -> (gzip) or (zlib)
        (gzip) -> FLAGS -> TIME -> OS -> EXLEN -> EXTRA -> NAME
        NAME -> COMMENT -> HCRC -> TYPE
        (zlib) -> DICTID or TYPE
        DICTID -> DICT -> TYPE
    Read deflate blocks:
            TYPE -> STORED or TABLE or LEN or CHECK
            STORED -> COPY -> TYPE
            TABLE -> LENLENS -> CODELENS -> LEN
    Read deflate codes:
                LEN -> LENEXT or LIT or TYPE
                LENEXT -> DIST -> DISTEXT -> MATCH -> LEN
                LIT -> LEN
    Process trailer:
        CHECK -> LENGTH -> DONE
 */

/* state maintained between inflate() calls.  Approximately 7K bytes. */
struct inflate_state {
    inflate_mode mode;          /* current inflate mode */
    int32_t last;                   /* true if processing last block */
    int32_t wrap;                   /* bit 0 true for zlib, bit 1 true for gzip */
    int32_t havedict;               /* true if dictionary provided */
    int32_t flags;                  /* gzip header method and flags (0 if zlib) */
    uint32_t dmax;              /* zlib header max distance (INFLATE_STRICT) */
    uint32_t check;        /* protected copy of check value */
    uint_ptr total;        /* protected copy of output count */
    gz_headerp head;            /* where to save gzip header information */
        /* sliding window */
    uint32_t wbits;             /* log base 2 of requested window size */
    uint32_t wsize;             /* window size or zero if not using window */
    uint_ptr whave;             /* valid bytes in the window */
    uint_ptr write;             /* window write index */
    uchar FAR *window;  /* allocated sliding window, if needed */
        /* bit accumulator */
    uint32_t hold;         /* input bit accumulator */
    uint_ptr bits;              /* number of bits in "in" */
        /* for string and stored block copying */
    uint_ptr length;            /* literal or length of data to copy */
    uint32_t offset;            /* distance back to copy string from */
        /* for table and code decoding */
    uint32_t extra;             /* extra bits needed */
        /* fixed and dynamic code tables */
    code const FAR *lencode;    /* starting table for length/literal codes */
    code const FAR *distcode;   /* starting table for distance codes */
    uint32_t lenbits;           /* index bits for lencode */
    uint32_t distbits;          /* index bits for distcode */
        /* dynamic table building */
    uint32_t ncode;             /* number of code length code lengths */
    uint32_t nlen;              /* number of length code lengths */
    uint32_t ndist;             /* number of distance code lengths */
    uint32_t have;              /* number of code lengths in lens[] */
    code FAR *next;             /* next available space in codes[] */
    uint16_t lens[320];   /* temporary storage for code lengths */
    uint16_t work[288];   /* work area for code table building */
    code codes[ENOUGH];         /* space for code tables */
};
