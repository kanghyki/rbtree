#ifndef RB_HPP
#define RB_HPP

#ifndef NULL
#define NULL (0)
#endif

#ifndef BLACK
#define BLACK (0)
#endif

#ifndef RED
#define RED (1)
#endif

template <typename T>
struct RBnode {
  public:
    RBnode() {
      color = BLACK;
      parent = NULL;
      left = NULL;
      right = NULL;
    }
    ~RBnode() {}

    char  color;
    // TODO: reference, pointer, value...
    T     value;

    RBnode<T>* left;
    RBnode<T>* right;
    RBnode<T>* parent;

  protected:

  private:
    RBnode(const RBnode& obj);
    RBnode& operator=(const RBnode& obj);
};


template <typename T>
class RBtree {
  private:
    RBtree(const RBtree& obj);
    RBtree& operator=(const RBtree& obj);

    RBnode<T>* root;
    RBnode<T>* nil;
    unsigned long size;

  public:
    RBtree() {
      RBnode<T>* nil = new RBnode<T>;
      this->size = 0;
      this->root = 0;
      this->nil = nil;
    }

    ~RBtree() {
      removeAll(this->root);
      delete this->nil;
    }

    void removeAll(RBnode<T>* node) {
      if (!node || node == this->nil) return;
      removeAll(node->left);
      removeAll(node->right);
      delete node;
    }

    void insert(T value) {
      RBnode<T>* node = new RBnode<T>;
      node->value = value;
      node->right = nil;
      node->left = nil;

      if (root == NULL) root = node;
      insertRecursive(node, root);
      preRecolor(node);
      ++size;
    }

    RBnode<T>* search(T value) {
      if (root == NULL) return NULL;

      return searchRecursive(value, root);
    }

    bool remove(T value) {
      RBnode<T>* node = search(value);

      if (!node) return false;
      deleteNode(node);
      --size;

      return true;
    }

  protected:

  private:
    /*
     * +---------------+
     * | INSERT        |
     * +---------------+
     */
    void insertRecursive(RBnode<T>* node, RBnode<T>* cur) {
      if (node->value < cur->value) {
        if (cur->left == nil) {
          node->parent = cur;
          cur->left = node;
          return ;
        }
        return insertRecursive(node, cur->left);
      }
      else if (node->value > cur->value) {
        if (cur->right == nil) {
          node->parent = cur;
          cur->right = node;
          return ;
        }
        return insertRecursive(node, cur->right);
      }
      node->parent = cur->parent;
      node->color = cur->color;
      node->left = cur->left;
      node->right = cur->right;
    }

    /*
     * +---------------+
     * | SEARCH        |
     * +---------------+
     */
    RBnode<T>* searchRecursive(T value, RBnode<T>* currentNode) {
      if (currentNode == nil) return NULL;

      T currentNodeValue = currentNode->value;

      if (value == currentNodeValue)
        return currentNode;
      else if (value < currentNodeValue)
        return searchRecursive(value, currentNode->left);

      return searchRecursive(value, currentNode->right);
    }

    /*
     * +---------------+
     * | DELETE        |
     * +---------------+
     */
    void deleteNode(RBnode<T>* node) {
      if (node->left == nil && node->right == nil) {
        if (node->parent) {
          if (node->parent->left == node)
            node->parent->left = nil;
          else
            node->parent->left = nil;
          nil->parent = node->parent;
          case1(nil);
        }
        else root = 0;
        delete node;
      }
      else if (node->left == nil || node->right == nil) {
        RBnode<T>* c;

        if (node->left == nil) c = node->right;
        else c = node->left;

        if (node->parent) {
          c->parent = node->parent;
          if (node->parent->left == node) node->parent->left = c;
          else node->parent->right = c;
        }
        else {
          c->parent = NULL;
          c->color = BLACK;
          root = c;
        }

        if (node->color == BLACK) {
          if (c->color == RED) c->color = BLACK;
          else case1(c);
        }
        delete node;
      }
      else {
        RBnode<T>* c;
        c = node->left;
        while (c->right != nil)
          c = c->right;
        if (node->left == c) {
          swapNodeValue(node, c);
          node = c;
          c = c->left;
          c->parent = node->parent;
          node->parent->left = c;
          if (node->color == BLACK) {
            if (c->color == RED) c->color = BLACK;
            else case1(c);
          }
          delete node;
        }
        else {
          swapNodeValue(node, c);
          node = c;
          c = c->left;
          c->parent = node->parent;
          node->parent->right = c;

          if (node->color == BLACK) {
            if (c->color == RED) c->color = BLACK;
            else case1(c);
          }
          delete node;
        }
      }
    }

    /*
     * +---------------+
     * | RECOLORING    |
     * +---------------+
     */
    void preRecolor(RBnode<T>* node) {
      RBnode<T>* rootNode = root;

      if (rootNode == node) node->color = BLACK;
      else if (node->parent->color == RED) recolor(node);
    }
    void recolor(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* u = getUncleNode(node);
      RBnode<T>* g = getGrandParentNode(node);

      if (u != 0 && u->color == RED) {
        p->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        preRecolor(g);
      }

      return restructInside(node);
    }

