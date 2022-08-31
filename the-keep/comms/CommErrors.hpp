/**
 * @filename: CommErrors.hpp
 * @description: Custom commiunication exceptions header
 * @author: KeepId {IL}
 * @date: 19 May 2022
 */

#pragma once
#include <stdexcept>

namespace thekeep 
{
    /// Class to cover all possible Database Errors; will be expanded in the future
    class DatabaseException: public std::runtime_error 
    {
        public:
            using runtime_error::runtime_error;  // re-use parent's constructors
    };

    /// Class to cover all possible Messaging Bus Errors; will be expanded in the future
    class MessagingException: public std::runtime_error 
    { 
        public:
            using runtime_error::runtime_error;
    };
}   