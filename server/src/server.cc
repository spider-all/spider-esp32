#include <iostream>

#include <httplib.h>
#include <nlohmann/json.hpp>

bool end_with(std::string const &str, std::string const &suffix) {
  if (str.length() >= suffix.length()) {
    return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
  } else {
    return false;
  }
}

int main(int argc, char const *argv[]) {
  httplib::Server svr;

  httplib::MultipartFormDataItems items = {
      {"text1", "text default", "", ""},
      {"text2", "aωb", "", ""},
      {"file1", "h\ne\n\nl\nl\no\n", "hello.txt", "text/plain"},
      {"file2", "{\n  \"world\", true\n}\n", "world.json", "application/json"},
      {"file3", "", "", "application/octet-stream"},
  };

  svr.Post("/hi", [](const httplib::Request &req, httplib::Response &res) {
    std::cout << req.get_param_value("test") << std::endl;
    std::cout << req.body << std::endl;
    nlohmann::json content = nlohmann::json::parse(req.body);
    std::cout << content["test1"].get<std::string>() << "123" << std::endl;
    res.set_content("Hello World!", "text/plain");
  });

  svr.listen("0.0.0.0", 8080);
  return EXIT_SUCCESS;
}