    /*
     * +---------------+
     * | RESTRUCTURING |
     * +---------------+
     */
    void restructInside(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* g = getGrandParentNode(node);
      /*
       *             [G]
       *            /  \
       *          [P] [nil]
       *         /  \
       *      [nil] [N]
       * */
      if (p->right == node && g->left == p) {
        rotateLeft(p);
        node = node->left;
      }
      /*
       *          [G]
       *         /  \
       *      [nil] [P]
       *           /  \
       *         [N] [nil]
       * */
      else if (p->left == node && g->right == p) {
        rotateRight(p);
        node = node->right;
      }
      restructOutside(node);
    }

    void restructOutside(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* g = getGrandParentNode(node);

      /*
       *            [G]
       *             |
       *            [P]
       *           /  \
       *         [N] [nil]
       * */
      if (node == p->left)
        rotateRight(g);
      /*
       *            [G]
       *             |
       *            [P]
       *           /  \
       *        [nil] [N]
       * */
      else
        rotateLeft(g);
      p->color = BLACK;
      g->color = RED;
    }

    /*
     * +---------------+
     * | ROTATE        |
     * +---------------+
     */
    void rotateLeft(RBnode<T>* node) {
      RBnode<T>* c = node->right;
      RBnode<T>* p = node->parent;

      if (c->left != nil) c->left->parent = node;
      node->right = c->left;
      node->parent = c;
      c->left = node;
      c->parent = p;
      if (p != 0) {
        if (p->left == node) p->left = c;
        else p->right = c;
      }
      else root = c;
    }
    void rotateRight(RBnode<T>* node) {
      RBnode<T>* c = node->left;
      RBnode<T>* p = node->parent;

      if (c->right != nil) c->right->parent = node;
      node->left = c->right;
      node->parent = c;
      c->right = node;
      c->parent = p;
      if (p != 0) {
        if (p->right == node) p->right = c;
        else p->left = c;
      }
      else root = c;
    }
    /*
     * +---------------+
     * | DELETE        |
     * +---------------+
     */
    /*
     * Case 1
     * node = mRootNode
     */
    void case1(RBnode<T>* node) {
      if (node->parent == NULL) return;
      case2(node);
    }
    /*
     * Case 2
     * S = RED
     */
    void case2(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* s = getSiblingNode(node);

      if (s->color == RED) {
        p->color = RED;
        s->color = BLACK;
        if (node == p->left) rotateLeft(p);
        else rotateRight(p);
      }
      case3(node);
    }
    /*
     * Case 3
     * P, S, S(L), S(R) = BLACK
     */
    void case3(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* s = getSiblingNode(node);

      if (p->color == BLACK
          && s->color == BLACK
          && s->left->color == BLACK
          && s->right->color == BLACK) {
        s->color = RED;
        case1(p);
      }
      else case4(node);
    }
    /*
     * Case 4
     * P = RED
     * S, S(L), S(R) = BLACK
     */
    void case4(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* s = getSiblingNode(node);

      if (p->color == RED
          && s->color == BLACK
          && s->left->color == BLACK
          && s->right->color == BLACK) {
        s->color = RED;
        p->color = BLACK;
      }
      else case5(node);
    }
    /*
     * Case 5
     * S, S(One Child) = BLACK
     * S(other child) = RED
     */
    void case5(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* s = getSiblingNode(node);

      if (s->color == BLACK) {
        if (node == p->left
            && s->right->color == BLACK
            && s->left->color == RED) {
          s->color = RED;
          s->left->color = BLACK;
          rotateRight(s);
        }
        else if (node == p->right
            && s->right->color == RED
            && s->left->color == BLACK) {
          s->color = RED;
          s->right->color = BLACK;
          rotateLeft(s);
        }
      }
      case6(node);
    }
    /*
     * Case 6
     * S = BLACK
     * S(R) = RED
     */
    void case6(RBnode<T>* node) {
      RBnode<T>* p = node->parent;
      RBnode<T>* s = getSiblingNode(node);

      if (p->color == RED) s->color = RED;
      else s->color = BLACK;
      p->color = BLACK;

      if (node == p->left) {
        s->right->color = BLACK;
        rotateLeft(p);
      }
      else {
        s->left->color = BLACK;
        rotateRight(p);
      }
    }
    /*
     * +---------------+
     * | UTIL          |
     * +---------------+
     */
    /*
     * Use only when the parent node is clearly present.
     */
    RBnode<T>* getGrandParentNode(RBnode<T>* node) {
      return node->parent->parent;
    }
    /*
     * Use only when the parent node is clearly present.
     * Return Uncle or nil.
     */
    RBnode<T>* getUncleNode(RBnode<T>* node) {
      RBnode<T>* grandParentNode = getGrandParentNode(node);

      if (node->parent == grandParentNode->left) return grandParentNode->right;

      return grandParentNode->left;
    }
    /*
     * Use only when the parent node is clearly present.
     * Return Sibling or nil.
     */
    RBnode<T>* getSiblingNode(RBnode<T>* node) {
      RBnode<T>* p = node->parent;

      if (node == p->left) return p->right;
      return p->left;
    }
    void swapNodeValue(RBnode<T>* dest, RBnode<T>* src) {
      const T tmp = src->value;

      src->value = dest->value;
      dest->value = tmp;
    }
};


#endif
