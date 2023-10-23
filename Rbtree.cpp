#include "Rbtree.hpp"
#include <iostream>

Rbtree::Rbtree()
{
	Rbnode	*nil = new Rbnode();

	mCount = 0;
	mRootNode = 0;
	mNil = nil;
}

Rbtree::~Rbtree()
{
}

int	Rbtree::GetCount()
{
	return (mCount);
}

int	Rbtree::Insert(int value)
{
	Rbnode	*newNode;

	if (mRootNode == 0)
	{
		newNode = new Rbnode(value, mNil);
		mRootNode = newNode;
	}
	else
	{
		if ((newNode = insertRecursive(value, mRootNode)) == 0)
		{
			return (0);
		}
	}
	preRecolor(newNode);
	mCount++;
	return (1);
}

Rbnode	*Rbtree::insertRecursive(int value, Rbnode *currentNode)
{
	int	currentNodeValue = currentNode->GetValue();

	if (value < currentNodeValue)
	{
		if (currentNode->GetLeftNode() == mNil)
		{
			Rbnode	*newNode = new Rbnode(value, mNil);
			newNode->SetParentNode(currentNode);
			currentNode->SetLeftNode(newNode);
			return (newNode);
		}
		return (insertRecursive(value, currentNode->GetLeftNode()));
	}
	else if (value > currentNodeValue)
	{
		if (currentNode->GetRightNode() == mNil)
		{
			Rbnode	*newNode = new Rbnode(value, mNil);
			newNode->SetParentNode(currentNode);
			currentNode->SetRightNode(newNode);
			return (newNode);
		}
		return (insertRecursive(value, currentNode->GetRightNode()));
	}
	else
	{
		return (0);
	}
}

Rbnode	*Rbtree::Search(int value)
{
	if (mRootNode == 0)
	{
		return (0);
	}
	return (searchRecursive(value, mRootNode));
}

Rbnode	*Rbtree::searchRecursive(int value, Rbnode *currentNode)
{
	if (currentNode == mNil)
	{
		return (0);
	}

	int	currentNodeValue = currentNode->GetValue();

	if (value == currentNodeValue)
	{
		return (currentNode);
	}
	else if (value < currentNodeValue)
	{
		return (searchRecursive(value, currentNode->GetLeftNode()));
	}
	else
	{
		return (searchRecursive(value, currentNode->GetRightNode()));
	}
}

int	Rbtree::Delete(int value)
{
	Rbnode	*delNode = Search(value);

	if (delNode)
	{
		deleteNode(delNode);
		mCount--;
		return (1);
	}
	return (0);
}

// TODO: Refactor
void	Rbtree::deleteNode(Rbnode *node)
{
	if (node->GetLeftNode() == mNil && node->GetRightNode() == mNil)
	{
		if (node->GetParentNode())
		{
			if (node->GetParentNode()->GetLeftNode() == node)
			{
				node->GetParentNode()->SetLeftNode(mNil);
			}
			else
			{
				node->GetParentNode()->SetLeftNode(mNil);
			}
			mNil->SetParentNode(node->GetParentNode());
			case1(mNil);
		}
		else
		{
			mRootNode = 0;
		}
		delete node;
	}
	else if (node->GetLeftNode() == mNil || node->GetRightNode() == mNil)
	{
		Rbnode	*c;
		node->GetLeftNode() == mNil ? c = node->GetRightNode() : c = node->GetLeftNode();
		if (node->GetParentNode())
		{
			c->SetParentNode(node->GetParentNode());
			if (node->GetParentNode()->GetLeftNode() == node)
			{
				node->GetParentNode()->SetLeftNode(c);
			}
			else
			{
				node->GetParentNode()->SetRightNode(c);
			}
		}
		else
		{
			c->SetParentNode(0);
			c->SetBlackColor();
			mRootNode = c;
		}

		if (node->GetColor() == BLACK)
		{
			if (c->GetColor() == RED)
			{
				c->SetBlackColor();
			}
			else
			{
				case1(c);
			}
		}
		delete node;
	}
	else
	{
		Rbnode	*c;
		c = node->GetLeftNode();
		while (c->GetRightNode() != mNil)
		{
			c = c->GetRightNode();
		}
		if (node->GetLeftNode() == c)
		{
			swapNodeValue(node, c);
			node = c;
			c = c->GetLeftNode();
			c->SetParentNode(node->GetParentNode());
			node->GetParentNode()->SetLeftNode(c);

			if (node->GetColor() == BLACK)
			{
				if (c->GetColor() == RED)
				{
					c->SetBlackColor();
				}
				else
				{
					case1(c);
				}
			}
			delete node;
		}
		else
		{
			swapNodeValue(node, c);
			node = c;
			c = c->GetLeftNode();
			c->SetParentNode(node->GetParentNode());
			node->GetParentNode()->SetRightNode(c);

			if (node->GetColor() == BLACK)
			{
				if (c->GetColor() == RED)
				{
					c->SetBlackColor();
				}
				else
				{
					case1(c);
				}
			}
			delete node;
		}
	}
}

