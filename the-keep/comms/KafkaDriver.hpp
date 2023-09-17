/**
 * @filename: KafkaDriver.hpp
 * @description: Kafka high-level abstraction
 * @author: KeepId {IL}
 * @date: March 27, 2022
 * 
 * Uses: https://github.com/morganstanley/modern-cpp-kafka (Morgan Stanley)
 */
#pragma once
#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>

#include "TheKeepMessaging.hpp"

namespace thekeep {
    using namespace std;

    /// @brief generic Messaging interface for The Keep; an instance per subscription/topic
    class KafkaDriver : public TheKeepMessaging {
            unique_ptr<kafka::clients::producer::KafkaProducer> producer;
            unique_ptr<kafka::clients::consumer::KafkaConsumer> consumer;
            mutex      kafka_mutex;  // for error preservation
            kafka::Error lasterror; // Kafka last error; naive approach for now: clean after read
        public:
            KafkaDriver() {}
            KafkaDriver(const string& kafka_server, const vector<string>& topics);
            virtual ~KafkaDriver() {}
            virtual void initialize(const string& kafka_server);
            virtual void subscribe(const string& topic);   
            virtual void subscribe(const set<string>& topics);        
            virtual void unsubscribe(const string& topic);        
            virtual int send(const string& topic, const string& message);
            virtual queue<string> receive(int timeoutms=1000); // defailt - 1s
            virtual queue<string> receive(const string& topic, int timeoutms); // to retire; filtering version
            virtual string last_error(); // reads and cleans the last error        
    };

} // namespace thekeep