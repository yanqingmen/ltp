package edu.hit.ir.ltp4j;


import java.util.Arrays;

/**
* LTPSegmentor Tester. 
* 
* @author <Authors name> 
* @since <pre>一月 14, 2018</pre> 
* @version 1.0 
*/ 
public class LTPSegmentorTest {
    public static void main(String[] args) {
        String modelPath = "E:\\data\\ltp_data_v3.4.0\\cws.model";
        LTPSegmentor ltpSegmentor = LTPSegmentor.createSegmentor(modelPath);

        String testQuery = "明天是星期几？";
        String[] words = ltpSegmentor.segment(testQuery);
        System.out.println(Arrays.asList(words));
    }
} 
