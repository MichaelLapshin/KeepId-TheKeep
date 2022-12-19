/**
 * @filename: MessageClient.hpp
 * @description: Abstraction layer for the messaging
 * @author: KeepId  {ML,IL}
 * @date: December 13, 2022
 */
#pragma once
#include <unistd.h>  // for sleep()
#include "core/Logger.hpp"
#include "comms/TheKeepDB.hpp"
#include "comms/TheKeepMessaging.hpp"

namespace thekeep {
    class MessageClient 
    {       
        TheKeepMessaging *km;
        TheKeepDB* kdb; 

      public:
        MessageClient(TheKeepMessaging *km, TheKeepDB* kdb): km(km), kdb(kdb)
        {
            // TODO: null pts checks if any needed
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
            using namespace std;
            unique_ptr<TheKeepMessaging> kd = make_unique<KafkaDriver>();
            kd->initialize("");
            kd->subscribe("keepid-tests");
            kd->send("keepid-tests", "test-c++ 1235");
            kd->send("keepid-tests", "test-c++ 123567");

            queue<string> messages;
            for (int i = 0; i < 100; i++)
            {
                sleep(1);
                messages = kd->receive("keepid-tests", 100);
                while (!messages.empty())
                {
                    DEBUG("tick: " + to_string(i) + " -> " + messages.front());
                    messages.pop();
                }
            }
        }
    };
} // namespace thekeep