/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_freerdp_freerdpcore_services_LibFreeRDP */

#ifndef _Included_com_freerdp_freerdpcore_services_LibFreeRDP
#define _Included_com_freerdp_freerdpcore_services_LibFreeRDP
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_new
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1new
  (JNIEnv *, jclass);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_free
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1free
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_connect
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1connect
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_disconnect
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1disconnect
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_cancel_connection
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1cancel_1connection
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_connection_info
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIIZILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1connection_1info
  (JNIEnv *, jclass, jint, jstring, jstring, jstring, jstring, jint, jint, jint, jint, jboolean, jint, jstring);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_performance_flags
 * Signature: (IZZZZZZZ)V
 */
JNIEXPORT void JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1performance_1flags
  (JNIEnv *, jclass, jint, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_advanced_settings
 * Signature: (ILjava/lang/String;Ljava/lang/String;ZZZZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1advanced_1settings
  (JNIEnv *, jclass, jint, jstring, jstring, jboolean, jboolean, jboolean, jboolean);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_data_directory
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1data_1directory
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_clipboard_redirection
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1clipboard_1redirection
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_sound_redirection
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1sound_1redirection
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_microphone_redirection
 * Signature: (IZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1microphone_1redirection
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_drive_redirection
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1drive_1redirection
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_set_gateway_info
 * Signature: (ILjava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1set_1gateway_1info
  (JNIEnv *, jclass, jint, jstring, jint, jstring, jstring, jstring);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_update_graphics
 * Signature: (ILandroid/graphics/Bitmap;IIII)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1update_1graphics
  (JNIEnv *, jclass, jint, jobject, jint, jint, jint, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_send_cursor_event
 * Signature: (IIII)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1send_1cursor_1event
  (JNIEnv *, jclass, jint, jint, jint, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_send_key_event
 * Signature: (IIZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1send_1key_1event
  (JNIEnv *, jclass, jint, jint, jboolean);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_send_unicodekey_event
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1send_1unicodekey_1event
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_send_clipboard_data
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1send_1clipboard_1data
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     com_freerdp_freerdpcore_services_LibFreeRDP
 * Method:    freerdp_get_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_freerdp_freerdpcore_services_LibFreeRDP_freerdp_1get_1version
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
