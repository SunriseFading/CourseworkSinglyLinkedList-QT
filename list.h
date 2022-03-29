#ifndef LIST_H
#define LIST_H

template<typename T>
class List
{
public:
    List();
    ~List();

    ///Очистка листа
    void clear();

    ///Добавление в самый конец
    void append(T data);

    ///Удаление по указанному индексу
    void removeAt(int index);

    ///Возвращает количество элементов в списке
    int length();

    ///Возвращает элемент по индексу
    T& operator[](const int index);

private:

    class Node
    {
    public:
        Node *Next;
        T data;

        Node(T new_data = T(), Node *new_Next = nullptr)
        {
            data = new_data;
            Next = new_Next;
        }
    };

    int len;
    Node *head;

};

template<typename T>
List<T>::List()
{
    len = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List()
{
    Node *temp;
    while (len)
    {
        temp = head->Next;
        delete head;
        head = temp;
        len--;
    }
}

template<typename T>
void List<T>::clear()
{
    Node *temp;
    while (len)
    {
        temp = head->Next;
        delete head;
        head = temp;
        len--;
    }
}

template<typename T>
void List<T>::append(T data)
{
    if(head == nullptr)
    {
        head = new Node(data);
        len = 1;
    }
    else
    {
        Node *current = head;
        while(current->Next != nullptr)
        {
            current = current->Next;
        }
        current->Next = new Node(data);
        len++;
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    if(index == 0)
    {
        Node *temp = head;
        head = head->Next;
        delete temp;
        len--;
    }
    else
    {
        Node *previous = head;
        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->Next;
        }
        Node *toDelete = previous->Next;
        previous->Next = toDelete->Next;
        delete toDelete;
        len--;
    }
}

template<typename T>
int List<T>::length()
{
    return len;
}

template<typename T>
T& List<T>::operator[](const int index)
{
    int count = 0;
    Node *current = head;
    while (current != nullptr && count <= index)
    {
        if(count == index)
        {
            return current->data;
        }
        count++;
        current = current->Next;
    }
}

#endif // LIST_H
