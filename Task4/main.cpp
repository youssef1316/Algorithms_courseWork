#include <iostream>

using namespace std;

bool checkAnagram (string s1, string s2) {
   if (s1.size() != s2.size()) return false;
   int check[127] = {0};
   for (int i = 0; i < s1.size() ; i ++) {
      check[s1[i]] ++;
   }
   for (int i = 0; i < s2.size(); i++) {
      check[s2[i]] --;
   }
   for (int i = 0; i < 127; i++) {
      if (check[i] != 0) return false;
   }
   return true;
}
int main() {
   string s1, s2;
   cout << "Enter the strings: \n";
   cin >> s1 >> s2;

   cout << (checkAnagram(s1, s2) ? "Anagram\n" : "Not anagram\n");
}