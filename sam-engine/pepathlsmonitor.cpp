/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pepathlsmonitor.cpp
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

#include "pepathlsmonitor.hpp"

PEPathlsMonitor::PEPathlsMonitor() : done(false) {}

void PEPathlsMonitor::add_pe_pathl(const std::string& pathl) {
    std::unique_lock<std::mutex> lock(PEPathlsMonitor::mtx); // Ensure Mutual Exclusion
    PEPathlsMonitor::pathls.push(pathl);
    PEPathlsMonitor::cv.notify_one();
}

bool PEPathlsMonitor::get_pe_pathl(std::string& pathl_buffer) {
    std::unique_lock<std::mutex> lock(PEPathlsMonitor::mtx); // Ensure Mutual Exclusion

    bool status {false};

    while (PEPathlsMonitor::pathls.empty() && !PEPathlsMonitor::done) {
        PEPathlsMonitor::cv.wait(lock);
    }

    if (PEPathlsMonitor::pathls.empty()) {
        return status;
    }

    pathl_buffer = PEPathlsMonitor::pathls.front();
    PEPathlsMonitor::pathls.pop();

    status = true;

    return status;
}

void PEPathlsMonitor::set_done() {
    std::unique_lock<std::mutex> lock(PEPathlsMonitor::mtx); // Ensure Mutual Exclusion
    PEPathlsMonitor::done = true;
    PEPathlsMonitor::cv.notify_all();
}
