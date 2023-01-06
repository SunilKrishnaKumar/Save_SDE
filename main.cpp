#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h> 
#include <mysql/jdbc.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main()
{
    try
    {
        // Create a connection to the MySQL server
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con = driver->connect("localhost", "sqluser", "qwerty");

        // Select the database
        con->setSchema("save_db");

        // Create a statement object
        sql::Statement *stmt = con->createStatement();

        // Execute the SELECT query
        string query = "SELECT t.* FROM Transactions t  
                        JOIN (SELECT DISTINCT merchant_cat_code FROM  Transactions) m
                        ON t.merchant_cat_code = m.merchant_cat_code
                        where t.transaction_amount > (10)*(SELECT avg(transaction_amount) 
                        FROM Transactions where merchant_cat_code = t.merchant_cat_code) ";
        sql::ResultSet *res = stmt->executeQuery(query);

        // Iterate over the result set and print the rows
        while (res->next())
        {
            cout << res->getInt(1) << " " << res->getString(2) << endl;
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
