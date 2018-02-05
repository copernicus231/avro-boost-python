/*
 * main.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: copernicus
 */

#include <boost/python.hpp>
#include <boost/python/dict.hpp>
#include "cpx.hh"
#include <fstream>
#include <avro/Compiler.hh>
#include <avro/Encoder.hh>
#include <avro/Decoder.hh>
#include <avro/Specific.hh>
#include <avro/Generic.hh>
#include "AvroWrapper.h"
using namespace boost::python;

int main(int argc, char ** argv) {
	 std::ifstream ifs("cpx.json");

	    avro::ValidSchema cpxSchema;
	    avro::compileJsonSchema(ifs, cpxSchema);

	    std::auto_ptr<avro::OutputStream> out = avro::memoryOutputStream();
	    avro::EncoderPtr e = avro::binaryEncoder();
	    e->init(*out);
	    c::cpx c1;
	    c1.re = 100;
	    c1.im = 105;
	    avro::encode(*e, c1);

	    std::auto_ptr<avro::InputStream> in = avro::memoryInputStream(*out);
	    avro::DecoderPtr d = avro::binaryDecoder();
	    d->init(*in);

	    avro::GenericDatum datum(cpxSchema);
	    avro::decode(*d, datum);


	    pyavro::AvroWrapper w;
	    w.set(&datum.value<avro::GenericRecord>());




	try {

		Py_Initialize();
		object sys_module = import("sys");
		str module_directory = "/home/copernicus/eclipse-workspace/boost-python/Debug";
		sys_module.attr("path").attr("insert")(1, module_directory);
		object main_module(
				(handle<>(borrowed(PyImport_AddModule("__main__")))));


		object main_namespace = main_module.attr("__dict__");

		main_namespace["AvroWrapper"] = class_<pyavro::AvroWrapper>("AvroWrapper").def("__getattr__",&pyavro::AvroWrapper::get);
		main_namespace["w"] = ptr(&w);
		boost::python::exec("from avrotest import process", main_namespace);

		for(int i=0;i<10;i++){

			handle<> ignored(
					(PyRun_String("\nprocess(w)", Py_file_input,
							main_namespace.ptr(), main_namespace.ptr())));
		}

	} catch (error_already_set ) {
		PyErr_Print();
	}
}

