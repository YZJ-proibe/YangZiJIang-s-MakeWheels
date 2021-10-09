### 纯虚函数
纯虚函数为了解决基类派生出对象不合理的情况，而被使用。

例如，动物作为一个基类可以派生出老虎、孔雀等子类，但动物本身生成对象明显不合常理。

```c++
#include <iostream>
#include <memory>
class Animals {
 public:
  virtual void roar() = 0;
};

class Tigers : public Animals {
 public:
  virtual void roar();
};

void Tigers::roar() { std::cout << "Tiger's roar" << std::endl; }

class Lions : public Animals {
 public:
  virtual void roar();
};

void Lions::roar() { std::cout << "Lions's roar" << std::endl; }

int main() {
  std::shared_ptr<Tigers> tiger = std::make_shared<Tigers>();
  std::shared_ptr<Lions> lion = std::make_shared<Lions>();
  tiger->roar();
  lion->roar();

  return 0;
}
```
抽象类不能实例化


菱形继承问题:
利用虚函数解决该问题

```c++
#include <iostream>
#include <memory>
class Animals {
 public:
  virtual void roar() = 0;
};

class Tigers : public Animals {
 public:
  virtual void roar();
};

void Tigers::roar() { std::cout << "Tiger's roar" << std::endl; }

class Lions : public Animals {
 public:
  virtual void roar();
};

void Lions::roar() { std::cout << "Lions's roar" << std::endl; }

class Liger : public Lions, Tigers {
 public:
  virtual void roar();
};

void Liger::roar() { std::cout << "Liger's roar" << std::endl; }

int main() {
  std::shared_ptr<Tigers> tiger = std::make_shared<Tigers>();
  std::shared_ptr<Lions> lion = std::make_shared<Lions>();
  std::shared_ptr<Liger> liger = std::make_shared<Liger>();

  tiger->roar();
  lion->roar();
  liger->roar();

  return 0;
}
```

Lambda表达式
匿名函数:没有名字的函数
写法[](函数参数)->函数返回类型{函数实现方法}
样例:
```c++
#include <algorithm>
#include <iostream>
int main() {
  int a[10] = {1, 2, 3, 4, 5};
  std::sort(a, a + 5, [=](int x, int y) -> bool { return x > y; });
  for (auto x : a) {
    std::cout << x << std::endl;
  }
  return 0;
}
/*样例输出
5
4
3
2
1
0
0
0
0
0*/
```
智能指针产生内存泄漏：
两个类中的智能指针互相指向，造成引用循环，造成内存泄漏。
为了解决循环引用而造成的内存泄漏：
引入弱指针weak_ptr的构造函数不会修改引用计数，从而不会对对象的内存进行管理，但是会检测所管理对象内存是否释放掉，从而避免非法访问。  

说说什么是大端小端，如何判断大端小端？
小端模式：低的有效字节存储在低的存储器地址。小端一般为主机字节；常用x86结构是小端很多arm,dsp都为小端模式
大端模式：高的有效字节存储在低的存储器地址。大端为网络字节;KEIL C51则为大端模式。

如何判断:
我们可以用联合体来判断什么是大端什么是小端，因为联合体变量总是从低地址存储
```c++
int fun1(){  
    union test{   
        char c;   
        int i; 
    };  
    test t; t.i = 1;  
    //如果是大端，则t.c为0x00，则t.c != 1，反之是小端  
    return (t.c == 1);  
} 
```
说说进程调度算法有哪些？
1.先来先服务调度算法
2.进程优先调度算法
3.高优先级优先调度算法
4.时间片轮转
5.多级反馈队列调度算法

1.先来先服务调度算法
把先进入队列的一个或几个进程调入内存，为其分配资源，创建进程，然后放进就绪队列。
2.进程现有调度算法
从后备队列里选若干个运行时间短的进程，把他们调入内存运行。
3.高优先级优先调度算法
从后备队列里选优先级高的进程先调入内存运行。
4.时间片轮转
后备队列里的每个进程都有一个相同的时间片，当时间片用完，该进程被送入就绪队列的末尾，再把处理机制分配给就绪队列的新对手进程
5.多级反馈队列调度算法
分为抢占式和非抢占式，综合前面多种调度算法

操作系统如何管理内存？
1.物理内存：物理内存有四个层次，寄存器，高速缓存，主存，磁盘
寄存器：速度最快，量少，贵
高速缓存次之
主存次之
磁盘速度最慢，量多，价格便宜

2.虚拟内存：操作系统为每一个进程分配一个独立的地址空间，但是虚拟内存，虚拟内存与物理内存存在映射关系，通过页表寻址完成虚拟地址和物理地址的转换。

Linux的用户态与系统态
1.内核态拥有最高权限，而用户态只能访问一部分指令
2.再进行中断，系统调用和异常的时候，会进入系统态
3.为什么要区分用户态和系统态？
再CPU所有的指令中一些指令是非常危险的？比如清内存，设置时钟等。所以区分用户态和系统态是处于安全考虑。

一个线程占多大内存？
一个linux线程大约占8M内存
linux的栈是同个缺页来分配内存的，不是所有的栈地址空间都分配内存。因此8M是最大消耗，实际内存的消耗只会实际需要的的内存（内存消耗每个再4k以内）

什么是页表？
页表是虚拟内存的概念。操作系统虚拟内存到物理内存的映射的表就是页表。
原因：不可能每一个虚拟内存的byte都对应到物理内存的地址。这张表将大的真正的物理内存地址也放不下，于是操作系统引入了页的概念。这样可以减少虚拟内存页对应物理内存页的映射表大小。

如果将每一个虚拟内存的Byte都对应到虚拟内存上，每个条目最少需要8字节（32位虚拟地址->32位物理地址）在4G内存的情况下，就需要32G的空间来存放对照表，那么这张表就大的真正的物理地址也存不下。

为什么要用虚拟内存：因为早期的内存分配方法存在问题：
进程的地址空间不隔离，会导致数据被随意修改。
内存使用效率低。
程序运行地址不确定。操作系统随机为进程分配内存空间，所以程序运行的地址不确定。

