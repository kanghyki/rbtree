#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "Rbnode.hpp"
#include <queue>
#include <stack>

using namespace std;

class Rbtree
{
public:
	Rbtree();
	~Rbtree();
	int		Insert(int value);
	Rbnode	*Search(int value);
	int		Delete(int value);
	int		GetCount();
// *** Test
	queue<int>	TestGetPostOrderResult();
	queue<int>	TestGetInOrderResult();
	int			TestBlackDepth();
	int			TestDoubleRed();
private:
	Rbnode	*insertRecursive(int value, Rbnode *currentNode);
	Rbnode	*searchRecursive(int value, Rbnode * currentNode);
	void	deleteNode(Rbnode *node);
	void	swapNodeValue(Rbnode *dest, Rbnode *src);
// *** Insert 
	void	preRecolor(Rbnode *node);
	void	recolor(Rbnode *node);
	void	restructInside(Rbnode *node);
	void	restructOutside(Rbnode *node);
// *** Rotate
	void	rotateLeft(Rbnode *node);
	void	rotateRight(Rbnode	*node);
// *** Delete
	void	case1(Rbnode *node);
	void	case2(Rbnode *node);
	void	case3(Rbnode *node);
	void	case4(Rbnode *node);
	void	case5(Rbnode *node);
	void	case6(Rbnode *node);
// *** utils
	Rbnode	*getGrandParentNode(Rbnode *node);
	Rbnode	*getUncleNode(Rbnode *node);
	Rbnode	*getSiblingNode(Rbnode *node);
// *** Test
	void	TestInOrder(Rbnode *node, queue<int> &result);
	void	TestPostOrder(Rbnode *node, queue<int> &result);
	void	TestPatrolBlackDepth(Rbnode *, stack<int>, stack<int> *);
	void	TestPatrolDoubleRed(Rbnode *node, int before, int *outResult);
private:
	int		mCount;
	Rbnode	*mRootNode;
	Rbnode	*mNil;
};

#endif
