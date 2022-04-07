
### Find external libaries ###   --> not needed at this level
# find_library(RD_KAFKA_PATH rdkafka)
# message("RD-CPP-Kafka library found at: ${RD_KAFKA_PATH}")
# find_library(CASSANDRA_DRIVER_PATH cassandra-cpp-driver)
# message("Cassandra-CPP-Driver found at: ${CASSANDRA_DRIVER_PATH}")

# attempt to include Kafka library - seems not needed
#target_include_directories(modern-cpp-kafka PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>")
#find_library(MODERN_KAFKA_PATH modern-cpp-kafka)
#message("Modern-CPP-Kafka library found at: ${MODERN_KAFKA_PATH}")

#---------------------------
# Check librdkafka library
#---------------------------
# if (DEFINED ENV{LIBRDKAFKA_ROOT})
#     set(LIBRDKAFKA_INCLUDE_DIR $ENV{LIBRDKAFKA_ROOT}/include)
#     set(LIBRDKAFKA_LIBRARY_DIR $ENV{LIBRDKAFKA_ROOT}/lib)
# else ()
#     set(LIBRDKAFKA_INCLUDE_DIR /usr/local/include)
#     set(LIBRDKAFKA_LIBRARY_DIR /usr/local/lib)
# endif ()

# message(STATUS "librdkafka include directory: ${LIBRDKAFKA_INCLUDE_DIR}")
# message(STATUS "librdkafka library directory: ${LIBRDKAFKA_LIBRARY_DIR}")

# Create a DBnMessaging library
add_library(DBnMessaging STATIC
            CommsConfig.hpp
            KafkaDriver.hpp
            KafkaDriver.cpp
            CassandraDriver.hpp
            CassandraDriver.cpp
            TheKeepDB.hpp
            TheKeepMessaging.hpp            
)

message("Added Keep's DB&Messaging library.")
