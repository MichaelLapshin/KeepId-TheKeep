/* The Keep DB aka Holy Cow chipschema */

CREATE KEYSPACE keepid_test
WITH REPLICATION = { 'class' : 'SimpleStrategy', 'replication_factor' : 1 };


CREATE TABLE keepid_test.users_chips (
    userid bigint, /* 64 bit may be an overkill, but safer */
    fieldid int,
    chip text,
    updated timestamp, /* last update time */
    PRIMARY KEY ((userid), fieldid)
);

-- insert test data
insert into keepid_test.users_chips (userid,fieldid,chip,updated) values (123,23,'EncyptedChips',dateof(now()));
