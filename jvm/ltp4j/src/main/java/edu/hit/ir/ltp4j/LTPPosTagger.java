package edu.hit.ir.ltp4j;

import edu.hit.ir.ltp4j.jni.LtpJNI;

/**
 * ltp pos tagger
 * Created by hzx on 18-1-14.
 */
public class LTPPosTagger {
    // postagger handle
    private long handle;

    /**
     *
     * @param modelPath
     * @return
     */
    public static LTPPosTagger createPosTagger(String modelPath) {
        long[] handle = new long[1];
        LtpJNI.createPosTagger(modelPath, null, handle);
        return new LTPPosTagger(handle[0]);
    }

    /**
     *
     * @param modelPath
     * @param lexiconPath
     * @return
     */
    public static LTPPosTagger createPosTagger(String modelPath, String lexiconPath) {
        long[] handle = new long[1];
        LtpJNI.createPosTagger(modelPath, lexiconPath, handle);
        return new LTPPosTagger(handle[0]);
    }


    /**
     *
     * @param handle
     */
    private LTPPosTagger(long handle) {
        this.handle = handle;
    }


    public String[] getPosTags(String[] words) {
        String[] tags = LtpJNI.postag(this.handle, words);
        return tags;
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        dispose();
    }

    private synchronized void dispose() {
        if (this.handle != 0L) {
            LtpJNI.releasePosTagger(this.handle);
            this.handle = 0;
        }
    }
}
