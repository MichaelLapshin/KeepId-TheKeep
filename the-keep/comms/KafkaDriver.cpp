// #include <stdio>
#include <kafka/Types.h>
#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>

#include "CommsConfig.hpp" // TODO: review location
#include "KafkaDriver.hpp"

using namespace kafka;
using namespace kafka::clients;
using namespace thekeep;


KafkaDriver::KafkaDriver(const string& kafka_server, const vector<string>& topics)
{
    initialize(kafka_server);
    ranges::for_each(topics,[&](const string& topic) { subscribe(topic); }); // C++20
//alt:  for(auto topic:topics) { subscribe(topic); } // C++17
}

void KafkaDriver::initialize(const string& kafka_server) 
{
    // Create configuration object
    kafka::Properties props({
                             {"bootstrap.servers",  KAFKA_URL.c_str()},
                             {"enable.idempotence", "true"},
                            });

    // Create a producer and consumer instances
    producer = make_unique<KafkaProducer>(props);
    consumer = make_unique<KafkaConsumer>(props);
}

void KafkaDriver::subscribe(const string& topic)
{
    // Check if already subscribed; if now - subscribe
    const Topic& newtopic(topic);  // type conversion; it's identical now
    if(!consumer->subscription().contains(newtopic)) {
        consumer->subscribe({newtopic});  // don't unsubscribe: static configuration
    }
}

void KafkaDriver::subscribe(const set<string>& topics) 
{
    const Topics& newtopics(topics); // type conversion; it's identical now
    consumer->subscribe(newtopics);
}    

void KafkaDriver::unsubscribe(const string& topic)
{
    consumer->unsubscribe(); // from all subscribers??
}

/**
 * @return error code as per Kafka; 0 if ok.  
 */
int KafkaDriver::send(const string& topic, const string& message) 
{
    auto line = std::make_shared<std::string>(message);
     
    // The ProducerRecord doesn't own `line`, it is just a thin wrapper
    auto record = producer::ProducerRecord(topic,
                                            kafka::NullKey,
                                            kafka::Value(line->c_str(), line->size()));

    // Send the message
    // producer->syncSend(record);  // blocking send for testing only
    producer->send(record,
                    // The delivery report handler
                    // Note: Here we capture the shared_pointer of `line`,
                    //       which holds the content for `record.value()`.
                    //       It makes sure the memory block is valid until the lambda finishes.
                    [&,line](const producer::RecordMetadata& metadata, const kafka::Error& error) {
                            if (!error) {
                                // DEBUG: to add logging
                                std::cout << "% Message delivered: " << metadata.toString() << std::endl;
                            } else {
                                this->lasterror = error;
                                // DEBUG: to add logging
                                std::cerr << "% Message delivery failed: " << error.message() << std::endl;
                            }
                         });
    return 0;
}

queue<string> KafkaDriver::receive(const string& topic, int timeoutms) 
{
    // Automatically Subscribe to topics
    subscribe(topic); // Check if already subscribed; if now - subscribe
    
    queue<string> results;

    auto records = consumer->poll(std::chrono::milliseconds(timeoutms));

    for (const auto& record: records) {
        
        if (record.value().size() == 0) continue; // skip empty messages

        if (!record.error()) {
            // some debugging; clean after tests:
            //
            // std::cout << "Got a new message..." << std::endl;
            // std::cout << "    Topic    : " << record.topic() << std::endl;
            // std::cout << "    Partition: " << record.partition() << std::endl;
            // std::cout << "    Offset   : " << record.offset() << std::endl;
            // std::cout << "    Timestamp: " << record.timestamp().toString() << std::endl;
            // std::cout << "    Headers  : " << kafka::toString(record.headers()) << std::endl;
            // std::cout << "    Key   [" << record.key().toString() << "]" << std::endl;
            // std::cout << "    Value [" << record.value().toString() << "]" << std::endl;

            std::cout << "% Message received: <" << record.topic() << "> " << record.value().toString() << std::endl;

            results.push(record.value().toString());
        } else {
            // TODO: add an exception?
            std::cerr << record.toString() << std::endl;
            lasterror = record.error(); // passive reporting
        }
    }
    
    return results;
}

// reads and cleans the last error; naive approach, but simple to implement
string KafkaDriver::last_error() 
{
    if(lasterror)
    {
        string e = lasterror.toString();
        lasterror=Error();
        return e;
    }
    else return "";
}

