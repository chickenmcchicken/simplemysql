#include "../include/database.hpp"

//DEFULT CONFIG FOR LOCAL DB
int main()
{


    database Database;
    if(Database.getPort()==0 ||Database.getIP()==NULL || Database.getPassword()==NULL || Database.getDBName()==NULL ||Database.getUser()==NULL)
    {
        Database.setIP("127.0.0.1");
        Database.setPort(3306);
        Database.setDBName("test");
        Database.setPassword("");
        Database.setUser("root");
        Database.init();

        return 0;


    }
    
}