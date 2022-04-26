/**
 * @filename: CassandraDriver.hpp
 * @description: Cassandra DB header
 * @author: KeepId {IL}
 * @date: March, 2022
 */

#pragma once
#include <string>
#include <cassandra.h>

#include "TheKeepDB.hpp"

using namespace std;

namespace thekeep {

  // generic Messaging interface for THe Keep
  class CassandraDriver : public TheKeepDB {
      CassFuture* connect_future;
      CassCluster* cluster;
      CassSession* session;

    public:
      CassandraDriver() : connect_future(NULL) {}

      virtual int connect(const string& ip, const string& user, const string& pwd);
      virtual void disconnect();
      virtual string get(const string& userid, const string& fieldid);
      virtual int put(const string& userid, const string& fieldid, const string& value);
  };

} // namespace thekeep