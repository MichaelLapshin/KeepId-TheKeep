/**
 * @filename: KafkaDriver.hpp
 * @description: Kafka high-level abstraction
 * @author: KeepId {IL}
 * @date: March 27, 2022
 * 
 * Uses: https://github.com/morganstanley/modern-cpp-kafka (Morgan Stanley)
 */

#pragma once
#include <string>

#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>

#include "TheKeepMessaging.hpp"

using namespace std;

namespace thekeep {


// generic Messaging interface for THe Keep
class KafkaDriver : public TheKeepMessaging {
        unique_ptr<kafka::clients::KafkaProducer> producer;
    public:
        virtual void initialize(const string& connection_string);
        virtual int send(const string& topic, const string& message);
        virtual string receive(const string& topic, int timeoutms);

};

} // namespace thekeep