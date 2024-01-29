#include <iostream>
#include <string.h>
#include <list>
#include <curl/curl.h>

// read file from stdin line by line
using namespace std;

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp) {
  cerr << "size =  " << size << " nmemb = " << nmemb << endl;
  ((string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

int main() {
  string str;
  string url = "http://127.0.0.1:7777/";
  string responce_buffer;
  CURL* curl = curl_easy_init();
  struct curl_slist * curl_list;
  list<string> lst;

  while (cin.good() and not cin.eof()) {
    getline(cin, str);
    if (str.empty()) {
      break;
    }
    lst.emplace_back(str);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "MEW");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce_buffer);
  curl_list = curl_slist_append(NULL, "X-Cat-Variable: Window");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_list);

  if (curl_easy_perform(curl) != CURLE_OK) {
    cerr << "Invalid result code" << endl;
    return 1;
  }
  curl_slist_free_all(curl_list);
  curl_easy_cleanup(curl);
  // for (auto iterator = lst.begin(); iterator != lst.end(); iterator++) {

  // }

  if (responce_buffer.empty())
    return 1;

  cout << "Responce= " << responce_buffer << endl;

  return 0;
}