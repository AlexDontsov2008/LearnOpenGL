#ifndef _UNCOPYABLE_HPP_
#define _UNCOPYABLE_HPP_


class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}
    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

#endif // _UNCOPYABLE_HPP_
