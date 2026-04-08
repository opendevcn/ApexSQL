#include "ax_querys.hpp"

auto AxQuerys::QuerysObject::querys(const std::string &line) -> AxStatusCode::ApexStatusCode
{

    if ("create database " == line.substr(0, 16))
    {
        std::string database_name{AxParserDatabaseName::ParserDatabaseNameObject::parseDatabaseName(line)};
        if (!database_name.empty())
        {
            AxCreateDatabase::CreateDatabaseObject::createDatabase(database_name);
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
    }

    if ("show databases" == line)
    {
        AxShowDatabases::ShowDatabasesObject::showDatabases();
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    if ("use " == line.substr(0, 4))
    {
        std::string database_name{line.substr(4)};
        AxHandleSystem::HandleSystemObject::strip(database_name);
        AxUseDatabase::UseDatabaseObject::useDatabaseObject(database_name);
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    if ("create table " == line.substr(0, 13))
    {
        std::string database_name{AxObjectStatusManage::ObjectStatusManage::getDatabaseObjectName()};
        if (database_name.empty() || "none" == database_name)
        {
            std::cerr << "error: you must use a database object first!" << std::endl;
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        auto [table_name, field_names, field_types, status_code] = AxParserQueryCreateTable::ParserQueryCreateTableObject::parserQueryCreateTable(line);
        if (!status_code)
        {
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        AxCreateTable::CreateTableObject::createTableObject(database_name, table_name, field_names, field_types);
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    if ("show tables" == line)
    {
        std::string database_name{AxObjectStatusManage::ObjectStatusManage::getDatabaseObjectName()};
        if (database_name.empty() || "none" == database_name)
        {
            std::cerr << "error: you must use a database object first!" << std::endl;
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        AxShowTables::ShowTablesObject::showTables(database_name);
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    if ("show struct " == line.substr(0, 12))
    {
        std::string database_name{AxObjectStatusManage::ObjectStatusManage::getDatabaseObjectName()};
        if (database_name.empty() || "none" == database_name)
        {
            std::cerr << "error: you must use a database object first!" << std::endl;
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        std::string table_name{line.substr(12)};
        AxHandleSystem::HandleSystemObject::strip(table_name);
        AxShowTableStruct::ShowTableStructObject::showTableStructObject(database_name, table_name);
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    if ("get current database object" == line)
    {
        std::string database_name{AxObjectStatusManage::ObjectStatusManage::getDatabaseObjectName()};
        if (database_name.empty() || "none" == database_name)
        {
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        std::cout << "current database object: '" << database_name << "'." << std::endl;
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    if ("get current object table number" == line)
    {
        std::string database_name{AxObjectStatusManage::ObjectStatusManage::getDatabaseObjectName()};
        if (database_name.empty() || "none" == database_name)
        {
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        std::string table_number{AxObjectStatusManage::ObjectStatusManage::getDatabaseTableNumber()};
        if (table_number.empty())
        {
            std::cerr << "fatal error: exist database object but can not show table number -> from database object '" << database_name << "'!" << std::endl;
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
        std::cout << "current object table number: '" << table_number << "'." << std::endl;
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    return AxStatusCode::ApexStatusCode::UNEXPECTED;
}