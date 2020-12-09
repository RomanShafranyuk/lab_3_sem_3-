#include <iostream>
#include "cpp-vector.h"
#include "cpp-list.h"
#include <vector>
#include <list>
using namespace std;
template <typename T>
using CollectionType = Vector<T>;
template <typename T>
void print(const CollectionType<T> &obj)
{
    auto tmp = obj.begin();
    for (size_t i = 0; i < obj.size(); i++)
    {
        cout << *tmp << ' ';
        ++tmp;
    }
    cout << endl;
}
int main()
{
    try
    {
        CollectionType<int> v1;
        v1.insert(v1.end(), 1);
        v1.insert(v1.end(), 67);
        cout << "Object: v1" <<endl;
        print(v1);
        CollectionType<int> v2(10);
        auto tmp = v2.begin();
        for (size_t i = 1; i <= v2.size(); ++i)
        {
            *tmp = (int)(i * i);
            ++tmp;
        }
        cout << "Object: v2" << endl;
        print(v2);

        cout << "Object: v3" << endl;
        CollectionType<int> v3(v2);
        v3.erase(v3.begin());
        print(v3);

        cout << "Object: v4" << endl;
        CollectionType<int> v4 = move(v3);
        v4.erase(v4.begin());
        print(v4);

        auto tmp1 = v4.begin();
        tmp1++;
        v4.insert(tmp1, 228);
        print(v4);
        v4.erase(tmp1);
        print(v4);
    }
    catch (const char *s)
    {
        cout << s;
    }
    return 0;
}