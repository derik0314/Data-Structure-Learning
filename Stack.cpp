#include<iostream>
using namespace std;

//栈--类定义
template<typename T>
class Stack{
    public:
        void clear();  //清空
        bool push(const T item);  //入栈
        bool pop(T& item);  //出栈
        bool top(T& item);  //获得栈顶内容
        bool isEmpty();  //是否空栈
        bool isFull();  //是否满栈
};

//顺序栈--类定义
template<typename T>
class ArrayStack:public Stack<T>{  //继承Stack
    private:
        int m_size;  //栈容量
        int m_top;  //栈顶，初始为-1
        T* m_stack;  //存放栈内容的连续空间
    public:
        ArrayStack(int size);
        ArrayStack();
        ~ArrayStack();
        void clear();
        bool push(const T item);
        bool pop(T & item);
        bool top(T & item);
        bool isEmpty();
        bool isFull();
};

//构造函数（有参数）
template<typename T>
ArrayStack<T>::ArrayStack(int size) {
    this->m_size = size;
    this->m_top = -1;  //表示栈为空的状态
    m_stack = new T[m_size];
}

//构造函数
template<typename T>
ArrayStack<T>::ArrayStack() {
    this->m_size = 0;
    this->m_top = -1;
    m_stack = new T[m_size];
}

//析构函数
template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] m_stack;
}

//清空函数
template<typename T>
void ArrayStack<T>::clear() {
    this->m_top = -1;  //表明栈中没有任何元素
}

//入栈（自动解决栈溢出）
template<typename T>
bool ArrayStack<T>::push(const T item) {
    if(this->m_top == m_size - 1) {  //如果栈已满则进行扩容
        T* newst = new T [this->m_size*2 + 1];  //增长幅度适中，避免重复扩容
        for(int i = 0; i <= this->m_top; i++ ) {
            newst[i] = this->m_stack[i];
        }
        delete [] this->m_stack;
        m_stack = newst;
        m_size = m_size*2 + 1;
    }
    ++ this->m_top;
    m_stack[this->m_top] = item;
    return true;
}

//出栈（将弹出栈顶元素赋值给传入参数）
template<typename T>
bool ArrayStack<T>::pop(T& item) {  //&实现在函数内部修改传入参数的数值
    if(this->m_top == -1) {
        std::cerr << "stack is empty, no item can be read！"<<std::endl;  //ceer用于输出错误信息
        return false;
    }else{
        item = m_stack[this->m_top];
        this->m_top--;
        return true;
    }
}

//获取栈顶元素
template<typename T>
bool ArrayStack<T>::top(T & item) {
    if(this->m_top == -1) {
        std::cerr << "stack is empty, no item can be read！" << std::endl;
        return false;
    }else{
        item = m_stack[this->m_top];
        return true;
    }
}

//链表节点的数据结构
template<typename T>
class LinkNode {
    private:
        T data;  
        LinkNode<T>* next;  
    public:
        LinkNode(T data, LinkNode<T>* next) : data(data), next(next) {}  // 构造函数，初始化数据域和指针域
        LinkNode(const T newData) : data(newData), next(nullptr) {}  // 构造函数，初始化数据域为newData，指针域为空指针
        LinkNode<T>* getNext() {  // 获取下一个节点的指针
            return next;
        }
        T getData() {  // 获取节点的数据元素
            return data;
        }
        void setNext(LinkNode<T>* newNext) {  // 设置下一个节点的指针
            next = newNext;
        }
};

//链式栈--类定义
template<typename T>
class LinkedStack:public Stack <T>{
    private:
        LinkNode<T>* m_top;  //头指针
        int m_size;  //结点个数
    public:
        LinkedStack(int size);
        ~LinkedStack();
        void clear();
        bool push(const T item);
        bool pop(T& item);
        bool top(T& item );
        bool isEmpty();
        bool isFull();
};

//链式构造函数
template<typename T>
LinkedStack<T>::LinkedStack(int size) {
    this->m_top = 0;
    this->m_size = 0;
}

//链式析构函数
template<typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}

//链式清空函数
template<typename T>
void LinkedStack<T>::clear() {
    while (this->m_top != 0) {
        LinkNode<T>* temp = this->m_top;
        this->m_top = this->m_top->getNext();
        delete temp;
    }
    this->m_size = 0;
}

//链式入栈
template<typename T>
bool LinkedStack<T>::push(const T item) {
    LinkNode<T>* temp = new LinkNode<T>(item, m_top);
    this->m_top = temp;
    this->m_size++;
    return true;
}

//链式出栈
template<typename T>
bool LinkedStack<T>::pop(T& item) {
    if (m_size == 0) {
        std::cerr << "Stack should not be empty, can not pop any item" << std::endl;
        return false;
    }
    item = this->m_top->getData();  //将栈顶元素的数据赋值给传入的item
    LinkNode<T>* temp = this->m_top->getNext();
    delete this->m_top;
    this->m_top = temp;
    this->m_size--;
    return true;
}

//中缀表达式23+(34*45)/(5+6+7) 对应的后缀表达式23 34 45 * 5 6 + 7 + / +
//后缀表达式--类定义
class Calculator {
private:
    Stack<double> s;
    bool getTwoOperands(double& opd1, double& opd2);
    void Compute(char op);
public:
    Calculator() { };
    void run();
    void clear();
};

//从栈中获取最上面的两个操作数
bool Calculator::getTwoOperands(double& opd1, double& opd2) {
    if (s.isEmpty()) {
        cerr << "Missing operand!" << endl;
        return false;
    }
    s.pop(opd1);  //从栈中弹出一个元素，将其赋值给opd1
    if (s.isEmpty()) {
        cerr << "Missing operand!" << endl;
        return false;
    }
    s.pop(opd2);
    return true;
}

