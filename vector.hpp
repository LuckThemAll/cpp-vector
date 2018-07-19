#include <algorithm>
#include <exception>
#include <stdexcept>
#include <initializer_list>
#include <iterator>

namespace art{

    template <typename Type, typename Allocator = std::allocator<Type>>
    class vector{
    public:
        typedef Type                                                     value_type;
        typedef Allocator                                                allocator_type;
        typedef value_type&                                              reference;
        typedef const value_type&                                        const_reference;
        typedef typename std::ptrdiff_t                                  difference_type;
        typedef std::size_t                                              size_type;
        typedef typename std::allocator_traits<Allocator>::pointer       pointer;
        typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;

        template<typename TypeT>
        class vector_iterator : public std::iterator<std::random_access_iterator_tag, TypeT> {
        public:
            vector_iterator() : _ptr(nullptr) {}
            vector_iterator(TypeT* rhs) : _ptr(rhs) {}
            vector_iterator(const vector_iterator &rhs) : _ptr(rhs._ptr) {}
            inline vector_iterator& operator=(const vector_iterator &rhs) {_ptr = rhs._ptr; return *this;}
            inline vector_iterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
            inline vector_iterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}

            inline reference operator*() const {return *_ptr;}
            inline reference operator[](difference_type rhs) const {return _ptr[rhs];}
            inline pointer   operator->() const {return _ptr;}

            inline vector_iterator& operator++() {++_ptr; return *this;}
            inline vector_iterator& operator--() {--_ptr; return *this;}
            inline vector_iterator  operator++(int) {vector_iterator tmp(*this); ++_ptr; return tmp;}
            inline vector_iterator  operator--(int) {vector_iterator tmp(*this); --_ptr; return tmp;}
            inline vector_iterator  operator+(difference_type rhs) const {return vector_iterator(_ptr+rhs);}
            inline vector_iterator  operator-(difference_type rhs) const {return vector_iterator(_ptr-rhs);}
            inline difference_type  operator-(const vector_iterator& rhs) const {return _ptr-rhs._ptr;}

            inline bool operator==(const vector_iterator& rhs) const {return _ptr == rhs._ptr;}
            inline bool operator!=(const vector_iterator& rhs) const {return _ptr != rhs._ptr;}
            inline bool operator>(const vector_iterator& rhs)  const {return _ptr > rhs._ptr;}
            inline bool operator<(const vector_iterator& rhs)  const {return _ptr < rhs._ptr;}
            inline bool operator>=(const vector_iterator& rhs) const {return _ptr >= rhs._ptr;}
            inline bool operator<=(const vector_iterator& rhs) const {return _ptr <= rhs._ptr;}
        private:
            pointer _ptr;
        };

        typedef vector_iterator<Type>                              iterator;
        typedef const vector_iterator<Type>                        const_iterator;
        typedef typename std::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename std::reverse_iterator<const_iterator>           const_reverse_iterator;

        // construct/copy/destroy
        explicit vector(const Allocator& alloc = Allocator());
        explicit vector(size_type size);
        vector(size_type size, const Type& value, const Allocator& alloc = Allocator());

