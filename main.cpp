
#include <iostream>
#include <string>

struct Student {
    std::string Name;
    int Age;
};

template<typename InfoType>
struct Node {
    Node *next;
    Node *prev;
    InfoType Inf;
};

template<typename InfoType>
struct CircularList {
    Node<InfoType> *first;
    Node<InfoType> *last;
};

template<typename InfoType>
void constructor(CircularList<InfoType> &List) {
    List.first = nullptr;
    List.last = nullptr;
}

template<typename InfoType>
void destructor(CircularList<InfoType> &List) {
    Node<InfoType> *Element = List.first->next;
    while (Element != List.first) {
        Node<InfoType> *Temp = Element->next;
        delete Element;
        Element = Temp;
    }
    delete Element;
    List.first = nullptr;
    List.last = nullptr;
}

template<typename InfoType>
unsigned int size(const CircularList<InfoType> &List) {
    unsigned int CountOut = 0;
    if ((List.first == nullptr) && (List.last == nullptr))
        return CountOut;
    else {
        Node<InfoType> *Element = List.first->next;
        while (Element != List.first) {
            CountOut++;
            Element = Element->next;
        }
        CountOut++;
        return CountOut;
    }
}

template<typename InfoType>
void push_front(CircularList<InfoType> &List, InfoType Info) {
    int Size = size(List);
    if (Size == 0) {
        Node<InfoType> *Element = new Node<InfoType>;
        Element->next = Element;
        Element->prev = Element;
        List.first = Element;
        List.first->Inf = Info;
    } else {
        Node<InfoType> *Element = new Node<InfoType>;//
        Element->Inf = Info;//
        Element->next = List.first;//
        List.first->prev = Element;//
        if (List.last == nullptr) {
            Element->prev = List.first;
            List.first->next = Element;
            List.last = List.first;
        } else {
            Element->prev = List.last;
            List.last->next = Element;
        }
        List.first = Element;//
    }
}

template<typename InfoType>
void push_back(CircularList<InfoType> &List, InfoType Info) {
    if (size(List) == 0) {
        push_front(List, Info);
    } else {
        Node<InfoType> *Element = new Node<InfoType>;//
        Element->Inf = Info;//
        Element->next = List.first;//
        List.first->prev = Element;//
        if (List.last == nullptr) {
            Element->prev = List.first;
            List.first->next = Element;
        } else {
            Element->prev = List.last;
            List.last->next = Element;
        }
        List.last = Element;//
    }
}

template<typename InfoType>
void push(CircularList<InfoType> &List, int IndexIn, InfoType Info) {
    int ListSize = size(List);
    if (IndexIn < ListSize) {
        int IndexTemp = 0;
        Node<InfoType> *ElementTemp = List.first;
        while (IndexTemp != IndexIn) {
            ElementTemp = ElementTemp->next;
            IndexTemp++;
        }
        if (ElementTemp == List.first) {
            push_front(List, Info);
        } else {
            Node<InfoType> *Element = new Node<InfoType>;
            Element->Inf = Info;
            Element->prev = ElementTemp->prev;
            ElementTemp->prev->next = Element;
            Element->next = ElementTemp;
            ElementTemp->prev = Element;
        }
    } else if (IndexIn == ListSize) {
        if (ListSize == 0)
            push_front(List, Info);
        else
            push_back(List, Info);

    }
}

template<typename InfoType>
void push(CircularList<InfoType> &List, Node<InfoType> *&iter, InfoType Info) {
    if (iter == List.last) {
        push_back(List, Info);
    } else {
        Node<InfoType> *Element = new Node<InfoType>;
        Element->Inf = Info;
        Element->prev = iter;
        Element->next = iter->next;
        iter->next = Element;
        Element->next->prev = Element;
    }
}

template<typename InfoType>
InfoType pop_front(CircularList<InfoType> &List) {
    InfoType Out;
    if (size(List) == 1) {
        Out = List.first->Inf;
        delete List.first;
        List.first = nullptr;
        List.last = nullptr;
        return Out;
    } else {
        Out = List.first->Inf;
        Node<InfoType> *ElementTemp = List.first;
        List.first = List.first->next;
        List.first->prev = List.last;
        List.last->next = List.first;
        delete ElementTemp;
        return Out;
    }
}

template<typename InfoType>
InfoType pop_back(CircularList<InfoType> &List) {
    InfoType Out;
    if (size(List) == 1) {
        Out = List.first->Inf;
        delete List.first;
        List.first = nullptr;
        List.last = nullptr;
        return Out;
    } else {
        Out = List.last->Inf;
        Node<InfoType> *ElementTemp = List.last;
        List.last = List.last->prev;
        List.first->prev = List.last;
        List.last->next = List.first;
        delete ElementTemp;
        return Out;
    }
}

