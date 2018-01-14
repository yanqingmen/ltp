package edu.hit.ir.ltp4j;

import edu.hit.ir.ltp4j.jni.LtpJNI;

/**
 * ltp segmentor
 * Created by hzx on 18-1-14.
 */
public class LTPSegmentor {
    // segmentor handle
    private long handle;

    /**
     *
     * @param modelPath
     * @return
     */
    public static LTPSegmentor createSegmentor(String modelPath) {
        long[] handle = new long[1];
        LtpJNI.createSegmentor(modelPath, null, handle);
        return new LTPSegmentor(handle[0]);
    }


    /**
     *
     * @param modelPath
     * @param lexiconPath
     * @return
     */
    public static LTPSegmentor createSegmentor(String modelPath, String lexiconPath) {
        long[] handle = new long[1];
        LtpJNI.createSegmentor(modelPath, lexiconPath, handle);
        return new LTPSegmentor(handle[0]);
    }

    /**
     *
     * @param handle
     */
    private LTPSegmentor(long handle) {
        this.handle = handle;
    }

    /**
     *
     * @param text
     * @return
     */
    public String[] segment(String text) {
        String[] words = LtpJNI.segment(this.handle, text);
        return words;
    }


    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        dispose();
    }

    public synchronized void dispose() {
        if (this.handle != 0L) {
            LtpJNI.releaseSegmentor(this.handle);
            this.handle = 0;
        }
    }
}
