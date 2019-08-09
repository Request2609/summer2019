#include <iostream>
#include <memory>
using namespace std ;
//饿汉模式:线程安全
//创建并初始化private static变量
//私有化构造方法
//创建单利对象的静态方法并返回创建的单利对象
class example {
public :
    ~example() {}
private :
    example() {} 
    static const example ex  ;
public :
    static example getExample() {
        return ex ;
    }
} ;

//懒汉模式：先不创建对象，在第一个用的时候才创建对象，线程不安全
//步骤：创建私有private static 变量
//私有构造方法
//创建单利对象的static getsingleton方法
class lazy {
private:
    lazy() {}   
    static lazy* lz;
public :
    ~lazy() ;
public :
    lazy getSigleton() {
        if(lz == NULL) {
            lz = new lazy() ;
        }
        return *lz ;
    }
} ;

/*
 在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。 
 请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 * */
//输入数据
#include <vector>
using namespace std ;
int getData() {
    return 1 ;         
}