使用虚拟内存的好处：
实现内存的连续使用，虽然物理内存上不连续，但映射到虚拟内存上是连续的。
方便实现进程通信和内存共享。
扩大地址空间，每一个进程独占一个4G的内存，虽然实际内存没有那么大。
内存保护：防止不同进程对物理内存的争夺和践踏，可以对特定的内存地址提供写保护，防止恶意篡改。

虚拟内存的缺点:
虚拟内存需要额外构建一个数据结构，占用内存。
虚拟地址映射到物理地址浪费时间
页面换入换出耗时。


虚拟地址到物理地址是如何映射的关系数据结构？

操作系统为每一个进程维护了一个从虚拟地址到物理地址的映射关系的数据结构，叫页表。页表中的每一项都记录了这个页的基地址。
基地址+偏移地址=线性地址

32位系统能访问4G以上的内存？
正常情况下是无法访问的。原因是计算机使用二进制，每位只有0或1，32位正好是2^32,正好是4G,因其他原因还需要占用一部分空间，所以内存只够识别3G多。要使用4G以上就只能换64位的操作系统。

但是PAE技术就可以实现32为访问4GB以上的内存。

原因：PAE技术将地址扩展到了36位，这样，系统就能够容纳2^36=64GB的内存。

并行和并发
1.并发：对于单个cpu在一个时刻只有一个进程在运行，但是线程的切换时间则减少到纳秒的数量级，多个任务不停来回切换。
2.并行：对于多个cpu,多个进程同时运行。
3.区别：通俗来讲，他们虽然都说是多个进程同时运行，但是他们的同时不是一个概念。并行的同时是多个进程同一时刻进行。并发的同时是经过线程的快速切换，使得看上去任务同时都在运行的现象。

说说进程，线程，协程是什么？
进程：程序是指令，数据以及其组织形式的描述，而进程则是程序的实例。
线程：微进程，一个进程里更小粒度的执行单元。一个进程里包含多个进程并发执行任务。
协程：协程是微线程，在子程序内部执行，可在子程序内部中断，转而执行别的子程序，在适当的时候返回来接着执行。

区别：
线程与进程的区别：
一个线程属于一个进程，一个进程可以包含多个线程。
一个线程挂掉，会令对应的进程挂掉，一个进程挂掉，不会对其他进程造成影响。
进程是系统资源调度的最小单位：线程是cpu调度的最小单位。
进程系统开销大于线程，线程需要的资源更少。
进程执行时拥有独立的内存，多个线程共享进程的内存，如代码段，数据段，扩展段，每个线程拥有自己的栈段和内核栈。
进程切换时需刷新TLB并获得新的地址空间，然后切换硬件上下文和内核栈，线程切换时只需要切换硬件上下文和内核栈。
每个进程都有一个映射表，进程切换是指令的切换和映射表的切换，线程的切换是指令的切换。
通信方式不一样.


线程和协程的区别？
协程执行效率极高。协程直接操作内核栈，基本上没有内核切换的开销，所以上下文切换非常快。
协程不需要多线程的锁机制,因为协程属于一个线程
一个线程可以有多个协程

什么是孤儿进程，僵尸进程，如何解决僵尸进程？
孤儿进程是指父进程停止运行后，而他的一个或多个子进程还在运行，那么这些进程将成为孤儿进程，孤儿进程将被init进程（进程号1）所收养，并由init进程对他们的完整状态收集工作。

僵尸进程：是指一个进程fork()函数创建子进程，如果子进程退出，而父进程并没调用wait()或者waitpid()系统调用取得子进程的终止状态，那么子进程的进程描述符仍然保存在系统中，占用系统资源，这中进程成为僵尸进程。wait()清理掉子进程PID。

如何解决僵尸进程：
（1）一般，为了防止产生僵尸进程，在fork子进程之后我们都要及时用wait系统调用;同时当子进程退出的时候，内核都会给父进程发送一个SIGCHLD信号，所以我们可以建立一个捕获SIGCHLD信号的信号处理函数，在函数体中调用waitpid,就可以清理退出的子进程以访达到防止僵尸进程的目的。
（2）使用kill命令
打开终端并输入下面命令
ps aux| grep Z
会列出进程表中所有的僵尸进程的详细内容。
然后输入命令：
kill -s SIGCHLD pid(父进程PID)

进程间通信的方式：
管道  
套接字socket：用于不同主机之间的通信
消息队列
信号量
信号
共享内存

进程间同步的方式：
1.信号量semaphone:是一个计数器，可以用来控制多个进程对共享资源的访问。信号量用于实现进程间同步和互斥。P操作（递减操作）可以用于阻塞一个进程，V操作（增加操作）可以用于解除阻塞进程。
2.管道：一个进程通过调用管程的一个过程进入管程。在任何时候，只能有一个进程在管程中执行，调用管程的任何其他进程都被堵塞，以待管程可用。
3.消息队列：消息的链接表，放在内核中，消息独立于发送与接受进程，进程终止时，消息队列及其内容并不会被删除；消息队列可以实现消息的随机查询，可以按照消息类型读取。

多线程：
第一个多线程程序
```c++
#include <iostream>
#include <thread>
void hello() { std::cout << "hello current world!" << std::endl; }
int main() {
  std::thread t(hello);
  std::cout << "Test order" << std::endl;

  t.join();
  return 0;
}
```
join()可以保证线程在函数完成前结束
deatch()线程分类，可以自己进行回收

