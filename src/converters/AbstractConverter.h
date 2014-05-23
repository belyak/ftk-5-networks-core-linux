/* 
 * File:   AbstractConverter.h
 * Author: andy
 *
 * Created on May 19, 2014, 3:24 AM
 */

#ifndef ABSTRACTCONVERTER_H
#define	ABSTRACTCONVERTER_H

#include <string>



class AbstractConverter {
public:
    virtual unsigned char get_chunk_size()=0;
    virtual std::string encode(const std::string & message)=0; 
    virtual std::string decode(const std::string & message)=0;
};

#endif	/* ABSTRACTCONVERTER_H */

