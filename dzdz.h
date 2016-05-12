#include <iostream>
using namespace std;
template <class T>
class forward_list
{
    struct Node
    {
        T data;      // Инф поле
        Node *pNext; // Указатель на следующий элемент
        bool flag;
        Node(): data(0), pNext(nullptr), flag(false) {}
        Node(T data_, Node * pNext_, bool flag_): data(data_), pNext(pNext_), flag(flag_) {}

        Node & operator=(const Node & noda)
        {
            if (this == &noda)
                return (*this);
            data = noda.data;
            return *this;
        }
        friend ostream& operator<<(ostream& out, const Node & noda)
        {
            out << noda.data << endl;
            return out;
        }
    };

    Node * head;
    size_t size;
    void push_front(const Node & noda)
    {
        Node * p;
        p = new Node;
        p->data = noda.data;
        p->pNext = head;
        head = p;
        size++;
    }
    
public:
    
    forward_list():
    head(nullptr), size(0)
    {}
    
    forward_list(const forward_list& other)
    :head(nullptr), size(0)
    {
        forward_list buf;
        for (Node * pi = other.head; pi; pi = pi->pNext)
        {
            buf.push_front(pi->data);
        }
        for (Node * pi = buf.head; pi; pi = pi->pNext)
        {
            push_front(pi->data);
        }
    }
    
    class iterator
    {
        Node * el; // указатель на элемент
    public:
        friend class forward_list;

        iterator()
        : el(nullptr)
        {}

        iterator(Node * p)
        : el(p)
        {}

        iterator(const iterator & iterator1)
        :el(iterator1.el)
        {}

        iterator operator=(const iterator & iterator1)
        {
            if (el == iterator1.el)
            {
                return *this;
            }
            el = iterator1.el;
            return (*this);
        }

        Node & operator*()
        {
            if (el == nullptr)
            {
                cout << "Wrong iterator" << endl;
            }
            return (*el);
        }

        Node * operator->()
        {
            if (el == nullptr)
            {
                cout << "Wrong iterator" << endl;
            }
            return (el);
        }

        bool operator==(const iterator & iterator1)
        {
            return (iterator1.el == el);
        }

        bool operator!=(const iterator & iterator1)
        {
            return (iterator1.el != el);
        }

        iterator operator++()
        {
            if(el->pNext)
            {
                el = el->pNext;
                return *this;
            }
        }

        iterator operator++(int)
        {
            if(el->pNext)
            {
                el = el->pNext;
                return *this;
            }
            return *this;

        }

        ~iterator()
        {}
    };

    iterator begin()
    {
        Node * p = head;
        return iterator(p);
    }

    iterator end()
    {
        Node * p = head;
        while (p->pNext)
            p = p->pNext;
        if (!(p->flag))
        {
            p->pNext = new Node(0, 0, true);
            return iterator(p->pNext);
        }
        return iterator(p);
    }

    iterator before_begin()
    {
        Node * p = new Node;
        p->pNext = head;
        return iterator(p);

    }
    
    // вставляет элементы после указанного элемента
    iterator insert_after( iterator pos, const T& value)
    {
        Node * p = new Node;
        p->data = value;
        Node * buf = pos->el->pNext;
        pos->el->pNext = p;
        p->pNext = buf;
        return pos++;
    }
    
    // вставляет элементы после указанного элемента
    iterator insert_after( iterator pos, size_t count, const T& value)
    {
        for ( int i = 0; i != count; i++)
        {
            insert_after(pos, value);
            pos++;
        }
        return pos++;
    }
    
    // Удаляет элемент, после указанного
    iterator erase_after( iterator pos )
    {
        Node * buf;
        buf=pos->pNext->pNext;
        // указатель на элемент следующий от удаляемого
        delete pos->pNext;
        pos->pNext = buf;
        return pos++;
    }
    
    // Удаляет элементы в интервале
    iterator erase_after(iterator first, iterator last)
    {
        for(iterator pos = first; pos != last; pos++ )
        {
            erase_after(pos);
        }
        return last;
    }

    // Функция добавления элемента в начало списка
    void push_front(const T &_data)
    {
        Node * p;
        p = new Node;
        p->data = _data;
        p->pNext = head;
        head = p;
        size++;

    }

    // Удаление первого элемента
    Node * pop_front()
    {
        if (empty())
        {
            cout << "Список пуст" << endl;
            return 0;
        }
        else
        {
            Node * p = head;
            head = head->pNext;
            size--;
            return p;
        }
    }

