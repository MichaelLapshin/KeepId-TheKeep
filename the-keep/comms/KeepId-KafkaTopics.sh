#!/bin/bash
# bash shell to setup KeepId's Kafka topics
# to be run during deployment (either with Docker file for Kafka container, or manually within the container)
echo "Creating KeepId's Kaka topics: KeepId-Control, KeepId-Data."
bin/kafka-topics.sh --create --topic KeepId-Control --bootstrap-server thekeep_kafka_1:9092
bin/kafka-topics.sh --create --topic KeepId-Data --bootstrap-server thekeep_kafka_1:9092

# if verification needed, you can uncomment the following lines to get info on the topic:
kafka-topics.sh --describe --topic KeepId-Control --bootstrap-server thekeep_kafka_1:9092
kafka-topics.sh --describe --topic KeepId-Data --bootstrap-server thekeep_kafka_1:9092
echo "Topics created"