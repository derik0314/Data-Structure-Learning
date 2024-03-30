#include <iostream>

//二叉树节点--类定义
template <typename T>
class BinaryTreeNode{
    friend class BinaryTree <T>;
    protected: 
        T info;
    public:
        BinaryTreeNode();
        BinaryTreeNode(const T& info);
        BinaryTreeNode(const T& info, BinaryTreeNode<T>* leftChild, 
                        BinaryTreeNode<T>* rightChild);
        virtual ~BinaryTreeNode();
        T value() const;
        BinaryTreeNode<T>* leftChild;
        BinaryTreeNode<T>* rightChild;
        BinaryTreeNode<T>* parent;
        void SetValue(const T& info);
        void SetleftChild(BinaryTreeNode<T>* leftChild);
        void SetrightChild(BinaryTreeNode<T>* rightChild);
        bool isLeaf() const;
};

//二叉树--类定义
template <typename T>
class BinaryTree{
    private:
        BinaryTreeNode<T>* root;
    public:
        BinaryTree();
        ~BinaryTree();
        bool isEmpty() const;
        BinaryTreeNode<T>* Root(); 
        BinaryTreeNode<T>* parent(BinaryTreeNode<T>* cur); 
        BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* cur); 
        BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* cur);
        void CreateTree(
            const T& info,
            const BinaryTree<T>& leftChild,
            const BinaryTree<T>& rightChild
        ) ;
        void DeleteBinaryTree(BinaryTreeNode<T>* root);
        void PreOrder(BinaryTreeNode<T>* root);
        void InOrder(BinaryTreeNode<T>* root);
        void PostOrder(BinaryTreeNode<T>* root);
        void LevelOrder(BinaryTreeNode<T>* root);
};

//前序周游二叉树
template<typename T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root){
    if(root != 0){
        visit(root);
        PreOrder(root->leftChild);
        PreOrder(root->rightChild);
    }
}

//中序周游二叉树
template<typename T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* root){
    if(root != 0){
        InOrder(root->leftChild);
        visit(root);
        InOrder(root->rightChild);
    }
}

//后序周游二叉树
template<typename T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* root){
    if(root != 0){
        PostOrder(root->leftChild);
        PostOrder(root->rightChild);
        visit(root);
    }
}

//层次遍历二叉树
template <class T>
void levelOrder(BinaryTreeNode<T> *t){
    arrayQueue<BinaryTreeNode<T>*> q;
    while(t != 0){
        visit(t);
        if(t->leftChild != 0)
            q.push(t->leftChild);  //从队尾压入队列
        if(t->rightChild !=0)
            q.push(t->rightChild);
        
        try{t = q.front();}  //t指向第一个元素
        catch(queueEmpty){return;}
        q.pop();  //从队首弹出元素
    }
}

//返回current的父节点
template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::parent(BinaryTreeNode<T>* cur) {
    std::stack<BinaryTreeNode<T>*> stack;
    BinaryTreeNode<T>* pt = this->root;
    if(this->root && cur){
        while(!stack.empty() || pt){
            if(pt){
                if(cur==pt->leftChild || cur==pt->rightChild)
                    return pt;
                stack.push(pt);
                pt = pt->leftChild;
            }else{
                pt = stack.top;
                stack.pop();
                pt = pt->rightChild;
            }
        }
    }
}

//删除二叉树
template<typename T>
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* root){
    if(root != 0){
        DeleteBinaryTree(root->leftChild);
        DeleteBinaryTree(root->rightChild);
        delete root;
    }
}

//二叉搜索树--类定义
template<typename T>
class BinarySearchTree{
    private:
        BinaryTreeNode<T>* root;
    public:
        BinaryTreeNode<T>* Find(BinaryTreeNode<T>* cur);
        void insetTreeNode(BinaryTreeNode<T>* root, 
                            BinaryTreeNode<T>* newPointer);
};

//二叉搜索树的插入
template<typename T>
void BinarySearchTree<T>::insetTreeNode(BinaryTreeNode<T>* root, BinaryTreeNode<T>* newPointer){
    BinaryTreeNode<T>* pointer = 0;
    if(root == 0){
        root = newPointer;
        return;
    }else{
        pointer = root;
        while(pointer != 0){
            if(newPointer->value() == pointer->value())
                return;
            else if(newPointer->value() < pointer->value()){
                if(pointer->leftChild == 0){
                    pointer->leftChild = newPointer;
                    return;
                }else   pointer = pointer->leftChild; 
            }else{
                if(pointer->rightChild == 0){
                    pointer->rightChild = newPointer;
                    return;
                }else   pointer = pointer->rightChild;
            }
        }
    }
}

//堆--类定义
template < typename T >
class MinHeap{
    private:
        T* heapArray;		//存放堆数据的数组
        int curSize;		//当前堆中元素数目
        int maxSize;		//堆所能容纳的最大元素数目
        void BuildHeap();	//建堆操作
    public:
        MinHeap(const int n);
        virtual ~MinHeap();
        bool isLeaf(int pos)const;
        int	leftChild(int pos)const;
        int	rightChild(int pos)const;
        int	parent(int pos)const;
        bool remove(int pos, T& node);
        bool inset(const T& newnode);
        T& removeMin();
        void SiftUp(int pos); 	//向上筛
        void SiftDown(int pos);//向下筛
};

//堆的构造函数
template < typename T >
MinHeap< T >::MinHeap(const int n){
	if( n <= 0) return;
	this->curSize = 0;
	this->maxSize = n;//初始化容量为n
	this->heapArray = new T[this->maxSize];
	this->buildHeap();
}