//计算
void Calculator::Compute(char op) {
    bool result;
    double operand1, operand2;
    result = getTwoOperands(operand1, operand2);
    if (result) {
        switch (op) {
            case '+': s.push(operand2 + operand1); break;
            case '-': s.push(operand2 - operand1); break;
            case '*': s.push(operand2 * operand1); break;
            case '/':
                if (abs(operand1) < 0.000001) {  //abs取绝对值
                    cerr << "Divide by 0!" << endl;
                    s.clear();
                } else {
                    s.push(operand2 / operand1);
                }
                break;
        }
    } else {
        s.clear();
    }
}

//读取表达式
void Calculator::run() {
    char c;
    double newOperand, res;
    while (std::cin >> c, c != '=') {
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
                Compute(c);
                break;
            default:
                std::cin.putback(c);  //将读取的数字c放回到输入流中
                std::cin >> newOperand;  //将数字赋值给newOperand
                s.push(newOperand);  
                break;
        }
    }
    if (s.pop(res))
        std::cout << res << std::endl;
}

//队列--类定义
template< typename T >
class Queue{
    public:
        void clear();  //清空队列
        bool enQueue(const T item);  //入队
        bool deQueue(T& item);  //出队
        bool getFront(T& item);  //返回队头元素
        bool isEmpty();  //判定队列是否空
        bool isFull();  //判定队列是否满
};

//链式队列--类定义
template <typename T>
class LinkedQueue : public Queue<T> {
private:
    int m_size;             // 当前元素个数
    LinkNode<T>* m_front;   // 队头指针
    LinkNode<T>* m_rear;    // 队尾指针
public:
    LinkedQueue() {
        this->m_size = 0;
        this->m_front = this->m_rear = 0;
    };
    ~LinkedQueue() {
        this->clear();
    }
    void clear();
    bool enQueue(const T item);
    bool deQueue(T& item);
    bool getFront(T& item);
    bool isEmpty();
    bool isFull();
    void dumpQueue();
};

//清空队列
template <typename T>
void LinkedQueue<T>::clear() {
    while (m_front != 0) {
        m_rear = m_front;
        m_front = m_front->getNext();
        delete m_rear;
    }
    m_rear = 0;
    m_size = 0;
}

//返回头指针
template <typename T>
bool LinkedQueue<T>::getFront(T& item) {  //将头指针数据赋值给item
    if (this->m_size == 0) {
        std::cout << "Queue is empty!" << std::endl;
        return false;
    }
    item = m_front->getData();
    return true;
}

//入队尾
template <typename T>
bool LinkedQueue<T>::enQueue(const T item) {
    if (this->m_rear == 0) {    // 空队列
        this->m_front = this->m_rear = new LinkNode<T>(item);
    } else {                    // 非空队列
        this->m_rear->setNext(new LinkNode<T>(item));  //
        this->m_rear = this->m_rear->getNext();  //更新队尾节点
    }
    this->m_size++;
    return true;
}

//出队首
template <typename T>
bool LinkedQueue<T>::deQueue(T& item) {
    LinkNode<T>* temp = 0;
    if (this->m_size == 0) {
        std::cout << "Queue is empty!" << std::endl;
        return false;
    }
    item = this->m_front->getData();
    temp = this->m_front;
    this->m_front = this->m_front->getNext();
    delete temp;
    if (this->m_front == 0) {  //当队列原本只有一个元素
        this->m_rear = 0;
    }
    this->m_size--;
    return true;
}

//循环队列--类定义
template <typename T>
class ArrayQueue : public Queue<T> {
private:
    int m_size;
    int m_front;
    int m_rear;
    T* m_queue;
public:
    ArrayQueue(int size);  // 构造函数
    ~ArrayQueue(void);  // 析构函数
    void clear();  // 清空队列
    bool enQueue(const T item);  // 入队操作
    bool deQueue(T& item);  // 出队操作
    bool getFront(T& item);  // 获取队头元素
    bool isEmpty();  // 判断队列是否为空
    bool isFull();  // 判断队列是否已满
};

//构造函数（循环队列）
template <typename T>
ArrayQueue<T>::ArrayQueue(int size) {
    if (size > 0) {
        m_size = size + 1;
    //浪费一个数组元素的空间来区分队列为空和队列满的情况
    } else {
        m_size = 1;
    }
    m_queue = new T[m_size];
    m_front = m_rear = 0;
}

//析构函数（循环队列）
template <typename T>
ArrayQueue<T>::~ArrayQueue(void) {
    delete[] m_queue;
}

//清空队列（循环队列）
template <typename T>
void ArrayQueue<T>::clear() {
    m_front = m_rear;
}

//入队尾（循环队列）
template <typename T>
bool ArrayQueue<T>::enQueue(const T item) {
    if (((m_rear + 1) % m_size) == m_front) {
        std::cout << "Queue is full, stack overflow!" << std::endl;
        return false;
    }
    m_queue[m_rear] = item;
    m_rear = (m_rear + 1) % m_size; 
    //取模是防止当前rear指向最后一个元素时加一会溢出？
    return true;
}

//出队首（循环队列）
template <typename T>
bool ArrayQueue<T>::deQueue(T& item) {
    if (m_front == m_rear) {
        std::cout << "Queue is empty!" << std::endl;
        return false;
    }
    item = m_queue[m_front];
    m_front = (m_front + 1) % m_size;
    return true;
}

//获取队头元素（循环队列）
template <typename T>
bool ArrayQueue<T>::getFront(T& item) {
    if (m_front == m_rear) {
        std::cout << "Queue is empty!" << std::endl;
        return false;
    }
    item = m_queue[m_front];
    return true;
}