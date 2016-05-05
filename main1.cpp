#include "DZ1_1.h"

int main()
{
    forward_list <int> list;
    forward_list <int> list1;
    list.push_front(100);
    list.push_front(150);
    list.push_front(200);
    list.show();
    list1.push_front(1);
    list1.show();
    list1 = list;
    cout << "проверка" << endl;

    list1.show();
    return 0;
}