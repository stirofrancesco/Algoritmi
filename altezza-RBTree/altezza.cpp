#include <iostream>
#include <fstream>

using namespace std;

#define RED 0
#define BLACK 1

template <class H> class Nodo{

  private:
    Nodo<H> *parent, *left, *right;
    H* key;
    int color;

  public:
    Nodo<H>(H key){
      this->key = new H(key);
      left = right = parent = NULL;
    }

    Nodo<H>* getParent(){ return parent; }
    Nodo<H>* getLeft(){ return left; }
    Nodo<H>* getRight(){ return right; }
    H getKey(){ return *key; }
    int getColor(){ return color; }
    void setParent(Nodo<H>* parent){ this->parent = parent; }
    void setLeft(Nodo<H>* left){ this->left = left; }
    void setRight(Nodo<H>* right){ this->right = right; }
    void setKey(H key){ this->key = new H(key); }
    void setColor(int color){ this->color = color; }
};

template <class H> class RBTree{

  private:
    Nodo<H>* root;

    void leftRotate(Nodo<H>* y){
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
      x->setParent(p);
      y->setParent(x);
      if(y->getRight()) y->getRight()->setParent(y);
    }

    void rightRotate(Nodo<H>* y){
      Nodo<H>* p = y->getParent();
      Nodo<H>* x = y->getLeft();
      if(!x) return;
      y->setLeft(x->getRight());
      x->setRight(y);
      if(p){
        if(y==p->getRight()) p->setRight(x);
        else p->setLeft(x);
      }
      else root = x;
      x->setParent(p);
      y->setParent(x);
      if(y->getLeft()) y->getLeft()->setParent(y);
    }

    void RBInsertFixup(Nodo<H>* y){
      if(y->getParent() && y->getParent()->getColor()==BLACK) return;
      if(y==root){
        y->setColor(BLACK);
        return;
      }
      Nodo<H>* padre = y->getParent();
      Nodo<H>* nonno = padre->getParent();
      Nodo<H>* zio = nonno->getLeft();
      if(padre == nonno->getLeft()) zio = nonno->getRight();
      // CASO 1
      if(zio && zio->getColor()==RED){
        padre->setColor(BLACK);
        zio->setColor(BLACK);
        nonno->setColor(RED);
        RBInsertFixup(nonno);
        return;
      }
      // CASO 2
      if(padre == nonno->getLeft()){
        if(y==padre->getRight()){
          leftRotate(padre);
          padre = y;
          y = padre->getLeft();
        }
        rightRotate(nonno);
        padre->setColor(BLACK);
        nonno->setColor(RED);
        return;
      }
      else{
        if(y==padre->getLeft()){
          rightRotate(padre);
          padre = y;
          y = padre->getRight();
        }
        leftRotate(nonno);
        padre->setColor(BLACK);
        nonno->setColor(RED);
        return;
    }
  }

  int _altezza(Nodo<H>* t){
    if(!t) return 0;
    int h1 = _altezza(t->getLeft());
    int h2 = _altezza(t->getRight());
    return (h1>h2?h1:h2)+1;
  }

  public:
    RBTree<H>(){
      root  = NULL;
    }

    RBTree<H>* insert(H x){
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
      newn->setColor(RED);
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
      RBInsertFixup(newn);
      return this;
    }

    int altezza(){
      return _altezza(root);
    }

};

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string type;
  int n;

  for(int i=0;i<100;i++){
    input >> type >> n;
    if(type=="int"){
      RBTree<int>* t = new RBTree<int>();
      for(int j=0;j<n;j++){
        int k; input >> k;
        t->insert(k);
      }
      output << t->altezza() << endl;
    }
    if(type=="double"){
      RBTree<double>* t = new RBTree<double>();
      for(int j=0;j<n;j++){
        double k; input >> k;
        t->insert(k);
      }
      output << t->altezza() << endl;
    }
  }
}
