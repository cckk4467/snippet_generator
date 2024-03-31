// @title main.cpp
// @description: bib
// @prefix: main gg

#include <bits/stdc++.h>

#include "argh.h"
#include "excep.cpp"
#include "json.hpp"
using json = nlohmann::json;

using namespace std;
namespace fs = std::filesystem;
json quick_code;
json global_config = {
    {"root_path", "./"},
    {"target_extension", ".cpp"},
    {"output_file_name", "cpp.json"},
};

unordered_map<string, regex> rules;
template <typename... T>
constexpr void AddRule(T &&...arg) {
    ((rules[arg] = regex("[^\\n]*@" + arg + "[: ]*([^#]*)")), ...);
}
const auto commentary_regex = regex("//.*");
class File {
    json para;
    string path;
    vector<string> body;
    // string GetValueOf(string para) {}

   public:
    void ReadFile(string path) {
        ifstream in(path);

        auto match_rule = [&](const string &line) {
            smatch m;
            for (auto [key_word, rule] : rules) {
                if (auto res = regex_match(line, m, rule); res) {
                    if (para.contains(key_word))
                        throw duplicated_argument(path.c_str(),
                                                  key_word.c_str());

                    if (key_word == "prefix") {
                        stringstream ss(m[1].str());
                        string s;
                        while (ss >> s) {
                            para[key_word].push_back(move(s));
                        }
                    } else {
                        para[key_word] = m[1].str();
                    }
                    return 1;
                }
            }
            return 0;
        };

        auto match_commentary = [&](const string &line) {
            smatch m;
            return regex_search(line, m, commentary_regex);
        };

        auto check_para = [&]() {
            for (auto [key_word, rule] : rules) {
                if (!para.contains(key_word))
                    throw argument_miss(path.c_str(), key_word.c_str());
            }
        };

        string line;
        while (getline(in, line)) {
            if (!match_rule(line) && !match_commentary(line)) {
                body.push_back(line);
            }
        }
        check_para();
        in.close();
    }
    const string GetPara(const string &name) {
        string s;
        for (auto &c : para[name]) s += c;
        return move(s);
    }
    const json &AsJson() {
        para["body"] = json(body);
        return para;
    }
};
auto handle(const string &name) {
    File file;
    file.ReadFile(name);
    quick_code[file.GetPara("title")] = file.AsJson();
};

auto scan_files(const string &path) -> void {
    for (auto &entry : fs::directory_iterator(path)) {
        if (entry.is_directory())
            scan_files(entry.path().string());
        else if (auto file = entry.path();
                 file.has_extension() &&
                 file.extension().string() ==
                     string(global_config["target_extension"])) {
            handle(entry.path().string());
        }
        // cout << entry.path().string() << endl;
        // cout << entry.path().extension().string() << endl;
    }
    return;
};

auto output_file = []() {
    ofstream out(global_config["output_file_name"]);
    out << quick_code.dump(4);
    out.close();
};
int main(int, char *argv[]) {
    AddRule<string>("title"s, "description"s, "prefix"s);
    argh::parser parser(argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

    cout << "Config >>>>>>>>>>>>>>>>" << endl;
    for (auto &[config, val] : global_config.items()) {
        if (parser(config)) val = parser(config).str();
        cout << config << " = " << val << endl;
    }
    cout << "<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    scan_files(global_config["root_path"]);
    output_file();
    return 0;
}