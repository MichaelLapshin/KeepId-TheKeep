/**
 * @filename: KafkaDriver.cpp
 * @description: Kafka high-level abstraction
 * @author: KeepId {IL}
 * @date: March 27, 2022
 * 
 * Uses: https://github.com/morganstanley/modern-cpp-kafka (Morgan Stanley)
 */

#include <kafka/Types.h>
#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>
#include <librdkafka/rdkafkacpp.h>

#include "core/Logger.hpp"
#include "CommErrors.hpp"
#include "CommsConfig.hpp"
#include "KafkaDriver.hpp"

using namespace kafka;
using namespace kafka::clients;
using namespace thekeep;

KafkaDriver::KafkaDriver(const string& kafka_server, const vector<string>& topics)
{
    initialize(kafka_server);
    ranges::for_each(topics,[&](const string& topic) { subscribe(topic); }); // C++20
//alt:   for(auto topic:topics) { subscribe(topic); } // C++17
}

void KafkaDriver::initialize(const string& kafka_server) 
{
    // Alternative configuration:
    // kafka::Properties props;
    // props.put("bootstrap.servers", "KAFKA_URL");
    // props.put("group.id", "KAFKA_URL");
    // props.put("enable.auto.commit", "false");

    // Prepare the configuration
    kafka::Properties props({
                             {"bootstrap.servers",  {KAFKA_URL.c_str()}},
                             // 'idempotence' is a producer only property; ignored for consumer
                             {"enable.idempotence", {"true"}},
                            });

    // Create a producer and consumer instances
    producer = make_unique<clients::producer::KafkaProducer>(props);
    consumer = make_unique<clients::consumer::KafkaConsumer>(props); 
}

void KafkaDriver::subscribe(const string& topic)
{
    // Check if already subscribed; if now - subscribe
    const Topic& newtopic(topic);  // type conversion; it's identical now
    if(!consumer->subscription().contains(newtopic))   // isC++20 
        consumer->subscribe({newtopic});  // don't unsubscribe: static configuration
}

/// @brief Subscribes to multiple topics
/// @param topics 
void KafkaDriver::subscribe(const set<string>& topics) 
{
    const Topics& newtopics(topics); // type conversion; it's identical now
    consumer->subscribe(newtopics);
}    

void KafkaDriver::unsubscribe(const string& topic)
{
    consumer->unsubscribe(); // Unsubscribe from the current subscription set.
}

/**
 * @return error code as per Kafka (no!); 0 if ok.  
 */
int KafkaDriver::send(const string& topic, const string& message) 
{
    auto line = std::make_shared<std::string>(message);
     
    // The ProducerRecord doesn't own `line`, it is just a thin wrapper
    auto record = producer::ProducerRecord(topic,
                                            kafka::NullKey,
                                            kafka::Value(line->c_str(), line->size()));

    // Send the message
    // producer->syncSend(record);  // DEBUG: blocking send for testing only
    producer->send(record,
                    // The delivery report handler
                    // Note: Here we capture the shared_pointer of `line`,
                    //       which holds the content for `record.value()`.
                    //       It makes sure the memory block is valid until the lambda finishes.
                    [&,line](const producer::RecordMetadata& metadata, const kafka::Error& error) {
                            if (!error) {
 //                             DEBUG("% Message delivered: " << metadata.toString()); // via logging
                            } else {
                                scoped_lock(this->kafka_mutex);
                                this->lasterror = error;
//                              ERROR("% Message delivery failed: " << error.message());
                            }
                         });
    return 0;
}


/// @brief Receive all available messages from subscribed topics
/// @param timeoutms - receive timeout if no messages are available right away; default: 1000ms
/// @return a queue/list of messages
queue<string> KafkaDriver::receive(int timeoutms)
{
    // Automatically Subscribe to topics
    // must be explicit   subscribe(topic); // Check if already subscribed; if now - subscribe

    queue<string> results;

    auto records = consumer->poll(std::chrono::milliseconds(timeoutms));
    return results;
}

/// @brief Receive a filtered list of subscribed topics (to be retired)
/// @param topic 
/// @param timeoutms 
/// @return 
queue<string> KafkaDriver::receive(const string& topic, int timeoutms) 
{
    // Automatically Subscribe to topics
 // must be explicit   subscribe(topic); // Check if already subscribed; if now - subscribe
    
    queue<string> results;

    auto records = consumer->poll(std::chrono::milliseconds(timeoutms));
    kafka::Topic ktopic(topic); // converts 'string' to 'Topic' type, which is actually as std:string as well 

    for (const auto& record: records) {
        
        if (record.value().size() == 0) continue; // skip empty messages

        if (!record.error()) {
            // some debugging; clean after tests:
            //
            // DEBUG("Got a new message...");
            // DEBUG("    Topic    : " << record.topic());
            // DEBUG("    Partition: " << record.partition());
            // DEBUG("    Offset   : " << record.offset());
            // DEBUG("    Timestamp: " << record.timestamp().toString());
            // DEBUG("    Headers  : " << kafka::toString(record.headers()));
            // DEBUG("    Key   [" << record.key().toString() << "]");
            // DEBUG("    Value [" << record.value().toString() << "]");

// DEBUG:  DEBUG("% Message received: <" << record.topic() << "> " << record.value().toString());

            if(record.topic() == ktopic)  // only read messages from relevant topics; what happens with others?
                results.push(record.value().toString());
            // TODO: handle case for multiple topics to be sure the messages are not lost!!!!

        } else {
            ERROR(record.toString());
            lock_guard<mutex> lk(kafka_mutex);
            lasterror = record.error(); // passive reporting
            throw MessagingException(record.toString());
        }
    }
    
    return results;
}

// reads and cleans the last error; naive approach, but simple to implement
string KafkaDriver::last_error() 
{
    if(lasterror)
    {
        lock_guard<mutex> lk(kafka_mutex);
        string e = lasterror.toString();
        lasterror=Error();
        return e;
    }
    else return "";
}

