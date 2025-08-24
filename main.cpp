#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

void iterate_entries(
  fs::path path,
  unsigned int &directories,
  unsigned int &files,
  std::string prefix
) {
  std::vector<fs::directory_entry> entries = {
    fs::directory_iterator(path), {}
  };

  for (int i = 0; i < entries.size(); i++) {
    fs::directory_entry entry = entries[i];
    bool is_last = (i == entries.size() - 1);

    std::cout
         << prefix
         << (is_last ? "└── " : "├── ")
         << entry.path().filename().string()
         << "\n";

    if (entry.is_directory()) {
      directories++;
      iterate_entries(
        entry.path(),
        directories,
        files,
        prefix + (is_last ? "    " : "│   ")
      );
    } else {
      files++;
    }
  }
}

int main(int argc, char *argv[]) {
  fs::path entry_point = fs::path(".");
  unsigned int directories = 1;
  unsigned int files = 0;

  std::cout << ".\n";
  iterate_entries(entry_point, directories, files, "");

  std::cout
       << "\n"
       << directories
       << " directories";
  if (files > 0) std::cout << ", " << files << " files";
  std::cout << "\n";

  return 0;
}
