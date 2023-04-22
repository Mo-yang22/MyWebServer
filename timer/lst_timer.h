#ifndef LST_TIMER
#define LST_TIMER
#define MAX_FD 65536           //最大文件描述符
#include <vector>
#include <time.h>
#include <unordered_map>
#include "../log/log.h"
using namespace std;
//连接资源结构体成员需要用到定时器类
//需要前向声明
class util_timer;
//连接资源
struct client_data
{
    //客户端socket地址
    sockaddr_in address;
    //本地?socket文件描述符
    int sockfd;
    //定时器
    util_timer *timer;
};
client_data users_timer[MAX_FD];

class util_timer
{
public:
    util_timer() : prev(NULL), next(NULL) {}

public:
    //超时时间
    time_t expire;
    //回调函数
    void (*cb_func)(client_data *);
    //连接资源
    client_data *user_data;
    //前向计时器
    util_timer *prev;
    //后继计时器
    util_timer *next;
};

class timer_heap
{
public:
    timer_heap():count(0){}
    ~timer_heap(){
        count=0;
        data.clear();
        data.shrink_to_fit();
    }
    void add_timer(int timer){
        if(!users_timer[timer].timer)
            return;
        data.push_back(timer);
        ref_[timer]=count++;
        shift_up(count-1);
    }
    void adjust_timer(int timer){
        if(!users_timer[timer].timer)
            return;
        shift_down(timer);
        shift_up(timer);
    }
    void del_timer(int timer){
        if(!users_timer[timer].timer)
            return;
        if(count >0){
            swap(data[timer],)
        }      
    }
private:
    void shift_down(int i){
        int k =i;
        while(2 * k + 1 < count){
            int j = 2 * k + 1;
            if((j+1)<count 
            && (users_timer[data[j]].timer->expire>
            users_timer[data[j+1]].timer->expire))
                j++;
            if(data[k] > data[j]){
                swap(ref_[data[k]],ref_[data[j]]);
                std::swap(data[k],data[j]);
                k = j;
                continue;
            }
            break;
        }
    }
    void shift_up(int i){
        int k = i;
        while(k>0){
            int j=(k-1)/2;
            if(j >0 &&data[j]>data[k]){
                std::swap(data[j],data[k]);
                k = j;
                continue;
            }
            break;
        }
    }
private:
    int count = 0;
    //保存users_timer中的索引到data索引的映射
    unordered_map<int,int> ref_;
    vector<int> data;
};
#endif
