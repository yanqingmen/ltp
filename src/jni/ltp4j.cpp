#include "segmentor/segment_dll.h"
#include "postagger/postag_dll.h"
#include "parser.n/parser_dll.h"
#include "ner/ner_dll.h"
#include "srl/SRL_DLL.h"

#include "ltp4j.h"

// handles
// segmentor handle
typedef void *SegmentorHandle;
// parser handle
typedef void *ParserHandle;
// postagger handle
typedef void *PosTaggerHandle;


// helper functions
// set handle
void setHandle(JNIEnv *jenv,  jlongArray jhandle,  void* handle) {
#ifdef __APPLE__
  jlong out = (long) handle;
#else
  int64_t out = (int64_t) handle;
#endif
  jenv->SetLongArrayRegion(jhandle, 0, 1, &out);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    createSegmentor
 * Signature: (Ljava/lang/String;Ljava/lang/String;[J)V
 */
JNIEXPORT void JNICALL Java_edu_hit_ir_ltp_jni_LtpJNI_createSegmentor
  (JNIEnv  *jenv, jclass jcls, jstring  jmodel_path, jstring jlexicon_path , jlongArray jhandle) {
    SegmentorHandle result;
    const char* model_path = jenv->GetStringUTFChars(jmodel_path, 0);
    const char* lexicon_path = nullptr;
    if(jlexicon_path != nullptr) {
        lexicon_path = jenv->GetStringUTFChars(jlexicon_path, 0);
    }
    
    result = segmentor_create_segmentor(model_path, lexicon_path);
    setHandle(jenv, jhandle, result);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    releaseSegmentor
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_edu_hit_ir_ltp_jni_LtpJNI_releaseSegmentor
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
    SegmentorHandle handle = (SegmentorHandle) jhandle;
    return segmentor_release_segmentor(handle);
}

/*
 * Class:     edu_hit_ir_ltp_jni_LtpJNI
 * Method:    segment
 * Signature: (JLjava/lang/String;)Ljava/util/List;
 */
JNIEXPORT jobjectArray  JNICALL Java_edu_hit_ir_ltp_jni_LtpJNI_segment
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