#ifndef CLIENT_IDATASTREAM_HPP
#define CLIENT_IDATASTREAM_HPP

#include <memory>

class IDataStream{
    struct Stream{
        size_t Size = 0;
        std::unique_ptr<void> Data = nullptr;
    };

public:


    virtual void DataStream() = 0;

private:

};

#endif