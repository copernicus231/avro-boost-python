/*
 * python_processor.hpp
 *
 *  Created on: Feb 12, 2018
 *      Author: copernicus
 */

#ifndef PYTHON_PROCESSOR_HPP_
#define PYTHON_PROCESSOR_HPP_

#include <boost/python.hpp>
#include "parent.hpp"

using namespace boost::python;

namespace negasoft {

class PythonProcessor {
public:
	static PythonProcessor* getInstance(){
		if(p == nullptr){
			p = new PythonProcessor();
			p->init();
		}
		return p;
	}
	PythonProcessor();
	virtual ~PythonProcessor();
	void init();
	const std::vector<uint8_t>& process(const uint8_t* data, size_t len);
	const std::vector<uint8_t>& process(std::unique_ptr<avro::InputStream> &ref);

private:
	bool convertDictToAvro(const boost::python::dict &dict);
private:
	static PythonProcessor *p;
	object main_namespace;
	avro::DecoderPtr d;
    negasoft::Parent record;
    std::vector<uint8_t> result;
};

} /* namespace negasoft */

#endif /* PYTHON_PROCESSOR_HPP_ */
