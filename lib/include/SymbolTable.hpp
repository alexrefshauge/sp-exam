#include <unordered_map>
#include <stdexcept>

namespace stochastic
{

    template <typename K>
    concept SymbolHashable = requires(K k) {
        { std::hash<K>{}(k) } -> std::convertible_to<std::size_t>;
    };

    template <SymbolHashable K, typename V>
    struct SymbolTable
    {
        std::unordered_map<K, V> symbol_map{};

        SymbolTable() : symbol_map() {}

        void store(K key, V value)
        {
            if (symbol_map.contains(key))
            {
                throw std::runtime_error("Key already in symbol table");
            }
            symbol_map.emplace(key, value);
        }

        V &lookup(K key)
        {
            return symbol_map.at(key);
        }

        unsigned long size() const
        {
            return symbol_map.size();
        }

        auto begin()
        {
            return symbol_map.begin();
        }

        auto end()
        {
            return symbol_map.end();
        }

        auto begin() const
        {
            return symbol_map.begin();
        }

        auto end() const
        {
            return symbol_map.end();
        }
    };

}
