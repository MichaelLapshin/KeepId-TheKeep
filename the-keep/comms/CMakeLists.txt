# ----------------------------------------------------------------------------
#  CMake file for the Communication Libraries: Kafka & Cassandra
# ----------------------------------------------------------------------------

# Create a DBnMessaging library
add_library(DBnMessaging STATIC
            KafkaDriver.cpp
            CassandraDriver.cpp
)

message("Added Keep's DB&Messaging library.")
