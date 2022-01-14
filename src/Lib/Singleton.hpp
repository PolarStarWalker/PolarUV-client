#ifndef CLIENT_SINGLETON_HPP
#define CLIENT_SINGLETON_HPP

template<class Type>
concept Singletonable = requires(Type type){
    type();
};

template<class Type>
class Singleton {
public:

    Singleton(Singleton&&) = delete;
    Singleton(const Singleton&) = delete;

    static Type &GetInstance() {
        static Singleton instance;
        return *(instance._instance);
    }

private:
    Singleton() { _instance = new Type; };
    ~Singleton() { delete _instance; }

    Type *_instance = nullptr;
};


#endif