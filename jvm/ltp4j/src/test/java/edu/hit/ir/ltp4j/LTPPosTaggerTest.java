package edu.hit.ir.ltp4j;


import java.util.Arrays;

/**
* LTPPosTagger Tester. 
* 
* @author <Authors name> 
* @since <pre>一月 14, 2018</pre> 
* @version 1.0 
*/ 
public class LTPPosTaggerTest {
    public static void main(String[] args) {
        String segModelPath = "E:\\data\\ltp_data_v3.4.0\\cws.model";
        LTPSegmentor ltpSegmentor = LTPSegmentor.createSegmentor(segModelPath);

        String posModelPath = "E:\\data\\ltp_data_v3.4.0\\pos.model";
        LTPPosTagger ltpPosTagger = LTPPosTagger.createPosTagger(posModelPath);


        String testQuery = "明天是星期几？";
        String[] words = ltpSegmentor.segment(testQuery);
        System.out.println(Arrays.asList(words));

        String[] tags = ltpPosTagger.getPosTags(words);
        System.out.println(Arrays.asList(tags));
    }
} 
