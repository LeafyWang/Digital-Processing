//Leafy 2017/03/19~
//Transition between Binary-Tree and Forest

#include<iostream>
#include<string>

using namespace std;

struct node
{
    char a;

    //Ϊ��ʱ��������������Ч
    node* leftchild;    //�������
    node* rightsibling; //���ֵ�

    //Ϊ������ʱ��������������Ч
    node* lchild;       //���ӽڵ�
    node* rchild;       //���ӽڵ�
};

class Tree
{
public:
    node* troot[10];            //��Ϊɭ��ʱ �洢���еĸ��ڵ�
    node* broot;                //��Ϊ������ʱ �洢�������ĸ��ڵ�
    int cnt;                    //��Ϊɭ��ʱ �洢���ڵ�ĸ���
    bool isBT;                  //��cntΪ1ʱ true�������BinaryTree false������Tree

    void buildBT();             //�½�һ�ö�����
    void BTtoF();               //��������ת��Ϊɭ��

    void transToBTree();        //��ɭ��ת��Ϊ������

    void PreOrderF();           //��ɭ�ֽ����������
    void PostOrderF();          //��ɭ�ֽ��к������
    void Pre(node* temp);       //�Զ����������������
    void Mid(node* temp);       //�Զ��������к������

    Tree()
    {
        for(int i=0;i<10;i++)
        {
            troot[i] = NULL;
        }
        broot = NULL;
        cnt = 0;
        isBT = false;
    }

private:
    void transToTree();         //˽�к��� ɭ��ת��Ϊ���������ӹ��̣��Ƚ�ɭ��ת��Ϊһ����
    void PreOrderT(node* temp); //˽�к��� ɭ�ֱ������ӹ��� ��һ�������б���
    void PostOrderT(node* temp);//˽�к��� ɭ�ֱ������ӹ��� ��һ�������б���

    void transfer(node* temp);
    void transfer_o(node* temp);
};

void Tree::buildBT()
{
    node* a[14];

    char x = 'a';

    for(int i=0;i<14;i++)
    {
        a[i] = new node;
        a[i]->a = x;
        x = x + 1;
        a[i]->lchild = NULL;
        a[i]->rchild = NULL;
        a[i]->leftchild = NULL;
        a[i]->rightsibling = NULL;
    }

    a[0]->lchild = a[1];
    a[0]->rchild = a[2];
    a[1]->lchild = a[3];
    a[1]->rchild = a[4];
    a[2]->lchild = a[7];
    a[4]->lchild = a[5];
    a[4]->rchild = a[6];
    a[7]->rchild = a[8];
    a[5]->lchild = a[9];
    a[5]->rchild = a[10];
    a[6]->lchild = a[11];
    a[8]->lchild = a[12];
    a[8]->rchild = a[13];

    troot[cnt] = a[0];
    broot = a[0];

    cnt = 1;

    cout << "create BinaryTree successfully." << endl;

}

void Tree::BTtoF()
{
    transfer_o(broot);

    troot[0] = new node;


    troot[0]->a = ' ';
    troot[0]->leftchild = broot;

    cnt = 1;


    /*node* t = broot;
    int i = 0;
    while(t!=NULL)
    {
        troot[i] = t;
        t = t->rightsibling;
        troot[i]->rightsibling = NULL;
        i++;
    }
    cnt = i;*/

    cout << "transfer to Forest successfully." << endl;

}

void Tree::transToBTree()
{
    transToTree();//�õ�һ����

    transfer(broot);
}

void Tree::PreOrderF()
{
    for(int i=0;i<cnt;i++)
    {
        PreOrderT(troot[i]);
    }
}

void Tree::PostOrderF()
{
    for(int i=0;i<cnt;i++)
    {
        PostOrderT(troot[i]);
    }
}

void Tree::Pre(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    cout << temp->a;
    Pre(temp->lchild);
    Pre(temp->rchild);

    return;
}

void Tree::Mid(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    Mid(temp->lchild);
    cout << temp->a;
    Mid(temp->rchild);

    return;
}

void Tree::transToTree() //forest->tree
{
    for(int i=cnt-1;i>0;i--)
    {
        if(troot[0]->leftchild!=NULL)
        {
            node* temp = troot[0]->leftchild;
            while(temp->rightsibling!=NULL)
            {
                temp = temp->rightsibling;
            }
            temp->rightsibling = troot[i-1];
        }
        else
        {
            troot[0]->leftchild = troot[i-1];
        }
    }
    cnt = 1;
    for(int i=1;i<10;i++)
    {
        troot[i] = NULL;
    }

    broot = troot[0];
}

void Tree::PreOrderT(node* temp)
{
    if(temp==NULL)
    {
        return;
    }
    cout << temp->a;

    if(temp->leftchild!=NULL)
    {
        node* t = temp->leftchild;
        while(t!=NULL)
        {
            PreOrderT(t);
            t = t->rightsibling;
        }
        return;
    }
}

void Tree::PostOrderT(node* temp)
{
    if(temp==NULL)
    {
        return;
    }

    if(temp->leftchild!=NULL)
    {
        node* t = temp->leftchild;
        while(t!=NULL)
        {
            PostOrderT(t);
            t = t->rightsibling;
        }
    }

    cout << temp->a;
}

void Tree::transfer(node* temp)
{
    if(temp==NULL)
        return;

    temp->lchild = temp->leftchild;
    temp->rchild = temp->rightsibling;

    transfer(temp->leftchild);
    transfer(temp->rightsibling);

}

void Tree::transfer_o(node* temp)
{
    if(temp==NULL)
        return;

    temp->leftchild = temp->lchild;
    temp->rightsibling = temp->rchild;

    transfer_o(temp->lchild);
    transfer_o(temp->rchild);
}

int main()
{
    Tree test;
    test.buildBT();
    cout  << "BinaryTree: Pre-Order" << endl;
    test.Pre(test.broot);
    cout  << endl << "BinaryTree: Mid-Order" << endl;
    test.Mid(test.broot);

    cout << endl << "Transfer to Forest:" << endl;
    test.BTtoF();
    //cout << test.troot[0]->leftchild->rightsibling->a;
    cout << endl << "Forest: Pre-Order" << endl;
    test.PreOrderF();
    cout << endl << "Forest: Post-Order" << endl;
    test.PostOrderF();

    cout << endl << "Transfer to BinaryTree:" << endl;
    test.transToBTree();
    cout  << endl << "BinaryTree: Pre-Order" << endl;
    test.Pre(test.broot);
    cout  << endl << "BinaryTree: Mid-Order" << endl;
    test.Mid(test.broot);
    return 0;
}