void	Rbtree::swapNodeValue(Rbnode *s1, Rbnode *s2)
{
	const int	tmp = s2->GetValue();

	s2->SetValue(s1->GetValue());
	s1->SetValue(tmp);
}

/* Insert */
void	Rbtree::preRecolor(Rbnode *node)
{
	Rbnode	*rootNode = mRootNode;

	if (rootNode == node)
	{
		node->SetBlackColor();
	}
	else if (node->GetParentNode()->GetColor() == RED)
	{
		recolor(node);
	}
}

void	Rbtree::recolor(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*u = getUncleNode(node);
	Rbnode	*g = getGrandParentNode(node);

	if (u != 0 && u->GetColor() == RED)
	{
		p->SetBlackColor();
		u->SetBlackColor();
		g->SetRedColor();
		preRecolor(g);
	}
	else
	{
		return (restructInside(node));
	}
}

void	Rbtree::restructInside(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*g = getGrandParentNode(node);
/*
 *             [G]
 *            /  \
 *          [P] [nil]
 *         /  \
 *      [nil] [N]
 * */
	if (p->GetRightNode() == node && g->GetLeftNode() == p)
	{
		rotateLeft(p);
		node = node->GetLeftNode(); // p
	}
/*
 *          [G]
 *         /  \
 *      [nil] [P]
 *           /  \
 *         [N] [nil]
 * */
	else if (p->GetLeftNode() == node && g->GetRightNode() == p)
	{
		rotateRight(p);
		node = node->GetRightNode(); // p
	}
	restructOutside(node);
}

void	Rbtree::restructOutside(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*g = getGrandParentNode(node);

/*
 *            [G]
 *             |
 *            [P]
 *           /  \
 *         [N] [nil]
 * */
    if (node == p->GetLeftNode())
	{
        rotateRight(g);
	}
/*
 *            [G]
 *             |
 *            [P]
 *           /  \
 *        [nil] [N]
 * */
    else
	{
        rotateLeft(g);
	}
	p->SetBlackColor();
	g->SetRedColor();
}

// Rotate
void	Rbtree::rotateLeft(Rbnode *node)
{
	Rbnode	*c = node->GetRightNode();
	Rbnode	*p = node->GetParentNode();

	if (c->GetLeftNode() != mNil)
	{
		c->GetLeftNode()->SetParentNode(node);
	}
	node->SetRightNode(c->GetLeftNode());
	node->SetParentNode(c);
	c->SetLeftNode(node);
	c->SetParentNode(p);
	if (p != 0)
	{
		if (p->GetLeftNode() == node)
		{
			p->SetLeftNode(c);
		}
		else
		{
			p->SetRightNode(c);
		}
	}
	else // new Root Node
	{
		mRootNode = c;
	}
}

void	Rbtree::rotateRight(Rbnode *node)
{
	Rbnode	*c = node->GetLeftNode();
	Rbnode	*p = node->GetParentNode();

	if (c->GetRightNode() != mNil)
	{
		c->GetRightNode()->SetParentNode(node);
	}
	node->SetLeftNode(c->GetRightNode());
	node->SetParentNode(c);
	c->SetRightNode(node);
	c->SetParentNode(p);
	if (p != 0)
	{
		if (p->GetRightNode() == node)
		{
			p->SetRightNode(c);
		}
		else
		{
			p->SetLeftNode(c);
		}
	}
	else // new Root Node
	{
		mRootNode = c;
	}
}

/*
 * Case 1
 * node = mRootNode
 */
void	Rbtree::case1(Rbnode *node)
{
	if (node->GetParentNode() != 0) 
	{
		case2(node);
	}
}

/*
 * Case 2
 * S = RED
 */
void	Rbtree::case2(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*s = getSiblingNode(node);

	if (s->GetColor() == RED)
	{
		p->SetRedColor();
		s->SetBlackColor();
		if (node == p->GetLeftNode())
		{
			rotateLeft(p);
		}
		else
		{
			rotateRight(p);
		}
	} 
	case3(node);
}

/*
 * Case 3
 * P, S, S(L), S(R) = BLACK
 */
void	Rbtree::case3(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*s = getSiblingNode(node);

	if (p->GetColor() == BLACK &&
		s->GetColor() == BLACK &&
		s->GetLeftNode()->GetColor() == BLACK &&
		s->GetRightNode()->GetColor() == BLACK)
	{
		s->SetRedColor();
		case1(p);
	}
	else
	{
		case4(node);
	}
}

/*
 * Case 4
 * P = RED
 * S, S(L), S(R) = BLACK
 */
void	Rbtree::case4(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*s = getSiblingNode(node);

	if (p->GetColor() == RED &&
		s->GetColor() == BLACK &&
		s->GetLeftNode()->GetColor() == BLACK &&
		s->GetRightNode()->GetColor() == BLACK)
	{
		s->SetRedColor();
		p->SetBlackColor();
	}
	else
	{
		case5(node);
	}
}

/*
 * Case 5
 * S, S(One Child) = BLACK
 * S(other child) = RED
 */
