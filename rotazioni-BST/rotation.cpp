#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;


template <class H> class Nodo{

  private:
    Nodo<H> *parent, *left, *right;
    H* key;

  public:
    Nodo<H>(H key){
      this->key = new H(key);
      left = right = parent = NULL;
    }

    Nodo<H>* getParent(){ return parent; }
    Nodo<H>* getLeft(){ return left; }
    Nodo<H>* getRight(){ return right; }
    H getKey(){ return *key; }
    void setParent(Nodo<H>* parent){ this->parent = parent; }
    void setLeft(Nodo<H>* left){ this->left = left; }
    void setRight(Nodo<H>* right){ this->right = right; }
    void setKey(H key){ this->key = new H(key); }
};

  template <class H> class BST{

    private:
      Nodo<H>* root;

      Nodo<H>* search(H x){
        Nodo<H>* tmp = root;
        while(tmp && tmp->getKey()!=x){
          if(x<tmp->getKey()) tmp = tmp->getLeft();
          else tmp = tmp->getRight();
        }
        return tmp;
      }

      Nodo<H>* _min(Nodo<H>* t){
        if(!t) return NULL;
        while(t->getLeft()) t = t->getLeft();
        return t;
      }

      Nodo<H>* _succ(Nodo<H>* t){
        if(!t) return NULL;
        if(t->getRight()) return _min(t->getRight());
        else return NULL;
      }

      void _inorder(Nodo<H>* t, ofstream& out){
        if(!t) return;
        _inorder(t->getLeft(),out);
        out << t->getKey() << " ";
        _inorder(t->getRight(),out);
      }

      void _preorder(Nodo<H>* t, ofstream& out){
        if(!t) return;
        out << t->getKey() << " ";
        _preorder(t->getLeft(),out);
        _preorder(t->getRight(),out);
      }

      void _postorder(Nodo<H>* t, ofstream& out){
        if(!t) return;
        _postorder(t->getLeft(),out);
        _postorder(t->getRight(),out);
        out << t->getKey() << " ";
      }

    public:
      BST<H>(){
        root = NULL;
      }

      BST<H>* insert(H x){
        Nodo<H>* tmp = root;
        Nodo<H>* p = NULL;
        while(tmp){
          p = tmp;
          if(x<tmp->getKey())
            tmp = tmp->getLeft();
          else
            tmp = tmp->getRight();
        }
        Nodo<H>* newn = new Nodo<H>(x);
        if(!p){
          root = newn;
        }
        else{
          if(x<p->getKey())
            p->setLeft(newn);
          else
            p->setRight(newn);
          newn->setParent(p);
        }
        return this;
      }

      BST<H>* canc(H x){
        Nodo<H>* y = search(x);
        Nodo<H>* p = y->getParent();
        if(!y) return this;
        // CASO 1 SOLO FIGLIO
        if(y->getLeft()==NULL || y->getRight()==NULL){
          Nodo<H>* son = y->getLeft();
          if(y->getRight()) son = y->getRight();
          if(!p) root = son;
          else{
            if(y==p->getLeft()) p->setLeft(son);
            else p->setRight(son);
          }
          if(son) son->setParent(p);
        }
        else{
          Nodo<H>* succ = _succ(y);
          H tmp = succ->getKey();
          canc(succ->getKey());
          y->setKey(tmp);
        }
        return this;
      }

      void leftRotate(H key){
        Nodo<H>* y = search(key);
        Nodo<H>* p = y->getParent();
        Nodo<H>* x = y->getRight();
        if(!x) return;
        y->setRight(x->getLeft());
        x->setLeft(y);
        if(p){
          if(y==p->getLeft()) p->setLeft(x);
          else p->setRight(x);
        }
        else root = x;
        y->setParent(x);
        x->setParent(p);
        if(y->getRight()) y->getRight()->setParent(y);
      }

      void rightRotate(H key){
        Nodo<H>* y = search(key);
        Nodo<H>* p = y->getParent();
        Nodo<H>* x = y->getLeft();
        if(!x) return;
        y->setLeft(x->getRight());
        x->setRight(y);
        if(p){
          if(y==p->getLeft()) p->setLeft(x);
          else p->setRight(x);
        }
        else root = x;
        y->setParent(x);
        x->setParent(p);
        if(y->getLeft()) y->getLeft()->setParent(y);
      }

      void inorder(ofstream& out){
        _inorder(root,out);
        out << endl;
      }

      void preorder(ofstream& out){
        _preorder(root,out);
        out << endl;
      }

      void postorder(ofstream& out){
        _postorder(root,out);
        out << endl;
      }

};

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string type,visit;
  int n,r;

  for(int i=0;i<100;i++){
    input >> type >> n >> r >> visit;
    if(type=="int"){
      BST<int>* t = new BST<int>();
      for(int j=0;j<n;j++){
        char tmp; input >> tmp >> tmp >> tmp >> tmp;
        if(tmp==':'){
          int k; input >> k;
          t->insert(k);
        }
        else{
          input >> tmp;
          int k; input >> k;
          t->canc(k);
        }
      }
      for(int j=0;j<r;j++){
        char tmp; input >> tmp >> tmp >> tmp >> tmp >> tmp;
        if(tmp==':'){
          int k; input >> k;
          t->leftRotate(k);
        }
        else{
          input >> tmp;
          int k; input >> k;
          t->rightRotate(k);
        }
      }
      if(visit == "inorder") t->inorder(output);
      if(visit == "preorder") t->preorder(output);
      if(visit == "postorder") t->postorder(output);
    }
    else{
      BST<double>* t = new BST<double>();
      for(int j=0;j<n;j++){
        char tmp; input >> tmp >> tmp >> tmp >> tmp;
        if(tmp==':'){
          double k; input >> k;
          t->insert(k);
        }
        else{
          input >> tmp;
          double k; input >> k;
          t->canc(k);
        }
      }
      for(int j=0;j<r;j++){
        char tmp; input >> tmp >> tmp >> tmp >> tmp >> tmp;
        if(tmp==':'){
          double k; input >> k;
          t->leftRotate(k);
        }
        else{
          input >> tmp;
          double k; input >> k;
          t->rightRotate(k);
        }
      }
      if(visit == "inorder") t->inorder(output);
      if(visit == "preorder") t->preorder(output);
      if(visit == "postorder") t->postorder(output);
    }
  }
}
