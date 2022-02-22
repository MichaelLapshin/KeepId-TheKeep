// Messaging abstraction

#pragma once
#include <string>

using namespace std;

namespace thekeep {


// generic Messaging interface for THe Keep
class TheKeepMessaging {
    public:
        virtual void initialize(const string& connection_string) = 0;
        virtual int send(const string& topic, const string& message) = 0;
        virtual string receive(const string& topic, int timeoutms) = 0;
};

} // namespace thekeep