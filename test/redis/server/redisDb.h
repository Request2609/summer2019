#pragma once
#include<iostream>
#include <string>
#include <list>
#include <vector>
#include <memory>
#include <map>
#include <set>
using namespace std ;

class redisDb ;
class dbObject ;

//数据库对象
class redisDb {
private :
    vector<shared_ptr<dbObject>> db ;
public :
    //数据库编号
    int num ;
    void append(shared_ptr<dbObject>rdb) { db.push_back(rdb); }
    //删除当前数据库中的一个对象
    void del() {
    }
} ;

class factory {
public :
    static shared_ptr<dbObject> getObject(string cmd) {
        if(cmd == "set") {
            shared_ptr<dbObject> tmp = make_shared<dbObject>() ;
            return tmp ;
        }   
        else {
            return nullptr ;
        }
    }
} ;

class dbObject {
public:
    dbObject() {}
    virtual ~dbObject() {}
public :
    virtual void set() ;
private :
    //保存所有键的过期时间
    //redis对象管理dict对象
    //shared_ptr<dict>dic ;
};

//set对象
class setCmd : dbObject {
public :
    void set() {} 
public :
    map<string, long long> expire ;
    int num ;
    string key ;
    string value ;
   // map<string, string>common ;
} ;

class hsetCmd : dbObject {
public :
    int num ;
} ;
/*
//字典
class dict {
private:
    //redisDb中的list对象，键值对，键不能有重复
    map<string, list<string>> ls ;
    map<string, set<string>> comset ;
    //hash集合
    map<string, map<string, string>>hset ;
    map<string, string>common ;
} ;*/
