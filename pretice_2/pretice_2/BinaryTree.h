#pragma once
#include <iostream>
#include <string>
#include<queue>
#include<graphics.h>
#define r 30
#define width 1000
#define heigh 600
using namespace std;
template <class T>
struct BinTreeNode
{	      //二叉树结点类定义
    T data;	 		      //数据域
    BinTreeNode<T>* leftChild, * rightChild, * parent;
    int x0, y0;
    //左子女、右子女链域
    BinTreeNode(BinTreeNode<T>* p)                //构造函数
    {
        data = '@'; leftChild = NULL;  rightChild = NULL; parent = p;

    }
    BinTreeNode()
    {
        data = '@'; leftChild = NULL;  rightChild = NULL; parent = NULL;
    }
};

template <class T>
class BinaryTree 
{			//二叉树类定义
public:
    BinaryTree() { root = new BinTreeNode<T>; root->parent = NULL; }	  		//构造函数
    ~BinaryTree() { destroy(root); }	  		//析构函数
    BinTreeNode<T>* Parent(BinTreeNode <T>* t)
    {	//返回双亲结点
        return t.parent;
    }
    BinTreeNode<T>* LeftChild(BinTreeNode<T>* t) {	//返回左子女
        return (t != NULL)?t->leftChild : NULL;
    }
    BinTreeNode<T>* RightChild(BinTreeNode<T>* t) { 	//返回右子女
        return (t != NULL)?t->rightChild : NULL;
    }
    BinTreeNode<T>* getRoot() const { return root; }	 //取根
    BinTreeNode<T>* CoParent(BinTreeNode<T>* p, BinTreeNode<T>* q);

    void levelOrder(BinTreeNode<T>* t);			//层次序遍历

     void Create(); //菜单
     bool Num(string s, string t);
     void Error();
     bool Examine_1(string str1, string str2);
     bool Examine_2(string str1, string str2);
     void Find(BinTreeNode<T>* d);
protected:
    BinTreeNode<T>* root; 		//二叉树的根指针
    T RefValue;	 		//数据输入停止标志
    void CreateBinTree1(BinTreeNode<T>* t, string str1, string str2);//前+中序遍历创建建树
    void CreateBinTree2(BinTreeNode<T>* t, string str1, string str2);//中+后序遍历创建建树
    void destroy(BinTreeNode<T>*& subTree); 		//删除

private:
    string str1; //缓存键盘读取的数据
    string str2; //缓存键盘读取的数据

};

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::CoParent(BinTreeNode<T>* p, BinTreeNode<T>* q)
{
    string str;
    char s;
    int i = 0;
    int n;
    BinTreeNode<T>* ch = new BinTreeNode<T>;
    ch = p;
    while (p->parent != NULL)
    {
        str += p->parent->data;
        p = p->parent;
    }
    while (q->parent != NULL)
    {
        s = q->parent->data;
        n = str.find(s);
        if (n != -1) break;
        else q=q->parent;
    }
        for (int i = 0; i <= n; i++)
        {
            ch = ch->parent;
        }
    return ch;
}

template<class T>
inline void BinaryTree<T>::levelOrder(BinTreeNode<T>* t)
{
    queue<BinTreeNode<T>*>  q;
    q.push(t);
    int x = width / 2;
    int dy = 120;
    int dx = 200;
    int n = 0;
    int y;
    q.front()->x0 = x;
    q.front()->y0 = 40;
    circle(q.front()->x0, q.front()->y0, r);
    xyprintf(q.front()->x0 - 2, q.front()->y0 - 7, "%c", q.front()->data);
    int temp[2] = { -1,1 };
    x /= 2;
    while (!q.empty())
    {
        if (q.front()->leftChild != NULL)
            q.push(q.front()->leftChild);
        if(q.front()->rightChild!=NULL)
            q.push(q.front()->rightChild);
        y = q.front()->y0;
        q.pop();
        if (!q.empty())
        {
            q.front()->y0 = q.front()->parent->y0 + dy;
            if (y != q.front()->y0)
                x /= 2;
            if (n%2 == 0)
                q.front()->x0 = q.front()->parent->x0 - x;
            else 
                q.front()->x0 = q.front()->parent->x0 + x;
            
            if (!q.empty() && q.front()->data != '@')
            {
                Sleep(500);
                ege_line(q.front()->parent->x0+(r)* temp[n % 2], q.front()->parent->y0+r-10 , q.front()->x0, q.front()->y0-r);
                circle(q.front()->x0, q.front()->y0, r);
                xyprintf(q.front()->x0 - 2, q.front()->y0 - 7, "%c", q.front()->data);
            }
            n++;
        }
    }
}

