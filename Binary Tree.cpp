#include <iostream>

//二叉树节点
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

//二叉树
template <typename T>
class BinaryTree{
    private:
        BinaryTreeNode<T>* m_root;
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