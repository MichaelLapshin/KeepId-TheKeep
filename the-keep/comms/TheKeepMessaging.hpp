/**
 * @filename: TheKeepMessaging.hpp
 * @description: Messaging abstraction
 * @author: KeepId {IL}
 * @date: March, 2022
 */
#pragma once
#include <set>
#include <queue>
#include <string>

namespace thekeep {
    using namespace std;

    // generic Messaging interface for The Keep
    // Currently, it supports 1:1 Kafka driver, but later can support more
    // types of messaging systems
    class TheKeepMessaging {
            void (*error_handler)() = nullptr; // async callback
            
        public:
            virtual ~TheKeepMessaging(){}; // just a dummy for proper child destruction

            /** Initializes connection to a Messaging Bus system */
            virtual void initialize(const string& server_url) = 0;
            virtual void subscribe(const string& topic) = 0;        
            virtual void subscribe(const set<string>& topics) = 0;        
            virtual void unsubscribe(const string& topic) = 0;        
            virtual int send(const string& topic, const string& message) = 0;
            virtual queue<string> receive(int timeoutms) = 0;
            virtual queue<string> receive(const string& topic, int timeoutms) = 0;  // to retire
            virtual void set_error_handler(void (*error_handler)()) { this->error_handler = error_handler; }
    };

} // namespace thekeep