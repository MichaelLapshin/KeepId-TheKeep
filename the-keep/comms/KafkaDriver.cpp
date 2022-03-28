// #include <stdio>

#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>

#include "CommsConfig.hpp" // TODO: review location
#include "KafkaDriver.hpp"

using namespace thekeep;
//using namespace kafka::clients;

// TODO: add implementation

void KafkaDriver::initialize(const string& connection_string) {
    // TODO:
}

int KafkaDriver::send(const string& topic, const string& message) {
    // TODO:
    return 0;
}

string KafkaDriver::receive(const string& topic, int timeoutms) {
    // TODO:
    return "n/a";
}
