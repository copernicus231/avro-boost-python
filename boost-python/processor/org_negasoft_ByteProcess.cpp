/*
 * org_negasoft_ByteProcess.c
 *
 *  Created on: Feb 12, 2018
 *      Author: copernicus
 */

#include "org_negasoft_ByteProcess.h"
#include "python_processor.hpp"

JNIEXPORT jbyteArray JNICALL Java_org_negasoft_ByteProcess_process
  (JNIEnv *a, jobject b, jbyteArray c){
	jsize size = a->GetArrayLength(c);
	jboolean b1;
	uint8_t* buffer = reinterpret_cast<uint8_t*>(a->GetPrimitiveArrayCritical(c,&b1));
	negasoft::PythonProcessor *pp = negasoft::PythonProcessor::getInstance();
	const std::vector<uint8_t> result = pp->process(buffer,size);
	a->ReleasePrimitiveArrayCritical(c,reinterpret_cast<void *>(buffer),0);
	jbyteArray ret = a->NewByteArray(result.size());
	a->SetByteArrayRegion(ret, 0,result.size(), reinterpret_cast<const int8_t*>(&result[0]));
	return ret;
}
