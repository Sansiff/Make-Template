namespace debugger {
#ifdef DEBUG
    template <typename T>
    void __print_var(string_view name, const T & x) { std::cerr << name << " = " << x; }
    void __print_var(string_view name, const string & x) { std::cerr << name << " = \"" << x << "\""; }
    void __print_var(string_view name, const char & x) { std::cerr << name << " = \'" << x << "\'"; }
    template <typename T>
    void __print_var(string_view name, const vector<T>& x) {
        std::cerr << name << " = ";
        bool is_first = true;
        for (auto & ele : x) std::cerr << (is_first ? (is_first = false, "[") : ", ") << ele;
        std::cerr << "]";
    }
    template <typename T>
    void __print_var(string_view name, const set<T>& x) {
        std::cerr << name << " = ";
        bool is_first = true;
        for (auto & ele : x) std::cerr << (is_first ? (is_first = false, "{") : ", ") << ele;
        std::cerr << "}";
    }
    template <typename K, typename V>
    void __print_var(string_view name, const map<K, V>& x) {
        std::cerr << name << " = ";
        bool is_first = true;
        for (auto & [k, v] : x) std::cerr << (is_first ? (is_first = false, "{") : ", ") << "(" << k << ": " << v << ")";
        std::cerr << "}";
    }
    template <typename T>
    void __log(string_view name, const T & x) {
        __print_var(name, x); std::cerr << '\n';
    }
    template <typename T, typename... Ts>
    void __log(string_view name, const T & x, const Ts&... others) {
        size_t pos = name.find(',');
        __print_var(name.substr(0, pos), x); std::cerr << ", ";
        __log(name.substr(pos + 1), others...);
    }
 
#define LOG(args...)\
    { std::cerr << "line " << __LINE__ << ": " << __func__ << "(): ";\
    __log(#args, ##args); }
#else
#define LOG(...) //log(a, b, c, ..., xxx);
#endif
}
using namespace debugger;