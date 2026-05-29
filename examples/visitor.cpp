#include <map>
#include <Vessel.hpp>
#include <iostream>
#include <fstream>
#include <set>
#include "models.cpp"

struct GraphReactionVisitor : stochastic::VesselVisitor
{
    std::map<std::string, size_t> symbols;
    std::string modelName;
    std::vector<Species> species;
    std::vector<Reaction> reactions;

    GraphReactionVisitor() : symbols(), modelName{} {}

    void visit(const Reaction &r) override
    {
        reactions.push_back(r);
    }

    void visit(const Species &s) override
    {
        species.push_back(s);
    }

    void visit(const Vessel &v) override
    {
        modelName = v.getName();
    }

    void exportGraph()
    {
        auto sCount = 0;
        auto rCount = 0;
        std::ofstream file(std::string(modelName).append(".txt"));
        std::map<std::string, std::string> speciesNode{};

        file << "digraph {\n";
        for (auto s : species)
        {
            auto sNode = std::string("s").append(std::to_string(sCount++));
            speciesNode[s.label] = sNode;
            file << "\t"
                 << sNode << "[label=\""
                 << s.label << "\",shape=\"box\",style=\"filled\",fillcolor=\"cyan\"];\n";
        }
        for (auto r : reactions)
        {
            auto rNode = std::string("r").append(std::to_string(rCount++));
            file << "\t"
                 << rNode << "[label=\"" << r.rate << "\",shape=\"oval\",style=\"filled\",fillcolor=\"yellow\"];\n";

            std::set<std::string> inputs;
            std::set<std::string> product;
            for (auto i : r.inputs)
                inputs.insert(i);
            for (auto p : r.product)
                product.insert(p);
            for (auto i : inputs)
            {
                if (!product.contains(i))
                    file << "\t"
                         << speciesNode[i] << "->" << rNode << ";\n";
            }
            for (auto p : product)
            {
                if (!inputs.contains(p))
                    file << "\t"
                         << rNode << "->" << speciesNode[p] << ";\n";
            }
        }

        file << "}" << std::endl;
        reactions.clear();
        species.clear();
        modelName = {};
    }
};

int main()
{
    auto model_seihr = seihr(10000);
    auto model_circadian = circadian();

    GraphReactionVisitor v{};

    model_seihr.accept(v);
    v.exportGraph();
    model_circadian.accept(v);
    v.exportGraph();

    return 0;
}
