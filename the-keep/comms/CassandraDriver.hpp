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

namespace thekeep 
{
  using namespace std;

  // generic Messaging interface for THe Keep
  class CassandraDriver : public TheKeepDB 
  {
      CassFuture* connect_future;
      CassCluster* cluster;
      CassSession* session;

    public:
      CassandraDriver() : connect_future(NULL) {}

      virtual int connect(const string& ip, const string& user, const string& pwd);
      virtual void disconnect();
      virtual TheKeepRecord get(const long userid, const int fieldid);
      virtual int put(const long userid, const int fieldid, const string& value);
      virtual int remove(const long userid, const int fieldid) { return 0; };


      // additional layer??
      virtual TheKeepRecord getchip(const long userid, const int fieldid) 
                            { return get(userid,fieldid); }
      virtual void putchip(const long userid, const int fieldid, const string& value)
                            { put(userid,fieldid,value); }
  };

} // namespace thekeep