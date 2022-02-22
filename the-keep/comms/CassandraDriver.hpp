#pragma once
#include <string>
#include <cassandra.h>

#include "TheKeepDB.hpp"

using namespace std;

namespace thekeep {


// generic Messaging interface for THe Keep
class CassandraDriver: public TheKeepDB : connect_future(NULL) {
    CassFuture* connect_future;
    CassCluster* cluster;
    CassSession* session;

    public:
        virtual int connect(const string& ip, const string& user, const string& pwd);
        virtual string get(const string& userid, const string& fieldid);
        virtual int put(const string& userid, const string& fieldid, const string& value);
};

} // namespace thekeep