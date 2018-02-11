/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef PARENT_HPP_3859206598__H_
#define PARENT_HPP_3859206598__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

namespace negasoft {
struct Child {
    std::string stringvalue;
    int32_t intvalue;
    double doublevalue;
    Child() :
        stringvalue(std::string()),
        intvalue(int32_t()),
        doublevalue(double())
        { }
};

struct Parent {
    std::string stringvalue;
    int32_t intvalue;
    double doublevalue;
    std::vector<Child > children;
    Parent() :
        stringvalue(std::string()),
        intvalue(int32_t()),
        doublevalue(double()),
        children(std::vector<Child >())
        { }
};

}
namespace avro {
template<> struct codec_traits<negasoft::Child> {
    static void encode(Encoder& e, const negasoft::Child& v) {
        avro::encode(e, v.stringvalue);
        avro::encode(e, v.intvalue);
        avro::encode(e, v.doublevalue);
    }
    static void decode(Decoder& d, negasoft::Child& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.stringvalue);
                    break;
                case 1:
                    avro::decode(d, v.intvalue);
                    break;
                case 2:
                    avro::decode(d, v.doublevalue);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.stringvalue);
            avro::decode(d, v.intvalue);
            avro::decode(d, v.doublevalue);
        }
    }
};

template<> struct codec_traits<negasoft::Parent> {
    static void encode(Encoder& e, const negasoft::Parent& v) {
        avro::encode(e, v.stringvalue);
        avro::encode(e, v.intvalue);
        avro::encode(e, v.doublevalue);
        avro::encode(e, v.children);
    }
    static void decode(Decoder& d, negasoft::Parent& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.stringvalue);
                    break;
                case 1:
                    avro::decode(d, v.intvalue);
                    break;
                case 2:
                    avro::decode(d, v.doublevalue);
                    break;
                case 3:
                    avro::decode(d, v.children);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.stringvalue);
            avro::decode(d, v.intvalue);
            avro::decode(d, v.doublevalue);
            avro::decode(d, v.children);
        }
    }
};

}
#endif
