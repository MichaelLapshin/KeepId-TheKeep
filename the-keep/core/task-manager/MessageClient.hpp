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
        TheKeepDB* kdb; 
        queue<string> messages; // FIFO queue

      public:
        // TODO: receive / sent topics constructor. Add built-in initialization
        MessageClient(TheKeepMessaging *km, TheKeepDB *kdb): km(km), kdb(kdb)
        {
            // null pts checks just in case (change to reference?)
            if(!km || !kdb) 
            {
                throw runtime_error("MessageClient initialized with a NULL object");
            }

            km->subscribe(KAFKA_CONTROL_TOPIC);
            km->subscribe(KAFKA_DATA_TOPIC);
        }

        // We have to set up a messaging loop; the Kafka does not 
        // allow to pick up data from a specific topic
        const string pollFetch() const
        {
            static auto q = km->receive();
            const string& msg=q.front();
            q.pop();
            return msg; // picks up only the very frist messasge - chceck how to handle this TODO
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
            //km->initialize("");
            //km->subscribe("keepid-tests");
            km->send("keepid-tests","test-c++ 1235");
            km->send("keepid-tests","test-c++ 123567");

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