#include "common.h"

#include <vector>
#include <iostream>
#include <unordered_map>

class Solution
{
public:
	virtual std::vector<int> twoSum(std::vector<int>& nums, int target) = 0;
};

// 方法一
class Solution1 : public Solution
{
public:
	std::vector<int> twoSum(std::vector<int>& nums, int target) override
	{
		size_t size = nums.size();
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = i + 1; j < size; ++j) {
				if (nums[i] + nums[j] == target) {
					return { static_cast<int>(i), static_cast<int>(j) };
				}
			}
		}
		return {};
	}
};

// 方法二
class Solution2 : public Solution
{
public:
	std::vector<int> twoSum(std::vector<int>& nums, int target) override
	{
		std::unordered_map<int, size_t> helper;
		size_t size = nums.size();
		for (size_t i = 0; i < size; ++i) {
			auto iter = helper.find(target - nums[i]);
			if (iter != helper.end()) {
				return { static_cast<int>(iter->second), static_cast<int>(i) };
			}
			else {
				helper.emplace(nums[i], i);
			}
		}
		return {};
	}
};

// 方法三
class Solution3 : public Solution
{
public:
	std::vector<int> twoSum(std::vector<int>& nums, int target) override
	{
		size_t left{ 0 }, right{ nums.size() - 1 };
		while (left != right) {
			int sum = nums[left] + nums[right];
			if (sum == target) {
				return { static_cast<int>(left), static_cast<int>(right) };
			}
			else if (sum < target) {
				++left;
			}
			else {
				--right;
			}
		}
		return {};
	}
};

template<typename T>
void printVector(const std::vector<T>& vec)
{
	std::cout << "[";
	size_t size = vec.size();
	for (size_t i = 0; i < size - 1; ++i) {
		std::cout << vec[i] << ", ";
	}
	std::cout << vec[size - 1] << "]";
}

int main()
{
	auto func = [&](std::vector<int>& nums, int target, std::vector<int>& ans, Solution& f) {
		std::cout << "输入：nums = ";
		printVector(nums);
		std::cout << ", target = " << target << "\n输出：";
		auto res = f.twoSum(nums, target);
		printVector(res);
		std::cout << "\n结果：";
		std::equal(ans.begin(), ans.end(), res.begin(), res.end()) ? colorPrint("正确\n\n", 2) : colorPrint("错误\n\n", 4);;
	};

	std::vector<int> nums1{ 2, 7, 11, 15 }, ans1{ 0, 1 };
	int target1{ 9 };
	std::vector<int> nums2{ 3, 2, 4 }, ans2{ 1,2 };
	int target2{ 6 };
	std::vector<int> nums3{ 3, 3 }, ans3{ 0, 1 };
	int target3{ 6 };

	std::cout << "方法一：\n";
	Solution1 s1;
	func(nums1, target1, ans1, s1);
	func(nums2, target2, ans2, s1);
	func(nums3, target3, ans3, s1);

	std::cout << std::endl;
	std::cout << "方法二：\n";
	Solution2 s2;
	func(nums1, target1, ans1, s2);
	func(nums2, target2, ans2, s2);
	func(nums3, target3, ans3, s2);

	std::cout << std::endl;
	std::cout << "方法三：\n";
	Solution3 s3;
	func(nums1, target1, ans1, s3);
	return 0;
}