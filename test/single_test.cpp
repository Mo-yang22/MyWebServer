#include <iostream>
#include <pthread.h>
using namespace std;
class single{
public:
    static single* getinstacnce();
private:
    //私有静态指针变量指向唯一实例
    static single* p;
    //静态锁,是因为静态成员函数只能操作静态变量
    static pthread_mutex_t lock;
    //私有化构造函数
    single(){
        pthread_mutex_init(&lock,NULL);
    }
    ~single();
};
//静态成员必须在类的外部进行定义和初始化
pthread_mutex_t single::lock;

single* single::p=NULL;

single* single::getinstacnce()
{
    if(p==NULL)
    {
        pthread_mutex_lock(&lock);
        if(p==NULL)
        {
            p= new single;
            cout<<"new"<<endl;
        }
        pthread_mutex_unlock(&lock);
    }
    return p;
}
int main()
{
    single* s=single::getinstacnce(); 
    single* s1=single::getinstacnce();
    cout<<s<<endl<<s1<<endl;
    return 0;
}