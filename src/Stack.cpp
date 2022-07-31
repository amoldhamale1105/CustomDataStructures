#ifndef TEMPLATE_METHODS
#include <Stack.hpp>

#else

template <typename T>
Stack<T>::Stack(Stack<T>& other) : head(nullptr)
{
    Vector<T> stackContainer;

    while (!other.isEmpty())
    {
        stackContainer.push_back(other.pop());
    }

    while (!stackContainer.isEmpty())
    {
        T currentElement = stackContainer.pop_back();
        this->push(currentElement);
        other.push(currentElement);
    }
}

template <class T>
void Stack<T>::operator=(Stack<T>& other)
{
    head = nullptr;
    Vector<T> stackContainer;

    while (!other.isEmpty())
    {
        stackContainer.push_back(other.pop());
    }

    while (!stackContainer.isEmpty())
    {
        T currentElement = stackContainer.pop_back();
        this->push(currentElement);
        other.push(currentElement);
    }
}

template <class T>
void Stack<T>::push(const T& data)
{
    Node* node = new Node(data);
    node->next = head;
    head = node;
}

template <class T>
T Stack<T>::pop()
{
    T retVal{};

    if (head != nullptr){
        Node* node = head;
        retVal = node->data;
        head = node->next;
        node->next = nullptr;
        delete node;
    }

    return retVal;
}

template <class T>
T Stack<T>::top() const
{
    return head != nullptr ? head->data : T{};
}

template <class T>
int Stack<T>::depth() const
{
    int count{0};
    Node* currentNode = head;
    
    while (currentNode != nullptr)
    {
        count++;
        currentNode = currentNode->next;
    }

    return count;
}

template <class T>
void Stack<T>::clear()
{
    if (head != nullptr)
        delete head;
    head = nullptr;
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return head == nullptr;
}

template <class T>
void Stack<T>::reverse()
{
    recReverse(*this);
}

template <class T>
void Stack<T>::insertAtBottom(Stack<T>& stack, const T& data)
{
    //Base case
    if (stack.isEmpty()){
        stack.push(data);
        return;
    }

    //Rec case
    T topElement = stack.pop();
    insertAtBottom(stack, data);
    stack.push(topElement);
}

template <class T>
void Stack<T>::recReverse(Stack<T>& stack)
{
    //Base case
    if (stack.depth() == 1)
        return;

    //Rec case
    T topElement = stack.pop();
    recReverse(stack);
    insertAtBottom(stack, topElement);
}

#endif

