/**
 * @filename: CommsConfig.hpp
 * @description: Temporary Kafka and Cassandra/DB configuration; will be re-factored to read config from a file
 * @author: KeepId {IL}
 * @date: March 27, 2022
 */

#pragma once
#include <string>

namespace thekeep {

    // Kafka Configurations constants
    const std::string KAFKA_URL = "thekeep_kafka_1"; // maybe "127.0.0.1"
    const std::string KAFKA_URLPORT = "thekeep_kafka_1:9092"; // maybe "127.0.0.1:9093"
    const uint KAFKA_PORT = 9093;
    const std::string KAFKA_CONTROL_TOPIC = "KeepId-Control";
    const std::string KAFKA_DATA_TOPIC = "KeepId-Data";

    // DB Configurations constants
    const std::string CASSANRDA_URL = "thekeep_cassandra"; // maybe "127.0.0.1"
    const uint CASSANRDA_PORT = 7007;
    const std::string CASSANRDA_URLPORT = "thekeep_cassandra:7007"; // maybe "127.0.0.1:7007"
    const std::string CASSANRDA_DB = "KeepId";
    const std::string CASSANRDA_SCHEMA = "KeepIdCow";
    const std::string CASSANRDA_USER = "cassandra";
    const std::string CASSANRDA_PASSWORD = "cassandra";

} // namespace thekeep