线程同步：
线程数据共享，避免多线程对数据进行抢夺
互斥量：pthread_mutex
```c++
#include <pthread.h>
#include <unistd.h>

#include <iostream>

static int ticks = 100;
pthread_mutex_t mutex;

void *sellticks(void *sg) {
  static int _indexTick = 1;
  while (true) {
    pthread_mutex_lock(&mutex);

    if (ticks > 0) {
      std::cout << pthread_self() << " Selling" << ' ' << _indexTick << " tick"
                << std::endl;
      ticks--;
    } else {
      pthread_mutex_unlock(&mutex);
      break;
    }
    
    _indexTick++;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t seller1;
  pthread_t seller2;
  pthread_t seller3;

  int sfg = pthread_create(&seller1, NULL, sellticks, NULL);
  int stg = pthread_create(&seller2, NULL, sellticks, NULL);
  int ssg = pthread_create(&seller3, NULL, sellticks, NULL);

  pthread_detach(seller1);
  pthread_detach(seller2);
  pthread_detach(seller3);

  pthread_exit(NULL);
  return 0;
}
```

线程产生死锁：
1.忘记解锁
2.线程多次加锁，由于已经加锁，已经拿到锁后，再次加锁，拿不到锁陷入死锁
3.一个线程占用了A资源，想要占用B资源，而B资源被另一个线程占用，线程B想要占用A资源，只用当这两个线程占用占用其想占用的资源后，才会对资源进行释放，造成死锁。

```c++
#include <pthread.h>

#include <iostream>
pthread_mutex_t mutex1, mutex2;

void *workA(void *sg) {
  pthread_mutex_lock(&mutex1);
  pthread_mutex_lock(&mutex2);
  while (true) {
    std::cout << "cpu use mutex1 and mutex2 source" << std::endl;
  }
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
}

void *workB(void *sg) {
  pthread_mutex_lock(&mutex2);
  pthread_mutex_lock(&mutex1);
  while (true) {
    std::cout << "cpu use mutex2 and mutex1 source" << std::endl;
  }
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex1);
}

int main() {
  pthread_mutex_init(&mutex1, NULL);
  pthread_mutex_init(&mutex2, NULL);

  pthread_t worker1, worker2;
  int sgw1 = pthread_create(&worker1, NULL, workA, NULL);
  int sgw2 = pthread_create(&worker2, NULL, workB, NULL);

  pthread_detach(worker1);
  pthread_detach(worker2);

  pthread_exit(NULL);

  return 0;
}
```

生产者消费者模型

使用：条件变量和互斥量
前提：生产仓库大小无限大

问题：再delete时需要把当前置为空

```c++
#include <pthread.h>
#include <unistd.h>

#include <iostream>
class Node {
 public:
  Node(int val, Node *next = NULL) : data(val), Next(next) {}
  ~Node(){}
  int data;
  Node *Next;
};

/*共享数据*/
int serialNumber = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
Node *head = NULL;

void *Factory(void *arg) {
  while (true) {
    pthread_mutex_lock(&mutex);
    Node *nextNode = new Node(++serialNumber);

    std::cout << "Factory produce goods of serial number = " << next->data
              << std::endl;

    nextNode->Next = head;
    head = nextNode;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    usleep(100);
  }
  return NULL;
}

void *Consumer(void *arg) {
  while (true) {
    Node *tmp = head;

    pthread_mutex_lock(&mutex);

    if (head != NULL) {
      std::cout << "Consumer consume goods of serial number = " << head->data
                << std::endl;

      head = head->Next;
      tmp = NULL;
      delete tmp;
      pthread_mutex_unlock(&mutex);
    } else {
      pthread_cond_wait(&cond, &mutex);
      pthread_mutex_unlock(&mutex);
    }
    usleep(100);
  }
  return NULL;
}
int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_t producer[3], consumer[3];

  for (int i = 0; i < 3; i++) {
    pthread_create(&producer[i], NULL, Factory, NULL);
    pthread_create(&consumer[i], NULL, Consumer, NULL);
  }

  for (int i = 0; i < 3; i++) {
    pthread_detach(producer[i]);
    pthread_detach(consumer[i]);
  }

  pthread_exit(NULL);
  return 0;
}
```

信号量
生产者消费者模型
仓库固定大小

```c++
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <iostream>
class Node {
 public:
  Node(int val, Node *next = NULL) : data(val), Next(next) {}
  ~Node() {}
  int data;
  Node *Next;
};

/*共享数据*/
int serialNumber = 0;
pthread_mutex_t mutex;
Node *head = NULL;
sem_t psem; //生产者仓库信号量
sem_t csem; //消费者信号量

void *Factory(void *arg) {
  while (true) {
    /*若psem仓库为0，产生阻塞，等待仓库有空间可以使用*/
    sem_wait(&psem);
    pthread_mutex_lock(&mutex);
    Node *nextNode = new Node(++serialNumber);

    std::cout << "Factory produce goods of serial number = " << nextNode->data
              << std::endl;

    nextNode->Next = head;
    head = nextNode;

    pthread_mutex_unlock(&mutex);
    sem_post(&csem);
  }
  return NULL;
}

void *Consumer(void *arg) {
  while (true) {
    Node *tmp = head;

    sem_wait(&csem);
    pthread_mutex_lock(&mutex);

    std::cout << "Consumer consume goods of serial number = " << head->data
              << std::endl;

    head = head->Next;
    tmp = NULL;
    delete tmp;
    pthread_mutex_unlock(&mutex);
    sem_post(&psem);
    }
  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);

  /*初始化信号量 生产者仓库为8*/
  sem_init(&psem, 0, 8); 
  sem_init(&csem, 0, 0);

  pthread_t producer[3], consumer[3];

  for (int i = 0; i < 3; i++) {
    pthread_create(&producer[i], NULL, Factory, NULL);
    pthread_create(&consumer[i], NULL, Consumer, NULL);
  }

  for (int i = 0; i < 3; i++) {
    pthread_detach(producer[i]);
    pthread_detach(consumer[i]);
  }

  pthread_mutex_destroy(&mutex);

  pthread_exit(NULL);
  return 0;
}
```

读写锁

由于共享数据有种情况，很多线程一起访问都不会有问题，比如读取某个文件的数据，这时候互斥量就不适合出现这里了，所以读写锁应运而生，我们可以一起读数据，但是不可以一起写数据，当一个线程在写数据时，不允许其他线程读取数据，和写入数据。

