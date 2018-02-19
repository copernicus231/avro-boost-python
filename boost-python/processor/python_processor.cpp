/*
 * python_processor.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: copernicus
 */

#include "python_processor.hpp"
#include "parent_module.hpp"
#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <avro/Compiler.hh>
#include <avro/Encoder.hh>
#include <avro/Decoder.hh>
#include <avro/Specific.hh>
#include <avro/Generic.hh>

using namespace boost::python;
namespace negasoft {

PythonProcessor* PythonProcessor::p = 0;

PythonProcessor::PythonProcessor() {
	// TODO Auto-generated constructor stub

}

PythonProcessor::~PythonProcessor() {
	// TODO Auto-generated destructor stub
}

void PythonProcessor::init(){
	d = avro::binaryDecoder();
	PyImport_AppendInittab( "parent", &initparent );
	Py_Initialize();
	object sys_module = import("sys");
	boost::filesystem::path p = boost::filesystem::current_path();
	str module_directory = p.c_str();
	sys_module.attr("path").attr("insert")(1, module_directory);
	object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
	main_namespace = main_module.attr("__dict__");
	object cpp_module( (handle<>(PyImport_ImportModule("parent"))) );
	main_namespace["parent"] = cpp_module;
	main_namespace["r"] = ptr(&record);
	boost::python::exec("from avrotest import process", main_namespace);
}

const std::vector<uint8_t>& PythonProcessor::process(const uint8_t* data, size_t len){
    std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(data,len);
	return process(in);
}

const std::vector<uint8_t>& PythonProcessor::process(std::unique_ptr<avro::InputStream> &in){
    d->init(*in);
    avro::decode(*d,record);
    bp::object o = boost::python::eval("\nprocess(r)",main_namespace);
    size_t len;
    convertDictToAvro( bp::extract<bp::dict>(o));

	return result;
}

bool PythonProcessor::convertDictToAvro(const boost::python::dict &dict){
	std::stringstream ostream;
    std::unique_ptr<avro::OutputStream> out = avro::ostreamOutputStream(ostream);
    avro::EncoderPtr e = avro::binaryEncoder();
    e->init(*out);
    std::ifstream ifs("cpx.json");
    avro::ValidSchema cpxSchema;
    avro::compileJsonSchema(ifs, cpxSchema);
    avro::GenericDatum datum(cpxSchema);
    avro::GenericRecord& r = datum.value<avro::GenericRecord>();
    r.field("func").value<int>()=10;
    r.field("func2").value<int>()=20;
    avro::encode(*e,datum);
    e->flush();
    std::streampos beg = ostream.tellg();
    ostream.seekg(0, std::ios_base::end);
    std::streampos end = ostream.tellg();
	ostream.seekg(0, std::ios_base::beg);
	result.reserve(end - beg);
	result.assign(std::istreambuf_iterator<char>(ostream), std::istreambuf_iterator<char>());
    std::string ss = bp::extract<std::string>(dict["func"].attr("__class__").attr("__name__"));
    std::cout<<ss<<std::endl;
    return true;
}
} /* namespace negasoft */
