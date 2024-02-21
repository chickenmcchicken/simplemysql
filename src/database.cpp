#include "../include/database.hpp"



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

