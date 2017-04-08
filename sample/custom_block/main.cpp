#include <easy/profiler.h>

class Foo
{
    const ::profiler::BaseBlockDescriptor* m_desc;
    ::profiler::Block m_customBlock;
public:
    Foo():m_desc(::profiler::registerDescription(
                     ::profiler::extract_enable_flag(),
                     "main.cpp" ":" "6","custom_block","main.cpp", 6,
                                                     ::profiler::BLOCK_TYPE_EVENT,
                                                     ::profiler::extract_color(profiler::colors::Red))),
        m_customBlock(m_desc,"custom_block")
    {}

    void init()
    {
        m_customBlock.start();
        /* some another work*/
    }

    void work()
    {
        /* some profiling work */
        for(volatile int i =0; i < 10000000; i++){}
    }

    void check()
    {
        m_customBlock.finish();
        ::profiler::storeBlockDirectly(&m_customBlock);//store finished block
        /* some another work*/
    }
};


int main()
{

    EASY_PROFILER_ENABLE;
    Foo foo;

    for(int j = 0; j < 5; j++)
    {
        foo.init();
        foo.work();
        foo.check();
    }

    profiler::dumpBlocksToFile("test_custom.prof");
    return 0;
}
