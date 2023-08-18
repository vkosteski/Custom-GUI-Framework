#pragma once
#include <cstdio>
#include <array>
#include <cstddef>

template<std::size_t N>
constexpr auto DecodeBase85(const std::array<char, N>& input) noexcept {
    constexpr std::size_t OUTPUT_SIZE = (N - 1) * 4 / 5;
    std::array<char, OUTPUT_SIZE> out{};

    constexpr auto decode85Byte = [](char c) constexpr -> unsigned int {
        return c >= '\\' ? c - 36 : c - 35;
        };

    for (std::size_t i = 0, j = 0; i + 4 < N; i += 5, j += 4) {
        unsigned int tmp = decode85Byte(input[i]) +
            85 * (decode85Byte(input[i + 1]) +
                85 * (decode85Byte(input[i + 2]) +
                    85 * (decode85Byte(input[i + 3]) +
                        85 * decode85Byte(input[i + 4]))));

        out[j] = static_cast<char>((tmp >> 0) & 0xFF);
        out[j + 1] = static_cast<char>((tmp >> 8) & 0xFF);
        out[j + 2] = static_cast<char>((tmp >> 16) & 0xFF);
        out[j + 3] = static_cast<char>((tmp >> 24) & 0xFF);
    }

    return out;
}

// ✅ Define the encoded data as a `std::array<char, N>`, NOT a raw string
constexpr std::array<char, 400> encodedData = {
    "%/P:vP>$(#>T$<8?####Q$###%/P:v%####?####$&###J$###h####&####$####t#########.$###%####$####:$########tn=j=$8HlEQ2TuY3l:$#%),##$#########0g'WC"
    "`-.:CVjSuY&5>##%),##$#########C,.33UnSc;'AViF6JrEH<Sk:0+bVe=K&&PDlf1eGdfX1F$*fUCs'el1K>,C5AH3I3b48(#$QUV$)%XHVd;#K7#####X/'.7`7r'7$QUV$*%XHV"
    "..."
};

// ✅ Pass `encodedData` to `DecodeBase85
//inline constexpr auto blur_x = DecodeBase85(encodedData);
