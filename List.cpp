//线性表--类定义
template <typename T>
class List {
public:
    void clear();                    // 置空线性表
    bool isEmpty();                  // 判断线性表是否为空
    bool append(const T value);      // 在表尾添加元素
    bool insert(const int p, const T value);  // 在指定位置插入元素
    bool remove(const int p);         // 删除指定位置的元素
    bool getValue(const int p, T& value);     // 返回指定位置的元素内容
    bool setValue(const int p, const T value); // 更新指定位置的元素内容
    bool getPos(int &p, const T value);       // 返回value元素内容的位置
};

//顺序表--类定义
template<typename T>
class ArrayList : public List<T> {
private:
    T* m_list; // 数据存储数组指针，指针类型可以进行动态内存分配
    int m_maxsize; // 数组最大容量
    int m_curlen; // 当前数组长度
    int m_position; // 游标位置
public:
    ArrayList(const int size); // 构造函数，初始化数组大小
    ~ArrayList(); // 析构函数，释放内存
    void clear(); // 清空数组
    int length(); // 返回数组长度
    bool isEmpty(); // 判断数组是否为空
    bool appendValue(const T value); // 在数组末尾添加元素
    bool insertValue(const int p, const T value); // 在指定位置插入元素
    bool deleteValue(const int p); // 删除指定位置的元素
    bool setValue(const int p, const T value); // 修改指定位置的元素
    bool getValue(const int p, T& value); // 获取指定位置的元素
    bool getValuePos(int& p, const T value); // 获取指定元素的位置
};

//构造函数
template<typename T>
ArrayList<T>::ArrayList(const int size) {
    this->m_maxsize = size;
    this->m_list = new T[m_maxsize];
    this->m_curlen = this->m_position = 0;
}

//析构函数
template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] this->m_list;
}

//获取指定元素的位置
template<typename T>
bool ArrayList<T>::getValuePos(int& p, const T value) {
    for (int i = 0; i < this->m_curlen; i++) {
        if (value == m_list[i]) {
            p = i; // 将找到的元素位置赋值给p
            return true; 
        }
    }
    return false; 
}

//在指定位置插入元素
template<typename T>
bool ArrayList<T>::insertValue(const int p, const T value) {
    if (this->m_curlen >= this->m_maxsize - 1) {
        std::cerr << "The list is overflow" << std::endl; // 判断是否有空间可插入
        return false;
    }
    if (p < 0 || p > (this->m_curlen - 1)) { // 判断插入位置是否合法
        std::cerr << "Insertion point is illegal" << std::endl;
        return false;
    }
    for (int i = this->m_curlen; i > p; i--) { // 移动元素
        this->m_list[i] = this->m_list[i - 1];
    }
    this->m_list[p] = value; // 插入元素
    this->m_curlen++; // 修改表长
    return true;
}

//删除指定位置的元素
template<typename T>
bool ArrayList<T>::deleteValue(const int p) {
    if (this->m_curlen <= 0) { 
        std::cerr << "No element to delete" << std::endl;
        return false;
    }
    if (p < 0 || p > (this->m_curlen - 1)) { 
        std::cerr << "Deletion is illegal" << std::endl;
        return false;
    }
    for (int i = p; i < this->m_curlen; i++) { 
        this->m_list[i] = this->m_list[i + 1];
    }
    this->m_curlen--; // 修改表长
    return true;
}

//单链表结点--类定义
template<typename T>
class LinkNode {
private:
    T m_data;
    LinkNode<T>* m_next;
public:
    LinkNode(const T info, LinkNode<T>* nextnode) : m_data(info), m_next(nextnode) {}
    LinkNode(LinkNode<T>* nextnode) : m_data(T()), m_next(nextnode) {}
    ~LinkNode() {
        delete m_next;
    }
    void setNext(LinkNode<T>* next) {
        m_next = next;
    }
    LinkNode<T>* getNext() {
        return m_next;
    }
    T getData() {
        return m_data;
    }
    void setData(const T data) {
        m_data = data;
    }
};

//单链表--类定义
template<typename T>
class LinkList : public List<T> {
private:
    LinkNode<T>* m_head;
    LinkNode<T>* m_tail;
    LinkNode<T>* setPos(const int p);
public:
    LinkList();
    ~LinkList();
    void clear();
    int length();
    bool isEmpty();
    bool appendValue(const T value);
    bool insertValue(const int p, const T value);
    bool deleteValue(const int p);
    bool getValue(const int p, T& value);
    bool getValuePos(int& p, const T value);
};

//构造函数（单链表）
template<typename T>
LinkList<T>::LinkList() {
    this->m_head = this->m_tail = new LinkNode<T>(0);
}

//析构函数（单链表）
template<typename T>
LinkList<T>::~LinkList() {
    LinkNode<T>* temp = nullptr;
    while (this->m_head != nullptr) {
        temp = this->m_head;
        this->m_head = this->m_head->getNext();
        delete temp;
    }
}

//检索（单链表）
template<typename T>
LinkNode<T>* LinkList<T>::setPos(const int i) {
    int count = 0;
    if (i < -1) {
        return nullptr;
    }
    if (i == -1) {
        return this->m_head;
    }
    LinkNode<T>* p = this->m_head->getNext();
    while (p != nullptr && count < i) {
        p = p->getNext();
        count++;
    }
    return p;
}

//插入（单链表）
template<typename T>
bool LinkList<T>::insertValue(const int position, const T value) {
    LinkNode<T>* pred = nullptr; // 前驱节点
    LinkNode<T>* newNode = nullptr;
    if ((pred = setPos(position - 1)) == nullptr) { // 如果找不到指定位置的前驱节点
        std::cerr << "illegal insertion point!" << std::endl; 
        return false;
    }
    newNode = new LinkNode<T>(value, pred->getNext()); // 创建新节点
    pred->setNext(newNode); // 将新节点插入到前驱节点之后
    if (pred == this->m_tail) { // 如果前驱节点是尾节点
        this->m_tail = newNode; 
    }
    return true; 
}

//删除（单链表）
template<typename T>
bool LinkList<T>::deleteValue(const int position) {
    LinkNode<T>* pred = nullptr;
    LinkNode<T>* toDelete = nullptr;
    pred = getPos(position - 1);
    if (pred == nullptr || pred == this->m_tail) {
        std::cerr << "illegal deletion point!" << std::endl;
        return false;
    }
    toDelete = pred->getNext();
    if (toDelete == this->m_tail) {
        this->m_tail = pred;
        pred->setNext(nullptr);
        delete toDelete;
    } else if (toDelete != nullptr) {
        pred->setNext(toDelete->getNext());
        delete toDelete;
    }
    return true;
}

//双向链表节点--类定义
template<typename T>
class DLinkNode {
private:
    T m_data;
    DLinkNode<T>* m_next;
    DLinkNode<T>* m_prev;
public:
    DLinkNode(const T data, DLinkNode<T>* prev = nullptr, DLinkNode<T>* next = nullptr);
    DLinkNode(DLinkNode<T>* prev = nullptr, DLinkNode<T>* next = nullptr);
    T getData();
    void setData(T data);
    DLinkNode<T>* getNext();
    void setNext(DLinkNode<T>* next);
    DLinkNode<T>* getPrev();
    void setPrev(DLinkNode<T>* prev);
};


