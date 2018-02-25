package edu.hit.ir.ltp4j;

import edu.hit.ir.ltp4j.jni.LtpJNI;

/**
 * ltp dep parser
 * Created by hzx on 18-1-14.
 */
public class LTPParser {
    // ltp parser handle
    private long handle;

    /**
     *
     * @param modelPath parser model path
     * @return new ltp parser
     */
    public static LTPParser createParser(String modelPath) {
        long[] handle = new long[1];
        LtpJNI.createParser(modelPath, handle);
        return new LTPParser(handle[0]);
    }


    /**
     *
     * @param handle
     */
    private LTPParser(long handle) {
        this.handle = handle;
    }

    public DepRel[] parse(String[] words, String[] tags) {
        int[][] heads = new int[1][];
        String[][] rels = new String[1][];
        LtpJNI.parse(this.handle, words, tags, heads, rels);
        DepRel[] depRels = new DepRel[words.length];

        for(int i=0; i<words.length; i++) {
            int head = heads[0][i];
            String rel = rels[0][i];
            DepRel depRel = new DepRel(rel, head);
            depRels[i] = depRel;
        }

        return depRels;
    }


    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        dispose();
    }

    private synchronized void dispose() {
        if (this.handle != 0L) {
            LtpJNI.releaseParser(this.handle);
            this.handle = 0;
        }
    }

    /**
     *
     */
    public static class DepRel {
        int head;
        String rel;

        public DepRel(String rel, int head) {
            this.rel = rel;
            this.head = head;
        }

        public int getHead() {
            return head;
        }

        public String getRel() {
            return rel;
        }

        public String toString() {
            return head + ":" + rel;
        }
    }
}
