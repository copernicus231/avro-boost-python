/*
 * AvroWrapper.h
 *
 *  Created on: Feb 2, 2018
 *      Author: copernicus
 */

#ifndef AVROWRAPPER_H_
#define AVROWRAPPER_H_

#include <avro/Generic.hh>
#include <boost/python.hpp>

namespace pyavro {

class AvroWrapper {
private:
	avro::GenericRecord* record;
public:
	AvroWrapper();
	virtual ~AvroWrapper();
	void set(avro::GenericRecord *r){
		record=r;
	}
	int get(const boost::python::str &l){

			avro::GenericDatum& d = record->field(boost::python::extract<const std::string>(l));
			return d.value<int>();
	}
};

} /* namespace pyavro */

#endif /* AVROWRAPPER_H_ */