写时独占的，写的优先级高
pthread_rwlock_wrlock()写锁
pthread_rwlock_rdlock()读锁
pthread_rwlock_unlock()解锁

判断大小端字节序：
```c++
#include <iostream>
int main() {
  union {
    short value;
    char bytes[sizeof(short)];
  } test;
  
  test.value = 0x0102;
  if (test.bytes[0] == 1 && test.bytes[1] == 2) {
    std::cout << "Big" << std::endl;
  }
  if (test.bytes[0] == 2 && test.bytes[1] == 1) {
    std::cout << "Small" << std::endl;
  }

  return 0;
}
```

网络编程socket实现简单的通信：
client

```c++
/*头文件*/
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <memory>
#define maxBuf (1 << 20)
#ifndef _CLIENT_H_
#define _CLIENT_H_

static char messages[maxBuf]="I am client";

class ClientSock {
 public:
  ClientSock(char *ip, char *port);
  ~ClientSock() { close(clientFd); };
  void error(char *error);
  void clientConnect();
  virtual void clientWrite();
  virtual void clientRead();

 private:
  char *_port;
  char *_ip;
  int clientFd;
  struct sockaddr_in serverAddr;
};
#endif

/*实现代码*/
#include "client.h"

static char reciveBuf[maxBuf] = {0};

void ClientSock::error(char *error) {
  std::cout << error << std::endl;
  exit(1);
}

ClientSock::ClientSock(char *ip, char *port) {
  this->_ip = ip;
  this->_port = port;

  /*创建套接字*/
  this->clientFd = socket(PF_INET, SOCK_STREAM, 0);

  /*为当前套接字分配地址信息*/
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(ip);
  serverAddr.sin_port = htons(atoi(port));
}

void ClientSock::clientConnect() {
  /*connect()向服务器发送连接请求*/
  if (connect(clientFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    this->error(const_cast<char *>("connect() error!"));
  }
}

void ClientSock::clientWrite() {
  // std::cout << "Listen...." << std::endl;
  char buf[] = "I am client";
  int nowLen = 0;
  int allLen = sizeof(buf);
  int getLen = 0;

  while (getLen < allLen) {
    nowLen = write(clientFd, buf + getLen, allLen - getLen);
    getLen += nowLen;
  }
}

void ClientSock::clientRead() {
  char buf[1024];
  int strLen = 0;
  int allLen = sizeof(buf);

  strLen = read(clientFd, buf, allLen);

  if (strLen == -1) {
    this->error(const_cast<char *>("read() error!"));
  }

  std::cout << "I accept from server information: " << buf << std::endl;
}

/*主体函数*/
#include "client.h"
int main(int argc, char *argv[]) {
  ClientSock *client = new ClientSock(argv[1], argv[2]);
  client->clientConnect();

  while(true){
  client->clientWrite();
  sleep(2);
  client->clientRead();
  }
  delete client;
  return 0;
}

```

server
```c++
/*头文件*/
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <memory>
#define maxBuf (1 << 20)
#ifndef _SERVER_H_
#define _SERVER_H_

static char messages[maxBuf];

class ServerSock {
 public:
  ServerSock(char *ip, char *port);
  ~ServerSock();
  void serverBind();
  void error(char *error);
  void serverListen();
  void serverAccept();
  void setMessages(char *others);
  virtual void serverWrite();
  virtual void serverRead();

 private:
  char *_port;
  char *_ip;
  int serverFd;
  int clientFd;
  struct sockaddr_in serverAddr;
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen;
};
#endif

/*实现代码*/
#include "server.h"

void ServerSock::error(char *error) {
  std::cout << error << std::endl;
  exit(1);
}

ServerSock::ServerSock(char *ip, char *port) {
  this->_ip = ip;
  this->_port = port;
  this->clientAddrLen = sizeof(clientAddr);
  /*创建套接字*/
  this->serverFd = socket(PF_INET, SOCK_STREAM, 0);

  /*为当前套接字分配地址信息*/
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(ip);
  serverAddr.sin_port = htons(atoi(port));
}

void ServerSock::serverBind() {
  if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    this->error(const_cast<char *>("bind() error!"));
  }
}

void ServerSock::serverListen() {
  if (listen(serverFd, 5) == -1) {
    this->error(const_cast<char *>("listen() error!"));
  }
}

void ServerSock::serverAccept() {
  clientFd = accept(serverFd, (struct sockaddr *)&clientAddr, &clientAddrLen);

  if (clientFd == -1) {
    this->error(const_cast<char *>("accept() error!"));
  }
}

void ServerSock::serverWrite() {
  //std::cout << "Listen...." << std::endl;
  char others[] = "I am server";

  int nowLen = 0;
  int allLen = sizeof(others);
  int getLen = 0;

  while (getLen < allLen) {
    nowLen = write(clientFd, others + getLen, allLen - getLen);

    getLen += nowLen;
  }
}

void ServerSock::serverRead() {
  char buf[maxBuf];
  int strLen = 0;
  int allLen = sizeof(buf);

  strLen = read(clientFd, buf, allLen);
  if (strLen == -1) {
    this->error(const_cast<char *>("read() error!"));
  }

  std::cout << "I accept from client information: " << buf << std::endl;
}

void ServerSock::setMessages(char *others) { strcpy(messages, others); }

ServerSock::~ServerSock() {
  close(clientFd);
  close(serverFd);
}

/*Main入口*/
#include "server.h"

int main(int argc, char *argv[]) {
  //char others[] = "I am server";
  ServerSock *server = new ServerSock(argv[1], argv[2]);
  server->serverBind();
  server->serverListen();

  server->serverAccept();
  //server->setMessages(others);
  while (true) {
    server->serverRead();
    sleep(2);
    server->serverWrite();
  }
  delete server;

  return 0;
}
```

Tcp滑动窗口：
由于发送端和接收端处理数据的能力不一样，可能发送端发送数据很快，而接收端处理数据很慢，所以利用一个固定大小的缓存区进行滑动，来控制发送数据的大小。

端口复用：setsockopt()可能端口被占用，我们可以复用该端口

