#include <string>
#include <set>

class Message
{
    friend class Folder;
public:
    explicit Message(const std::string &str = "")
        : contents(str) { }
    Message(const Message& m)
        : contents(m.contents), folders(m.folders)
    {
        add_to_Folders(m);
    }
    Message& operator=(const Message& rhs)
    {
            remove_from_Folders();
            contents = rhs.contents;
            folders = rhs.folders;
            add_to_Folders(rhs);
            return *this;
    }
    ~Message()
    {
        remove_from_Folders();
    }
    void save(Folder&);
    void remove(Folder&)
    {
        folders.erase(&f);
        f.remMsg(this);
    }
    friend void swap(Message& lhs, Message& rhs);
private:
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders(const Message&)
    {
        for(auto f : m.folders)
            f->addMsg(this);
    }
    void remove_from_Folders()
    {
        for(auto f : folders)
            f->remMsg(this);
        folders.clear();
    }
};

void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    for(auto f : lhs.folders)
        f->remMsg(&lhs);
    for(auto f : rhs.folders)
        f->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for(auto f : lhs.folders)
        f->addMsg(&lhs);
    for(auto f : rhs.folders)
        f->addMsg(&rhs);
}