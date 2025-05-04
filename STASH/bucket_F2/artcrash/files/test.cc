#include <iostream> 
#include <string>
#include <glibmm.h>

int main(int argc, char **argv)
{
        std::string c = "(0.00, 0.50) (1.00, 0.50)";

        // This segfaults::
        Glib::ustring s = Glib::ustring::compose("%1\n[%2]", c, (float)3.2);

        // This works.
        // Glib::ustring s = Glib::ustring(c);

        std::cout << "OK" << std::endl;;

        return 0;
}
