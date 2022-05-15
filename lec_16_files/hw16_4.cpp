#include <iostream>

class IndentStreamBuf : public std::streambuf
{
public:
    IndentStreamBuf(std::streambuf& buf): dest_buf_(buf)
    {
    }

    int_type overflow(int_type c) override
    {
        // indent at new line
        if (new_line_)
        {
            // fill indent level spaces
            for (int i = 0; i < indent_level_; ++i)
            {
                dest_buf_.sputc(' ');
            }
            new_line_ = false;
        }

        // then write this char
        auto ret = dest_buf_.sputc(c);

        // if this char indicate end of line, flag a new line
        if (c == '\n')
        {
            new_line_ = true;
        }

        return ret;
    }

    void indent()
    {
        indent_level_ += 4;
    }

    void unindent()
    {
        indent_level_ = (indent_level_-4) < 0 ? 0:indent_level_-4;
    }

private:
    std::streambuf& dest_buf_;
    uint32_t indent_level_{0};
    bool new_line_{true}; // start as a new line
};

class IndentStream : public std::ostream
{
public:
    IndentStream(std::ostream& os) : my_buf_(*os.rdbuf()), std::ostream(&my_buf_)
    {
    }

    friend std::ostream& indent(std::ostream&);
    friend std::ostream& unindent(std::ostream&);
private:
    IndentStreamBuf my_buf_;
};

std::ostream& indent(std::ostream& stream)
{
    auto& s = static_cast<IndentStream&>(stream);
    s.my_buf_.indent();
    return stream;
}

std::ostream& unindent(std::ostream& stream)
{
    auto& s = static_cast<IndentStream&>(stream);
    s.my_buf_.unindent();
    return stream;
}
int main()
{

    IndentStream ins (std::cout);

    ins << "int" << std::endl;
    ins << "fib(int n) {" << indent << std::endl;
    ins << "if (n==0) return 0;" << std::endl;
    ins << "if (n==1) return 1;" << std::endl;
    ins << "return fib(n-2) + fib(n-1);" << unindent << std::endl;
    ins << "}" << std::endl;

    return 0;
}
