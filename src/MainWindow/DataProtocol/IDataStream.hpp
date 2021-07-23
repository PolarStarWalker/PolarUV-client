#ifndef CLIENT_IDATASTREAM_HPP
#define CLIENT_IDATASTREAM_HPP

#include <memory>

class IDataStream{
public:
    struct Stream{
        size_t Size = 0;
        std::unique_ptr<void> Data = nullptr;
    };

    virtual DataStream

private:

};

#endif //CLIENT_IDATASTREAM_HPP
