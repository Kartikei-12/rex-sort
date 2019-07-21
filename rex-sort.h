
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
    DLL_Node_ptr head; DLL_Node_ptr mid;
    DLL_Node_ptr tail; DLL_Node_ptr last;
    
    void sort_insert_util(
        DLL_Node_ptr node,
        DLL_Node_ptr start,
        DLL_Node_ptr end
    )
    {
        while(node->get_data() > start->get_data() &&
              node->get_data() < end->get_data())
        {
            start = start->get_right();
            end = end->get_left();
        }   
        end = (
            !(node->get_data() > start->get_data()) &&
            node->get_data() < end->get_data()
        )? start : end;
        if(end->get_data() <= node->get_data())
            node->insert_in_between(end, end->get_right());
        else
            node->insert_in_between(end->get_left(), end);
    }
public:
    DoublyLinkedList():
        size(0),
        head(NULL), tail(NULL),
        mid(NULL), last(NULL) {;}
    DLL_Node_ptr begin() { return head;}
    DLL_Node_ptr end() { return tail;}
    // DoublyLinkedList(T_ list)
    // {
    //     if(list.size() < 3)
    //         throw UserException("List of insufficient size.", __FILE__, __LINE__);
    //     size = 2;
    //     head = new DoublyLinkedListNode<T>(*(list.begin()));
    //     tail = new DoublyLinkedListNode<T>(*(list.begin()+1));
    //     head->set_right(tail);
    //     tail->set_left(head);
    //     for(auto i=list.begin()+2; i!=list.end(); ++i, ++size)
    //     {
    //         DLL_Node_ptr node = new DoublyLinkedListNode<T>(*i);
    //         node->insert_in_between(tail, NULL);
    //     }
    //     int mid_index = size/2;
    //     DLL_Node_ptr temp_node = head;
    //     while(mid_index--)
    //         temp_node = temp_node->get_right();
    //     mid = temp_node;
    // }
    void sort_insert(const T& data)
    {
        DLL_Node_ptr node = new DoublyLinkedListNode<T>(data);
        if(head == NULL)
            head = tail = mid = last = node;
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
        else if(data > mid->get_data())// head---mid--data--tail
        {
            if(last->get_data() > mid->get_data())// head---mid--last--tail
                if(data < last->get_data())// head---mid--data-last-tail
                    sort_insert_util(node, mid, last);
                else// head---mid--last-data-tail
                    sort_insert_util(node, last, tail);
            else// head---last--mid--data--tail
                sort_insert_util(node, mid, tail);
            mid = mid->get_right();
            last = node;
        }
        else// head--data--mid---tail
        {
            if(last->get_data() < mid->get_data())// head---last--mid--tail
                if(data < last->get_data())// head-data-last-mid---tail
                    sort_insert_util(node, head, last);
                else// head--last-data--mid---tail
                    sort_insert_util(node, last, mid);
            else// head---data--mid--last--tail
                sort_insert_util(node, head, mid);
            mid = mid->get_left();
            last = node;
        }
        ++size;
    }

    VEC compile_answer()
    {
        VEC ans;
        DLL_Node_ptr temp = head;
        
        ans.reserve(size);
        
        while(temp != NULL)
        {
            ans.push_back(temp->get_data());
            temp = temp->get_right();
        }
        return ans;
    }

    DLL_Node_ptr get_head() { return head;}
};
#undef DLL_Node_ptr

TEMPLATE_INIT
VEC rex_sort(VEC original_array)
{
    DoublyLinkedList<T, VEC> arr;
    for(T i : original_array)
        arr.sort_insert(i);
    return arr.compile_answer();
}

TEMPLATE_INIT // Vector printer
std::ostream& operator<<(std::ostream& os, VEC& obj)
{
    std::cout<<std::endl<<"[";
    for(T i:obj)
        std::cout<<i<<", ";   
    std::cout<<"]"<<std::endl;
    return os;
}

// Doubly Linked List printer
std::ostream& operator<<(std::ostream& os, DLL_AUTO_AUTO& obj)
{
    auto head_ = obj.get_head();
    std::cout<<std::endl<<"[";
    while(head_ != NULL)
    {
        std::cout<<head_->get_data()<<", ";
        head_ = head_->get_right();
    }
    std::cout<<"]"<<std::endl;
    return os;
}
#undef VEC
#undef DLL_Node_ptr 
#undef LIST_INIT_TYPE
#undef DLL_AUTO_AUTO
#undef TEMPLATE_INIT
