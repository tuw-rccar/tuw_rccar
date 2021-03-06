/***************************************************************************
 *   Software License Agreement (BSD License)                              *
 *   Copyright (C) 2012 by Markus Bader <markus.bader@tuwien.ac.at>        *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *                                                                         *
 *   1. Redistributions of source code must retain the above copyright     *
 *      notice, this list of conditions and the following disclaimer.      *
 *   2. Redistributions in binary form must reproduce the above copyright  *
 *      notice, this list of conditions and the following disclaimer in    *
 *      the documentation and/or other materials provided with the         *
 *      distribution.                                                      *
 *   3. Neither the name of the copyright holder nor the names of its      *
 *      contributors may be used to endorse or promote products derived    *
 *      from this software without specific prior written permission.      *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY *
 *   WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 ***************************************************************************/

#ifndef SHARED_MEM_HANDLER_ARDUINO_OBJECT
#define SHARED_MEM_HANDLER_ARDUINO_OBJECT

#include <shmfw/variable.h>
#include <shmfw/handler.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <tuw_shm/shm_arduino_objects.h>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace tuw {
namespace shm {

class HandlerObject;

typedef std::shared_ptr<HandlerObject> HandlerObjectPtr;

/**
 * class to enable polymorphismus on shared objects
 **/
class HandlerObject {
public:
    virtual std::string name() {
        return "xx";
    }
    virtual std::string type_name() {
        return "xx";
    }
    virtual void it_has_changed() {
    }
    virtual void lock() {
    }
    virtual void unlock() {
    }
    virtual bool locked() {
        return false;
    }
    virtual std::string timestamp() {
        return "xx";
    }
    virtual std::string value() const {
        return "xx";
    }
    virtual std::string value ( uint32_t i ) const {
        return "xx";
    }
    virtual uint32_t size() const {
        return 0;
    }
    virtual void value ( const std::string &str ) {
    }
    virtual int construct ( const std::string &name, ShmFw::HandlerPtr &shmHdl, unsigned int size = 1 ) {
        return ShmFw::Header::ERROR;
    }
    static HandlerObjectPtr  open ( const std::string &name, ShmFw::HandlerPtr &shmHdl );
    static HandlerObjectPtr create ( const std::string &name, ShmFw::HandlerPtr &shmHdl, const std::string &type );
};

template <class T>
class HandlerVar : public HandlerObject {
public:
private:
    ShmFw::Var<T> v;
public:
    HandlerVar ( const std::string &name, ShmFw::HandlerPtr &shmHdl ) {
        v.construct ( name, shmHdl );
    }
    HandlerVar() {
    }
    std::string type_name () {
        return v.type_name();
    }
    virtual void it_has_changed() {
        v.itHasChanged();
    }
    virtual void lock() {
        v.try_lock();
    }
    virtual void unlock() {
        v.unlock();
    }
    virtual bool locked() {
        return v.locked();
    }
    virtual std::string timestamp() {
        return to_simple_string ( v.timestampShm() ) ;
    }
    std::string name () {
        return v.name();
    }
    std::string value() const {
        return boost::lexical_cast<std::string> ( *v );
    }
    virtual std::string value ( uint32_t i ) const {
        if ( i > 0 ) return "Out of bound";
        return value();
    }
    virtual uint32_t size() const {
        return 1;
    }
    void value ( const std::string &str ) {
        *v = boost::lexical_cast<T> ( str );
    }
    int construct ( const std::string &name, ShmFw::HandlerPtr &shmHdl, unsigned int size = 1 ) {
        return v.construct ( name, shmHdl );
    }
};


};
};



#endif //SHARED_MEM_HANDLER_ARDUINO_OBJECT




