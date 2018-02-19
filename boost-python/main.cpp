/*
 * main.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: copernicus
 */

#include <boost/python.hpp>
#include <boost/python/dict.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <avro/Compiler.hh>
#include <avro/Encoder.hh>
#include <avro/Decoder.hh>
#include <avro/Specific.hh>
#include <avro/Generic.hh>
#include "python_processor.hpp"

using namespace boost::python;

int main(int argc, char ** argv) {

		negasoft::PythonProcessor process;
	    std::unique_ptr<avro::OutputStream> out = avro::memoryOutputStream();
	    std::cout<<"count bytes:"<<(*out).byteCount()<<std::endl;
	    avro::EncoderPtr e = avro::binaryEncoder();
	    e->init(*out);
	    negasoft::Parent p;
	    p.doublevalue = 1.1;
	    p.intvalue = 2;
	    p.stringvalue = "dos";
	    for(int i=0;i<277;i++){
	    	negasoft::Child c;
	    	c.doublevalue=3.0;
	    	c.intvalue = i;
	    	c.stringvalue="zero";
	    	p.children.push_back(c);
	    }
	    avro::encode(*e,p);

	    std::cout<<"count bytes:"<<(*out).byteCount()<<std::endl;

	try {

		process.init();
		std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(*out);
		const std::vector<uint8_t>& v = process.process(in);
		std::cout<<"return size:"<<v.size()<<std::endl;

	} catch (error_already_set& ) {
		PyErr_Print();
	}
}

