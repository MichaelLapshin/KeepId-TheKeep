/**
 * @filename: MessageClient.hpp
 * @description: Abstraction layer for the messaging
 * @author: KeepId  {ML,IL}
 * @date: December 13, 2022
 */
#pragma once
#include <unistd.h>  // for sleep()
#include "core/Logger.hpp"
#include "comms/CommsConfig.hpp"
#include "comms/TheKeepDB.hpp"
#include "comms/TheKeepMessaging.hpp"

// Implementation specific drivers; a bit deviation from decoupled design, but much simpler
#include "comms/KafkaDriver.hpp"
#include "comms/CassandraDriver.hpp"

namespace thekeep {
    using namespace std;

    // idea: a MessageClient per topic.. or area of interest; 
    // we would need to separate Data and Conrtol messaging flows; 
    // Messsage Client keeps its internal queue of received messages
    // and return them one by one
    // it's initialized from outside with a list? or single topic

    class MessageClient
    {
        TheKeepMessaging *km;
        TheKeepDB *kdb;
        queue<string> messages; // FIFO queue

    public:
    MessageClient() {}
        /// @brief a single receive / sent topic constructor with built-in initialization
        ///        Assumes global Kafka and Database configuration from CommsConfig.hpp
        /// @param topic - a topic to which will be subcsription
        MessageClient(string topic) : MessageClient(vector<string> {topic}) {}

        /// @brief receive / sent topics constructor with built-in initialization
        ///        Assumes global Kafka and Database configuration from CommsConfig.hpp
        /// @param topics - topics to which will be subcsription
        MessageClient(const vector<string>& topics)
        {
            // vector<string> topics{KAFKA_CONTROL_TOPIC, KAFKA_DATA_TOPIC};
            TheKeepMessaging *km = new KafkaDriver(KAFKA_URL, topics);
            TheKeepDB *kdb = new CassandraDriver();
            kdb->connect(CASSANRDA_URL, CASSANRDA_USER, CASSANRDA_PASSWORD);
        }

        /// @brief Proper De-coupled Constructor with implementation done outside
        /// @param km   - initialized The Keep's DB
        /// @param kdb  - initialized Kafka driver subscribed to required topics
        MessageClient(TheKeepMessaging *km, TheKeepDB *kdb) : km(km), kdb(kdb)
        {
            // null pts checks just in case (change to reference?)
            if (!km || !kdb)
            {
                throw runtime_error("MessageClient initialized with a NULL object");
            }

            km->subscribe(KAFKA_CONTROL_TOPIC); // todo: another messaging object
            km->subscribe(KAFKA_DATA_TOPIC);
        }

        // We have to set up a messaging loop; the Kafka does not 
        // allow to pick up data from a specific topic
        const string pollFetch() const
        {
            static auto q = km->receive();
            const string& msg=q.front();
            q.pop();
            return msg; // picks up only the very first messasge - chceck how to handle this TODO
        }

        const string pollFetchDataUpdate() const
        {
            auto q = km->receive("topic",60);
            const string& msg=q.front();
            q.pop();
            return msg;
        }
        
        const string fetchUserDataRequest() const
        {
            
            return "";
        }

        void send() 
        {
            // km->send("keepid-tests","test-c++ 1235");
            // km->send("keepid-tests","test-c++ 123567");

            queue<string> messages;
            for (int i = 0; i < 100; i++)
            {
                sleep(1);
                messages = km->receive(KAFKA_DATA_TOPIC, 100);
                while (!messages.empty())
                {
                    DEBUG("tick: " + to_string(i) + " -> " + messages.front());
                    messages.pop();
                }
            }
        }
    };
} // namespace thekeep