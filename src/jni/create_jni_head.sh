if [ -d 'ltp4j.h' ]; then
  rm -f ltp4j.h
fi

cd ../../jvm/ltp4j/src/main/java
if [ -d 'edu_hit_ir_ltp_jni_LtpJNI.h' ]; then
  rm -f edu_hit_ir_ltp_jni_LtpJNI.h
fi
javah edu.hit.ir.ltp.jni.LtpJNI
mv edu_hit_ir_ltp_jni_LtpJNI.h ../../native/ltp4j.h