    // Возвращает максимально допустимое количество элементов в контейнере
    size_t max_size() const
    {
        size_t s = sizeof(T) + sizeof(Node *);
        s = 4000000000 / s;
        return s;
    }
    // показывает контейнер
    void show()
    {
        if (empty())
        {
            cout << "Список пуст" << endl;
        }
        else
            for (Node * pi = head; pi; pi = pi->pNext) // Просмотр списка
                cout << pi->data << endl;
    }

    // Проверяет отсутствие элементов в контейнере
    bool empty()
    {
        return (head == nullptr);
    }

    // Очищает контейнер
    void clear()
    {
        while(!empty())
        {
            Node * a = pop_front();
            delete a;
        }
    }

    // Доступ к первому элементу
    Node & front()
    {
        return *head;
    }

    // изменяет размер контейнера
    void resize( size_t count )
    {
        if (count < size)
        {
            forward_list buf;
            for(int i = 0; i != count; i++)
                buf.push_front(pop_front());
            clear();
            for(int i = 0; i != count; i++)
                push_front(buf.pop_front());
        }
    }

    // Изменение размера
    void resize( size_t count, const T& value)
    {
        if(count < size)
        {
            resize(count);
        }
        else
        {
            forward_list buf;
            for(int i = 0; i != size; i++)
                buf.push_front(pop_front());
            for(int i = 0; i != count - size; i++)
                push_front(value);
            for(int i = 0; i != size; i++)
                push_front(buf.pop_front());
        }
    }
    
    // удаляются последовательно повторяющихся элементов
    void unique()
    {
        forward_list buf;
        for(Node * pi = head; pi->pNext; pi = pi->pNext)
        {
            if (pi->data == pi->pNext->data)
            {
                erase_after(iterator(pi));
                unique();
            }
        }
    }
    
    // Переворачивает значение функции
    void reverse()
    {
        forward_list buf;
        buf = *this;
        size_t size1 = size;
        clear();
        for(int i = 0; i != size1; i++)
        {
            push_front(*buf.pop_front());
        }
    }
    // слияние двух отсортированных списков
    
    void merge(forward_list & other)
    {
        size_t size1 = other.size;
        for(int i = 0; i != size1; i++)
            push_front(*other.pop_front());
        sort();
    }
    // удаляет все элементы, равные value
    void remove( const T& value )
    {
        forward_list buf;
        for(Node * pi = head; pi; pi = pi->pNext)
        {
            if (pi->data != value)
            {
                buf.push_front(pi->data);
            }
        }
        buf.reverse();
        *this = buf;
    }
    
    // сортировка
    void sort()
    {
        Node * p = head, * buf = nullptr, * pred= nullptr;
        bool flag = false;
        do
        {
            flag = false;
            p = head;
            while(p->pNext)
            {
                if(p->data > p->pNext->data)
                {
                    if(p == head)
                    {
                        buf = p;
                        p = buf->pNext;
                        buf->pNext = p->pNext;
                        p->pNext = buf;
                        head = p;
                        flag = true;
                    }
                    else
                    {
                        buf = p;
                        p = buf->pNext;
                        buf->pNext = p->pNext;
                        p->pNext = buf;
                        pred->pNext = p;
                        flag = true;
                    }
                }
                pred = p;
                p = p->pNext;
            }
        }
        while(flag);
    }
    
    // Обменивает содержимое
    void swap(forward_list& other)
    {
        forward_list buf1(*this);
        clear();
        forward_list buf;

        for (Node * pi = other.head; pi; pi = pi->pNext)
        {
            buf.push_front(pi->data);
        }
        for (Node * pi = buf.head; pi; pi = pi->pNext)
        {
            push_front(pi->data);
        }
        other = buf1;
    }

    // перемещает элементы из другого forward_list
    void splice_after(iterator pos, forward_list& other)
    {
        if (&other != this)
        {
            for (int i = 0; i != other.size(); i++)
            {
                insert_after(pos, other.pop_front());
                pos++;
            }
            clear(other);
        }
        else
        {
            cout << "Ошибка" << endl;
        }
    }

    forward_list& operator=(const forward_list& other)
    {
        if (&other == this)
        {
            return * this;
        }

        clear();
        forward_list buf;

        for (Node * pi = other.head; pi; pi = pi->pNext)
        {
            buf.push_front(pi->data);
        }
        for (Node * pi = buf.head; pi; pi = pi->pNext)
        {
            push_front(pi->data);
        }
        return * this;
    }
   
    ~forward_list()
    {
        clear();
    }
};