        template< class InputIt >
        vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );

        vector( const vector& other, const Allocator& alloc );
        vector( std::initializer_list<Type> init, const Allocator& alloc = Allocator() );

        vector( vector&& other, const Allocator& alloc );

        ~vector();

        //operators
        vector& operator=( const vector& other );
        vector& operator=( vector&& other );

        void assign( size_type count, const Type& value );
        template< class InputIt, class = typename std::enable_if <!std::is_integral <InputIt>::value>::type>
        void assign( InputIt first, InputIt last );

        //allocator getter
        allocator_type get_allocator() const;

        //access to element with range check
        reference       at( size_type pos );
        const_reference at( size_type pos ) const;

        //access to element without range check
        reference       operator[]( size_type pos );
        const_reference operator[]( size_type pos ) const;

        //front element
        reference front();
        const_reference front() const;

        //back element
        reference back();
        const_reference back() const;

        //data access
        Type* data() noexcept;
        const Type* data() const noexcept;

        //iterators
        iterator                begin() noexcept;
        const_iterator          begin() const noexcept;
        const_iterator          cbegin() noexcept;

        iterator                end() noexcept;
        const_iterator          end() const noexcept;
        const_iterator          cend() noexcept;

        reverse_iterator        rbegin() noexcept;
        const_reverse_iterator  rbegin() const noexcept;
        const_reverse_iterator  crbegin() const noexcept;

        reverse_iterator        rend() noexcept;
        const_reverse_iterator  rend() const noexcept;
        const_reverse_iterator  crend() const noexcept;

        // capacity
        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        void reserve(size_type size);
        size_type capacity() const noexcept;
        void shrink_to_fit();

        // modifiers
        void clear() noexcept;

        iterator insert( const_iterator pos, const Type& value );
        iterator insert( const_iterator pos, Type&& value );
        iterator insert( const_iterator pos, size_type count, const Type& value );
        template< class InputIt, class = typename std::enable_if <!std::is_integral <InputIt>::value>::type >
        iterator insert( const_iterator pos, InputIt first, InputIt last );
        iterator insert( const_iterator pos, std::initializer_list<Type> initist );

        template< class... Args >
        iterator emplace( const_iterator pos, Args&&... args );

        iterator erase( const_iterator pos );
        iterator erase( const_iterator first, const_iterator last );

        void push_back( Type&& value );

        template< class... Args >
        void emplace_back( Args&&... args );

        void pop_back();

        void resize( size_type count );
        void resize( size_type count, const value_type& value);

        void swap( vector& other ) noexcept;



        //Operators
        template <class U, class UAllocator>
        friend bool operator==(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs);

        template <class U, class UAllocator>
        friend bool operator<(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs);

        template <class U, class UAllocator>
        friend bool operator!=(const vector<U, UAllocator>& lhs, const vector<U,UAllocator>& rhs);

        template <class U, class UAllocator>
        friend bool operator> (const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs);

        template <class U, class UAllocator>
        friend bool operator>=(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs);

        template <class U, class UAllocator>
        friend bool operator<=(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs);

    private:
        const int _m_SIZE_INCREASE_FACTOR = 2;
        const int _m_INIT_CAPACITY = 10;


        Allocator _m_allocator;
        Type* _m_first = nullptr;
        Type* _m_last = nullptr;
        Type* _m_end_of_capacity = nullptr;

        void _m_allocate_and_copy(size_type need_size);
        void _m_initialize(iterator first, iterator last);
        void _m_destroy(iterator first, iterator last);
    };

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::_m_allocate_and_copy(size_type need_size) {
        if (need_size >= capacity()) {
            need_size = need_size * _m_SIZE_INCREASE_FACTOR;
        }
        pointer new_first = _m_allocator.allocate(need_size);
        if (new_first == _m_first)
            return;
        if (_m_first) {
            try {
                std::copy(_m_first, _m_first + std::min(size(), need_size), new_first);
            }
            catch (...) {
                _m_allocator.deallocate(new_first, need_size * _m_SIZE_INCREASE_FACTOR);
                throw;
            }
            _m_allocator.deallocate(_m_first, capacity());
        }
        size_type old_size = size();
        _m_first = new_first;
        _m_last = new_first + old_size;
        _m_end_of_capacity = _m_first + need_size;
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::_m_initialize(iterator first, iterator last) {
        for (auto it = first; it != last; ++it){
            _m_allocator.construct(&*it, Type());
        }
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::_m_destroy(iterator first, iterator last) {
        for (iterator it = first; it != last; ++it){
            _m_allocator.destroy(&*it);
        }
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>::vector(const vector& other, const Allocator& alloc ) {
        _m_allocator = alloc;
        _m_allocate_and_copy(other.size());
        for (size_type i = 0; i < other.size(); ++i) _m_allocator.construct(_m_first + i, other[i]);
    }
    template<typename Type, typename Allocator>
    vector<Type, Allocator>::vector(size_type new_size) {
        _m_allocate_and_copy(new_size);
        _m_last = _m_first + new_size;
        _m_initialize(begin(), end());
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>::vector(const Allocator& alloc) {
        _m_allocator = alloc;
        /*_m_allocate_and_copy((unsigned) _m_INIT_CAPACITY);
        _m_last = _m_first + _m_INIT_CAPACITY;
        _m_initialize(begin(), end());*/
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>::vector(size_type new_size, const Type& value, const Allocator& alloc) {
        _m_allocator = alloc;
        assign(new_size, value);
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>::vector(std::initializer_list<Type> init, const Allocator& alloc) {
        _m_allocator = alloc;
        assign(init.begin(), init.end());
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>::vector( vector&& other, const Allocator& alloc ) {
        _m_allocator = alloc;
        _m_first = other._m_first;
        _m_last = other._m_last;
        _m_end_of_capacity = other._m_end_of_capacity;
        assign(other.begin(), other.end());
    }
    //vector( vector&& other, const Alloc& alloc );

    template<typename Type, typename Allocator>
    template<typename InputIt>
    vector<Type, Allocator>::vector(InputIt first, InputIt last, const Allocator& alloc ) {
        _m_allocator = alloc;
        assign(first, last);
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>::~vector() {
        _m_destroy(begin(), end());
        _m_allocator.deallocate(_m_first, capacity());
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>& vector<Type, Allocator>::operator=(const vector& other) {
        if (this != &other) {
            erase(begin(), end());
            if (other.size() > capacity()) {
                _m_allocate_and_copy(other.size());
            }
            for (size_type i = 0; i < other.size(); ++i) {
                _m_allocator.construct(_m_first + i, other[i]);
            }
            _m_last = _m_first + other.size();
        }
        return *this;
    }

    template<typename Type, typename Allocator>
    vector<Type, Allocator>& vector<Type, Allocator>::operator=(vector<Type, Allocator>&& other) {
        if (this == &other) return *this;
        clear();
        swap(other);
        return *this;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::begin() noexcept {
        return iterator(_m_first);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_iterator vector<Type, Allocator>::begin() const noexcept {
        return iterator(_m_first);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_iterator vector<Type, Allocator>::cbegin() noexcept {
        return begin();
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::end() noexcept {
        return iterator(_m_last);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_iterator vector<Type, Allocator>::end() const noexcept {
        return iterator(_m_last);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_iterator vector<Type, Allocator>::cend() noexcept {
        return end();
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::reverse_iterator vector<Type, Allocator>::rbegin() noexcept {
        return vector<Type, Allocator>::reverse_iterator(_m_first + size());
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reverse_iterator vector<Type, Allocator>::rbegin() const noexcept {
        return vector<Type, Allocator>::const_reverse_iterator(_m_last - 1);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reverse_iterator vector<Type, Allocator>::crbegin() const noexcept {
        return vector<Type, Allocator>::const_reverse_iterator(_m_last - 1);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::reverse_iterator vector<Type, Allocator>::rend() noexcept {
        return vector<Type, Allocator>::reverse_iterator(_m_first - 1);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reverse_iterator vector<Type, Allocator>::rend() const noexcept {
        return vector<Type, Allocator>::const_reverse_iterator(_m_first - 1);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reverse_iterator vector<Type, Allocator>::crend() const noexcept {
        return vector<Type, Allocator>::const_reverse_iterator(_m_first - 1);
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::assign(size_type count, const Type& value) {
        erase(begin(), end());
        if (count > capacity()) _m_allocate_and_copy(count);
        for (size_type i = 0; i < count; ++i) _m_allocator.construct(_m_first + i, value);
        _m_last = _m_first + count;
    }

    template<typename Type, typename Allocator>
    template<class InputIt, typename isIterator >
    void vector<Type, Allocator>::assign(InputIt first, InputIt last) {
        erase(begin(), end());
        difference_type count = std::distance(first, last);

        if (capacity() < count) {
            _m_allocate_and_copy((unsigned int) count);
        }

        for (auto it = begin(); first != last; ++it, ++first) {
            _m_allocator.construct(&*it, value_type(*first));
        }

        _m_last = _m_first + count;
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::push_back(Type&& value) {
        size_type new_size = size() + 1;
        if (new_size >= capacity()) _m_allocate_and_copy(new_size);
        std::swap(*(_m_last++), value);
    }

    template<typename Type, typename Allocator>
    template<class... Args>
    void vector<Type, Allocator>::emplace_back(Args&& ... args) {
        emplace(end(), std::forward<Args>(args)...);
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::pop_back() {
        std::allocator_traits<Allocator>::destroy(_m_allocator, _m_last);
        --_m_last;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::insert(const_iterator pos, const Type& value) {
        size_type new_size = size() + 1;
        size_type index = pos - begin();
        if (new_size > capacity()) _m_allocate_and_copy(new_size);
        pos = begin() + index;
        std::copy_backward(pos, end(), pos + size() - index + 1);
        *pos = value;
        ++_m_last;
        return pos;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::insert(const_iterator pos, Type&& value) {
        size_type index = pos - begin();
        size_type new_size = size() + 1;
        if (new_size > capacity()) _m_allocate_and_copy(new_size);
        auto new_iter = begin() + index;
        std::copy_backward(new_iter, end(), end() + 1);
        *new_iter = value;
        ++(_m_last);
        return new_iter;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::insert(iterator it, size_type n, const Type& value) {
        size_type new_size = size() + n;
        size_type index = it - begin();
        if (new_size > capacity()) _m_allocate_and_copy(new_size);
        it = begin() + index;
        std::copy_backward(it, end(), it + n + size() - index);
        std::fill(it, it + n, value);
        _m_last = _m_first + new_size;
        return it;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::insert(const_iterator pos, std::initializer_list<Type> init) {
        return insert(pos, init.begin(), init.end());
    }

    template<typename T, typename Allocator>
    template<class... Args>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::emplace(const_iterator pos, Args&& ... args) {
        size_type index = pos - begin();
        size_type new_size = size() + 1;
        if (new_size > capacity()) _m_allocate_and_copy(new_size);
        auto new_iter = begin() + index;
        std::copy_backward(new_iter, end(), ++_m_last);
        _m_allocator.construct(&*new_iter, std::forward<Args>(args)...);
        return new_iter;
    }

    template<typename Type, typename Allocator>
    template<typename InputIt, typename isIterator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::insert(const_iterator from, InputIt first, InputIt last) {
        difference_type distance = std::distance(first, last);
        size_type new_size = size() + distance;
        size_type index = from - begin();
        if (new_size > capacity()) _m_allocate_and_copy(new_size);
        auto iter = begin() + index;
        std::copy_backward(iter, end(), end() + distance);
        std::copy(first, last, iter);
        _m_last = _m_first + new_size;
        return iter;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::erase(iterator pos) {
        std::allocator_traits<Allocator>::destroy(_m_allocator, &*pos);
        std::copy(pos + 1, end(), pos);
        --_m_last;
        return pos;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::iterator vector<Type, Allocator>::erase(iterator first, iterator last) {
        for (iterator it = first; it != last; ++it) std::allocator_traits<Allocator>::destroy(_m_allocator, &*it);
        if (end() > last + 1) std::copy(last + 1, end(), first + 1);
        _m_last -= std::distance(first, last);
        return first;
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::swap(vector& other) noexcept {
        std::swap(_m_first, other._m_first);
        std::swap(_m_last, other._m_last);
        std::swap(_m_end_of_capacity, other._m_end_of_capacity);
        std::swap(_m_allocator, other._m_allocator);
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::clear() noexcept {
        _m_allocator.deallocate(_m_first, capacity());
        _m_first = _m_last = _m_end_of_capacity = nullptr;
    }

    template<typename Type, typename Allocator>
    Allocator vector<Type, Allocator>::get_allocator() const{
        return _m_allocator;
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::resize(size_type count) {
        size_type current_size = size();
        if (count > capacity()) _m_allocate_and_copy(count);
        _m_last = _m_first + count;
        if (current_size < size()) _m_initialize(begin() + current_size, end());
        else _m_destroy(end(), begin() + current_size);
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::resize(size_type count, const Type& value) {
        size_type prev_size = size();
        resize(count);
        if (count <= prev_size)  return;
        for (size_type i = prev_size; i < count; ++i) _m_allocator.construct(_m_first + i, value);
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::reserve(size_type size) {
        if (size > capacity()) _m_allocate_and_copy(size);
    }

    template<typename Type, typename Allocator>
    void vector<Type, Allocator>::shrink_to_fit() {
        _m_allocate_and_copy(size());
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::size_type vector<Type, Allocator>::capacity() const noexcept {
        return _m_end_of_capacity - _m_first;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::size_type vector<Type, Allocator>::size() const noexcept {
        return _m_last - _m_first;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::size_type vector<Type, Allocator>::max_size() const noexcept {
        return (size_type)(-1) / sizeof(Type);
    }

    template<typename Type, typename Allocator>
    inline bool vector<Type, Allocator>::empty() const noexcept {
        return size() == 0;
    }

    template<typename Type, typename Allocator>
    inline Type& vector<Type, Allocator>::at(size_type pos) {
        if (pos >= size()) throw std::out_of_range("Out of range");
        return _m_first[pos];
    }

    template<typename Type, typename Allocator>
    inline const Type& vector<Type, Allocator>::at(size_type pos) const {
        if (pos >= size()) throw std::out_of_range("Out of range");
        return _m_first[pos];
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::reference vector<Type, Allocator>::front() {
        return *(begin());
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reference vector<Type, Allocator>::front() const{
        return *(begin());
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::reference vector<Type, Allocator>::back() {
        return *(end() - 1);
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reference vector<Type, Allocator>::back() const {
        return *(end() - 1);
    }

    template<typename Type, typename Allocator>
    Type* vector<Type, Allocator>::data() noexcept {
        return _m_first;
    }

    template<typename Type, typename Allocator>
    const Type* vector<Type, Allocator>::data() const noexcept {
        return _m_first;
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::const_reference vector<Type, Allocator>::operator[](size_type i) const {
        return _m_first[i];
    }

    template<typename Type, typename Allocator>
    typename vector<Type, Allocator>::reference vector<Type, Allocator>::operator[](size_type i){
        return _m_first[i];
    }

    template<class U, class UAllocator>
    bool operator==(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs)
    {
        if (lhs.size() != rhs.size()) {
            return false;
        }

        auto iterL = lhs.begin();
        auto iterR = rhs.begin();

        for (;iterL != lhs.end(); iterL++, iterR++) {
            if (*iterL != *iterR) {
                return false;
            }
        }

        return true;
    }

    template<class U, class UAllocator>
    bool operator<(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs)
    {
        auto size = std::min(lhs.size(), rhs.size());

        for (typename vector<U, UAllocator>::size_type i = 0; i < size; i++) {
            if (lhs[i] < rhs[i]) {
                return true;
            }
        }
        return lhs.size() < rhs.size();
    }

    template<class U, class UAllocator>
    bool operator!=(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs)
    {
        return !(lhs == rhs);
    }

    template<class U, class UAllocator>
    bool operator> (const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs)
    {
        return rhs < lhs;
    }

    template<class U, class UAllocator>
    bool operator>=(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs)
    {
        return rhs <= lhs;
        return rhs <= lhs;
    }

    template<class U, class UAllocator>
    bool operator<=(const vector<U, UAllocator>& lhs, const vector<U, UAllocator>& rhs)
    {
        auto size = std::min(lhs.size(), rhs.size());

        for (typename vector<U, UAllocator>::size_type i = 0; i < size; i++) {
            if (lhs[i] < rhs[i]) {
                return true;
            }
        }
        return lhs.size() == rhs.size();
    }

    template<class U, class UAllocator>
    bool operator==(const art::vector<U, UAllocator>& lhs, const std::vector<U, UAllocator>& rhs) {
        auto a = lhs.size();
        if (lhs.size() != rhs.size()) {
            return false;
        }
        auto a8 = lhs[0];
        auto a1 = lhs[1];
        auto a2= lhs[2];
        auto a3 = lhs[3];

        for (auto i = 0; i < lhs.size(); ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }

        return true;
    }
}