template<class T>
inline void BinaryTree<T>::Create()
{
    cout << "-----------------------------------" << endl;
    cout << "【1】 前+中序遍历创建二叉树；" << endl;
    cout << "【2】 中+后序遍历建立二叉树。" << endl;
    cout << "请选择：";
    int ch;
    bool p;
    while (cin >> ch)
    {
        if (ch == 1)
        {
            cout << "请输入前序遍历：";
            cin >> str1;
            cout << "请输入中序遍历：";
            cin >> str2;
            p=Num(str1, str2);
            if (p)
            {
                p=Examine_1(str1,str2);
                if (p)
                {
                    CreateBinTree1(root, str1, str2);
                    initgraph(width, heigh, 0);
                    setbkcolor(WHITE);
                    setcolor(BLACK);
                    ege_enable_aa(true);
                    levelOrder(root);
                    getch();
                    closegraph();
                    cout << endl;
                    cout << "是否进行祖先查询？";
                    cout << "【1】 是" << '\t' << "【2】否" << endl;
                    cout << "请选择：";
                    int x;
                    cin >> x;
                    if(x==1)
                        Find(root);
                }
                else 
                    Error();
            }
            else
                Error();
        }
        else if (ch == 2)
        {
            cout << "请输入中序遍历：";
            cin >> str1;
            cout << "请输入后序遍历：";
            cin >> str2;
            p = Num(str1, str2);
            if (p)
            {
                p = Examine_2(str1,str2);
                if (p)
                {
                    CreateBinTree2(root, str1, str2);
                    initgraph(width, heigh, 0);
                    setbkcolor(WHITE);
                    setcolor(BLACK);
                    ege_enable_aa(true);
                    levelOrder(root);
                    getch();
                    closegraph();
                    clearviewport();
                    cout << endl;
                    cout << "是否进行祖先查询？";
                    cout << "【1】 是" << '\t' << "【2】否" << endl;
                    cout << "请选择：";
                    int x;
                    cin >> x;
                    if (x == 1)
                        Find(root);
                }
                else 
                    Error();
            }
            else
                Error();
        }
        else
            cout << "输入非法，请重新输入：" << endl;
        cout << "【1】 前+中序遍历创建二叉树；" << endl;
        cout << "【2】 中+后序遍历建立二叉树。" << endl;
        cout << "请选择：";
    }
}

template<class T>
inline bool BinaryTree<T>::Num(string s, string t)
{
    int x = s.length();
    int y = t.length();
    if (x == y) return true;
    else 
        return false;
}

template<class T>
inline void BinaryTree<T>::Error()
{
    cout << "该序列无法建立二叉树,请重新输入：" << endl;
}

template<class T>
inline bool BinaryTree<T>::Examine_1(string str1, string str2)
{
    if (str1[0] != NULL && str2[0] != NULL)//判断序列是否遍历完毕		
    {
        int i = 0, j = 0;
        char rootNode = str1[0];//根
        int p = str2.find(rootNode);//根在中序序列中的位置
        if (p == -1) return false;//如果未找到根节点，GetP函数返回-1，则终止检查函数，返回0，不能构建为二叉树

        if (p >= 0)
        {
            i = Examine_1(str1.substr(1, p), str2.substr(0, p));//找到了根节点，则分别截取中序里根节点左侧元素
                                                              //从第一个元素开始截取，截取p个元素
        }//同时截取前序序列里等长的p个元素序列，从第二个元素开始，构成新的前序序列，进行递归操作

         //截取中序序列的右子树和前序序列的剩下部分
        if (p < str1.size())
        {
            j = Examine_1(str1.substr(p + 1, (str1.size() - 1 - p)), str2.substr(p + 1, (str2.size() - 1 - p)));
        }
        //当二者都检测不出错误时，最后返回1，表示可以打印出二叉树
        return (i + j == 2) ? true : false;//必须i=j=1,才表示能够构建为二叉树
    }
    //如果遍历完毕，则返回1,即检查过程中没有问题，
    else return true;
}

template<class T>
inline bool BinaryTree<T>::Examine_2(string str1, string str2)
{
    if (str1[0] != NULL && str2[0] != NULL)
    {
        int i = 0, j = 0;
        char rootNode = str2[str2.length() - 1];//根
        int p = str1.find(rootNode);//根在中序序列中的位置
        if (p == -1) return false;

        if (p >= 0)
        {
            i = Examine_2(str1.substr(0, p), str2.substr(0, p));
        }
        if (p < str1.size())
        {
            j = Examine_2(str1.substr(p + 1, (str1.size() - 1 - p)), str2.substr(p, (str2.size() - 1 - p)));
        }
        return (i + j == 2) ? true : false;
    }
    else return true;
}

