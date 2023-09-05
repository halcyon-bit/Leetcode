#include "common.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#undef max

class Solution
{
public:
    virtual int lengthOfLongestSubstring(const std::string& s) = 0;
};

class Solution1 : public Solution
{
public:
    int lengthOfLongestSubstring(const std::string& s) override
    {
        size_t size{ s.size() };
        size_t start{ 0 }, res{ 0 };
        for (size_t i = 0; i < size; ++i) {
            size_t j = start;
            for (; j < i; ++j) {
                if (s[i] == s[j]) {
                    start = j + 1;
                    break;
                }
            }

            res = std::max(res, i - start + 1);
        }
        return static_cast<int>(res);
    }
};

class Solution2 : public Solution
{
public:
    int lengthOfLongestSubstring(const std::string& s) override
    {
        size_t size{ s.size() }, start{ 0 };  // 滑动窗口的大小和起始位置
        size_t res{ 0 }, len{ 0 };  // 结果
        std::unordered_map<char, size_t> helper;
        for (size_t i = 0; i < size; ++i) {
            auto iter = helper.find(s[i]);
            if (iter != helper.end() && iter->second >= start) {
                start = iter->second + 1;
                len = i - start;
            }
            helper[s[i]] = i;
            ++len;
            res = std::max(len, res);
        }
        return static_cast<int>(res);
    }
};

int main()
{
    ;
    auto func = [&](const std::string& str, int ans, Solution& s) {
        std::cout << R"(输入：s = ")" << str << R"(")" << std::endl;
        std::cout << "输出：";
        auto res = s.lengthOfLongestSubstring(str);
        std::cout << res;
        std::cout << "\n结果：";
        ans == res ? colorPrint("正确\n\n", 2) : colorPrint("错误\n\n", 4);
    };

    std::string str1{ "abcabcbb" }, str2{ "bbbbb" }, str3{ "pwwkew" }, str4{ "abba" }, str5{ "awefxciuhnkr" };
    int ans1{ 3 }, ans2{ 1 }, ans3{ 3 }, ans4{ 2 }, ans5{ 12 };

    std::cout << "方法一：\n";
    Solution1 s1;
    func(str1, ans1, s1);
    func(str2, ans2, s1);
    func(str3, ans3, s1);
    func(str4, ans4, s1);
    func(str5, ans5, s1);

    std::cout << "\n方法二：\n";
    Solution2 s2;
    func(str1, ans1, s2);
    func(str2, ans2, s2);
    func(str3, ans3, s2);
    func(str4, ans4, s2);
    func(str5, ans5, s2);
	return 0;
}