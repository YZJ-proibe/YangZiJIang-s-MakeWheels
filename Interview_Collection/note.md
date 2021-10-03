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
协程执行效率极高。协程直接操作操作栈，基本上没有内核切换的开销，所以上下文切换非常快。
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
