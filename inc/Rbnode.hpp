#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <iostream>

#define RED (0)
#define BLACK (1)

class Rbnode {
  private:
    Rbnode(const Rbnode& obj);
    Rbnode& operator=(const Rbnode& obj);

    Rbnode* mLeftNode;
    Rbnode* mRightNode;
    Rbnode* mParentNode;
    char mColor;
    int mValue;
    char mIsNil;

  protected:

  public:
    Rbnode();
    Rbnode(int value, Rbnode *nil);
    ~Rbnode();

    void SetValue(int value);
    void SetBlackColor();
    void SetRedColor();
    void SetParentNode(Rbnode *node);
    void SetLeftNode(Rbnode *node);
    void SetRightNode(Rbnode *node);

    int GetValue();
    int GetColor();
    Rbnode* GetParentNode();
    Rbnode* GetLeftNode();
    Rbnode* GetRightNode();
};

#endif
