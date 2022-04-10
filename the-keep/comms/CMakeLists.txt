# ----------------------------------------------------------------------------
#  CMake file for the Communication Libraries: Kafka & Cassandra
# ----------------------------------------------------------------------------

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
