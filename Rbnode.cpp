#include "Rbnode.hpp"
#include <iostream>

using namespace std;

Rbnode::Rbnode()
{
	mColor = BLACK;
	mValue = 0;
	mParentNode = 0;
	mLeftNode = 0;
	mRightNode = 0;
	mIsNil = 1;
}

Rbnode::Rbnode(int value, Rbnode *nil)
{
	mColor = RED;
	mValue = value; 
	mParentNode = 0;
	mLeftNode = nil;
	mRightNode = nil;
	mIsNil = 0;
}

Rbnode::~Rbnode()
{
}

void	Rbnode::SetValue(int value)
{
	mValue = value;
}

void	Rbnode::SetBlackColor()
{
	if (mIsNil == 0)
	{
		mColor = BLACK;
	}
	else
	{
		cout << "mNil" << endl;
	}
}

void	Rbnode::SetRedColor()
{
	if (mIsNil == 0)
	{
		mColor = RED;
	}
	else
	{
		cout << "mNil" << endl;
	}
}

void	Rbnode::SetParentNode(Rbnode *node)
{
	mParentNode = node;
}

void	Rbnode::SetLeftNode(Rbnode *node)
{
	if (mIsNil == 0)
	{
		mLeftNode = node;
	}
	else
	{
		cout << "mNil" << endl;
	}
}

void	Rbnode::SetRightNode(Rbnode *node)
{
	if (mIsNil == 0)
	{
		mRightNode = node;
	}
	else
	{
		cout << "mNil" << endl;
	}
}

int	Rbnode::GetValue()
{
	return (mValue);
}

int	Rbnode::GetColor()
{
	return (mColor);
}

Rbnode	*Rbnode::GetParentNode()
{
	return (mParentNode);
}

Rbnode	*Rbnode::GetLeftNode()
{
	return (mLeftNode);
}

Rbnode	*Rbnode::GetRightNode()
{
	return (mRightNode);
}

