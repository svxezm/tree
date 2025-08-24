#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::ostringstream iterate_entries(
  fs::path path,
  unsigned int &directories,
  unsigned int &files,
  std::string prefix
) {
  std::ostringstream tree;
  std::vector<fs::directory_entry> entries = {
    fs::directory_iterator(path), {}
  };

  for (int i = 0; i < entries.size(); i++) {
    fs::directory_entry entry = entries[i];
    bool is_last = (i == entries.size() - 1);
    std::ostringstream line;

    line << prefix
         << (is_last ? "└── " : "├── ")
         << entry.path().filename().string()
         << "\n";

    tree << line.str();

    if (entry.is_directory()) {
      directories++;
      tree << iterate_entries(
        entry.path(),
        directories,
        files,
        prefix + (is_last ? "    " : "│   ")
      ).str();
    } else {
      files++;
    }
  }

  return tree;
}

int main(int argc, char *argv[]) {
  fs::path entry_point = fs::path(".");
  unsigned int directories = 1;
  unsigned int files = 0;

  std::ostringstream tree = iterate_entries(entry_point, directories, files, "");
  std::ostringstream counts;

  counts << directories << " directories";

  if (files > 0) counts << ", " << files << " files";

  std::cout << "." << std::endl;
  std::cout << tree.str() << std::endl;
  std::cout << counts.str() << std::endl;

  return 0;
}
