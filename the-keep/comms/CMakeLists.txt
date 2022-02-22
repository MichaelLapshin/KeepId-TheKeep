
### Find external libaries ###
find_library(MODERN_KAFKA_PATH modern-cpp-kafka)
message("Modern-CPP-Kafka library found at: ${MODERN_KAFKA_PATH}")

find_library(CASSANDRA_DRIVER_PATH cassandra-cpp-driver)
message("Cassandra-CPP-Driver found at: ${CASSANDRA_DRIVER_PATH}")

# Create a DBnMessaging library
add_library(DBnMessaging STATIC
            KafkaDriver.hpp
            KafkaDriver.cpp
            CassandraDriver.hpp
            CassandraDriver.cpp
            TheKeepDB.hpp
            TheKeepMessaging.hpp            
)

message("Added Keep's DB&Messaging library.")
