package edu.hit.ir.ltp4j;


import edu.hit.ir.ltp4j.jni.LtpJNI;

import java.util.Arrays;

/**
* LTPParser Tester. 
* 
* @author <Authors name> 
* @since <pre>一月 14, 2018</pre> 
* @version 1.0 
*/ 
public class LTPParserTest {
    public static void main(String[] args) {
        String segModelPath = "/home/hzx/workspace/ltp/ltp_data_v3.4.0/cws.model";
        String posModelPath = "/home/hzx/workspace/ltp/ltp_data_v3.4.0/pos.model";
        String parserModelPath = "/home/hzx/workspace/ltp/ltp_data_v3.4.0/parser.model";

        LTPSegmentor ltpSegmentor = LTPSegmentor.createSegmentor(segModelPath);
        LTPPosTagger ltpPosTagger = LTPPosTagger.createPosTagger(posModelPath);
        LTPParser ltpParser = LTPParser.createParser(parserModelPath);

        String testQuery = "明天是星期几？";
        String[] words = ltpSegmentor.segment(testQuery);
        System.out.println(Arrays.asList(words));

        String[] tags = ltpPosTagger.getPosTags(words);
        System.out.println(Arrays.asList(tags));

        LTPParser.DepRel[] depRels = ltpParser.parse(words, tags);
        System.out.println(Arrays.asList(depRels));
    }
} 
