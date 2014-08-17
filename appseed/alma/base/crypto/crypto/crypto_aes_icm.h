/*
 * aes_icm.h
 *
 * Header for AES Integer Counter Mode.
 *
 * David A. McGrew
 * Cisco Systems, Inc.
 *
 */
#pragma once


#ifndef AES_ICM_H
#define AES_ICM_H

typedef struct {
  v128_t   counter;                /* holds the counter value          */
  v128_t   offset;                 /* initial offset value             */
  v128_t   keystream_buffer;       /* buffers bytes of keystream       */
  aes_expanded_key_t expanded_key; /* the cipher key                   */
  int32_t      bytes_in_buffer;        /* number of unused bytes in buffer */
} aes_icm_ctx_t;


err_status_t
aes_icm_context_init(aes_icm_ctx_t *ca,
           const uchar *key); 

err_status_t
aes_icm_set_iv(aes_icm_ctx_t *ca, void *iv);

err_status_t
aes_icm_encrypt(aes_icm_ctx_t *ca,
      uchar *buf, uint32_t *bytes_to_encr);

err_status_t
aes_icm_output(aes_icm_ctx_t *ca,
          uchar *buf, int32_t bytes_to_output);

err_status_t 
aes_icm_dealloc(cipher_t *ca);
 
err_status_t 
aes_icm_encrypt_ismacryp(aes_icm_ctx_t *ca, 
          uchar *buf, 
          uint32_t *enc_len, 
          int32_t forIsmacryp);
 
err_status_t 
aes_icm_alloc_ismacryp(cipher_t **ca, 
             int32_t key_len, 
             int32_t forIsmacryp);

#endif /* AES_ICM_H */

