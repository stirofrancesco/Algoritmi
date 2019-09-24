#include <iostream>
#include <fstream>

using namespace std;

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
    static const int RED = 0;
    static const int BLACK = 1;

    char printC(int color){
      if(color==RED) return 'R';
      return 'B';
    }

    void _inorder(Nodo<H>* t, ofstream& out){
      if(!t) return;
      _inorder(t->getLeft(),out);
      out << "(" << t->getKey() << "," << printC(t->getColor()) << ")" << " ";
      _inorder(t->getRight(),out);
    }

    void _preorder(Nodo<H>* t, ofstream& out){
      if(!t) return;
      out << "(" << t->getKey() << "," << printC(t->getColor()) << ")" << " ";
      _preorder(t->getLeft(),out);
      _preorder(t->getRight(),out);
    }

    void _postorder(Nodo<H>* t, ofstream& out){
      if(!t) return;
      _postorder(t->getLeft(),out);
      _postorder(t->getRight(),out);
      out << "(" << t->getKey() << "," << printC(t->getColor()) << ")" << " ";
    }

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
      }
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

    void inorder(ofstream& out){
      _inorder(root,out);
      out << endl;
    }

    void preorder(ofstream& out){
      _preorder(root,out);
      out << endl;
    }

    void postorder(ofstream & out){
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
  int n;

  for(int i=0;i<100;i++){
    input >> type >> n >> visit;
    if(type=="int"){
      RBTree<int>* t = new RBTree<int>();
      for(int j=0;j<n;j++){
        int k; input >> k;
        t->insert(k);
      }
      if(visit == "inorder") t->inorder(output);
      if(visit == "preorder") t->preorder(output);
      if(visit == "postorder") t->postorder(output);
    }
    if(type=="double"){
      RBTree<double>* t = new RBTree<double>();
      for(int j=0;j<n;j++){
        double k; input >> k;
        t->insert(k);
      }
      if(visit == "inorder") t->inorder(output);
      if(visit == "preorder") t->preorder(output);
      if(visit == "postorder") t->postorder(output);
    }
  }
}
