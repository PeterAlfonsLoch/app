//
//  c_os_crypt.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 11/10/12.
//
//
#include "framework.h"

/*

int crypt_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, ::primitive::memory & memKeyDataParam)
{
    
   ::primitive::memory memKeyData(memKeyDataParam);
    
   ::count iSize = memKeyDataParam.get_size();
    
   memKeyData.allocate(32);
    
   if(iSize < 32)
   {
        
      memset(&((byte *) memKeyData.get_data())[iSize], 0, 32 - iSize);
        
   }
    
   CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    
   CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);
    
   CFDataRef keyData = memKeyData.get_os_cf_data();
    
   CFErrorRef error = NULL;
    
   SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);
    
   if(error != NULL)
   {
        
      CFRelease(parameters);
        
      CFRelease(keyData);
        
      CFRelease(error);
        
      return 0;
        
   }
    
   SecTransformRef transform = SecEncryptTransformCreate(key, &error);
    
   if(error != NULL)
   {
        
      CFRelease(parameters);
        
      CFRelease(keyData);
        
      CFRelease(key);
        
      CFRelease(error);
        
      return 0;
        
   }
    
   SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);
    
   if(error != NULL)
   {
        
      CFRelease(transform);
        
      CFRelease(keyData);
        
      CFRelease(parameters);
        
      CFRelease(key);
        
      CFRelease(error);
        
      return 0;
        
   }
    
   unsigned char iv[8] = {1,2,3,4,5,6,7,8};
    
   CFDataRef dataIv = CFDataCreate(kCFAllocatorDefault, (const UInt8 *) iv, sizeof(iv));
 
   SecTransformSetAttribute(transform, kSecIVKey, dataIv, &error);
                             
   if(error != NULL)
   {
        
      CFRelease(dataIv);
                                        
      CFRelease(transform);
                                        
      CFRelease(parameters);
        
      CFRelease(keyData);
                                        
      CFRelease(key);
                                        
      CFRelease(error);
                                        
      return 0;
                                        
   }
                                    
   CFDataRef dataIn = storageDecrypt.get_os_cf_data();
                             
   SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);
                             
   if(error != NULL)
   {

      CFRelease(dataIn);
                                 
      CFRelease(dataIv);
                                 
      CFRelease(transform);
        
      CFRelease(parameters);
        
      CFRelease(keyData);
        
      CFRelease(key);
        
      CFRelease(error);
        
      return 0;
    
   }
    
   /* Encrypt the data. */
                            
 /*  CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);
                             
   if(error != NULL)
   {
        
      CFRelease(dataIv);
                                 
      CFRelease(dataIn);
        
      CFRelease(transform);
        
      CFRelease(parameters);
        
      CFRelease(keyData);
        
      CFRelease(key);
        
      CFRelease(error);
        
      return 0;
    
   }

   ::primitive::memory memory;
                             
   storageEncrypt.set_os_cf_data(data);
                             
   CFRelease(dataIv);
                                    
   CFRelease(data);
                             
   CFRelease(dataIn);
                             
   CFRelease(transform);
                             
   CFRelease(keyData);
                             
   CFRelease(parameters);
                             
   CFRelease(key);
                             
    return (int) storageEncrypt.get_size();

}

int crypt_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, ::primitive::memory & memKeyDataParam)
{
   
   ::primitive::memory memKeyData(memKeyDataParam);
   
   ::count iSize = memKeyDataParam.get_size();
   
   memKeyData.allocate(32);
   
   if(iSize < 32)
   {
      
      memset(&((byte *) memKeyData.get_data())[iSize], 0, 32 - iSize);
      
   }
   
   CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
   
   CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);
   
   CFDataRef keyData = memKeyData.get_os_cf_data();
   
   CFErrorRef error = NULL;
   
   SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);
   
   if(error != NULL)
   {
      
      CFRelease(parameters);
      
      CFRelease(keyData);
      
      CFRelease(error);
      
      return 0;
      
   }
   
   SecTransformRef transform = SecDecryptTransformCreate(key, &error);
   
   if(error != NULL)
   {
      
      CFRelease(parameters);
      
      CFRelease(keyData);
      
      CFRelease(key);
      
      CFRelease(error);
      
      return 0;
      
   }
   
   SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);
   
   if(error != NULL)
   {
      
      CFRelease(transform);
      
      CFRelease(keyData);
      
      CFRelease(parameters);
      
      CFRelease(key);
      
      CFRelease(error);
      
      return 0;
      
   }
   
   unsigned char iv[8] = {1,2,3,4,5,6,7,8};
   
   CFDataRef dataIv = CFDataCreate(kCFAllocatorDefault, (const UInt8 *) iv, sizeof(iv));
   
   SecTransformSetAttribute(transform, kSecIVKey, dataIv, &error);
   
   if(error != NULL)
   {
      
      CFRelease(dataIv);
      
      CFRelease(transform);
      
      CFRelease(parameters);
      
      CFRelease(keyData);
      
      CFRelease(key);
      
      CFRelease(error);
      
      return 0;
      
   }
   
   CFDataRef dataIn = storageEncrypt.get_os_cf_data();
   
   SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);
   
   if(error != NULL)
   {
      
      CFRelease(dataIn);
      
      CFRelease(dataIv);
      
      CFRelease(transform);
      
      CFRelease(parameters);
      
      CFRelease(keyData);
      
      CFRelease(key);
      
      CFRelease(error);
      
      return 0;
      
   }
   
   /* Decrypt the data. */
   
/*   CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);
   
   if(error != NULL)
   {
      
      CFRelease(dataIv);
      
      CFRelease(dataIn);
      
      CFRelease(transform);
      
      CFRelease(parameters);
      
      CFRelease(keyData);
      
      CFRelease(key);
      
      CFRelease(error);
      
      return 0;
      
   }
   
   ::primitive::memory memory;
   
   storageDecrypt.set_os_cf_data(data);
   
   CFRelease(dataIv);
   
   CFRelease(data);
   
   CFRelease(dataIn);
   
   CFRelease(transform);
   
   CFRelease(keyData);
   
   CFRelease(parameters);
   
   CFRelease(key);
   
   return (int) storageDecrypt.get_size();
   
}

*/