#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Nodo{

  private:
    Nodo<H> *left, *right, *parent;
    H* key;

  public:
    Nodo<H>(H* key){
      this->key = key;
      left = right = parent = NULL;
    }

    void setLeft(Nodo<H>* left){ this->left = left; }
    void setRight(Nodo<H>* right){ this->right = right; }
    void setParent(Nodo<H>* parent){ this->parent = parent; }
    void setKey(H key){ this->key = new H(key); }
    Nodo<H>* getLeft(){ return left; }
    Nodo<H>* getRight(){ return right; }
    Nodo<H>* getParent(){ return parent; }
    H getKey(){ return *key; }
};


template <class H> class BST{
  private:
    Nodo<H>* root;
    int n;

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

    Nodo<H>* _minimum(Nodo<H>* t){
      if (!t) return NULL;
      while (t->getLeft())
        t = t->getLeft();
      return t;
    }

    Nodo<H>* _successor(Nodo<H>* t){
      if(!t) return NULL;
      if(t->getRight())
        return _minimum(t->getRight());

      Nodo<H>* parent = t->getParent();
      while(parent && parent->getRight()==t){
        t = parent;
        parent = parent->getParent();
      }
      return t;
    }


  public:
    BST<H>(){
      root = NULL;
      n=0;
    }

    BST<H>* insert(H x){
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
      return this;
    }

    BST<H>* canc(H x){
      Nodo<H>* t = search(x);
      if(!t) return NULL;
      Nodo<H>* p = t->getParent();
      // punto all'unico figlio
      if (t->getLeft()==NULL || t->getRight()==NULL){
        Nodo<H>* son = t->getRight();
        if (t->getLeft()) son = t->getLeft();
        if (!p) root = son;
        else{
          if (t==p->getLeft()) p->setLeft(son);
          else p->setRight(son);
        }
        if(son) son->setParent(p);
      }
      else{
        Nodo<H>* succ = _successor(t);
        H tmp = succ->getKey();
        canc(succ->getKey());
        t->setKey(tmp);
      }
      return this;
    }

    BST<H>* leftRotate(H key){
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

    BST<H>* rightRotate(H key){
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

    H minimum(){
      return _minimum(root)->getKey();
    }

    H successor(H x){
      return _successor(search(x))->getKey();
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

  int op1,op2;
  string type;
  string visit;
  for (int i=0;i<100;i++){
    input >> type >> op1 >> op2 >> visit;
    if(type=="int"){
      BST<int>* tree = new BST<int>();
      for (int j=0;j<op1;j++){
        string toparse;
        string operation="";
        string number="";
        input >> toparse;
        int k;
        for (k=0;toparse[k]!=':';k++)
          operation+=toparse[k];
        for (int x=k+1;x<toparse.length();x++)
          number+=toparse[x];
        if(operation=="ins")
          tree->insert(stoi(number));
        else
          tree->canc(stoi(number));
      }
      for (int j=0;j<op2;j++){
        string toparse;
        string rotation="";
        string number="";
        input >> toparse;
        int k;
        for (k=0;toparse[k]!=':';k++)
          rotation+=toparse[k];
        for (int x=k+1;x<toparse.length();x++)
          number+=toparse[x];
        if(rotation=="right") tree->rightRotate(stoi(number));
        else tree->leftRotate(stoi(number));
      }
      if(visit == "inorder") tree->inorder(output);
      if(visit == "preorder") tree->preorder(output);
      if(visit == "postorder") tree->postorder(output);
    }
    else{
      BST<double>* tree = new BST<double>();
      for (int j=0;j<op1;j++){
        string toparse;
        string operation="";
        string number="";
        input >> toparse;
        int k;
        for (k=0;toparse[k]!=':';k++)
          operation+=toparse[k];
        for (int x=k+1;x<toparse.length();x++)
          number+=toparse[x];
        if(operation=="ins")
          tree->insert(stod(number));
        else
          tree->canc(stod(number));
      }
      for (int j=0;j<op2;j++){
        string toparse;
        string rotation="";
        string number="";
        input >> toparse;
        int k;
        for (k=0;toparse[k]!=':';k++)
          rotation+=toparse[k];
        for (int x=k+1;x<toparse.length();x++)
          number+=toparse[x];
        if(rotation=="right") tree->rightRotate(stod(number));
        else tree->leftRotate(stod(number));
      }
      if(visit == "inorder") tree->inorder(output);
      if(visit == "preorder") tree->preorder(output);
      if(visit == "postorder") tree->postorder(output);
    }
  }
}
