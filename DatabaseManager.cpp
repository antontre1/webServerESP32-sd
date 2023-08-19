#include <ArduinoJson.h>
#include "DatabaseManager.h"
#include <sqlite3.h>
#include <SD.h> // Bibliothèque pour le système de fichiers SD

sqlite3 *db; // Declare a single database pointer


void initDatabaseManager() {
        if (db_open("/mydatabase.db", &db)) {
        return;
    }

    db_exec(db, "CREATE TABLE IF NOT EXISTS temperatures (id INTEGER PRIMARY KEY, value REAL, timestamp INTEGER);");

    sqlite3_close(db);
}

int db_open(const char *filename, sqlite3 **db) {
    int rc = sqlite3_open(filename, db);
    if (rc) {
        Serial.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
        return rc;
    } else {
        Serial.printf("Opened database successfully\n");
    }
    return rc;
}

char *zErrMsg = 0;
int db_exec(sqlite3 *db, const char *sql) {
    Serial.println(sql);
    int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        Serial.printf("Operation done successfully\n");
    }
    return rc;
}


// Callback function to retrieve the results
static int query_callback(void *data, int argc, char **argv, char **azColName) {
    DynamicJsonDocument *jsonDoc = reinterpret_cast<DynamicJsonDocument *>(data);
    JsonArray jsonArray = jsonDoc->to<JsonArray>();
    JsonObject jsonObj = jsonArray.createNestedObject();
    
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "id") == 0) {
            jsonObj["id"] = atoi(argv[i]);
        } else if (strcmp(azColName[i], "value") == 0) {
            jsonObj["value"] = atof(argv[i]);
        } else if (strcmp(azColName[i], "timestamp") == 0) {
            jsonObj["timestamp"] = atol(argv[i]);
        }
    }
    return 0;
}

int db_query_temperatures(int startTime, int endTime, String &result) {
    DynamicJsonDocument jsonDoc(1024);
    String sql = String("SELECT * FROM temperatures WHERE timestamp BETWEEN ") + startTime + " AND " + endTime + ";";
    char *errMsg;
    int rc = sqlite3_exec(db, sql.c_str(), query_callback, &jsonDoc, &errMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    }
    serializeJson(jsonDoc, result);
    return SQLITE_OK;
}
