package edu.hit.ir.ltp.jni;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.util.List;


/**
 * jni func for ltp
 * Created by hzx on 2017/12/13.
 */
public class LtpJNI {
    static Log logger = LogFactory.getLog(LtpJNI.class);

    static {
        try {
            NativeLibLoader.initNativeLibs();
        }catch (Exception ex) {
            logger.error("Failed to load native library", ex);
            throw new RuntimeException(ex);
        }
    }


    /**
     * create segmentor with lexicon
     * @param path
     * @param lexiconPath
     * @param handle  handle of segmentor
     * @return
     */
    public final static native void createSegmentor(String path, String lexiconPath, long[] handle);


    /**
     * release segmentor
     * @param handle
     * @return
     */
    public final static native int releaseSegmentor(long handle);


    /**
     * segment
     * @param handle
     * @param line
     * @return
     */
    public final static native String[] segment(long handle, String line);

    /**
     *
     * @param path
     * @param lexiconPath
     * @param handle
     */
    public final static native void createPosTagger(String path, String lexiconPath, long[] handle);

    /**
     *
     * @param handle
     * @return
     */
    public final static native int releasePosTagger(long handle);

    /**
     *
     * @param handle
     * @param words
     * @return
     */
    public final static native String[] postag(long handle, String[] words);

    /**
     *
     * @param path
     * @param handle
     */
    public final static native void createParser(String path, long[] handle);

    /**
     *
     * @param handle
     * @return
     */
    public final static native int releaseParser(long handle);

    /**
     *
     * @param handle parser handle
     * @param words words array
     * @param postags pos array
     * @param heads depRel heads handler
     * @param depRels depRels handler
     * @return
     */
    public final static native int parse(long handle,
                                         String[] words,
                                         String[] postags,
                                         int[][] heads,
                                         String[][] depRels);
}
