/**
 * @filename: TheKeepDB.hpp
 * @description: Generic DB driver header
 * @author: KeepId {IL}
 * @date: March, 2022
 */
#pragma once
#include <string>

namespace thekeep
{
    using namespace std;

    struct TheKeepRecord
    {
        /* data: dup from the  */
        long userid; /* 64 bit may be an overkill, but safer */
        int fieldid;
        string chip;
        long timestamp; // for now - long;
    };

    // interface class
    class TheKeepDB
    {
        // use inheritance for now;

    public:
        // Generic portion of the interface; low-level
        virtual ~TheKeepDB() {}; // don't forget to implement!

        /** Sets up a connection to a DB
         * 
         * @return status of a connection; 0 - ok
         */
        virtual int connect(const string &ip, const string &user, const string &pwd) = 0;

        /** Disconnects from a DB for a graceful shutdown */
        virtual void disconnect() = 0;
        
        // ??? externally defined and static schema for now
        // virtual bool schema_init() = 0;

        /** Retreive a chunk of data for a user-field combination
         * @return an encrypted chunk representing a field
         */
        virtual TheKeepRecord get(const long userid, const int fieldid) = 0;

        /** Saves an encrypted field into a Holy Cow DB
         * @return status; success = 0
         */
        virtual int put(const long userid, const int fieldid, const string &value) = 0;

        /** 
         * Removes an unused any longer record; used after re-encryption and saving with
         * a new kwy
         * 
         * @return status; success = 0
         */
        virtual int remove(const long userid, const int fieldid) = 0;

        /** 
         *   The Keep's specific interface
         *   Schema: [userid,fieldid, [encrypted field(s)?]]
         *   provides an additional layer
         */
        virtual TheKeepRecord getchip(const long userid, const int fieldid) = 0;
        virtual void putchip(const long userid, const int fieldid, const string &value) = 0;
    };

} // namespace thekeep