通信并发
利用子进程和父进程进行通信，可以允许多个客户端进行访问，问题:每次调用accept()过程耗费资源

IO多路复用

select:server 
```c++
/*select多路复用*/
#include "socket.h"

int main(int argc, char *argv[]) {
  ServerSock *server = new ServerSock(argv[1], argv[2]);
  server->serverBind();
  server->serverListen();
  fd_set rdset, tmp;
  FD_ZERO(&rdset);
  FD_SET(server->serverFd, &rdset);
  int maxfd = server->serverFd;
  while (1) {
    tmp = rdset;
    /*将fdset集合从用户态拷贝到内核态，获取新的fdset集合*/
    int ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
    if (ret == -1) {
      server->error("select error");
    } else if (ret == 0) {
      continue;
    } else if (ret > 0) {
      if (FD_ISSET(server->serverFd, &tmp)) {
        server->serverAccept();
        FD_SET(server->clientFd, &rdset);
        maxfd = maxfd > server->clientFd ? maxfd : server->clientFd;
      }
    }

    for (int i = server->serverFd + 1; i <= maxfd; i++) {
      if (FD_ISSET(i, &tmp)) {
        char buf[1024] = {0};
        int len = read(i, buf, sizeof(buf));
        if (len == -1) {
          server->error("read() error!");
        } else if (len == 0) {
          close(i);
          FD_CLR(i, &rdset);
        } else if (len > 0) {
          std::cout << "read buf = " << buf << std::endl;
          write(i, buf, strlen(buf) + 1);
        }
      }
    }
  }
  return 0;
}
```
缺点：
1.每次调用select都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多时，开销很大。
2.每次调用select都需要在内核遍历传进来的fd，这个开销在fd很多的时候也很大.
3.select支持的文件描述符数量很小，只能有1024个。
4.fds集合不能重用，每次需要重置。

epoll

```c++
#include "socket.h"

int main(int argc, char *argv[]) {
  ServerSock *server = new ServerSock(argv[1], argv[2]);
  server->serverBind();
  server->serverListen();

  /*调用epoll_create()创建一个epoll实例*/
  int epfd = epoll_create(100);

  /*将监听的文件描述符相关的信息添加入epoll实例中*/
  struct epoll_event epev;
  epev.events = EPOLLIN;
  epev.data.fd = server->serverFd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, server->serverFd, &epev);

  struct epoll_event epevs[1024];
  while (true) {
    int ret = epoll_wait(epfd, epevs, 1024, -1);
    if (ret == -1) {
      server->error(const_cast<char *>("epoll_wait() error"));
    }

    for (int i = 0; i < ret; i++) {
      int curfd = epevs[i].data.fd;
      if (curfd == server->serverFd) {
        server->serverAccept();
        epev.events = EPOLLIN;
        epev.data.fd = server->clientFd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, server->clientFd, &epev);
      } else {
        if (epevs[i].events & EPOLLOUT) {
          continue;
        }
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        int Len = read(curfd, buf, sizeof(buf));
        if (Len == -1) {
          server->error(const_cast<char *>("read() error!"));
        } else if (Len == 0) {
          std::cout << "close client" << std::endl;
          epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
        } else if (Len > 0) {
          std::cout << buf << std::endl;
          write(curfd, buf, strlen(buf) + 1);
        }
      }
    }
  }
  return 0;
}
```
epoll对文件描述符有两种操作模式LT(水平模式)和ET(边缘模式)。简单来说，LT是epoll的默认模式。
当epoll_wait函数检测到有事件发生并通知应用程序，而应用程序不一定立即处理，这样epoll_wait再次检测到事件时
还会通知应用程序，直到事件被处理。

ET模式，只要epoll_wait函数检测到事件发生，通知应用程序立即进行处理，后续的epoll_wait函数将不在检测此事件。
因此ET模式在很大程度上降低了同一个事件被epoll触发的次数，因此效率比LT模式高。

解释为什么epoll默认时LT模式
LT是省却的工作模式，并且同时支持阻塞与非阻塞 socket,这种做法中内核告诉你一个文件描述符就绪了，然后你可以对这个
就绪的文件描述符进行IO。如果你不做任何操作，内核还是会继续通知你，所以这种模式出问题的概率会小一点。传统的select
和poll都是这种模型。

设计模式

当前单例模式，构造函数不能被调用，只有一个实例，该实例被所有程序模块共享。
那么我们必须保证：
（1）该类不能被复制。
（2）该类不能被公开创造。
那么对于c++来说，它的构造函数，拷贝构造函数和赋值函数都不能被公开。

```c++
#include <iostream>

class SignleTon {
 private:
  static SignleTon* p;
  SignleTon() { std::cout << "create Singleton" << std::endl; }
  ~SignleTon() { std::cout << "destory Singleton" << std::endl; }

 public:
  static SignleTon* getSignleTon() {
    if (p == nullptr) {
      p = new SignleTon();
    }
    return p;
  }
};

SignleTon* SignleTon::p = nullptr;

int main() {
  SignleTon* p = SignleTon::getSignleTon();
  SignleTon* pp = SignleTon::getSignleTon();
  return 0;
}
```
该单例模式在单线程是安全的，但是在多线程时，并不安全，当有A,B两个线程可以对SignleTon进行访问时，当A访问SignleTon
进入if()中，由于第一个进入，所以p==nullptr,但是发生系统中断，B线程也进入，然后执行完上述流程，切换至A，又重新执行了一遍，
这样就产生了两个实例，造成数据安全问题，并且发生了内存泄漏问题。

