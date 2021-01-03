#include <iostream>
#include <vector>
#include <string>

#include <filesystem>
#include <fstream>

std::string yodafy(const std::vector<std::string>& string_vector) {

   std::string retval;

   if(string_vector.size() < 3) { // needs at least 3 words for yodafiable sentence (subject and predicate)
     std::cerr << "A sentence needs at least 3 words in it." << std::endl; // Tell user to make a better sentence
     exit(0);
   }

   for (int i = 2; i < string_vector.size(); i++) { // For loop through the every word after the first two
      retval += string_vector[i]; // Add these words to the result first (because that is how yoda speaks)
      retval += (i == string_vector.size() - 1 ? "" : " "); // We make sure that we don't put a space between the last word and the comma
   }

   retval += ","; // Add comma
   retval += " " + string_vector[0] + " " + string_vector[1]; // Add first two words

   return retval;

}

bool ends_with_period(const std::string& text) {
   return text.at(text.size() - 1) == '.';
}

int main(int argc, char** argv) {

   if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " [text with subject and predicate]" << std::endl;  
        exit(0);
   }

   int start = 1;
   int end;

   for (int i = start; i < argc; i++) {

      std::string patched_string = argv[i];
      if (i == argc - 1) {
          if(!ends_with_period(patched_string)) patched_string = patched_string + "."; // We add a period internally to the last word so that it doesn't break the following code.
      }

      if (ends_with_period(patched_string)) { // This section does a for loop of the text provided, and when it hits a period, it executes the yodafier

          end = i;

          std::vector<std::string> yodafied;

          for (int j = start; j <= end; j++) {
             std::string word = std::string(argv[j]);
             std::string result = (j == end && ends_with_period(word) ? std::string(word).substr(0, word.size() - 1) : word);
             yodafied.emplace_back(result);
          }

          std::cout << yodafy(yodafied) << std::endl;

          
          start = (end == argc - 1 ? end : end + 1); 
      }
   }

   return 0;
}

