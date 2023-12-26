#include "Glfw.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        cerr << "Error : argument\n";
        return 1;
    }

    try
    {
        string map_file(av[1]);
        // read_file(map_file);

        Glfw glfw;        
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}