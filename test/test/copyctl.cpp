#include <iostream>
#include <set>
using namespace std ;
//copy控制
class Message ;
class Folder {
public :
    void addMsg(Message*) {}
    void remMsg(Message*) {}
} ;

class Message {
    friend class Folder ;
public :
    explicit Message(const string &str = ""):content(str) {}
    Message(const Message&) ;
    ~Message() ;
    Message& operator=(const Message& m) ;
    void save(Folder&folder) ;
    void remove(Folder&) ;
private :
    string content ;
    set<Folder*>folders ;
    void add_to_folders(const Message& ) ;
    void remove_from_folders() ;
} ;

void Message::save(Folder&f) {
    folders.insert(&f) ;
    f.addMsg(this) ;
}

void Message::remove(Folder& f) {
    folders.erase(&f) ;
    f.remMsg(this) ;
}

//Message类的拷贝控制成员
void Message :: add_to_folders(const Message& m) {
    for(auto f: m.folders) {
        f->addMsg(this) ;
    }
}

Message::Message(const Message&m) :content(m.content), folders(m.folders){
    add_to_folders(m) ;
}

void Message::remove_from_folders() {
    for(auto f: folders) {
        f->remMsg(this) ;
    }
}

Message :: ~Message() {
    remove_from_folders() ;
}

Message& Message :: operator=(const Message& tmp) {
    remove_from_folders() ;
    content = tmp.content ;
    folders = tmp.folders ;
    add_to_folders(tmp) ;
    return *this ;
}
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

