class NoDefault{
public:
    NoDefault(int n){}
};

class C{
public:
    C() : nd(0) {}
private:
    NoDefault nd;
};

int main(){
    C c;

    return 0;
}