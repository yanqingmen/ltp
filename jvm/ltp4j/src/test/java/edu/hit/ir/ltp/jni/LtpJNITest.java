package edu.hit.ir.ltp.jni;


import java.util.Arrays;

/**
* LtpJNI Tester. 
* 
* @author <Authors name> 
* @since <pre>一月 10, 2018</pre> 
* @version 1.0 
*/ 
public class LtpJNITest {
    public static void main(String[] args) {
        String path = "/home/hzx/workspace/ltp/ltp_data_v3.4.0/cws.model";
        long[] handle = new long[1];
        // create segmentor
        LtpJNI.createSegmentor(path, null, handle);
        // test segment
        String test = "今天中午吃什么";
        String[] words = LtpJNI.segment(handle[0], test);
        System.out.println(Arrays.toString(words));
        // release segmentor
        LtpJNI.releaseSegmentor(handle[0]);
    }

} 
