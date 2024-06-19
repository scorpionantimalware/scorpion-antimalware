/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scananalyzer.cpp
 * 
 * Copyright (c) 2024-present Scorpion Anti-malware (see AUTHORS.md).
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include "scananalyzer.hpp"

void ScanAnalyzer::add_malware_pathl(const std::string& pathl) {
    std::lock_guard<std::mutex> lock(ScanAnalyzer::malware_pathls_mtx);
    ScanAnalyzer::malware_pathls.push_back(pathl);
}

void ScanAnalyzer::add_benign_pathl(const std::string& pathl) {
    std::lock_guard<std::mutex> lock(ScanAnalyzer::benign_pathls_mtx);
    ScanAnalyzer::benign_pathls.push_back(pathl);
}

size_t ScanAnalyzer::get_malware_count() {
    std::lock_guard<std::mutex> lock(ScanAnalyzer::malware_pathls_mtx);
    return ScanAnalyzer::malware_pathls.size();
}

size_t ScanAnalyzer::get_benign_count() {
    std::lock_guard<std::mutex> lock(ScanAnalyzer::benign_pathls_mtx);
    return ScanAnalyzer::benign_pathls.size();
}
