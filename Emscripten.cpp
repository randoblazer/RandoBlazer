#include "Randomizer.h"

#include <emscripten/bind.h>
#include <string>

namespace RandoblazerExport {
    int CheckFile(const std::string& in_file) { return Randomizer::CheckFile(in_file); }
    std::string Randomize(const std::string& in_file, const std::string& out_file, unsigned int seed, const std::string& options_string) {
        std::string seedName;
        bool result = Randomizer::Randomize(in_file, out_file,
                          seed, Randomizer::Options(options_string), &seedName);

        return result ? seedName : "";
    }
}

EMSCRIPTEN_BINDINGS(randoblazer) {
    emscripten::function("CheckFile", &RandoblazerExport::CheckFile);
    emscripten::function("Randomize", &RandoblazerExport::Randomize);
}