template<class T>
inline void BinaryTree<T>::Find(BinTreeNode<T>* d)
{
    BinTreeNode<T>* p = new BinTreeNode<T>;
    BinTreeNode<T>* q = new BinTreeNode<T>;
    BinTreeNode<T>* s = new BinTreeNode<T>;
    queue<BinTreeNode<T>*>  t;
    cout << "请分别输入两个data：";
    char ch1, ch2;
    cin >> ch1 >> ch2;
    int n = str1.find(ch1);
    int m = str1.find(ch2);
    if (ch1 != -1 && ch2 != -1)
    {     
        t.push(d);       
        while (!t.empty())
        {
            if (t.front()->data == ch1) p = t.front();
            else if (t.front()->data == ch2) q = t.front();
            if (t.front()->leftChild != NULL)
                t.push(t.front()->leftChild);
            if (t.front()->rightChild != NULL)
                t.push(t.front()->rightChild);
            t.pop();
        }
        s=CoParent(p, q);
        cout << "其共同祖先的data为：" << s->data << endl;
    }
    else
    {
        if (ch1 == -1 && ch2 == -1)
            cout << "两个data都不在树中" << endl;
        else if (ch1 == -1)
            cout << "第一个data不在树中" << endl;
        else 
            cout << "第二个data不在树中" << endl;
        return;
    }
}

template<class T>
void BinaryTree<T>::CreateBinTree1(BinTreeNode<T>* t, string str1, string str2)
{
    //前+中序遍历创建二叉树
    BinTreeNode<T>* NextL = new BinTreeNode<T>(t);  //左孩子
    BinTreeNode<T>* NextR = new BinTreeNode<T>(t);    //右孩子
    if (str1.length() == 0)
    {
        t = NULL;
        delete NextL;
        delete NextR;
        return;
    }
    t->leftChild= NextL;
    t->rightChild=NextR;
    char rootNode = str1[0];//根
    int index = str2.find(rootNode);//根在中序序列中的位置
    string lchild_str2 = str2.substr(0, index);//左孩子的中序序列
    string rchild_str2 = str2.substr(index + 1);//右孩子的中序序列
    int lchild_length = lchild_str2.length();//左孩子的长度
    int rchild_length = rchild_str2.length();//右孩子的长度
    string lchild_str1 = str1.substr(1, lchild_length);//左孩子的前序序列
    string rchild_str1 = str1.substr(1 + lchild_length);//右孩子的前序序列
    if (t != NULL)
    {
        t->data = rootNode;
        CreateBinTree1(NextL, lchild_str1, lchild_str2);//递归创建左孩子
        CreateBinTree1(NextR, rchild_str1, rchild_str2);//递归创建右孩子
    }
}

template<class T>
inline void BinaryTree<T>::CreateBinTree2(BinTreeNode<T>*  t, string str1, string str2)
{
    BinTreeNode<T>* NextL = new BinTreeNode<T>(t);  //左孩子
    BinTreeNode<T>* NextR = new BinTreeNode<T>(t);    //右孩子
    if (str1.length() == 0)
    {
        t = NULL;
        delete NextL;
        delete NextR;
        return;
    }
    t->leftChild = NextL;
    t->rightChild = NextR;
    char rootNode = str2[str2.length()-1];//根
    int index = str1.find(rootNode);//根在中序序列中的位置
    string lchild_str1 = str1.substr(0, index);//左孩子的中序序列
    string rchild_str1 = str1.substr(index+1);//右孩子的中序序列
    int lchild_length = lchild_str1.length();//左孩子的长度
    int rchild_length = rchild_str1.length();//右孩子的长度
    string lchild_str2 = str2.substr(0, lchild_length);//左孩子的后序序列
    string rchild_str2 = str2.substr(lchild_length,rchild_length);//右孩子的后序序列
    if (t != NULL)
    {
        t->data = rootNode;  
        CreateBinTree2(NextR, rchild_str1, rchild_str2);//递归创建右孩子
        CreateBinTree2(NextL, lchild_str1, lchild_str2);//递归创建左孩子
    }
}

template<class T>
inline void BinaryTree<T>::destroy(BinTreeNode<T>*& subTree)
{
    //私有函数: 删除根为subTree的子树
    if (subTree != NULL) {
        destroy(subTree->leftChild);     //删除左子树
        destroy(subTree->rightChild);   //删除右子树
        delete subTree; 			 //删除根结点
    }
}


