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
}
