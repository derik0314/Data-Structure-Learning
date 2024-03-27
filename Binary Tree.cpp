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
        void setValue(const T& info);
        void setLeftChild(BinaryTreeNode<T>* leftChild);
        void setRightChild(BinaryTreeNode<T>* rightChild);
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
        BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* cur); 
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
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* cur) {
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
        void InsertTreeNode(BinaryTreeNode<T>* root, 
                            BinaryTreeNode<T>* newPointer);
};

//二叉搜索树的插入
template<typename T>
void BinarySearchTree<T>::InsertTreeNode(BinaryTreeNode<T>* root, BinaryTreeNode<T>* newPointer){
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
        bool IsLeaf(int pos)const;
        int	LeftChild(int pos)const;
        int	RightChild(int pos)const;
        int	Parent(int pos)const;
        bool Remove(int pos, T& node);
        bool Insert(const T& newnode);
        T& RemoveMin();
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
bool MinHeap< T >::IsLeaf(int pos) const {
	return (pos >= this->curSize/2) && //该位置处于堆的下半部分
		 (pos <= this->curSize-1); //堆的索引从0开始
}

//返回父节点位置
template < typename T >
int MinHeap< T >::Parent(int pos) const {
	return (pos-1)/2;
}

//返回左子节点位置
template < typename T >
int MinHeap< T >::LeftChild(int pos)const {
	return pos*2+1;
}

//返回右子节点位置
template < typename T >
int MinHeap< T >::RightChild(int pos) const {
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
	int j = this->LeftChild(i);  //获得左子节点位置
	T temp = this->heapArray[i];  //临时存储父节点的值
	while( j < this->curSize){	
		if((j < this->curSize-1) && 
		   (this->heapArray[j] > this->heapArray[j+1])){//如果右子节点更小
			j++;  //令j为右子节点的位置
		}
		if(temp > this->heapArray[j]){//如果父节点大于子节点值
			this->heapArray[i] = this->heapArray[j];  //子节点值上移
			i = j;  //原父节点位置更新为子节点位置
			j = this->LeftChild(j);
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
bool MinHeap< T >::Insert( const T& newnode){
	if(this->curSize == this->maxSize)
		return false;
	this->heapArray[this->curSize] = newnode;  	//将新元素存入堆存储数组最后一个
	this->siftUp(this->curSize);	//向上调整
	this->curSize ++;
	return true;
}

//移除最小值
template < typename T >
T& MinHeap< T >::RemoveMin(){
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
bool MinHeap< T >::Remove(int pos, T& node){
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


