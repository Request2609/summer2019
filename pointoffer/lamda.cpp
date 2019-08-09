#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std ;

int main()
{
    int a = 10 ;
    int cc =1 ;
    string word ;
    //标准格式
    //[capture list](parameter list)->return type{function body} ;
    //capture　list 是捕获列表，在本函数中已定义的局部变量可以传入到lamda表达式中
    //parameter list 是参数列表
    //箭头指向的第一个是返回类型
    //大括号里面是函数体
    //下面是一个小例子：
    //lamda值捕获是在创建时拷贝该值，而不是调用时拷贝
    auto f = [a] (int i, string s) ->int {
        cout << i << "   " << s <<"    " << a<< endl ;
        return 9 ;
    } ;
    int ret = f(20, "linux");
    //当我们混合使用显示捕获和隐式捕获的时候，[]中第一个元素必须是&或者=，
    //此符号制定了默认捕获方式为引用或值
    //cc隐式捕获，值捕获方式
    for_each(word.begin(), word.end(), [=, &a]{cout << cc <<"     "<< a<< endl ;}) ;
    //a隐式捕,引用捕获,注意在已经设置隐式引用捕获的情况下
    //不能显示的往捕获列表中传引用,隐式值捕获也是同样的道理
    for_each(word.begin(), word.end(), [&, a]{cout << cc <<"     "<< a<< endl ;}) ;
    cout << ret << endl ;
    return 0;
}

int biggies(vector<string>&word, vector<string>::size_type sz) {
    //按照字典排序
    sort(word.begin(), word.end()) ;
    //按照长度排序
    stable_sort(word.begin(), word.end(), [](const string&a, const string&b){return a.size()<b.size();}) ;
    //获取一个迭代器,指向一个满足size>=sz的元素
    auto wc = find_if(word.begin(), word.end(), [sz](const string&a){return a.size()>=sz;}) ;
    //获取一个迭代器，指向第一个满足size>=sz的元素
    auto count = word.end()- wc;
    for_each(wc, word.end(), [](const string& s){cout <<s << endl ;}) ;
    cout << endl ;
       
}   
