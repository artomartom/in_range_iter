

#include <hello.hpp>

int s_main( )
{
  ::Log<Console>::Write("hello");
     
 
    return 0;
};

#if WIN32
int wWinMain(_In_ HINSTANCE hinst, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int){ return ::Exception::Invoke(s_main, hinst); };
#endif

int main() { return ::Exception::Invoke(s_main ); };

