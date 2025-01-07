
#pragma once

#include <vector>

namespace mr { namespace middle {
    // Returns the Levenshtein distance between word1 and word2.
    static inline size_t
    levenshtein_dist_bounded(const std::string &word1, const std::string &word2, size_t k = 7) {
        size_t size1 = word1.size();
        size_t size2 = word2.size();

        // If the difference in lengths is greater than k, we can return early
        if (std::max(size1, size2) - std::min(size1, size2) > k) {
            return k + 1;
        }

        // If one of the words has zero length, the distance is equal to the size
        // of the other word (if within k)
        if (size1 == 0)
            return size2 <= k ? size2 : k + 1;
        if (size2 == 0)
            return size1 <= k ? size1 : k + 1;

        // Create a matrix with only the band we need
        // For each row i, we only need to compute columns from max(0, i-k) to
        // min(size2, i+k)
        std::vector<std::vector<size_t>> verif(size1 + 1, std::vector<size_t>(size2 + 1, k + 1));

        // Initialize first row and column within the band
        verif[0][0] = 0;
        for (size_t j = 1; j <= std::min(size2, k); j++) {
            verif[0][j] = j;
        }
        for (size_t i = 1; i <= std::min(size1, k); i++) {
            verif[i][0] = i;
        }

        // Fill the matrix while staying within the band
        for (size_t i = 1; i <= size1; i++) {
            // Calculate the range of j values within our band
            size_t start = (i > k) ? (i - k) : 1;
            size_t end = std::min(size2, i + k);

            // Skip if we're outside the band
            if (start > end) {
                return k + 1;
            }

            // Track the minimum value in this row
            size_t rowMin = k + 1;

            for (size_t j = start; j <= end; j++) {
                size_t cost = (word2[j - 1] == word1[i - 1]) ? 0 : 1;

                verif[i][j] = std::min(
                    {(i > 0 && j > 0) ? verif[i - 1][j - 1] + cost : k + 1,
                     (j > 0) ? verif[i][j - 1] + 1 : k + 1,
                     (i > 0) ? verif[i - 1][j] + 1 : k + 1}
                );

                rowMin = std::min(rowMin, verif[i][j]);
            }

            // If entire row is > k, we can terminate early
            if (rowMin > k) {
                return k + 1;
            }
        }

        // Return k+1 if the actual distance would be greater than k
        return std::min(verif[size1][size2], k + 1);
    }

    static inline std::optional<size_t>
    relative_similar(const std::string &word1, const std::string &word2) {
        size_t maxLength = std::max(word1.length(), word2.length());
        size_t distance = levenshtein_dist_bounded(word1, word2);

        return distance <= (maxLength * 0.3 + 1) ? std::make_optional(distance) : std::nullopt;
    }
}} // namespace mr::middle