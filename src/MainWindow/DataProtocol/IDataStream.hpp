#ifndef CLIENT_IDATASTREAM_HPP
#define CLIENT_IDATASTREAM_HPP

#include <memory>

class IDataStream{
protected:
    struct Stream{
        int Size = 0;
        std::shared_ptr<void> Data;
    };


public:

    [[nodiscard]] virtual Stream GetStream() const = 0;
    virtual std::ostream& Print(IDataStream::Stream&) const = 0;
    virtual ~IDataStream()  = default;

private:

};

#endif