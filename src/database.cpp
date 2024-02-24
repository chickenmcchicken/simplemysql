#include "../include/database.hpp"

#include <format>
#include <string>
#include <cstring>
#include <algorithm> 



void database::setIP(const char* ip)
{
    database::info.ip= ip;
}



const char* database::getIP()
{
    return database::info.ip;

}

void database::setDBName(const char* name)
{
    database::info.db_name= name;

}

const char* database::getDBName()
{
    return database::info.db_name;
}


void database::setPort(int port)
{
    database::info.port=port;
}


int database::getPort()
{
    return database::info.port;
}


/*
TODO:
Figured out i have  to modify the code later on to check on any other user since there
can be more than one person accessing the db in the same time
*/
void database::setUser(const char* user)
{
    database::info.username =  user;
}


const char* database::getUser()
{
    return database::info.username;
}

void database::setPassword(const char* password)
{
    database::info.password= password;
}

const char* database::getPassword()
{
    return info.password;
}

bool database::connect()
{   
    
    

    /*
    TODO:
    chage local host to an actual db server
    */

   try
   {
   
        if(!database::db) return 1; //didn't initilzaie correctly;
        database::db= mysql_real_connect(db, database::info.ip, database::info.username, database::info.password, database::info.db_name, database::info.port, nullptr, 0);
        
        if(database::db)
        {
            std::cout << "done" <<std::endl;
            return database::status = true;


        }
        else
        {
            std::cout << mysql_error(db) << std::endl;
            return database::status = false;
            

        }
    }
    catch(const std::exception& e)
    {
    std::cerr << e.what() << '\n';
     return database::status= false;
    }


}


/*
Pings the database and checks the status
will be imporant, if db aint connected then program will not run

*/
bool database::callback_status()
{

    int db_status = mysql_ping(database::db);
    if(db_status == 0 ) return database::status = true;
    else return database::status = false;

}





void database::init()
{
    if(database::getDBName()==NULL)
    {
        std::cout << "database name is null" <<std::endl;
        return;
    }
    if(database::getPort()==0)
    {
        std::cout << "port is null" <<std::endl;        
        return;
    }
    if(database::getUser()==NULL)
    {
        std::cout << "user is null" <<std::endl;
        return;
    }
    if(database::getPassword()==NULL)
    {
    std::cout << "password is null" <<std::endl;
        return;
    }    
    if(database::getIP()==NULL)
    {
        std::cout << "Ip is null" <<std::endl;
        return;
    }
    if (callback_status() == true)
    {
        std::cout << "db is already initiliazed" <<std::endl;
        return;
    }
    database::connect();
    std::cout <<"setup complete" <<std::endl;
}

void database::shutdown()
{
    mysql_close(database::db);
}


void database::new_table(std::string table_name,std::string data_type, std::string  column)
{
    std::string st = std::format("CREATE TABLE IF NOT EXITS {}({}{});", table_name, column, data_type);
    mysql_query(database::db, table_name.c_str());
}






void database::new_column(std::string table_name, std::string data_type, std::string column)
{
    std::string st = std::format("ALTER TABLE {} ADD IF NOT EXISTs {} {};", table_name, column, data_type);
}

void database::new_column(std::string table_name, std::string data_type[], std::string column[])
{
    int x = 0 ;//place holder to loop theough array
    // we will be looping through columns
    do
    {
        database::new_column(table_name, data_type[x], column[x]);
    }
    while( x <= sizeof(column)/sizeof(column[0]));
}


/*
type args: column, database, table row


*/
void database::_delete(std::string type, std::string name, std::string table = "")
{
    std::string db_s = std::string(database::info.db_name);
    //lowercases type
    for(auto x: type)
    {
        x= tolower(x);
    }

    if(type =="database")
    {
        std::string st= std::format("DROP DATABASE IF EXISTS {};", name); 
        mysql_query(db, st.c_str());
    }
    else if(type == "table")
    {
        std::string st= std::format("DROP TABLE IF EXISTS {};", name); 
        mysql_query(db, st.c_str());


    }
    else if(type == "column")
    {
        std::string st= std::format("DROP COLUMN IF EXISTS {};", name); 
        mysql_query(db, st.c_str());
    
    }
    else if(type == "row")
    {
        std::string st= std::format("DROP ROW IF EXISTS {};", name); 
        mysql_query(db, st.c_str());
    
    }
    else
    {
        std::cerr << "invalid usage" << std::endl;
    }
}


void database::shutdown()
{
    mysql_close(database::db);
}