#pragma once
#include<iostream>
#include <string>
#include <list>
#include <memory>
#include <map>
#include <set>
using namespace std ;

class dict ;

class redisDb
{
public:
    redisDb() {}
    ~redisDb() {}
private :
    //保存所有键的过期时间
    map<string, long long> expire ;
    //redis对象管理dict对象
    shared_ptr<dict>dic ;
}; 
//字典
class dict {
private:
    //redisDb中的list对象，键值对，键不能有重复
    map<string, list<string>> ls ;
    map<string, set<string>> comset ;
    //hash集合
    map<string, map<string, string>>hset ;
    map<string, string>com ;
} ;
