#include "Rbtree.hpp"
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

size_t	times = 0;
size_t	passed = 0;

void	printBool(int result)
{
	if (result)
	{
		cout << "PASS ✅" << endl;
		passed++;
	}
	else
	{
		cout << "FAIL 🔥" << endl;
	}
	times++;
}

int	compareResult(queue<int> &expected, queue<int> result)
{
	int	rst = 1;
	int	printFlag = 0;
	queue<int> expected_tmp;
	queue<int> result_tmp;

	if (expected.size() != result.size())
	{
		cout << "! Size Error !" << setw(10) << endl;
		cout << "Expected" << setw(10) << "Result" << setw(10) << endl;
		cout << expected.size() << setw(10) << result.size() << setw(10) <<  endl;
		while (expected.size() > 0 && result.size() > 0)
		{
			cout << expected.front() << setw(10) << result.front() << setw(10) <<  endl;
			expected.pop();
			result.pop();
		}
		while (result.size() > 0)
		{
			cout << "-" << setw(10) << result.front() << setw(10) <<  endl;
			result.pop();
		}
		while (expected.size() > 0)
		{ 
			cout << expected.front() << setw(10) << "-" << setw(10) <<  endl;
			expected.pop();
		}
		rst = 0;
	}
	else
	{
		while (expected.size() > 0)
		{
			if (expected.front() != result.front())
			{
				rst = 0;
				printFlag = 1;
			}
			expected_tmp.push(expected.front());
			result_tmp.push(result.front());
			expected.pop();
			result.pop();
		}
		if (printFlag)
		{
			cout << "Expected" << setw(10) << "Result" << setw(10) << endl;
			while (expected_tmp.size() > 0)
			{
				cout << expected_tmp.front() << setw(10) << result_tmp.front() << setw(10) <<  endl;
				expected_tmp.pop();
				result_tmp.pop();
			}
		}
	}
	return (rst);
}

void	testInsertInOrder()
{
	Rbtree 		rb;
	queue<int>	expected;

	cout << "----------------------" << endl;
	cout << "Insert Test (In Order)" << endl;
	rb.Insert(100);
	expected.push(100);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(150);
	expected.push(100);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(200);
	expected.push(100);
	expected.push(150);
	expected.push(200);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(300);
	expected.push(100);
	expected.push(150);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(175);
	expected.push(100);
	expected.push(150);
	expected.push(175);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(180);
	expected.push(100);
	expected.push(150);
	expected.push(175);
	expected.push(180);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(190);
	expected.push(100);
	expected.push(150);
	expected.push(175);
	expected.push(180);
	expected.push(190);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Insert(160);
	expected.push(100);
	expected.push(150);
	expected.push(160);
	expected.push(175);
	expected.push(180);
	expected.push(190);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	printBool(rb.Insert(100) == 0);
	printBool(rb.Insert(150) == 0);
}

void	testDeleteInOrder()
{
	Rbtree 		rb;
	queue<int>	expected;

	cout << "----------------------" << endl;
	cout << "Delete Test (In Order)" << endl;
	printBool(rb.Delete(1000) == 0);

	rb.Insert(100);
	rb.Insert(150);
	rb.Insert(200);
	rb.Insert(300);
	rb.Insert(175);
	rb.Insert(180);
	rb.Insert(190);
	rb.Insert(160);

	expected.push(100);
	expected.push(150);
	expected.push(160);
	expected.push(175);
	expected.push(180);
	expected.push(190);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(190);
	expected.push(100);
	expected.push(150);
	expected.push(160);
	expected.push(175);
	expected.push(180);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(175);
	expected.push(100);
	expected.push(150);
	expected.push(160);
	expected.push(180);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(180);
	expected.push(100);
	expected.push(150);
	expected.push(160);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(160);
	expected.push(100);
	expected.push(150);
	expected.push(200);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(200);
	expected.push(100);
	expected.push(150);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(100);
	expected.push(150);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(150);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));

	rb.Delete(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetInOrderResult()));
}

void	testInsertPostOrder()
{
	Rbtree 		rb;
	queue<int>	expected;

	cout << "----------------------" << endl;
	cout << "Insert Test (Post Order)" << endl;
	rb.Insert(100);
	expected.push(100);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(150);
	expected.push(150);
	expected.push(100);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(200);
	expected.push(100);
	expected.push(200);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(300);
	expected.push(100);
	expected.push(300);
	expected.push(200);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(175);
	expected.push(100);
	expected.push(175);
	expected.push(300);
	expected.push(200);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(180);
	expected.push(100);
	expected.push(180);
	expected.push(175);
	expected.push(300);
	expected.push(200);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(190);
	expected.push(100);
	expected.push(175);
	expected.push(190);
	expected.push(180);
	expected.push(300);
	expected.push(200);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Insert(160);
	expected.push(100);
	expected.push(160);
	expected.push(175);
	expected.push(150);
	expected.push(190);
	expected.push(300);
	expected.push(200);
	expected.push(180);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	printBool(rb.Insert(100) == 0);
	printBool(rb.Insert(150) == 0);
}

void	testDeletePostOrder()
{
	Rbtree 		rb;
	queue<int>	expected;

	cout << "----------------------" << endl;
	cout << "Delete Test (Post Order)" << endl;
	printBool(rb.Delete(1000) == 0);

	rb.Insert(100);
	rb.Insert(150);
	rb.Insert(200);
	rb.Insert(300);
	rb.Insert(175);
	rb.Insert(180);
	rb.Insert(190);
	rb.Insert(160);

	expected.push(100);
	expected.push(160);
	expected.push(175);
	expected.push(150);
	expected.push(190);
	expected.push(300);
	expected.push(200);
	expected.push(180);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(190);
	expected.push(100);
	expected.push(160);
	expected.push(175);
	expected.push(150);
	expected.push(300);
	expected.push(200);
	expected.push(180);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(175);
	expected.push(100);
	expected.push(160);
	expected.push(150);
	expected.push(300);
	expected.push(200);
	expected.push(180);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(180);
	expected.push(100);
	expected.push(150);
	expected.push(300);
	expected.push(200);
	expected.push(160);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(160);
	expected.push(100);
	expected.push(300);
	expected.push(200);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(200);
	expected.push(100);
	expected.push(300);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(100);
	expected.push(300);
	expected.push(150);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(150);
	expected.push(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));

	rb.Delete(300);
	printBool(rb.TestBlackDepth());
	printBool(rb.TestDoubleRed());
	printBool(compareResult(expected, rb.TestGetPostOrderResult()));
}

void	test(void)
{
	Rbtree	rb;
	int		flag = 1;

	for (int i = 0; i < 1000; i += 2)
	{
		rb.Insert(i);
		printBool(rb.TestBlackDepth());
		printBool(rb.TestDoubleRed());
		if (flag == 1)
		{
			rb.Insert(999 - i);
			printBool(rb.TestBlackDepth());
			printBool(rb.TestDoubleRed());
			flag = 0;
		}
		else
			flag = 1;
	}
}

int	main(void)
{
	testInsertPostOrder();
	testInsertInOrder();
	testDeletePostOrder();
	testDeleteInOrder();
	test();
	cout << "PASS " << passed << " ✅" << endl;
	cout << "FAIL " << times - passed << " 🔥" << endl;
	return (0);
}
