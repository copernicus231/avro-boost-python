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
#include "parent_module.hpp"

using namespace boost::python;

int main(int argc, char ** argv) {
	 std::ifstream ifs("record.json");

	    avro::ValidSchema cpxSchema;
	    avro::compileJsonSchema(ifs, cpxSchema);

	    std::unique_ptr<avro::OutputStream> out = avro::memoryOutputStream();
	    avro::EncoderPtr e = avro::binaryEncoder();
	    e->init(*out);
	    negasoft::Parent p;
	    p.doublevalue = 1.1;
	    p.intvalue = 2;
	    p.stringvalue = "dos";
	    for(int i=0;i<3;i++){
	    	negasoft::Child c;
	    	c.doublevalue=3.0;
	    	c.intvalue = i;
	    	c.stringvalue="zero";
	    	p.children.push_back(c);
	    }
	    avro::encode(*e,p);


	    std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(*out);
	    avro::DecoderPtr d = avro::binaryDecoder();
	    d->init(*in);
	    negasoft::Parent r;
	    avro::decode(*d,r);
	try {
		PyImport_AppendInittab( "parent", &initparent );
		Py_Initialize();
		object sys_module = import("sys");
		boost::filesystem::path p = boost::filesystem::current_path();
		str module_directory = p.c_str();
		sys_module.attr("path").attr("insert")(1, module_directory);
		object main_module(
				(handle<>(borrowed(PyImport_AddModule("__main__")))));


		object main_namespace = main_module.attr("__dict__");

		object cpp_module( (handle<>(PyImport_ImportModule("parent"))) );
		main_namespace["parent"] = cpp_module;
		main_namespace["r"] = ptr(&r);
		boost::python::exec("from avrotest import process", main_namespace);

		for(int i=0;i<10;i++){
			r.intvalue=i;
			handle<> ignored(
					(PyRun_String("\nprocess(r)", Py_file_input,
							main_namespace.ptr(), main_namespace.ptr())));
		}

	} catch (error_already_set& ) {
		PyErr_Print();
	}
}

