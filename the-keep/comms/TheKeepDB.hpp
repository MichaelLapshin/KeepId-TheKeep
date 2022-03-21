// Generic DB driver

#pragma once
#include <string>

using namespace std;

namespace thekeep {

// interface class
class TheKeepDB {
    // use inheritance for now; 

    public: 
        // TODO: too simple interface; too generic... 
        virtual int connect(const string& ip, const string& user, const string& pwd) = 0;
        virtual void disconnect() = 0;
        virtual string get(const string& userid, const string& fieldid) = 0;
        virtual int put(const string& userid, const string& fieldid, const string& value) = 0;
};

} // namespace thekeep
