#include "common.h"

#include <vector>
#include <iostream>

struct ListNode
{
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* head{ new ListNode(-1) };
		ListNode* node{ head };

		int carry{ 0 };  // 进位标志
		while (l1 != nullptr || l2 != nullptr) {
			int sum{ 0 };
			if (l1 != nullptr) {
				sum += l1->val;
				l1 = l1->next;
			}
			if (l2 != nullptr) {
				sum += l2->val;
				l2 = l2->next;
			}
			sum += carry;
			node->next = new ListNode(sum % 10);
			carry = sum / 10;
			node = node->next;
		}
		// 进位
		if (carry == 1) {
			node->next = new ListNode(1);
		}
		node = head->next;
		delete head;
		return node;
	}
};

ListNode* createList(const std::vector<int>& nums)
{
	size_t size{ nums.size() };
	if (size == 0) {
		return nullptr;
	}

	ListNode* head{ new ListNode(-1) };
	ListNode* node{ head };
	for (auto each : nums) {
		node->next = new ListNode(each);
		node = node->next;
	}

	node = head->next;
	delete head;
	return node;
}

void deleteList(ListNode* head)
{
	ListNode* node{ nullptr };
	while (head != nullptr) {
		node = head->next;
		delete head;
		head = node;
	}
}

void printList(ListNode* head)
{
	std::cout << "[";
	if (head == nullptr) {
		std::cout << "]";
	}
	else {
		while (head->next != nullptr) {
			std::cout << head->val << ", ";
			head = head->next;
		}

		std::cout << head->val << "]";
	}
}

bool checkList(ListNode* l1, ListNode* l2)
{
	while (l1 != nullptr && l2 != nullptr) {
		if (l1->val == l2->val) {
			l1 = l1->next;
			l2 = l2->next;
		}
		else {
			return false;
		}
	}
	return !(l1 != nullptr || l2 != nullptr);
}

int main()
{
	auto func = [&](ListNode* l1, ListNode* l2, ListNode* ans, Solution& s) {
		std::cout << "输入：l1 = ";
		printList(l1);
		std::cout << ", l2 = ";
		printList(l2);
		std::cout << "\n输出：";
		auto res = s.addTwoNumbers(l1, l2);
		printList(res);
		std::cout << "\n结果：";
		checkList(ans, res) ? colorPrint("正确\n\n", 2) : colorPrint("错误\n\n", 4);
		deleteList(l1);
		deleteList(l2);
		deleteList(ans);
		deleteList(res);
	};

	std::vector<int> nums11{ 2,4,3 }, nums21{ 5,6,4 }, ans1{ 7,0,8 };
	std::vector<int> nums12{ 0 }, nums22{ 0 }, ans2{ 0 };
	std::vector<int> nums13{ 9,9,9,9,9,9,9 }, nums23{ 9,9,9,9 }, ans3{ 8,9,9,9,0,0,0,1 };

	Solution s;

	auto l1{ createList(nums11) };
	auto l2{ createList(nums21) };
	auto ans{ createList(ans1) };
	func(l1, l2, ans, s);


	l1 = createList(nums12);
	l2 = createList(nums22);
	ans = createList(ans2);
	func(l1, l2, ans, s);

	l1 = createList(nums13);
	l2 = createList(nums23);
	ans = createList(ans3);
	func(l1, l2, ans, s);
	return 0;
}