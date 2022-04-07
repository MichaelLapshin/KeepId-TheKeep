// #include <stdio>

#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>

#include "CommsConfig.hpp" // TODO: review location
#include "KafkaDriver.hpp"

using namespace thekeep;
using namespace kafka::clients;

// TODO: add implementation

void KafkaDriver::initialize(const string& connection_string) {
    // TODO:

    // Create configuration object
        kafka::Properties props ({
            {"bootstrap.servers",  KAFKA_URL.c_str()}, //??
            {"enable.idempotence", "true"},
        });

    // Create a producer instance   
    producer = make_unique<KafkaProducer>(props);
}

int KafkaDriver::send(const string& topic, const string& message) 
{
    // TODO:
    for (auto line = std::make_shared<std::string>();
                     std::getline(std::cin, *line);
              line = std::make_shared<std::string>()) 
    {
        // The ProducerRecord doesn't own `line`, it is just a thin wrapper
        auto record = producer::ProducerRecord(topic,
                                                kafka::NullKey,
                                                kafka::Value(line->c_str(), line->size()));

        // Send the message
        producer->send(record,
                        // The delivery report handler
                        // Note: Here we capture the shared_pointer of `line`,
                        //       which holds the content for `record.value()`.
                        //       It makes sure the memory block is valid until the lambda finishes.
                        [line](const producer::RecordMetadata& metadata, const kafka::Error& error) {
                            if (!error) {
                                std::cout << "% Message delivered: " << metadata.toString() << std::endl;
                            } else {
                                std::cerr << "% Message delivery failed: " << error.message() << std::endl;
                            }
                        });

        if (line->empty()) break;
    }

    return 0;
}

string KafkaDriver::receive(const string& topic, int timeoutms) {
    // TODO:
    return "n/a";
}