template<typename InfoType>
InfoType pop(CircularList<InfoType> &List, int IndexIn) {
    if (IndexIn == 0) {
        return pop_front(List);
    } else if (IndexIn == (size(List) - 1)) {
        return pop_back(List);
    } else {
        InfoType Out;
        int IndexTemp = 0;
        Node<InfoType> *Element = List.first;
        while (IndexTemp != IndexIn) {
            Element = Element->next;
            IndexTemp++;
        }
        Out = Element->Inf;
        Node<InfoType> *ElementNext = Element->next;
        Node<InfoType> *ElementPrev = Element->prev;
        ElementNext->prev = ElementPrev;
        ElementPrev->next = ElementNext;
        delete Element;
        return Out;
    }
}

template<typename InfoType>
InfoType pop(CircularList<InfoType> &List, Node<InfoType> *&iter) {
    if (iter == List.first)
        return pop_front(List);
    else if (iter == List.last)
        return pop_back(List);
    else {
        InfoType Out = iter->Inf;
        Node<InfoType> *ElementNext = iter->next;
        Node<InfoType> *ElementPrev = iter->prev;
        ElementNext->prev = ElementPrev;
        ElementPrev->next = ElementNext;
        delete iter;
        return Out;
    }
}

template<typename InfoType>
InfoType get(CircularList<InfoType> &List, int Index) {
    InfoType Out;
    int IndexTemp = 0;
    Node<InfoType> *Element = List.first;
    while (IndexTemp != Index) {
        Element = Element->next;
        IndexTemp++;
    }
    Out = Element->Inf;
    return Out;
}

template<typename InfoType>
int find(CircularList<InfoType> &List, InfoType Info) {
    int IndexTemp = 0;
    Node<InfoType> *Element = List.first;
    while ((Element->Inf != Info) && (IndexTemp < size(List))) {
        Element = Element->next;
        IndexTemp++;
    }
    if (IndexTemp == size(List))
        return -1;
    else return IndexTemp;
}

