#include <string>
#include <thread>

void open_document(std::string const& filename);
bool done_editing();
std::string get_filename_from_user();
void edit_document(std::string const& filename);
enum type { open_new_document };
struct user_command{ type type; };
user_command get_usr_input();
void process_user_input(user_command);


void exit_document(std::string const& filename)
{
  open_document(filename);
  while(!done_editing())
  {
    user_command cmd = get_usr_input();
    if(cmd.type == open_new_document)
    {
      std::string const new_name = get_filename_from_user();
      std::thread t(edit_document, new_name);   // 
      t.detach();
    }
    else
    {
      process_user_input(cmd);
    }
  }
}