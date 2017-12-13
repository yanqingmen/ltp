package edu.hit.ir.ltp.jni;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;


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

    
}