保证线程安全和内存安全单例模式
```c++
#include <iostream>
#include <memory>
#include <mutex>

class SignleTon {
 private:
  static std::shared_ptr<SignleTon> p;
  static std::mutex m_mutex;

  SignleTon() { std::cout << "create Singleton" << std::endl; }

 public:
  ~SignleTon() { std::cout << "destory Singleton" << std::endl; }

  static std::shared_ptr<SignleTon> getSignleTon() {
    if (p == nullptr) {
      std::lock_guard<std::mutex> lock(m_mutex);
      p = std::shared_ptr<SignleTon>(new SignleTon);
    }
    return p;
  }
};

std::shared_ptr<SignleTon> SignleTon::p = nullptr;
std::mutex SignleTon::m_mutex;

int main() {
  std::shared_ptr<SignleTon> p = SignleTon::getSignleTon();
  std::shared_ptr<SignleTon> pp = SignleTon::getSignleTon();
  return 0;
}
```
lock_guard和unique_lock的区别
lock_guard是一个互斥量作用包装程序，他提供RALL机制，在作用域块的持续时间内拥有一个互斥量。
当控制流离开lock_guard作用域时，lock_guard析构并释放互斥量。它的特点，无需手动加锁解锁，不能中途
解锁，需要等到作用域结束才解锁。不能复制。

unique_lock,创建可以不锁定，可以随时加锁解锁，作用域规则同lock_guard相同，条件变量需要该类型的锁作为参数。
此时必须使用（unique_lock)。

线程池：
```c++
#include <assert.h>

#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
 public:
  /*处理task*/
  explicit ThreadPool(int threadcount = 8) : _pool(std::make_shared<Pool>()) {
    assert(threadcount > 0);

    for (int i = 0; i < threadcount; i++) {
      std::thread([pool = _pool] {
        std::unique_lock<std::mutex> locker(pool->m_mutex);

        while (true) {
          if (!pool->m_queues.empty()) {
            auto task = std::move(pool->m_queues.front());
            pool->m_queues.pop();
            locker.unlock();
            task();
            locker.lock();

          } else if (pool->isClose) {
            break;
          } else {
            pool->cond.wait(locker);
          }
        }
      }).detach();
    }
  }

  ThreadPool() = default;
  ThreadPool(ThreadPool&&) = default;

  /*当线程池析构时，唤醒阻塞的线程并关闭*/
  ~ThreadPool() {
    if (static_cast<bool>(_pool)) {
      std::lock_guard<std::mutex> locker(_pool->m_mutex);
      _pool->isClose = true;
    }
    _pool->cond.notify_all();
  }

  template <class F>
  void AddTask(F&& task) {
    {
      std::lock_guard<std::mutex> locker(_pool->m_mutex);
      _pool->m_queues.emplace(std::forward<F>(task));
    }
    _pool->cond.notify_one();
  }

 private:
  struct Pool {
    std::mutex m_mutex;
    std::condition_variable cond;
    bool isClose = false;
    std::queue<std::function<void()>> m_queues;
  };
  std::shared_ptr<Pool> _pool;
};

void task1() { std::cout << "I am first thread!" << std::endl; }

void task2() { std::cout << "I am second thread!" << std::endl; }

int main() {
  std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>(8);
  pool->AddTask(task1);
  pool->AddTask(task2);
  pool->AddTask(task2);
  return 0;
}
```

为什么要使用线程池技术？

好处：
重用存在的线程，减少对象的消亡，和创建，提高性能。
控制最大并发线程数，提高系统资源的使用率，同时避免过多的竞争，避免堵塞。

进程有多少种状态？
5种:创建态，运行态，就绪态，阻塞态，中止态。
过程：一个进程被创建后，放入就绪队列，等待操作系统调度执行，执行过程中，可能切换到阻塞状态（并发），任务完成后，进程销毁中止。

管道的实现原理：
操作系统在内核开辟一段缓存区(成为管道)用于通信。管道是一种两个进程间进行单项通信的机制。

简述mmap的使用场景
mmap是一种内存映射文件的方法，即将一个文件或其他对象映射到进程的地址空间，实现文件磁盘地址和进程虚拟地址空间中一段虚拟地址
的一一对映关系。

死锁的条件：
进程之间互斥
请求且保持
不可剥夺条件
循环且等待

常见的关系性数据库和非关系型数据库之间的区别

关系型数据库有：mysql,oracle,sql server ,sqlite

关系型数据库最典型的数据库是表，由二维表及其之间的联系所组成的一个数据组织。
优点：
1.易于维护：都使用表结构，格式一致。
2.使用方便，Sql语言通用，可用于复杂查询。
3.复杂操作：支持sql,可用于一个表及多个表之间的非常复杂的查询。

缺点：
1.读写能力较差，尤其是一个海量数据的高效读写。
2.固定的表结构，灵活欠缺。
3.高并发读写需求传统关系型数据库来说，硬盘IO是一个很大瓶颈。

非关系型数据库：redis,mongoDB

非关系型数据库，严格意义上不是一种数据库，应该是一种数据结构化存储方式的集合，可以是文档或键值对等。

从数据结构的角度看，有哪些索引：
B+树索引
为什么使用B+树而不是用红黑树？
原因：当数据量很大时，数据无法存储在主存上，数据需要存储在磁盘上，而在磁盘上存取的效率本身就很低，有加上机械运动，效率更低。
因此需要减少树的高度，又因为磁盘顺序访问的速度很快，可以预读取，效果十分不错，而红黑树是一个二叉树，树高远大于b+树，所以执行IO操作的次数多于B+树。

GET和POST的区别：
GET产生一个TCP数据包，POST产生两个TCP数据包
对于GET请求，浏览器会把http header和data一并发送出去，服务器相应200ok，速度快，但是不安全。
对于POST请求，浏览器先发送header,服务器相应100continue,浏览器再发送data,服务器返回200ok，速度慢，安全。
GET请求只能进行url编码，POST支持多种类型的编码。
GET比POST更不安全，参数直接漏在URL上，不能传输敏感信息。