void	Rbtree::case5(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*s = getSiblingNode(node);

	if (s->GetColor() == BLACK)
	{
		if (node == p->GetLeftNode() &&
			s->GetRightNode()->GetColor() == BLACK &&
			s->GetLeftNode()->GetColor() == RED)
		{
			s->SetRedColor();
			s->GetLeftNode()->SetBlackColor();
			rotateRight(s);
		}
		else if (node == p->GetRightNode() &&
				s->GetRightNode()->GetColor() == RED &&
				s->GetLeftNode()->GetColor() == BLACK)
		{
			s->SetRedColor();
			s->GetRightNode()->SetBlackColor();
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
void	Rbtree::case6(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();
	Rbnode	*s = getSiblingNode(node);

	if (p->GetColor() == RED)
	{
		s->SetRedColor();
	}
	else
	{
		s->SetBlackColor();
	}
	p->SetBlackColor();

	if (node == p->GetLeftNode())
	{
		s->GetRightNode()->SetBlackColor();
		rotateLeft(p);
	}
	else
	{
		s->GetLeftNode()->SetBlackColor();
		rotateRight(p);
	}
}

// Use only when the parent node is clearly present.
Rbnode	*Rbtree::getGrandParentNode(Rbnode *node)
{
	return (node->GetParentNode()->GetParentNode());
}

/*
 * Use only when the parent node is clearly present.
 * Return Uncle or mNil.
 */
Rbnode	*Rbtree::getUncleNode(Rbnode *node)
{
	Rbnode	*grandParentNode = getGrandParentNode(node);

	if (node->GetParentNode() == grandParentNode->GetLeftNode())
	{
		return (grandParentNode->GetRightNode());
	}
	return (grandParentNode->GetLeftNode());
}

/*
 * Use only when the parent node is clearly present.
 * Return Sibling or mNil.
 */
Rbnode	*Rbtree::getSiblingNode(Rbnode *node)
{
	Rbnode	*p = node->GetParentNode();

	if (node == p->GetLeftNode())
	{
		return (p->GetRightNode());
	}
	return (p->GetLeftNode());
}

/*
 * Test
 */
queue<int>	Rbtree::TestGetInOrderResult()
{
	queue<int>	result;

	if(mRootNode)
	{
		TestInOrder(mRootNode, result);
	}
	return (result);
}

void	Rbtree::TestInOrder(Rbnode *node, queue<int> &result)
{
	if (node == mNil)
	{
		return ;
	}

	if (node->GetLeftNode())
	{
		TestInOrder(node->GetLeftNode(), result);
	}
	result.push(node->GetValue());
	if (node->GetRightNode())
	{
		TestInOrder(node->GetRightNode(), result);
	}
}

queue<int>	Rbtree::TestGetPostOrderResult()
{
	queue<int>	result;

	if (mRootNode)
	{
		TestPostOrder(mRootNode, result);
	}
	return (result);
}

void	Rbtree::TestPostOrder(Rbnode *node, queue<int> &result)
{
	if (node == mNil)
	{
		return ;
	}

	if (node->GetLeftNode())
	{
		TestPostOrder(node->GetLeftNode(), result);
	}

	if (node->GetRightNode())
	{
		TestPostOrder(node->GetRightNode(), result);
	}
	result.push(node->GetValue());
}

int	Rbtree::TestBlackDepth(void)
{
	int			before, now;
	stack<int>	patrol, result;

	cout << "[BLACK DEPTH] ";
	if (mRootNode)
	{
		TestPatrolBlackDepth(mRootNode, patrol, &result);
	}
	else
	{
		return (1);
	}
	before = result.top();
	result.pop();
	while (result.size() > 0)
	{
		now = result.top();
		if (before != now)
		{
			return (0);
		}
		before = now;
		result.pop();
	}
	return (1);
}

void	Rbtree::TestPatrolBlackDepth(Rbnode *node, stack<int> patrol, stack<int> *result)
{
	if (node == 0)
	{
//		cout << patrol.size() << "/";
		result->push(patrol.size());
		return ;
	}

	if (node->GetColor() == BLACK)
	{
		patrol.push(1);
	}
	TestPatrolBlackDepth(node->GetLeftNode(), patrol, result);
	TestPatrolBlackDepth(node->GetRightNode(), patrol, result);
}

int	Rbtree::TestDoubleRed(void)
{
	int	outResult = 1;
	cout << "[DOUBLE RED] ";
	if (mRootNode)
	{
		TestPatrolDoubleRed(mRootNode, mRootNode->GetColor(), &outResult);
	}
	else
	{
		return (1);
	}

	if (outResult == 0)
	{
		return (0);
	}
	return (1);
}

void	Rbtree::TestPatrolDoubleRed(Rbnode *node, int before, int *outResult)
{
	if (node == 0)
	{
		return ;
	}

	if (before == RED && node->GetColor() == RED)
	{
		outResult = 0;
	}
	TestPatrolDoubleRed(node->GetLeftNode(), node->GetColor(), outResult);
	TestPatrolDoubleRed(node->GetRightNode(), node->GetColor(), outResult);
}
