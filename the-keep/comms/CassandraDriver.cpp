#include <stdio.h>
#include <cassandra.h>

#include "CommsConfig.hpp"
#include "CassandraDriver.hpp"
using namespace thekeep;

// TODO: add implementation

int CassandraDriver::connect(const string &ip, const string &user, const string &pwd)
{
  /* Setup and connect to Cassandra cluster */
  //connect_future = NULL;        // CassFuture*
  cluster = cass_cluster_new();   // CassCluster*
  session = cass_session_new();   // CassSession*
  const char *hosts = ip.c_str(); // 

  /* Add contact points */
  cass_cluster_set_contact_points(cluster, hosts);
  cass_cluster_set_credentials(cluster, user.c_str(), pwd.c_str()); 

  /* Provide the cluster object as configuration to connect the session */
  connect_future = cass_session_connect(session, cluster);

  // dup todo
  if (cass_future_error_code(connect_future) == CASS_OK)
  {
    CassFuture *close_future = NULL;

    //....
  }
  else
  {
    /* Handle error */
    const char *message;
    size_t message_length;
    cass_future_error_message(connect_future, &message, &message_length);
    fprintf(stderr, "KeepDB->Cassandra: Unable to connect: '%.*s'\n", (int)message_length, message);
  }

  return 0;
}

//
void CassandraDriver::disconnect()
{
  cass_future_free(connect_future);
  cass_cluster_free(cluster);
  cass_session_free(session);
}

TheKeepRecord CassandraDriver::get(const long userid, const int fieldid)
{
  string result_field; 
  TheKeepRecord record;

  if (cass_future_error_code(connect_future) == CASS_OK)
  {
    CassFuture *close_future = NULL;

    /* Build statement and execute query */
    const char *queryTest = "SELECT release_version FROM system.local"; // sanity check
    const char *queryChip = "SELECT chip FROM keepid_test.users_chips where userid=? and fieldid=?"; //chip only as well
    const char *query = "SELECT * FROM keepid_test.users_chips where userid=? and fieldid=?"; //chip only as well
    CassStatement *statement = cass_statement_new(query, 2);
    cass_statement_bind_int64(statement, 0, userid);
    cass_statement_bind_int32(statement, 1, fieldid);

    CassFuture *result_future = cass_session_execute(session, statement);

    if (cass_future_error_code(result_future) == CASS_OK)
    {
      /* Retrieve result set and get the first row */
      const CassResult *result = cass_future_get_result(result_future);
      const CassRow *row = cass_result_first_row(result);

      if (row)
      {
        const CassValue *cvUserId = cass_row_get_column_by_name(row, "userid");
        const CassValue *cvFieldId = cass_row_get_column_by_name(row, "fieldid");
        const CassValue *cvChip = cass_row_get_column_by_name(row, "chip");
        const CassValue *cvTimestamp = cass_row_get_column_by_name(row, "updated");

        const char *chip;
        size_t chip_length;
        cass_value_get_string(cvChip, &chip, &chip_length);
        printf("DEBUG: Encrypted data chip: '%.*s'\n", (int)chip_length, chip);
        result_field = string(chip);
        
        long usrid; 
        cass_value_get_int64(cvUserId, &usrid);
        int fldId;
        cass_value_get_int32(cvFieldId,&fldId);
        cass_int64_t tmstamp;

        // TODO: maybe read a timestamp; 
        /* 'time' uses a signed 64-bit integer */
        // cass_statement_bind_int64(statement, 2, time_of_day);
        // cass_value_get_time(cvFieldId,&fldId);

        record.userid = usrid;
        record.chip = chip;
        record.fieldid = fldId;
      }

      cass_result_free(result);
    }
    else
    {
      /* Handle error */
      const char *message;
      size_t message_length;
      cass_future_error_message(result_future, &message, &message_length);
      fprintf(stderr, "KeepDB->Cassandra: Unable to run query: '%.*s'\n", (int)message_length, message);
    }

    cass_statement_free(statement);
    cass_future_free(result_future);

    /* Close the session */
    close_future = cass_session_close(session);
    cass_future_wait(close_future);
    cass_future_free(close_future);
  }
  else
  {
    /* Handle error */
    const char *message;
    size_t message_length;
    cass_future_error_message(connect_future, &message, &message_length);
    
    fprintf(stderr, "KeepDB->Cassandra: Unable to connect: '%.*s'\n", (int)message_length, message);
  }

  return record;
}

int CassandraDriver::put(const long userid, const int fieldid, const string &value)
{
  // TODO:
  return 0;
}