面试题：NC102 在二叉树中找到两个节点的最近公共祖先
题解：
1.数据量小用暴力方法先求出每个节点的父亲，和深度，然后不断往上爬，然后判断两个点是不是一个点。
2.数据量大，用树剖的写法，用重儿子把树化成轻重链，通过节点往上跳方法实现
这里只给出数据量大的代码:
```c++
class Solution {
 public:
  /**
   *
   * @param root TreeNode类
   * @param o1 int整型
   * @param o2 int整型
   * @return int整型
   */
  std::unordered_map<TreeNode*, TreeNode*> wightSon;
  std::unordered_map<int, int> linkHead;
  std::unordered_map<int, int> sonSize;
  std::unordered_map<int, int> father;
  std::unordered_map<int, int> dep;
  void dfs1(TreeNode* pa, TreeNode* pb) {
    int u = pa->val;
    int fa = pb->val;
    dep[u] = dep[fa] + 1;
    father[u] = fa;
    sonSize[u] = 1;
    int Maxson = 0;
    std::vector<TreeNode*> edge;
    edge.clear();
    if (pa->left != nullptr) {
      edge.push_back(pa->left);
    }
    if (pa->right != nullptr) {
      edge.push_back(pa->right);
    }
    for (int i = 0; i < edge.size(); i++) {
      TreeNode* pv = edge[i];
      int v = pv->val;
      dfs1(pv, pa);
      sonSize[u] += sonSize[v];
      if (sonSize[v] > Maxson) {
        wightSon[pa] = pv;
        Maxson = sonSize[v];
      }
    }
  }

  void dfs2(TreeNode* pa, int phead) {
    int u = pa->val;
    linkHead[u] = phead;
    if (wightSon[pa] == nullptr) {
      return;
    }
    dfs2(wightSon[pa], phead);
    std::vector<TreeNode*> edge;
    edge.clear();
    if (pa->left != nullptr) {
      edge.push_back(pa->left);
    }
    if (pa->right != nullptr) {
      edge.push_back(pa->right);
    }
    for (int i = 0; i < edge.size(); i++) {
      TreeNode* pv = edge[i];
      int v = pv->val;
      if (pv != wightSon[pa]) {
        dfs2(pv, v);
      }
    }
  }

  int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
    // write code here
    dfs1(root, root);
    dfs2(root, root->val);
    while (linkHead[o1] != linkHead[o2]) {
      if (dep[linkHead[o1]] < dep[linkHead[o2]]) {
        swap(o1, o2);
      }
      o1 = father[linkHead[o1]];
    }
    return dep[o1] < dep[o2] ? o1 : o2;
    return 0;
  }
};
```

mmap技术:
mmap的工作原理，当你调用这个的时后，他只是在你的虚拟空间中分配一段内存，连真实的物理地址都不会分配，当访问这段空间时，cpu陷入os内核执行异常处理，然后异常处理会在这个时间分配一段物理内存，然后用文件内容填充这块内存，然后返回你进程的上下文，这时的程序才会感知到这块内存有数据。

mmap优点总结
1.对文件的读取操作跨过页缓存，减少了数据的拷贝次数，用内存读写代替I/O读写，提高文件的读取效率。
2.实现了用户和内核的高效交互方式。两空格的各自修改操作可以直接反应在映射的区域内。从而被对方空间及时捕捉。
3.提供进程的共享内存及互相通信的方式。不管是父进程还是无亲缘关系的进程，都可以将自身用户空间映射到同一个文件或匿名映射到同一片区域。从而通过各自对映射区域的改动，达到进程间互相通信和数据共享的目的。
4.可用于实现大规模的数据传输。内存空间不足，是制约大数据操作的一个方面，解决方案往往是借助磁盘空间协助操作，补充内存的不足。但是进一步会造成大规模的IO操作，极大的影响效率。这个问题可以通过mmap映射技术很好的解决。

mmap是共享文件
Linux下mmap读取文件内容/修改文件内容

```c++
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char *argv[]) {
  int fd = 0;
  char *ptr = NULL;
 
  struct stat buf = {0};

  /*获取文件描述符*/
  fd = open(argv[1], O_RDWR);

  /*将文件复制到buf中*/
  fstat(fd, &buf);

  /*mmap将文件内容拷贝到内存中，返回指针ptr*/
  ptr = (char *)mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                     0);
  
  /*关闭文件描述符fd*/
  close(fd);

  /*打印文件中的内容*/
  std::cout << "MMAP: " << ' ' << ptr << std::endl;

  /*修改文件中的内容*/
  ptr[0]='M';
  
  /*打印修改后的内容*/
  std::cout << "MMAP: " << ' ' << ptr << std::endl;

  return 0;
}
```

合并有序链表
因为是有序的，所以用两个指针，一个一个慢，遇到符合条件的，就把当前元素插入链表，然后后移一位直到结束。
```c++
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
 public:
  ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
    ListNode *T, *Ts, *ans;
    if (pHead1 == nullptr && pHead2 != nullptr) {
      return pHead2;
    } else if (pHead1 != nullptr && pHead2 == nullptr) {
      return pHead1;
    } else if (pHead1 != nullptr && pHead2 != nullptr) {
      T = pHead1->val < pHead2->val ? pHead1 : pHead2;
      Ts = T != pHead1 ? pHead1 : pHead2;
      ans = T;
    } else {
      return pHead1;
    }

    while (T != nullptr || Ts != nullptr) {
      if ((T->next == nullptr && Ts != nullptr) || (Ts == nullptr)) {
        if (Ts != nullptr) {
          T->next = Ts;
        }
        break;
      }
      int u = T->val;
      int v = T->next->val;
      int w = Ts->val;
      if (w >= u && w <= v) {
        auto p = Ts;
        Ts = Ts->next;
        auto Tnxt = T->next;
        T->next = p;
        p->next = Tnxt;
      }
      T = T->next;
    }
    return ans;
  }
};
```
Mysql面试题:
1.说下mysql的索引有哪些，聚簇和非聚簇索引是什么？
索引按照数据结构来说主要包含B+数和Hash索引。
聚簇索引是指索引和数据是绑定的，找到了索引就找到了数据。
2.非聚簇索引是指索引和数据是分离的，需要根据索引上的值回表查询，非聚簇索引也叫辅助索引。2.什么是覆盖索引和回表？
如果在查询过程中，如果一个索引覆盖或者覆盖所需要查询的字段值，我们就称为覆盖索引。
回表，是select获得的列中，包含大量非索引列，索引就需要到表中找相应列的信息。
3.锁的类型有哪些？
mysql锁又分为（共享锁）读锁和（排他锁）写锁
读锁是共享的，写锁是不共享的，他会阻塞其他读锁和写锁
行锁又可以分为乐观锁和悲观锁，悲观锁可以用update实现，乐观锁则通过版本号实现。
4.事务的基本特性和隔离级别？
事务基本特性ACID分别是：
原子性 指的是一个事务中的操作要么全部成功，要么全部失败。
一致性 指的是数据库总是从一个一致性的状态转换到另一个一致性状态。
隔离性 一个事务的修改在最终提交前都不可见。
持久性 一个事务一旦提交，就永久保存到数据库中。