template<typename InfoType>
void print(const CircularList<InfoType> &List) {

    if ((List.first == nullptr) && (List.last == nullptr))
        std::cout << "Empty" << std::endl;
    else if ((List.first != nullptr) && (List.last == nullptr))
        std::cout << List.first->Inf << std::endl;
    else {
        Node<InfoType> *Element = List.first;
        while (Element != List.last) {
            std::cout << Element->Inf << "; ";
            Element = Element->next;
        }
        std::cout << List.last->Inf << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, const Student &student) {
    out << student.Name << ' ' << student.Age;
    return out;
}

bool operator==(const Student &S1, const Student &S2) {
    return ((S1.Name == S2.Name) && (S1.Age == S2.Age));
}

bool operator!=(const Student &S1, const Student &S2) {
    return !(S1 == S2);
}

template<typename InfoType, unsigned int Size>
struct DoublyLinkedLinearList {
    Node<InfoType> Storage[Size];
    Node<InfoType> *First;
    Node<InfoType> *Last;
};

template<typename InfoType, unsigned int Size>
void constructor(DoublyLinkedLinearList<InfoType, Size> &List) {
    for (int i = 0; i < Size; i++) {
        List.Storage[i].next = nullptr;
        List.Storage[i].prev = nullptr;
    }
    List.First = nullptr;
    List.Last = nullptr;
}

template<typename InfoType, unsigned int Size>
void destructor(DoublyLinkedLinearList<InfoType, Size> &List) {
    for (int i = 0; i < Size; i++) {
        List.Storage[i].next = nullptr;
        List.Storage[i].prev = nullptr;
    }
    List.First = nullptr;
    List.Last = nullptr;
}

template<typename InfoType, unsigned int Size>
unsigned int size(const DoublyLinkedLinearList<InfoType, Size> &List) {
    unsigned int CountOut = 0;
    if ((List.First == nullptr) && (List.Last == nullptr))
        return CountOut;
    else if ((List.First != nullptr) && (List.Last == nullptr)) {
        CountOut++;
        return CountOut;
    } else {
        Node<InfoType> *Element = List.First;
        while (Element != List.Last) {
            CountOut++;
            Element = Element->next;
        }
        CountOut++;
        return CountOut;
    }
}

template<typename InfoType, unsigned int Size>
int FreeAddress(const DoublyLinkedLinearList<InfoType, Size> &List) {
    int Count = 0;
    for (int i = 0; i < Size; i++) {
        if ((List.Storage[i].next == nullptr) && (List.Storage[i].prev == nullptr))
            if (&List.Storage[i] == List.First)
                continue;
            else return i;
        Count++;
    }
    return -1;

}

template<typename InfoType, unsigned int Size>
void push_back(DoublyLinkedLinearList<InfoType, Size> &List, InfoType Info) {
    unsigned int ListSize = size(List);
    int a = FreeAddress(List);
    if (a != -1) {
        if (ListSize == 0) {
            List.Storage[a].Inf = Info;
            List.First = &List.Storage[a];
        } else if (ListSize == 1) {

            List.Storage[a].Inf = Info;
            List.Last = &List.Storage[a];
            List.First->next = List.Last;
            List.Last->prev = List.First;
        } else {

            List.Storage[a].Inf = Info;
            List.Last->next = &List.Storage[a];
            List.Last->next->prev = List.Last;
            List.Last = &List.Storage[a];
        }
    } else std::cout << "There is no free space to push" << std::endl;
}

template<typename InfoType, unsigned int Size>
void push(DoublyLinkedLinearList<InfoType, Size> &List, unsigned int Index, InfoType Info) {
    unsigned int ListSize = size(List);
    if (Index > ListSize)
        std::cout << "Invalid index" << std::endl;
    else if (Index == ListSize)
        push_back(List, Info);
    else {
        int a = FreeAddress(List);
        if (a != -1) {
            if (ListSize == 0) {
                List.Storage[a].Inf = Info;
                List.First = &List.Storage[a];
            }
            if (ListSize == 1) {
                List.Storage[a].Inf = Info;
                List.First->prev = &List.Storage[a];
                List.First->prev->next = List.First;
                List.Last = List.First;
                List.First = &List.Storage[a];
            } else {
                unsigned int IndexTemp = 0;
                Node<InfoType> *Element = List.First;
                while (IndexTemp != Index) {
                    if (Element != List.Last)
                        Element = Element->next;
                    IndexTemp++;
                }
                if (Element == List.First) {
                    List.Storage[a].Inf = Info;
                    List.First->prev = &List.Storage[a];
                    List.First->prev->next = List.First;
                    List.First = List.First->prev;
                } else {
                    List.Storage[a].Inf = Info;
                    Element->prev->next = &List.Storage[a];
                    Element->prev->next->prev = Element->prev;
                    Element->prev = Element->prev->next;
                    Element->prev->next = Element;
                }
            }
        } else
            std::cout << "There is no free space to push" <<
                      std::endl;
    }
}

template<typename InfoType, unsigned int Size>
InfoType pop_front(DoublyLinkedLinearList<InfoType, Size> &List) {
    InfoType InfoOut = List.First->Inf;
    unsigned int ListSize = size(List);
    if (ListSize == 1) {
        InfoOut = List.First->Inf;
        destructor(List);
        return InfoOut;
    } else if (ListSize == 2) {
        InfoOut = List.First->Inf;
        List.First = List.First->next;

        List.First->prev->next = nullptr;
        List.First->prev = nullptr;
        List.Last = nullptr;
        return InfoOut;
    } else {
        List.First = List.First->next;

        List.First->prev->next = nullptr;
        List.First->prev = nullptr;
        return InfoOut;
    }
}

template<typename InfoType, unsigned int Size>
InfoType pop_back(DoublyLinkedLinearList<InfoType, Size> &List) {

    unsigned int ListSize = size(List);
    if (ListSize == 1) {
        return pop_front(List);
    } else if (ListSize == 2) {
        InfoType InfoOut = List.Last->Inf;
        InfoOut = List.Last->Inf;
        List.Last = List.Last->prev;

        List.Last->next->prev = nullptr;
        List.Last->next = nullptr;
        List.First = List.Last;
        List.Last = nullptr;
        return InfoOut;
    } else {
        InfoType InfoOut = List.Last->Inf;
        List.Last = List.Last->prev;

        List.Last->next->prev = nullptr;
        List.Last->next = nullptr;
        return InfoOut;
    }
}

template<typename InfoType, unsigned int Size>
InfoType pop(DoublyLinkedLinearList<InfoType, Size> &List, unsigned int Index) {
    if (Index == 0)
        return pop_front(List);
    else if (Index == size(List) - 1)
        return pop_back(List);
    else {
        unsigned int IndexTemp = 0;
        Node<InfoType> *Element = List.First;
        while (IndexTemp != Index) {
            Element = Element->next;
            IndexTemp++;
        }
        InfoType InfoOut = Element->Inf;
        Element->prev->next = Element->next;
        Element->next->prev = Element->prev;
        Element->next = nullptr;
        Element->prev = nullptr;

        return InfoOut;
    }
}

template<typename InfoType, unsigned int Size>
InfoType get(DoublyLinkedLinearList<InfoType, Size> &List, unsigned int Index) {
    Node<InfoType> *Element = List.First;
    unsigned int IndexTemp = 0;
    while (IndexTemp != Index) {
        Element = Element->next;
        IndexTemp++;
    }
    return Element->Inf;
}

template<typename InfoType, unsigned int Size>
int find(DoublyLinkedLinearList<InfoType, Size> &List, InfoType Value) {
    int IndexTemp = 0;
    Node<InfoType> *Element = List.First;
    while ((Element->Inf != Value) && (IndexTemp < size(List))) {
        Element = Element->next;
        IndexTemp++;
    }
    if (IndexTemp == size(List))
        return -1;
    else return IndexTemp;
}

template<typename InfoType, unsigned int Size>
void print(DoublyLinkedLinearList<InfoType, Size> &List) {
    if ((List.First == nullptr) && (List.Last == nullptr))
        std::cout << "Empty" << std::endl;
    else if ((List.First != nullptr) && (List.Last == nullptr))
        std::cout << List.First->Inf << std::endl;
    else {
        Node<InfoType> *Element = List.First;
        while (Element != List.Last) {
            std::cout << Element->Inf << "; ";
            Element = Element->next;
        }
        std::cout << List.Last->Inf << std::endl;
    }
}

int main() {
    CircularList<int> AfterTest;
    constructor(AfterTest);
    for (int i = 0; i < 5; i++)
        push_front(AfterTest, i);
    for (int i = 0; i < 5; i++)
        std::cout << pop_front(AfterTest) << std::endl;
    DoublyLinkedLinearList<int, 3> Test;
    constructor(Test);
    print(Test);
    push_back(Test, 100);
    print(Test);
    push(Test, 0, 200);
    print(Test);
    push(Test, 2, 300);
    print(Test);
    std::cout << pop(Test, 1) << ' ' << find(Test, 200) << ' ' << pop_front(Test) << ' ' << pop_back(Test) << std::endl;
    print(Test);
    destructor(Test);
    print(Test);

    DoublyLinkedLinearList<Student, 4> Class;
    constructor(Class);
    Student Vasya = {"Vasiliy Ivanovich Gerc", 18},
            Tanya = {"Tatiana Vasilievna Kapustina", 18},
            Misha = {"Mihail Andreevich Zubkov", 19},
            Petya = {"Pyotr Vladimirovich Medvedev", 19};
    push_back(Class, Vasya);
    push(Class, 1, Petya);
    push(Class, 1, Tanya);
    push(Class, 1, Misha);
    print(Class);
    std::cout << find(Class, Tanya) << std::endl;
    std::cout << get(Class, 1) << std::endl;
    destructor(Class);
    CircularList<int> Test1;
    constructor(Test1);
    std::cout << "Circular List \"Test1\" was initialized" << std::endl;
    std::cout << "Test1: ";
    print(Test1);
    std::cout << "Pushing value \'5\' to the begining" << std::endl;
    push_front(Test1, 5);
    std::cout << "Test1: ";
    print(Test1);
    std::cout << "Pushing value \'6\' to the end" << std::endl;
    push_back(Test1, 6);
    std::cout << "Test1: ";
    print(Test1);
    std::cout << "Pushing value \'7\' to the end" << std::endl;
    push_back(Test1, 7);
    std::cout << "Test1: ";
    print(Test1);
    std::cout << "Pushing value \'8\' to the index 1 position" << std::endl;
    push(Test1, 1, 8);
    std::cout << "Test1: ";
    print(Test1);
    std::cout << "Pushing value \'9\' to the pre-last position using iterator" << std::endl;
    push(Test1, Test1.last->prev, 9);
    std::cout << "Test1: ";
    print(Test1);
    std::cout << "Size of the list: " << size(Test1) << std::endl;
    destructor(Test1);
    std::cout << "Size after destruction: " << size(Test1) << std::endl;
    std::cout << "--------" << std::endl;

    CircularList<double> Test2;
    constructor(Test2);
    std::cout << "Circular List \"Test2\" was initialized" << std::endl;
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'100.2\' to the end" << std::endl;
    push_back(Test2, 100.2);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Destruction Test2" << std::endl;
    destructor(Test2);
    std::cout << "--------" << std::endl;

    std::cout << "Pushing value \'44.44\' to the begining" << std::endl;
    push_front(Test2, 44.44);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'777.777\' to the end" << std::endl;
    push_back(Test2, 777.777);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'7.0\' to the end using index = last element index(1)" << std::endl;
    push(Test2, 1, 7.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'404.0\' to the begining using index 0" << std::endl;
    push(Test2, 0, 404.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'333.333\' to the end" << std::endl;
    push_back(Test2, 333.333);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Destruction Test2" << std::endl;
    destructor(Test2);
    std::cout << "--------" << std::endl;

    std::cout << "Pushing value \'1.0\' to the index 0" << std::endl;
    push(Test2, 0, 1.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'0.0\' to the index 0" << std::endl;
    push(Test2, 0, 0.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'2.0\' to the index 2" << std::endl;
    push(Test2, 2, 2.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Destruction Test2" << std::endl;
    destructor(Test2);
    std::cout << "--------" << std::endl;

    std::cout << "Creating a list of 10 values and getting an iterator on value = 4" << std::endl;
    double a = 0.0;
    for (int i = 0; i < 5; i++) {
        push_back(Test2, a);
        a += 1.0;
    }
    Node<double> *Iter = Test2.last;
    for (int i = 0; i < 5; i++) {
        push_back(Test2, a);
        a += 1.0;
    }
    std::cout << "Test2: ";
    print(Test2);

    std::cout << "Pushing value \'777.0\' using gotten iterator" << std::endl;
    push(Test2, Iter, 777.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'666.0\' using gotten iterator" << std::endl;
    push(Test2, Iter, 666.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'100.0\' using the iterator on the first element" << std::endl;
    push(Test2, Test2.first, 100.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing value \'888.0\' using the iterator on the last element" << std::endl;
    push(Test2, Test2.last, 888.0);
    std::cout << "Test2: ";
    print(Test2);
    std::cout << "Pushing \'0.0\' back" << std::endl;
    push_back(Test2, 0.0);
    print(Test2);
    std::cout << "--------" << std::endl;
    print(Test2);

    std::cout << "Pop 1st element: " << pop_front(Test2) << std::endl;
    std::cout << "Pop 1st element again: " << pop_front(Test2) << std::endl;
    print(Test2);
    std::cout << "Pop last element: " << pop_back(Test2) << std::endl;
    std::cout << "Pop last element again: " << pop_back(Test2) << std::endl;
    print(Test2);
    int Index = 0;
    std::cout
            << "Enter the index of the element you want to pop(except index = 3, because we need iter on this element later)"
            << std::endl;
    std::cin >> Index;
    std::cout << "The value of the element with this index = " << pop(Test2, Index) << std::endl;
    print(Test2);

    std::cout << "--------" << std::endl;
    print(Test2);
    std::cout << "Popping the value using the iterator we gotten: " << pop(Test2, Iter) << std::endl;
    print(Test2);
    std::cout << "Popping the value using the iterator first: " << pop(Test2, Test2.first) << std::endl;
    std::cout << "Popping the value using the iterator last: " << pop(Test2, Test2.last) << std::endl;
    print(Test2);

    std::cout << "--------" << std::endl;
    print(Test2);
    std::cout << "Enter the index of the element you want to get(<" << size(Test2) << "): " << std::endl;
    std::cin >> Index;
    std::cout << "Your element = " << get(Test2, Index) << std::endl;
    print(Test2);

    std::cout << "--------" << std::endl;
    print(Test2);
    std::cout << "Enter the value of the element which position you want to get: " << std::endl;
    double Value = 0;
    std::cin >> Value;
    std::cout << "Its position: " << find(Test2, Value) << std::endl;
    destructor(Test2);
    std::cout << "--------" << std::endl;

    CircularList<Student> MyGroup;
    constructor(MyGroup);
    std::cout << "\"Student\" type List \"MyGroup\" :";
    print(MyGroup);
    std::cout << "Pushing \"Vasya\" into MyGroup" << std::endl;
    push_front(MyGroup, Vasya);
    print(MyGroup);
    std::cout << "Pushing \"Tanya\" into MyGroup" << std::endl;
    push_back(MyGroup, Tanya);
    print(MyGroup);
    std::cout << "Pushing \"Misha\" into MyGroup" << std::endl;
    push(MyGroup, 1, Misha);
    print(MyGroup);
    std::cout << "Pushing \"Petya\" into MyGroup" << std::endl;
    push(MyGroup, MyGroup.first, Petya);
    print(MyGroup);
    std::cout << "Poping element 2: " << pop(MyGroup, 2) << std::endl;
    print(MyGroup);
    std::cout << "Finding Petya's index: " << find(MyGroup, Petya) << std::endl;
    destructor(MyGroup);

    return 0;
}