#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::ostringstream iterate_entries(
  fs::directory_iterator entries,
  unsigned int &directories,
  unsigned int &files,
  int indenting
) {
  std::ostringstream oss;

  for (const auto& entry : entries) {
    if (indenting == 1) {
      oss << "├── ";
    } else {
      oss << "|";
      for (int i = 1; i < indenting; i++) {
        oss << "    ";
      }
      oss << "└── ";
    }

    oss << entry.path().filename().string() << "\n";

    if (entry.is_directory()) {
      directories++;
      fs::directory_iterator dir_entries(
        entry.path().string(), fs::directory_options::none
      );

      oss << iterate_entries(
        dir_entries,
        directories,
        files,
        indenting + 1
      ).str();
    } else {
      files++;
    }
  }

  return oss;
}

int main(int argc, char *argv[]) {
  fs::directory_iterator entries(".", fs::directory_options::none);
  unsigned int directories = 1;
  unsigned int files = 0;

  std::ostringstream tree = iterate_entries(entries, directories, files, 1);
  std::ostringstream counts;

  counts << directories << " directories";

  if (files > 0) counts << ", " << files << " files";

  std::cout << "." << std::endl;
  std::cout << tree.str() << std::endl;
  std::cout << counts.str() << std::endl;

  return 0;
}
