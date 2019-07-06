
class UserException
{
    int found_in_line;
    std::string message, found_in_file;
public:
    UserException(std::string s, std::string ff, int fl):
        message(s), found_in_file(ff), found_in_line(fl) { ; }

    std::string what()  {
        return message+" File: "+found_in_file+" Line: "+std::to_string(found_in_line);
    }
};
