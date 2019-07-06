
#define VEC std::vector<T>
#define DLL_Node_ptr DoublyLinkedListNode<T>*
#define LIST_INIT_TYPE std::initializer_list<T>
#define DLL_AUTO_AUTO DoublyLinkedList<auto, auto>
#define TEMPLATE_INIT template <typename T>

TEMPLATE_INIT
class DoublyLinkedListNode
{
    T data;
    DLL_Node_ptr left; DLL_Node_ptr right;
public:
    DoublyLinkedListNode(T d): data(d), left(NULL), right(NULL) { ; }
    T get_data() { return data; }
    DLL_Node_ptr get_left() { return left; }
    DLL_Node_ptr get_right() { return right; }
    void set_left(DLL_Node_ptr left_neighbour) { left = left_neighbour; }
    void set_right(DLL_Node_ptr right_neighbour) { right = right_neighbour; }

    void insert_in_between(DLL_Node_ptr left_, DLL_Node_ptr right_)
    {
        left = left_;
        right = right_;
        if(left_ != NULL)
            left_->set_right(this);
        if(right_ != NULL)
            right_->set_left(this);
    }
};

template <typename T, typename T_>
class DoublyLinkedList
{
    int64_t size;
    DLL_Node_ptr head; DLL_Node_ptr mid; DLL_Node_ptr tail;
public:
    DoublyLinkedList(): size(0), head(NULL), tail(NULL), mid(NULL) {;}
    DoublyLinkedList(T_ list)
    {
        if(list.size() < 3)
            throw UserException("List of insufficient size.", "", 0)
        size = 2;
        head = new DoublyLinkedListNode<T>(*(list.begin()));
        tail = new DoublyLinkedListNode<T>(*(list.begin()+1));
        head->set_right(tail);
        tail->set_left(head);
        for(auto i=list.begin()+2; i!=list.end(); ++i, ++size)
        {
            DLL_Node_ptr node = new DoublyLinkedListNode<T>(*i);
            node->insert_in_between(tail, NULL);
        }
        int mid_index = size/2;
        DLL_Node_ptr temp_node = head;
        while(mid_index--)
            temp_node = temp_node->get_right();
        mid = temp_node;
    }
    void sort_insert_util(
        DLL_Node_ptr node,
        DLL_Node_ptr start
    )
    {
        while(start->get_data() < node->get_data())
            start = start->get_right();
        if(start->get_data() < node->get_data())
            node->insert_in_between(start, start->get_right());
        else
            node->insert_in_between(start->get_left(), start);
    }
    void sort_insert(const T& data)
    {
        DLL_Node_ptr node = new DoublyLinkedListNode<T>(data);
        if(head == NULL)
            head = tail = mid = node;
        else if(data >= tail->get_data())
        {
            node->insert_in_between(tail, NULL);
            tail = tail->get_right();
            mid = mid->get_right();
        }
        else if(data <= head->get_data())
        {
            node->insert_in_between(NULL, head);
            head = head->get_left();
            mid = mid->get_left();
        }
        else if(data == mid->get_data())
            node->insert_in_between(mid, mid->get_right());
        else if(data < mid->get_data())
        {
            sort_insert_util(node, mid);
            mid = mid->get_left();
        }
        else
        {
            sort_insert_util(node, head);
            mid = mid->get_right();
        }
        ++size;
    }

    VEC compile_answer()
    {
        VEC ans;
        ans.reserve(size);
        DLL_Node_ptr temp = head;
        while(temp != NULL)
        {
            ans.push_back(temp->get_data());
            temp = temp->get_right();
        }
        return ans;
    }
};
#undef DLL_Node_ptr

TEMPLATE_INIT // Vector printer
std::ostream& operator<<(std::ostream& os, VEC& obj)
{
    std::cout<<std::endl<<"[";
    for(auto i:obj)
        std::cout<<i<<", ";   
    std::cout<<"]"<<std::endl;
    return os;
}

TEMPLATE_INIT
VEC rex_sort(VEC& original_array)
{
    DoublyLinkedList<T, VEC> arr;
    for(auto i : original_array)
        arr.sort_insert(i);
    return arr.compile_answer();
}

// Doubly Linked List printer
std::ostream& operator<<(std::ostream& os, DLL_AUTO_AUTO& obj)
{
    auto head_ = obj.head;
    std::cout<<std::endl<<"[";
    while(head_ != NULL)
    {
        std::cout<<head_->get_data()<<", ";
        head_ = head_->get_right();
    }
    std::cout<<"]"<<std::endl;
    return os;
}


