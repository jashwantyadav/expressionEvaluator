#ifndef Token_Header
#define Token_Header 1

class Token{
    public:
    virtual ~Token() = default;
    virtual bool isOperator() = 0;
};

#endif
