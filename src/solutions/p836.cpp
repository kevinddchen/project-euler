#include <string>

#include <cassert>

/*

Take the first letter of each bolded word in the problem description:
https://projecteuler.net/problem=836

*/

constexpr std::string_view ANSWER = "aprilfoolsjoke";

std::string p836()
{
    return "aprilfoolsjoke";
}

int main()
{
    const std::string ans = p836();
    printf("%s\n", ans.c_str());
    assert(ans == ANSWER);
}
