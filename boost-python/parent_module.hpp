/*
 * parent_module.hpp
 *
 *  Created on: Feb 9, 2018
 *      Author: copernicus
 */

#ifndef SCHEMA_PARENT_MODULE_HPP_
#define SCHEMA_PARENT_MODULE_HPP_

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/indexing_suite.hpp>

#include "parent.hpp"
namespace bp = boost::python;


namespace negasoft{
	typedef std::vector<Child > Childs;

	auto operator==( Child const& u, Child const& v )
	    -> bool
	{
	    return true;
	}

}


BOOST_PYTHON_MODULE(parent)
{
	bp::class_<negasoft::Childs>("Childs").def(bp::vector_indexing_suite<negasoft::Childs>());
	bp::class_<negasoft::Parent>("Parent")
			.def_readonly("stringvalue",&negasoft::Parent::stringvalue)
			.def_readonly("intvalue",&negasoft::Parent::intvalue)
			.def_readonly("doublevalue",&negasoft::Parent::doublevalue)
			.def_readonly("children",&negasoft::Parent::children);
	bp::class_<negasoft::Child>("Child")
			.def_readonly("stringvalue",&negasoft::Child::stringvalue)
			.def_readonly("intvalue",&negasoft::Child::intvalue)
			.def_readonly("doublevalue",&negasoft::Child::doublevalue);
}

#endif /* SCHEMA_PARENT_MODULE_HPP_ */
