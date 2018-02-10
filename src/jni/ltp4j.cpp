#include "segmentor/segment_dll.h"
#include "postagger/postag_dll.h"
#include "parser.n/parser_dll.h"

#include "ltp4j.h"

#include<stdio.h>

// handles
// segmentor handle
typedef void *SegmentorHandle;
// parser handle
typedef void *ParserHandle;
// postagger handle
typedef void *PosTaggerHandle;


// helper functions
// set handle
void set_handle(JNIEnv *jenv,  jlongArray jhandle,  void* handle) {
#ifdef __APPLE__
  jlong out = (long) handle;
#else
  int64_t out = (int64_t) handle;
#endif
  jenv->SetLongArrayRegion(jhandle, 0, 1, &out);
}

void set_string_vector(JNIEnv *jenv, jobjectArray jstring_array,  std::vector<std::string>& string_vector) {
    int jlen = jenv->GetArrayLength(jstring_array);
    for(int i=0; i<jlen; i++) {
        jstring jitem = (jstring) jenv->GetObjectArrayElement(jstring_array, i);
        const char *item = jenv->GetStringUTFChars(jitem, 0);
        string_vector.push_back(std::string(item));
        if (item != NULL) jenv->ReleaseStringUTFChars(jitem, item);
    }
}

void set_int_vector(JNIEnv *jenv, jintArray jint_array,  std::vector<int>& int_vector) {
    int jlen = jenv->GetArrayLength(jint_array);
    jint *int_array = jenv->GetIntArrayElements(jint_array, 0);
    for(int i=0; i<jlen; i++) {
        int_vector.push_back(int_array[i]);
    }
    // release
    jenv->ReleaseIntArrayElements(jint_array, int_array, 0);
}

jobjectArray get_jstring_array(JNIEnv *jenv, std::vector<std::string> string_vector) {
    jobjectArray jstring_array = (jobjectArray) jenv->NewObjectArray(
            string_vector.size(), jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
    for(int i=0; i<string_vector.size(); i++) {
        jenv->SetObjectArrayElement(jstring_array, i, jenv->NewStringUTF(string_vector[i].c_str()));
    }
    
    return jstring_array;
}

jintArray get_jint_array(JNIEnv *jenv, std::vector<int> int_vector) {
    jintArray jint_array = jenv->NewIntArray(int_vector.size());
    const int* int_array = &int_vector[0];
    jenv->SetIntArrayRegion(jint_array, 0, int_vector.size(), (const jint*) int_array);
    
    return jint_array;
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    createSegmentor
 * Signature: (Ljava/lang/String;Ljava/lang/String;[J)V
 */
JNIEXPORT void JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_createSegmentor
  (JNIEnv  *jenv, jclass jcls, jstring  jmodel_path, jstring jlexicon_path , jlongArray jhandle) {
    SegmentorHandle result;
    const char* model_path = jenv->GetStringUTFChars(jmodel_path, 0);
    const char* lexicon_path = nullptr;
    if(jlexicon_path != nullptr) {
        lexicon_path = jenv->GetStringUTFChars(jlexicon_path, 0);
    }
    
    result = segmentor_create_segmentor(model_path, lexicon_path);
    set_handle(jenv, jhandle, result);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    releaseSegmentor
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_releaseSegmentor
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
    SegmentorHandle handle = (SegmentorHandle) jhandle;
    return segmentor_release_segmentor(handle);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    segment
 * Signature: (JLjava/lang/String;)Ljava/util/List;
 */
JNIEXPORT jobjectArray  JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_segment
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jtext) {
    SegmentorHandle handle = (SegmentorHandle) jhandle;
    const char* text =  jenv->GetStringUTFChars(jtext, 0);
    std::string line(text);
    std::vector<std::string> words;
    int flag = segmentor_segment(handle, line, words);
    jobjectArray jwords = (jobjectArray) jenv->NewObjectArray(
            words.size(), jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
    for(int i=0; i<words.size(); i++) {
        jenv->SetObjectArrayElement(jwords, i, jenv->NewStringUTF(words[i].c_str()));
    }
    
    return jwords;
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    createPosTagger
 * Signature: (Ljava/lang/String;Ljava/lang/String;[J)V
 */
JNIEXPORT void JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_createPosTagger
  (JNIEnv *jenv, jclass jcls, jstring jmodel_path, jstring jlexicon_path, jlongArray jhandle) {
    PosTaggerHandle handle;
    const char* model_path = jenv->GetStringUTFChars(jmodel_path, 0);
    const char* lexicon_path = nullptr;
    if(jlexicon_path != nullptr) {
        lexicon_path = jenv->GetStringUTFChars(jlexicon_path, 0);
    }
    
    handle = postagger_create_postagger(model_path, lexicon_path);
    set_handle(jenv, jhandle, handle);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    releasePosTagger
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_releasePosTagger
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
    PosTaggerHandle handle = (PosTaggerHandle) jhandle;
    return postagger_release_postagger(handle);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    postag
 * Signature: (J[Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_postag
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jobjectArray jwords_array) {
    PosTaggerHandle handle = (PosTaggerHandle) jhandle;
    
    std::vector<std::string> words;
    std::vector<std::string> tags;
    set_string_vector(jenv, jwords_array, words);    
    
    int flag = postagger_postag(handle, words, tags);
    jobjectArray jtags = (jobjectArray) jenv->NewObjectArray(
            tags.size(), jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
    for(int i=0; i<tags.size(); i++) {
        jenv->SetObjectArrayElement(jtags, i, jenv->NewStringUTF(tags[i].c_str()));
    }
    
    return jtags;
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    createParser
 * Signature: (Ljava/lang/String;[J)V
 */
JNIEXPORT void JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_createParser
  (JNIEnv *jenv, jclass jcls, jstring jmodel_path, jlongArray jhandle) {
    ParserHandle handle;
    const char* model_path = jenv->GetStringUTFChars(jmodel_path, 0);
    
    handle = parser_create_parser(model_path);
    set_handle(jenv, jhandle, handle);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    releaseParser
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_releaseParser
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
   ParserHandle handle = (ParserHandle) jhandle;
   return parser_release_parser(handle);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    parse
 * Signature: (J[Ljava/lang/String;[Ljava/lang/String;[[I[[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_edu_hit_ir_ltp4j_jni_LtpJNI_parse
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jobjectArray jwords, jobjectArray jtags, jobjectArray jheads_handle, jobjectArray jdeprels_handle) {
    ParserHandle handle = (ParserHandle) jhandle;
    std::vector<std::string> words;
    std::vector<std::string> tags;
    set_string_vector(jenv, jwords, words);
    set_string_vector(jenv, jtags, tags);
    
    std::vector<int> heads;
    std::vector<std::string> deprels;
    
    int ret = parser_parse(handle, words, tags, heads, deprels);
    jintArray jheads = get_jint_array(jenv, heads);
    jobjectArray jdeprels =  get_jstring_array(jenv, deprels);
    
    jenv->SetObjectArrayElement(jheads_handle, 0, jheads);
    jenv->SetObjectArrayElement(jdeprels_handle, 0, jdeprels);
    
    return ret;
}