#ifndef RBNODE_HPP
#define RBNODE_HPP

#define RED (0)
#define BLACK (1)

class Rbnode
{
public:
	Rbnode();
	Rbnode(int value, Rbnode *nil);
	~Rbnode();

	void	SetValue(int value);
	void	SetBlackColor();
	void	SetRedColor();
	void	SetParentNode(Rbnode *node);
	void	SetLeftNode(Rbnode *node);
	void	SetRightNode(Rbnode *node);

	int		GetValue();
	int		GetColor();
	Rbnode	*GetParentNode();
	Rbnode	*GetLeftNode();
	Rbnode	*GetRightNode();
private:
	Rbnode	*mLeftNode;
	Rbnode	*mRightNode;
	Rbnode	*mParentNode;
	char	mColor;
	int		mValue;
	char	mIsNil;
};

#endif
