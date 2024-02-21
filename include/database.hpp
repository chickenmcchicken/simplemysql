#pragma once

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <mysql_connection.h>
#include <mysql/mysql.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <mysql_driver.h>






struct db_info
{
    const char *ip;
    int8_t port;
    const char* username;
    const char* db_name;
    const char* password;
};

class database
{


    public:
        void init();
        bool status = false; // for future people that are seeing this why leave it unintiazlized if there is no DB status to begin with??? 
        MYSQL *db= mysql_init(NULL); //initilaes it
        bool connect();
        bool callback_status();
        MYSQL_RES fetch_data();// todo
        db_info info;



        void setIP(const char* ip);
        void setDBName(const char* name);
        void setUser(const char* user);
        void setPort(int port);
        void setPassword(const char* password);

  
        const char* getIP();      
        const char* getDBName();
        const char* getUser();
        int getPort();
        const char* getPassword();

        


};
#endif