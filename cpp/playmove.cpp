#include "iostream"
#include "utility"
#include "string"
#include "vector"
#include "cstdlib"

using namespace std;

class movet
{
static int id; 
public:
    int mid;
    int size;
    char *buff;
    movet(){
        mid = id++;
        size = 0;
        buff = 0;
    }
    movet(int n, const char *src, int line):size(n){
        mid = id++;
        printf("%d init================%d\n", mid, line);
        buff = (char*)malloc(n*sizeof(int));
        memcpy(buff, src, n);
    }
    movet(const movet &rhs){
        printf("%d you copy it, i know\n", mid);
        size = rhs.size;
        memcpy(buff, rhs.buff, size);
    }
    movet(movet &&rhs){
        printf("%d you move it, i know\n", mid);
        size= rhs.size;
        buff = rhs.buff;
        rhs.clear();
    }

    movet& operator=(movet &rhs){
        printf("%d copy ===============\n", mid);
        if(this != &rhs){
            size = rhs.size;
            memcpy(buff, rhs.buff, size);
        }
        return *this;
    }

    movet& operator=(movet &&rhs){
        printf("%d copy rvalue==========\n", mid);
        if(this != &rhs){
            swap(size, rhs.size);
            swap(buff, rhs.buff);
        }
        return *this;
    }

    void clear(){
        size = 0;
        buff = 0;
    }

    void show(){
        printf("%d show->size: %d buff: %s\n", mid, size, buff);
    }
    ~movet(){
        if(!buff){
            printf("%d end ~movet %d buff:empty\n", id, size);
        }
        else{
            printf("%d end ~movet %d buff:%s\n", id, size, buff);
            // free(buff);
        }
    }

    /* data */
};

int movet::id = 1;


movet test(){
    movet t(5, "test\0", __LINE__);
    t.buff[0] = 'a';
    return t;
}

movet test2(){
    movet t(5, "test\0", __LINE__);
    return move(t);
}

void overload(const int &x){
    printf("lvalue %d\n", x);
}

void overload(int &&x){
    printf("rvalue %d\n", x);
}

template<class T>
void fn(T &&x){
    overload(x);
    overload(forward<T>(x));
}

int main(){
    // movet t = test();
    movet *t = new movet(5, "test\0", __LINE__);
    // movet t1 = move(*t);
    delete t;
    t->show();

    int n = 100;
    fn(move(n));

    // t.show();
    // movet t1(5, "test\0", __LINE__);
    // t1 = t;
    // t1 = test();
    // t1 = test2();
    return 0;
}