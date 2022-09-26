//
// Created by yangy on 8/19/2021.
//

#ifndef CHOCOPY_COMPILER_CHOCOPY_OPTIMIZATION_HPP
#define CHOCOPY_COMPILER_CHOCOPY_OPTIMIZATION_HPP

#include "BasicBlock.hpp"
#include "IRBuilder.hpp"
#include "Module.hpp"
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using std::string;
/** https://stackoverflow.com/questions/5447675/how-to-convert-a-string-to-a-class-name */
template <class T, typename M_> void *constructor(M_ *module_) {
    return (void *)new T{module_};
}
template <typename M_> struct arg_to_pass {
    typedef void *(*constructor_t)(M_ *);
    typedef std::map<std::string, constructor_t> map_type;
    map_type m_classes;
    M_ *module;

    template <class T> void register_class(std::string const &n, M_ *&module_) {
        module = module_;
        m_classes.insert(std::make_pair(n, &constructor<T, M_>));
    }

    void *construct(std::string const &n) {
        auto i = m_classes.find(n);
        if (i == m_classes.end())
            return nullptr; // or throw or whatever you want
        return i->second(module);
    }
};


#endif // CHOCOPY_COMPILER_CHOCOPY_OPTIMIZATION_HPP
