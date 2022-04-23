// Messaging abstraction

#pragma once
#include <queue>
#include <string>

using namespace std;

namespace thekeep {

// generic Messaging interface for The Keep
// Currently, it supports 1:1 Kafka driver, but later can support more
// types of messaging systems
class TheKeepMessaging {
        void (*error_handler)() = nullptr; // async callback
        
    public:
        virtual ~TheKeepMessaging() = 0;
        virtual void initialize(const string& server_url) = 0;
        virtual void subscribe(const string& topic) = 0;        
        virtual void subscribe(const set<string>& topics) = 0;        
        virtual void unsubscribe(const string& topic) = 0;        
        virtual int send(const string& topic, const string& message) = 0;
        virtual queue<string> receive(const string& topic, int timeoutms) = 0;
        virtual void set_error_handler(void (*error_handler)()) { this->error_handler = error_handler; }
};

} // namespace thekeep