//判断是否为叶节点
template < typename T >
bool MinHeap< T >::isLeaf(int pos) const {
	return (pos >= this->curSize/2) && //该位置处于堆的下半部分
		 (pos <= this->curSize-1); //堆的索引从0开始
}

//返回父节点位置
template < typename T >
int MinHeap< T >::parent(int pos) const {
	return (pos-1)/2;
}

//返回左子节点位置
template < typename T >
int MinHeap< T >::leftChild(int pos)const {
	return pos*2+1;
}

//返回右子节点位置
template < typename T >
int MinHeap< T >::rightChild(int pos) const {
	return pos*2+2;
}

//建初堆
template < typename T >
void MinHeap< T >::BuildHeap(){
	for( int i = this->curSize/2-1; i>=0; i-- ){
		this->siftDown(i);//反复调用进行筛选
	}
}

//向下筛选
template < typename T >
void MinHeap< T >::SiftDown(int pos){
	int i = pos;  //标识父节点位置
	int j = this->leftChild(i);  //获得左子节点位置
	T temp = this->heapArray[i];  //临时存储父节点的值
	while( j < this->curSize){	
		if((j < this->curSize-1) && 
		   (this->heapArray[j] > this->heapArray[j+1])){//如果右子节点更小
			j++;  //令j为右子节点的位置
		}
		if(temp > this->heapArray[j]){//如果父节点大于子节点值
			this->heapArray[i] = this->heapArray[j];  //子节点值上移
			i = j;  //原父节点位置更新为子节点位置
			j = this->leftChild(j);
		}else break;   
	}
	this->heapArray[i] = temp;
}

//向上筛选
template < typename T >
void MinHeap< T >::SiftUp(int pos){
	int tempPos = pos;
	T temp = this->heapArray[tempPos];
	while((tempPos > 0) && 
	  (this->heapArray[this->parent(tempPos)] > temp)){
		this->heapArray[tempPos]  
        = this->heapArray[this->parent(tempPos)];
		tempPos = this->parent(tempPos);
	}
	this->heapArray[tempPos] = temp;
}

//插入新元素
template < typename T >
bool MinHeap< T >::inset( const T& newnode){
	if(this->curSize == this->maxSize)
		return false;
	this->heapArray[this->curSize] = newnode;  	//将新元素存入堆存储数组最后一个
	this->siftUp(this->curSize);	//向上调整
	this->curSize ++;
	return true;
}

//移除最小值
template < typename T >
T& MinHeap< T >::removeMin(){
	if(this->curSize == 0 ){
		std::cout<<"No item to delete"<<std::endl;
		exit(1);
	}else{
		this->swap(0, --this->curSize);//交换堆顶和堆尾元素
		if(this->curSize > 1){
			this->siftDown(0); //向下筛选，重新排序
		}
		return this->heapArray[this->curSize]; 
        //返回要被删除的最小元素（堆尾元素、最初的堆首元素）
	}
}

//删除元素
template < typename T >
bool MinHeap< T >::remove(int pos, T& node){
	if(( pos < 0) || ( pos >= this->curSize))
		return false;
	node = this->heapArray[pos];
	this->heapArray[pos] = this->heapArray[--this->curSize];
    // 更新当前堆的大小后将堆中最后一个节点的值赋给指定位置的节点
	if(this->heapArray[this->parent(pos)] > this->heapArray[pos])
	    this->siftUp(pos);
	else this->siftDown(pos);
	return true;
}

//哈夫曼树--类定义
template<typename T>
class HuffmanTree {
private:
    BinaryTreeNode<T>* root;
private:
    void mergeTree(BinaryTreeNode<T>* leftChild, BinaryTreeNode<T>* rightChild, BinaryTreeNode<T>* parent);
    void deleteTree(BinaryTreeNode<T>* root);
public:
    HuffmanTree(T weight[], int n);
    virtual ~HuffmanTree();
};

//子树合并父节点（哈夫曼树）	
template<typename T>
void HuffmanTree<T>::mergeTree(BinaryTreeNode<T>* leftChild, BinaryTreeNode<T>* rightChild, BinaryTreeNode<T>* parent) {
    parent = new BinaryTreeNode<T>();
    parent->left = leftChild;
    parent->right = rightChild;
    parent->value = leftChild->value + rightChild->value;
}

//构造函数（哈夫曼树）
template<typename T>
HuffmanTree<T>::HuffmanTree(T weight[], int n) {
    MinHeap<BinaryTreeNode<T>> heap(n);
    BinaryTreeNode<T>* parent = nullptr;
    BinaryTreeNode<T>* leftChild = nullptr;
    BinaryTreeNode<T>* rightChild = nullptr;
    BinaryTreeNode<T>* nodeList = new BinaryTreeNode<T>[n];
    for (int i = 0; i < n; i++) {  //构建二叉树
        nodeList[i].value = weight[i];
        nodeList[i].parent = nodeList[i].leftChild = nodeList[i].rightChild = nullptr;  //父子关系还未明确就先置为空
        heap.inset(nodeList[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        parent = new BinaryTreeNode<T>();
        leftChild = &heap.removeMin();  //heap.removeMin()返回的是对象，而leftChild是指针，所以用&获取地址
        rightChild = &heap.removeMin();
        mergeTree(leftChild, rightChild, parent);
        heap.insert(*parent);
    }
    this->root = parent;
    delete[] nodeList;
}