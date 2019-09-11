#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Nodo{

  private:
    Nodo<H> *left, *right, *parent;
    H* key;
    int color;

  public:
    Nodo<H>(H* key){
      this->key = key;
      left = right = parent = NULL;
    }

    void setLeft(Nodo<H>* left){ this->left = left; }
    void setRight(Nodo<H>* right){ this->right = right; }
    void setParent(Nodo<H>* parent){ this->parent = parent; }
    void setKey(H key){ this->key = new H(key); }
    void setColor(int color){ this->color = color; }
    Nodo<H>* getLeft(){ return left; }
    Nodo<H>* getRight(){ return right; }
    Nodo<H>* getParent(){ return parent; }
    int getColor(){ return color; }
    H getKey(){ return *key; }
};


template <class H> class RBTree{
  private:
    Nodo<H>* root;
    int n;
    static const int BLACK = 0;
		static const int RED = 1;

    Nodo<H>* search(H x){
      Nodo<H>* tmp = root;
      while (tmp && tmp->getKey()!=x){
        if (x<tmp->getKey())
          tmp = tmp->getLeft();
        else
          tmp = tmp->getRight();
      }
      return tmp;
    }

    void RBInsertFixup(Nodo<H> *z) {
			if(z->getParent()!=NULL && z->getParent()->getColor()==BLACK) return;
			if(z == root) {
				z->setColor(BLACK);
				return;
			}
			Nodo<H> *padre = z->getParent();
			Nodo<H> *nonno = padre->getParent();
			Nodo<H> *zio = nonno->getRight();
			if(padre == nonno->getRight()) zio = nonno->getLeft();
			if(zio!=NULL && zio->getColor() == RED) {
				// caso 1
				zio->setColor(BLACK);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				RBInsertFixup(nonno);
				return;
			}
			if(padre == nonno->getLeft()) {
				if(z == padre->getRight()) {
					// caso 3
					this->leftRotate(padre->getKey());
					padre = z;
					z = padre->getLeft();
				}
				// caso 2
				this->rightRotate(nonno->getKey());
				padre->setColor(BLACK);
				nonno->setColor(RED);
				return;
			}
			else { // casi simmetrici ai precedenti
				if(z == padre->getLeft()) {
					// caso 3
					this->rightRotate(padre->getKey());
					padre = z;
					z = padre->getRight();
				}
				// caso 2
				padre->setColor(BLACK);
				nonno->setColor(RED);
				this->leftRotate(nonno->getKey());
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
      root = NULL;
      n=0;
    }

    RBTree<H>* insert(H x){
      Nodo<H>* tmp = root;
      Nodo<H>* p = NULL;
      while (tmp){
        p = tmp;
        if(x<tmp->getKey())
          tmp = tmp->getLeft();
        else
          tmp = tmp->getRight();
      }
      Nodo<H>* newn = new Nodo<H>(new H(x));
      newn->setColor(RED);
      if (!p){
        root = newn;
      }
      else{
        if (x<p->getKey())
          p->setLeft(newn);
        else
          p->setRight(newn);

        newn->setParent(p);
      }
      RBInsertFixup(newn);
      return this;
    }

    RBTree<H>* leftRotate(H key){
      Nodo<H>* y = search(key);
      Nodo<H>* z = y->getParent();
      Nodo<H>* x = y->getRight();
      if (!x) return this;
      y->setRight(x->getLeft());
      x->setLeft(y);
      if(z){
        if(z->getLeft()==y) z->setLeft(x);
        else z->setRight(x);
      }
      else root = x;
      x->setParent(z);
      y->setParent(x);
      if(y->getRight()) y->getRight()->setParent(y);
      return this;
    }

    RBTree<H>* rightRotate(H key){
      Nodo<H>* y = search(key);
      Nodo<H>* z = y->getParent();
      Nodo<H>* x = y->getLeft();
      if (!x) return this;
      y->setLeft(x->getRight());
      x->setRight(y);
      if(z){
        if(z->getRight()==y) z->setRight(x);
        else z->setLeft(x);
      }
      else root = x;
      x->setParent(z);
      y->setParent(x);
      if(y->getLeft()) y->getLeft()->setParent(y);
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
    if (type == "int"){
      RBTree<int>* tree = new RBTree<int>();
      for(int j=0;j<n;j++){
        int tmp;
        input >> tmp;
        tree->insert(tmp);
      }
      cout << tree->altezza() << endl;
      output << tree->altezza() << " ";
    }
    else{
      RBTree<double>* tree = new RBTree<double>();
      for(int j=0;j<n;j++){
        double tmp;
        input >> tmp;
        tree->insert(tmp);
      }
      output << tree->altezza() << " ";
    }
    output << endl;
  }
}
