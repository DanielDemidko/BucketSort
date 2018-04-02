#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T> std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec)
{
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(out, " "));
    return out;
}

template<typename T> std::vector<T> BucketSort(const std::vector<T> &data)
{
    if (data.size() == 1)
    {
        return data;
    }
    std::vector<std::vector<T>> buckets(data.size() / 4);
    auto hash =
        [
            a = *std::min_element(data.cbegin(), data.cend()),
            b = *std::max_element(data.cbegin(), data.cend()) + 1,
            n = buckets.size()
        ] (const T &x)->size_t
    {
        return std::floor(n * (x - a) / (b - a));
    };
    for (const auto &i : data)
    {
        std::cout << "DEBUG: hash(" << i << ") = " << hash(i) << std::endl;
        buckets[hash(i)].push_back(i);
    }
    std::vector<T> result;
    for (auto &i : buckets)
    {
        std::sort(i.begin(), i.end());
        result.reserve(result.size() + i.size());
        result.insert(result.end(), i.begin(), i.end());
    }
    return result;
}


int main()
{
    std::cout << BucketSort<int>({ 5, 8, 7, 3, 1, 2, 4, 6, 10, 9 }) << std::endl;
}

