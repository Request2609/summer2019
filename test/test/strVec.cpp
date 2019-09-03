#include <iostream>
#include <string>
#include <memory>
using namespace std ;

class strVec {
public :
    strVec():element(nullptr), firstFree(nullptr), cap(nullptr) {}//allocator成员进行默认初始化
    strVec(const strVec&) ;
    strVec (strVec&& s) noexcept;
    strVec& operator=(const strVec&) ;
    strVec& operator=(strVec&& tmp) noexcept ;
    ~strVec() ;
    void push_back(const string&) ;
    size_t size() ;
    size_t capacity() ;
    string* begin() const{ return element ; }
    string* end() const{ return firstFree ; }
    //...
private :
    static allocator<string>alloc ;
    void chkNAlloc() {if(size() == capacity()) realocate() ;}
    //工具函数，被拷贝函数，赋值运算符和析构函数所使用
    pair<string*, string*> allocNCopy(const string*, const string*) ;
    void free() ;
    void realocate() ;
    
    string* element ;//指向数组首元素的指针
    string* firstFree ;//指向数组第一个空闲元素的指针
    string* cap ; //指向数组尾后位置的指针
} ;

//移动赋值运算符
strVec& strVec ::  operator=(strVec&& s) noexcept{
    //自动检测自赋值
    if(&s != this) {
        free() ;//释放已有元素
        element = s.element ;
        firstFree = s.firstFree ;
        cap = s.cap ;
        s.element = s.firstFree = s.cap = nullptr ;
    }
    return *this ;
}

///移动cp构造函数
strVec :: strVec(strVec&& s) noexcept :
    element(s.element), firstFree(s.firstFree), cap(s.cap){
    s.element = s.firstFree = s.cap = nullptr ;
}

void strVec :: push_back(const string& s) {
    chkNAlloc() ;//确保有空间容纳新元素
    //将firstFree指向s字符串
    alloc.construct(firstFree++, s) ;
}

//alloc n copy成员
pair<string*, string*> strVec :: allocNCopy(const string*b, const string* e) {
    //分配空间保存给定范围中的元素，使用尾后指针减去首元素的指针，构造给定元素的副本
    auto data = alloc.allocate(e-b) ;
    //初始化并返回pair,该pair由data和uninitialized_copy的返回值构成
    return {data, uninitialized_copy(b, e, data)} ;
}

void strVec :: free() {
    //不能传递dealloc一个空指针,如果alloc为0,函数什么也不做
    //逆序销毁元素
    if(element) {
        for(auto p=firstFree; p!=element;) {
            alloc.destroy(--p) ;
        }
        //释放自己分配的空间
        alloc.deallocate(element, cap-element) ;
    }
}

//copy控制成员
strVec :: strVec(const strVec& s) {
    auto newData = allocNCopy(s.begin(), s.end()) ;
    element = newData.first ;
    firstFree = cap = newData.second ;
}

strVec :: ~strVec() { free(); }

strVec& strVec :: operator=(const strVec& tmp) {
    auto data = allocNCopy(tmp.begin(), tmp.end()) ;
    free() ;
    element = data.first ;
    firstFree = cap = data.second ;
    return *this ;
}

void strVec :: realocate() {
    //分配当前两倍的内存空间
    auto newCap = size()?2*size():1 ;
    //分配新内存
    auto newData = alloc.allocate(newCap) ;
    //将数据从旧内存copy到新内存
    auto dest = newData ;//指向新数组中下一个
    auto elem = element ; //指向就数组中下一个空闲元素
    for(size_t i=0; i!=size(); i++) {
        alloc.construct(dest++, move(*elem++)) ;
    }
    free();
    element = newData ;
    firstFree = dest ;
    cap = element+newCap ;
}

int main() {
    
    return 0;
}