计算机网络:
七层模型：
应用层：例如为操作系统或网络应用程序提供访问网络服务的接口常见：Telent,Ftp,http,snmp,dns
表示层：（提供数据转换格式服务）例如解密与加密，图片解码和编码，数据的压缩和解压缩，常见：URL加密，口令加密，图片编码码
会话层：建立端连接，并提供访问验证和会话管理。
传输层：提供进程之间的通信逻辑，常见的TCP,UDP，socket

网络层：为数据在节点之间传输创建逻辑链路，并分组转发数据，常见路由器
链路层：在通信的实体间建立数据链路
物理层：为数据设备提供原始比特流的传输通路
简述静态路由和动态路由
1.静态路由是由系统管理员设计与构建的路由表规定的路由。适用于网关数量有限的场合
2.动态路由是由路由选择协议而动态构建的，路由协议之间通过交换各自所拥有的路由信息实时更新路由表的内容。
动态路由可以自动学习网络的拓扑结构，并更新路由表。其缺点是路由广播更新信息将占用大量的网络宽带。

说说有哪些路由协议：
RIP路由协议：距离向量协议。收集所有可到达目的地的站点信息，并保存到达目的地的站点数量，但RIP只用于小型的同构网络，因为它运行的最大站点数不超过15个，任何超过15个站点目的地均被标记不可到达。
OSPF路由协议:收集所有路由的链路状态信息，然后再利用一定的算法计算出到每个节点的最短路径。OSPF将一定区域划分为区，相应的对应两种选择方式。当源和目的地在同一区域，选择区内路由协议，当源和目的地不在一个区时，选择区间路由协议。
IGRP和EIGRP协议

3.简述域名的解析过程，本机如何干预域名解析
（1）在浏览器中输入www.baidu.com,操作系统会先检查自己本地的host文件是否有这个网址映射关系，如果有，就先调用这个IP地址映射。
（2）如果hosts里没有这个域名的映射，则查找本地DNS解析缓存器，是否有这个网址映射关系，如果有直接返回，完成域名解析。
（3）如果hosts与本地DNS解析器缓存都没有相应的网址映射关系，首先回找TCP/IP参数中设置的服务器，通过服务器进行查询域名。
4.MAC地址和ip地址的区别？
（1）ip地址是IP协议统一的提供的地址格式，它为互联网上的每一个网络和每一台主机分配一个逻辑地址，以此来屏蔽物理地址的差异。而MAC地址，指的是物理地址，用来定义网络设备的位置。
（2）IP地址的分配是根据网络的拓扑结构，而不是根据谁制造了网络配置。
（3）ARP协议负责将IP地址映射到MAC地址上来完成。

TCP三次握手？

（1）第一次握手：建立连接时，客户端向服务器发送SYN包（seq=x),请求建立连接，等待确认
（2）第二次握手：服务器收到一个SYN包返回一个ACK(ACK=x+1)包,同时发送一个SYN包（seq=y)给客户端。
（3）第三次握手：客户端收到一个SYN+ACK,在返回一个ACK(ACK=y+1),告诉服务器端已经收到了。
（4）三次握手完成，开始传输数据。

说说TCP两次握手行不行？
不行。为了数据的可靠传输，TCP协议的通信双方，都必须维护一个序列号，以标识发送出去的数据包，哪些是已经被对方所接收的。三次握手的通信双方，即是通信双方互相告知序列号的起始值，并确定对方已经收到了序列号起始值的必经步骤。两次握手无法做到。

TCP和UDP的区别？
TCP协议是有连接的 ，UDP是无连接的
TCP面向字节流，UDP面向报文。
TCP确保超时重传，保证数据完整，UDP不保证，只努力交付。
TCP有流量控制和堵塞控制，UDP没有，网络拥堵不会影响发送端的发送速率。
TCP是一对一连接，UDP可以一对一也可以一对多。

简述TCP超时重传
TCP可靠性中最重要的一个机制是处理数据超时和重传。TCP协议要求在发送端每发送一个报文段，就启动一个定时器并等待确认信息；接收端成功接收新数据后返回确认信息。若在定时器超时前数据未能被确认，TCP就认为报文段中的数据已丢失或损坏，需要对报文段中的数据重新组织和重传。
TCP协议在发送端每发送一个报文段，就启动一个定时器并等待确认信息。

解决拥塞：拥塞控制
通过慢启动解决

发送开始时，定义拥塞窗口为1，每次收到一个ACK应答，拥塞窗口增加1；每次发送窗口取拥塞窗口和接收窗口的最小值。
慢启动：在启动初期以指数增长；设置一个慢启动阈值，当指数增长达到阈值就停止指数增长，开始线性增长，按照线性增长的方式增长到拥塞窗口；线性增长达到网络拥塞时立即把拥塞窗口置回1，进行新一轮慢启动，同时新一轮的阈值变为原来的一半。

HTTP:
cookie和session的关系和区别是什么
1.cookie与session都是会话方式的一种。他们的典型使用场景就是“购物车”,当你点击下单按钮时，服务端并不清除具体的用户的具体操作。为了标识并跟踪该用户，了解购物车中有几样物品，服务器通过用户创建cookie/session来获取这些信息。
2.cookie数据放在客户端浏览器上，session数据放在服务器上。

